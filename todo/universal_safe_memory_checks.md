# Activate `@safe` memory checks across all language modes

Activate pointer arithmetic and indexing checks in `@safe` functions
across all language modes (not just `-lang=d`) only when `func_safety`
is not `FUNC_SAFETY_UNKNOWN`.

This will make memory checks be deactivated by default because
`func_safety` defaults to `FUNC_SAFETY_UNKNOWN`.
