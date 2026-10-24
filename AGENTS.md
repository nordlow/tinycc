# Agent Instructions

Use parallel builds (`-jN`) for all `make` invocations. `N` is the
number of CPU cores (e.g. `-j8`, or `-j$(nproc)`).

## Verification (required)

Whenever you modify files in this repository, you MUST verify that no
regressions are introduced. Choose the command by what you changed:

- **Changes to the compiler or its sources** (anything that affects
  the built `tcc` binary or runtime libraries): run

      make -j$(nproc) && make -j$(nproc) test

  Running `make -j$(nproc) test` alone is NOT sufficient, since it can test a
  stale binary.

- **Changes only under `tests/`** (including `tests/tests2/`): `make
  -j$(nproc) test` is sufficient.

Run the applicable command after every change while
iterating. Incremental builds are fast, so don't batch up edits before
verifying.

## Adding tests

When adding a new test, prefer placing it under `tests/tests2/`
instead of directly under `tests/`. Follow the existing conventions
there: use the next free numeric prefix, name the source
`NN_descriptive_name.c`, and add a matching
`NN_descriptive_name.expect` file with the expected output.

Only add a test directly under `tests/` if it cannot be expressed in
the `tests/tests2/` framework.

## Final check (before declaring a task done)

Before considering a task complete, do a clean reconfigure and full
rebuild to rule out stale build artifacts and configure-time issues:

    ./configure && make -j$(nproc) -B && make -j$(nproc) test

This currently (on an AMD Ryzen AI 7 350 w/ Radeon 860M) takes only
about 3 seconds (`./configure` ~41 ms, full rebuild ~1.5 s), so always
run it as the last step for any task that changed non-test code, and
whenever incremental results look suspicious.

## Rules

- Do not skip verification, and do not report success if any step
  fails.
- Chain steps with `&&` so tests never run against a failed build.

## Profiling & PGO Optimization

When evaluating performance or hot spots in the compiler, build `tcc` using Clang or GCC with maximum preferred optimizations and Profile-Guided Optimization (PGO) via the automated Makefile target:

```bash
make pgo PGO_CC=clang
make pgo PGO_CC=gcc
```

*(Note: GNU Make assigns a default built-in value to `CC` (`cc`/`gcc`), so passing `PGO_CC=...` explicitly is required to override the compiler selection).*

This automatically handles instrumented building, training runs (defaulting to an optimal sweet spot of **25 iterations**), profile merging, and final PGO-optimized production build.

*Note (2026-10-24):* On AMD Ryzen AI 7 350, Linux x64, Clang PGO (`CC=clang make pgo`, ~5.13M lines/sec) outperforms GCC PGO (`CC=gcc make pgo`, ~4.62M lines/sec) by ~11% due to LLVM's aggressive profile-guided inlining and optimizer passes.



## Profiling Strategy (`perf` & Valgrind Cachegrind)

When analyzing and optimizing performance hot spots:

1. **Instruction-Level Tracing (Valgrind Cachegrind):**
   ```bash
   valgrind --tool=cachegrind ./tcc -B. -Iinclude -I. tcc.c -o /dev/null
   cg_annotate cachegrind.out.<pid>
   ```
   *Rule:* Measure instruction reference (`Ir`) counts before and after changes. Discard optimizations that increase total `I refs`.

2. **Hardware Performance Sampling (`perf`):**
   ```bash
   perf record -o perf.data -- ./tcc -B. -Iinclude -I. tcc.c -o /dev/null
   perf report -i perf.data --stdio -n --no-children
   ```

## Key Session Takeaways (2026-10-24)

- **Frontend SIMD Parsing:** Replacing byte-by-byte loops in `parse_pp_string` and `parse_line_comment` with glibc's SIMD-optimized `memchr` speeds up string and comment lexing.
- **PGO Sweet Spot:** **25 training iterations** provides the optimal balance between profile weight fidelity and build speed in `make pgo`.
- **Compiler Performance:** Clang PGO (`~5.43M lines/sec`) outperforms GCC PGO (`~4.86M lines/sec`) by ~11% due to LLVM's advanced profile-guided inlining passes.


This document was written by Claude at
https://claude.ai/chat/c8505b13-607c-4cb7-b180-5e3c7e8dda0f.
