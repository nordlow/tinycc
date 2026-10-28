# Syntax for D-Like Function Attributes

Add syntax support for D-style `@pure` function attribute.

Introduce parsing support for D-like builtin attributes, starting with
`@pure` on function declarations and definitions:

    int f(int x) @pure { return x; }
    int g(int x) @pure;
