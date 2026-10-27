#if defined test_scope_success
void test_success(void) {
    scope(success) {}
}
#elif defined test_scope_failure
void test_failure(void) {
    scope(failure) {}
}
#endif
