# Memory allocation opt-out attributes

Introduce fine-grained attributes to opt out of specific categories of memory allocation in functions or scopes:

- **Stack memory opt-out**: Forbid stack allocation (e.g., variable-length arrays, `alloca`, large automatic arrays/locals) to ensure predictable stack usage in embedded or recursion-heavy systems.
- **Scoped/bounded heap memory opt-out**: Forbid heap allocations with scoped or bounded lifetimes (e.g., explicit region-based or arena allocations).
- **Garbage-collected memory opt-out (`@nogc`)**: Forbid heap allocations involving automatic garbage collection (GC) with unbounded or non-deterministic reclamation lifetimes (similar to D's `@nogc`).

## Rationale
Enable strict memory usage guarantees for real-time systems, embedded targets, and high-performance determinism-critical codebases.
