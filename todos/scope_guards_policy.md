# Recommendation for scope(success) and scope(failure) Without Error Handling

- **Chosen Policy**: Option 3 (**Error with a clear diagnostic**).
- **Rationale**:
  - **Option 1 (Do nothing)**: Unacceptable due to silent failures and
    resource leaks (code inside the guard would never execute).
  - **Option 2 (Mimic `scope(exit)`)**: Unsafe because it executes
    failure cleanup on success (or vice versa), violating correctness.
  - **Option 3 (Compile-time error)**: Emitting a clear compile-time
    error (`error: scope(success) / scope(failure) requires error
    status tracking`) guarantees safety and prevents incorrect code
    generation until return-value/error tracking is implemented.
