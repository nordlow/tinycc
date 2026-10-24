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

When evaluating performance or hot spots in the compiler, build `tcc` using Clang with maximum preferred optimizations and Profile-Guided Optimization (PGO):

1. **Instrumented Build:**
   ```bash
   make clean && CC=clang CFLAGS="-O3 -march=native -fprofile-generate" LDFLAGS="-fprofile-generate" ./configure && make -j$(nproc) -B && make -j$(nproc) test
   ```
2. **Profile Merging:**
   ```bash
   llvm-profdata merge -output=tcc.profdata $(find . -name "*.profraw")
   ```
3. **PGO-Optimized Build:**
   ```bash
   make clean && CC=clang CFLAGS="-O3 -march=native -fprofile-use=$(pwd)/tcc.profdata" LDFLAGS="-fprofile-use=$(pwd)/tcc.profdata" ./configure && make -j$(nproc) -B && make -j$(nproc) test
   ```

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

3. **Validation Loop:**
   - Run `make -j$(nproc) && make -j$(nproc) test` after every change.
   - Run `./configure && make -j$(nproc) -B && make -j$(nproc) test` before final commit.


This document was written by Claude at
https://claude.ai/chat/c8505b13-607c-4cb7-b180-5e3c7e8dda0f.
