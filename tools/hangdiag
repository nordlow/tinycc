#!/usr/bin/env python3
"""Run a command with a time limit; if it is still alive, dump diagnostics.

usage: tools/hangdiag.py [-o DIR] [--strace-secs N] SECONDS command...

Exit status: 124 if the command hung (and was killed), otherwise the
command's own exit status (128+N if it died from signal N).

Diagnostics go to DIR (default: hangdiag.<pid>/):
  out.log        combined stdout/stderr of the command
  ps.txt         process forest of the command's session
  procs.txt      per process: state, CPU%, wchan, syscall, fds, gdb backtrace
  strace.txt     one strace -f of every live process in the session
  summary.txt    one-line classification per process (also printed to stderr)
"""
import argparse
import os
import shutil
import signal
import subprocess
import sys
import time
from pathlib import Path

CLK_TCK = os.sysconf("SC_CLK_TCK")


def read(path, default=""):
    try:
        return Path(path).read_text(errors="replace").strip()
    except OSError:
        return default


def parse_stat(pid):
    """Return dict with state/ppid/pgrp/sid/ticks/comm, or None if gone."""
    data = read(f"/proc/{pid}/stat")
    if not data:
        return None
    try:
        comm = data[data.index("(") + 1:data.rindex(")")]
        rest = data[data.rindex(")") + 2:].split()
        return {
            "state": rest[0],
            "ppid": int(rest[1]),
            "pgrp": int(rest[2]),
            "sid": int(rest[3]),
            "ticks": int(rest[11]) + int(rest[12]),  # utime + stime
            "comm": comm,
        }
    except (ValueError, IndexError):
        return None


def session_pids(sid):
    """All pids whose session id is `sid` (the command ran under setsid)."""
    pids = []
    for entry in os.listdir("/proc"):
        if entry.isdigit():
            st = parse_stat(int(entry))
            if st and st["sid"] == sid:
                pids.append(int(entry))
    return sorted(pids)


def cmdline(pid):
    return read(f"/proc/{pid}/cmdline").replace("\0", " ").strip() or f"[{pid}]"


def list_fds(pid):
    out = []
    try:
        for fd in sorted(os.listdir(f"/proc/{pid}/fd"), key=int):
            try:
                out.append(f"  {fd} -> {os.readlink(f'/proc/{pid}/fd/{fd}')}")
            except OSError:
                pass
    except OSError as e:
        out.append(f"  (cannot list fds: {e})")
    return out


def cpu_percent(pids, interval=1.0):
    """CPU% of each pid over `interval` seconds."""
    before = {p: (parse_stat(p) or {}).get("ticks") for p in pids}
    t0 = time.monotonic()
    time.sleep(interval)
    dt = time.monotonic() - t0
    res = {}
    for p in pids:
        st = parse_stat(p)
        if st and before.get(p) is not None:
            res[p] = (st["ticks"] - before[p]) / CLK_TCK / dt * 100
    return res


def classify(state, cpu, wchan, syscall):
    if state == "Z":
        return "zombie (parent never wait()ed)"
    if state == "T":
        return "stopped by a signal (job control / SIGTTIN tty read?)"
    if state == "D":
        return "uninterruptible kernel/filesystem wait, not a program loop"
    if state == "R" or cpu > 50:
        return "BUSY LOOP in user space -> use gdb / perf (gdb bt below)"
    w = wchan.lower()
    if "pipe" in w:
        return "blocked on a pipe: check fds, who holds the other end? (jobserver?)"
    if "futex" in w:
        return "blocked on a futex: lock/thread deadlock -> thread apply all bt"
    if "do_wait" in w or "wait4" in w or "waitid" in w:
        return "waiting for a child: follow the child process"
    if "tty" in w or "n_tty" in w:
        return "waiting for terminal input"
    if syscall.startswith("0 "):  # read on x86-64
        fd = syscall.split()[1]
        return f"in read(fd={fd}): waiting for input (fd 0 = stdin)"
    if "poll" in w or "select" in w or "sleep" in w:
        return "polling/sleeping (timeout loop?)"
    return "sleeping, see wchan/syscall/strace"


def run_capture(argv, timeout):
    try:
        r = subprocess.run(argv, stdin=subprocess.DEVNULL, capture_output=True,
                           text=True, errors="replace", timeout=timeout)
        return r.stdout + r.stderr
    except subprocess.TimeoutExpired as e:
        partial = e.stdout.decode(errors="replace") if isinstance(e.stdout, bytes) else (e.stdout or "")
        return partial + "\n(timed out)\n"
    except OSError as e:
        return f"(failed to run {argv[0]}: {e})\n"


