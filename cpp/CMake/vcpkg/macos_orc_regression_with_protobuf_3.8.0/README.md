`orc` 1.5.5 builds failed with protobuf 3.8.0 on macOS: [#6739](https://github.com/microsoft/vcpkg/pull/6739)
>In file included from /Users/poorman/Desktop/vcpkg/buildtrees/orc/src/42606d7789-7b02d4b2ea/c++/src/wrap/orc-proto-wrapper.cc:44:
c++/src/orc_proto.pb.cc:965:145: error: possible misuse of comma operator here [-Werror,-Wcomma]
static bool dynamic_init_dummy_orc_5fproto_2eproto = (  ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptors(&descriptor_table_orc_5fproto_2eproto), true);
                                                                                                                                                ^
c++/src/orc_proto.pb.cc:965:57: note: cast expression to void to silence warning
static bool dynamic_init_dummy_orc_5fproto_2eproto = (  ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptors(&descriptor_table_orc_5fproto_2eproto), true);
                                                        ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                                                        static_cast<void>(                                                                      )
1 error generated.

It turns out that this failure is introduced by this commit: https://github.com/protocolbuffers/protobuf/tree/1467e08d7c26a7087e5e5b14a4ab2755926e7249

Before this commit, the generated code:
```cpp
// Force running AddDescriptors() at dynamic initialization time.
static bool dynamic_init_dummy_orc_5fproto_2eproto = (  ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptors(&descriptor_table_orc_5fproto_2eproto), true);
```

After:
```cpp
// Force running AddDescriptors() at dynamic initialization time.
static bool dynamic_init_dummy_orc_5fproto_2eproto = (  ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptors(&descriptor_table_orc_5fproto_2eproto), true);
```

https://stackoverflow.com/questions/689677/why-cast-unused-return-values-to-void

https://stackoverflow.com/questions/46895568/possible-misuse-of-comma-operator-here

https://github.com/Microsoft/clang/commit/ba3bb7db1d551babd413964db6b48de7d2ed523c

https://github.com/cocos2d/cocos2d-x/pull/18350

https://stackoverflow.com/questions/15708411/how-to-deal-with-global-constructor-warning-in-clang
