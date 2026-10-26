#if defined test_block_scope
void f(void) { unittest { } }

#elif defined test_missing_block
unittest;
#endif