def run_strace(pids, outfile, seconds):
    if not shutil.which("strace"):
        outfile.write_text("strace not installed\n")
        return
    argv = ["strace", "-f", "-tt", "-s", "120", "-o", str(outfile)]
    for p in pids:
        argv += ["-p", str(p)]
    try:
        proc = subprocess.Popen(argv, stdin=subprocess.DEVNULL,
                                stdout=subprocess.DEVNULL, stderr=subprocess.PIPE)
    except OSError as e:
        outfile.write_text(f"strace failed: {e}\n")
        return
    time.sleep(seconds)
    proc.send_signal(signal.SIGINT)  # strace detaches cleanly on SIGINT
    try:
        _, err = proc.communicate(timeout=5)
    except subprocess.TimeoutExpired:
        proc.kill()
        _, err = proc.communicate()
    if proc.returncode not in (0, None, -signal.SIGINT, 130) and err:
        with outfile.open("a") as f:
            f.write("\n# strace stderr:\n" + err.decode(errors="replace"))


def diagnose(root, outdir, strace_secs):
    pids = session_pids(root)
    if not pids:
        return
    cpu = cpu_percent(pids)
    pids = [p for p in pids if parse_stat(p)]

    ps = run_capture(["ps", "-eo", "pid,ppid,pgid,stat,pcpu,etime,wchan:24,args",
                      "--forest"], 10)
    keep = [ln for i, ln in enumerate(ps.splitlines())
            if i == 0 or (ln.split() and ln.split()[0].isdigit()
                          and int(ln.split()[0]) in pids)]
    (outdir / "ps.txt").write_text("\n".join(keep) + "\n")

    run_strace(pids, outdir / "strace.txt", strace_secs)

    have_gdb = shutil.which("gdb") is not None
    summary, report = [], []
    for p in pids:
        st = parse_stat(p) or {"state": "?", "comm": "?"}
        wchan = read(f"/proc/{p}/wchan")
        syscall = read(f"/proc/{p}/syscall")
        c = cpu.get(p, 0.0)
        verdict = classify(st["state"], c, wchan, syscall)
        summary.append(f"pid {p:<7} {st['state']} {c:5.1f}%cpu  "
                       f"{st['comm']:<12} {verdict}")

        report += [f"== pid {p}: {cmdline(p)}",
                   f"state:   {st['state']}  cpu: {c:.1f}%",
                   f"wchan:   {wchan}",
                   f"syscall: {syscall}",
                   "fds:"] + list_fds(p)
        if have_gdb:
            bt = run_capture(["gdb", "-p", str(p), "-batch",
                              "-ex", "thread apply all bt"], 20)
            report.append("backtrace:")
            report += [ln for ln in bt.splitlines()
                       if ln.startswith(("#", "Thread", "(timed", "ptrace"))
                       or "Operation not permitted" in ln]
        else:
            report.append("backtrace: gdb not installed")
        report.append("")

    (outdir / "procs.txt").write_text("\n".join(report) + "\n")
    (outdir / "summary.txt").write_text("\n".join(summary) + "\n")
    print("\n".join(summary), file=sys.stderr)


def kill_session(root):
    for sig in (signal.SIGTERM, signal.SIGKILL):
        try:
            os.killpg(root, sig)
        except ProcessLookupError:
            return
        time.sleep(2 if sig == signal.SIGTERM else 0)


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("-o", "--outdir", help="diagnostics directory")
    ap.add_argument("--strace-secs", type=float, default=3.0,
                    help="how long to strace the hung processes (default 3)")
    ap.add_argument("seconds", type=float, help="time limit")
    ap.add_argument("command", nargs=argparse.REMAINDER)
    args = ap.parse_args()
    cmd = args.command[1:] if args.command[:1] == ["--"] else args.command
    if not cmd:
        ap.error("missing command")

    outdir = Path(args.outdir or f"hangdiag.{os.getpid()}")
    outdir.mkdir(parents=True, exist_ok=True)

    with (outdir / "out.log").open("wb") as log:
        # start_new_session == setsid(): the whole process tree shares one
        # session id, so we can find every descendant and kill them together.
        proc = subprocess.Popen(cmd, stdin=subprocess.DEVNULL, stdout=log,
                                stderr=subprocess.STDOUT, start_new_session=True)
        try:
            rc = proc.wait(timeout=args.seconds)
        except subprocess.TimeoutExpired:
            print(f"HANG after {args.seconds:g}s; diagnostics in {outdir}/",
                  file=sys.stderr)
            try:
                diagnose(proc.pid, outdir, args.strace_secs)
            finally:
                kill_session(proc.pid)
                proc.wait()
            return 124
    return 128 - rc if rc < 0 else rc


if __name__ == "__main__":
    sys.exit(main())
