# Agent Instructions

Use parallel builds (`-jN`) for all `make` invocations. `N` is the number of
CPU cores (e.g. `-j8`, or `-j$(nproc)`).

## Verification (required)

Whenever you modify files in this repository, you MUST verify that no
regressions are introduced. Choose the command by what you changed:

- **Changes to the compiler or its sources** (anything that affects the built
  `tcc` binary or runtime libraries): run

      make -jN && make -jN test

  Running `make -jN test` alone is NOT sufficient, since it can test a
  stale binary.

- **Changes only under `tests/`**: `make -jN test` is sufficient.

Run the applicable command after every change while iterating. Incremental
builds are fast, so don't batch up edits before verifying.

## Final check (before declaring a task done)

Before considering a task complete, do a clean reconfigure and full rebuild
to rule out stale build artifacts and configure-time issues:

    ./configure && make -j8 -B && make -j8 test

This takes only about 3 seconds (`./configure` ~41 ms, full rebuild ~1.5 s),
so always run it as the last step for any task that changed non-test code,
and whenever incremental results look suspicious.

## Rules

- Do not skip verification, and do not report success if any step fails.
- Chain steps with `&&` so tests never run against a failed build.
