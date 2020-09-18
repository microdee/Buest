#ifdef BOOST_INCLUDE_REGION
#error Boost include regions cannot be nested, one region is already opened before
#endif
#define BOOST_INCLUDE_REGION 1

THIRD_PARTY_INCLUDES_START

// temporarily undefine simplistic UE4 macros boost might also use
#if DO_CHECK
#define BUEST_DO_CHECK 1

#pragma push_macro("DO_CHECK")
#pragma push_macro("checkCode")
#pragma push_macro("check")
#pragma push_macro("checkf")
#pragma push_macro("verify")
#pragma push_macro("verifyf")
#pragma push_macro("unimplemented")
#pragma push_macro("ensure")

#undef DO_CHECK
#undef checkCode
#undef check
#undef checkf
#undef verify
#undef verifyf
#undef unimplemented
#undef ensure

#endif

// disable extra warnings THIRD_PARTY_INCLUDES_START didn't disable yet
#pragma warning( push )
#pragma warning( disable : 4103 )   // alignment changed after including header, may be due to missing #pragma pack(pop)
