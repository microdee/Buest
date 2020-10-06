
#pragma warning( pop )

// restore temporary macro undefs
#ifdef BUEST_DO_CHECK
#undef BUEST_DO_CHECK

#pragma pop_macro("DO_CHECK")
#pragma pop_macro("checkCode")
#pragma pop_macro("check")
#pragma pop_macro("checkf")
#pragma pop_macro("verify")
#pragma pop_macro("verifyf")
#pragma pop_macro("unimplemented")
#pragma pop_macro("ensure")

#endif

#ifdef BUEST_MSVC_GNUC_AVOIDANCE
//#pragma pop_macro("__GNUC__")
#define __GNUC__ BUEST_MSVC_GNUC_AVOIDANCE
#endif

THIRD_PARTY_INCLUDES_END

#undef BOOST_INCLUDE_REGION