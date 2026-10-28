# Thread-local storage (TLS) for compiler globals

Make all compiler state globals (such as `func_safety`, `func_vt`, `funcname`, `ind`, `loc`, etc.) reside in thread-local storage (TLS) to lay the groundwork for multi-threaded compilation.
