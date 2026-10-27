#if defined test_missing_paren
version VersionId
#elif defined test_bad_condition
version(1 + 2) int x;
#elif defined test_bad_version_spec
version = ;
#elif defined test_bad_debug_spec
debug = ;
#elif defined test_colon
version(Foo) :
int x;
#elif defined test_debug_colon
debug : int x;
#elif defined test_bad_condition_tail
version(Foo extra) int x;
#elif defined test_bad_debug_condition
debug(1 + 2) int x;
#elif defined test_bad_version_spec_paren
version = (Foo);
#elif defined test_eof_block
version(Foo) {
#elif defined test_eof_else_block
version(Nope) int x; else {
#elif defined test_eof_condition
version(Foo
#endif
