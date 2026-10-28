# Task: ARM QEMU Unittest Bootstrap

## Goal Enable cross-compilation and execution of `tcc` unit tests
targeting ARM architecture via QEMU user-mode emulation
(`qemu-arm-static`) on Arch Linux.

## Feasibility
Yes, this is fully possible on Arch Linux:
1. **Packages**: `qemu-user-static` and `qemu-user-static-binfmt`
   provide transparent execution of ARM binaries on x86_64 host.
2. **Cross-compilation**: `tcc` natively supports cross-compilation
   (`./tcc -target arm ...` or building with ARM targets enabled).
3. **Execution**: Binfmt registration allows running ARM executables
   transparently (`./test_arm` invokes qemu-arm-static automatically).

## Steps
1. Install dependencies: `sudo pacman -S qemu-user-static
   qemu-user-static-binfmt`
2. Verify cross-compilation target in `tcc`.
3. Add a test runner target for ARM tests in `tests/tests2/`.
