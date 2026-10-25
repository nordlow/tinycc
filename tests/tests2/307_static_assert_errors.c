#if defined test_d_static_assert_msg
 static assert(0, "custom d static assert message");

#elif defined test_d_static_assert_nomsg
 static assert(0);

#elif defined test_d_static_assert_struct_msg
 struct s1 { static assert(0, "struct d static assert msg"); };

#elif defined test_d_static_assert_struct_nomsg
 struct s2 { static assert(0); };
#endif
