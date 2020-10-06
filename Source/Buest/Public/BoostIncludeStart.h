#ifdef BOOST_INCLUDE_REGION
#error Boost include regions cannot be nested, one region is already opened before
#endif
#define BOOST_INCLUDE_REGION 1

THIRD_PARTY_INCLUDES_START

// temporarily undefine simplistic UE4 macros boost might also use

#pragma push_macro("TEXT")
#pragma push_macro("CONSTEXPR")
#pragma push_macro("PI")
#pragma push_macro("dynamic_cast")
#pragma push_macro("VARARGS")
#pragma push_macro("CDECL")
#pragma push_macro("STDCALL")
#pragma push_macro("FORCEINLINE")
#pragma push_macro("FORCENOINLINE")
#pragma push_macro("ABSTRACT")
#pragma push_macro("LINE_TERMINATOR")
#pragma push_macro("LINE_TERMINATOR_ANSI")
#pragma push_macro("DLLEXPORT")
#pragma push_macro("DLLIMPORT")
#pragma push_macro("LIKELY")
#pragma push_macro("UNLIKELY")
#pragma push_macro("RESTRICT")
#pragma push_macro("MOBILE")
#pragma push_macro("CONSOLE")
#pragma push_macro("PLATFORM_WINDOWS")
#pragma push_macro("PLATFORM_COMPILER_CLANG")
#pragma push_macro("PLATFORM_APPLE")
#pragma push_macro("PLATFORM_MAC")
#pragma push_macro("PLATFORM_LINUX")
#pragma push_macro("PLATFORM_FREEBSD")
#pragma push_macro("PLATFORM_UNIX")

#undef TEXT
#undef CONSTEXPR
#undef PI
#undef dynamic_cast
#undef VARARGS
#undef CDECL
#undef STDCALL
#undef FORCEINLINE
#undef FORCENOINLINE
#undef ABSTRACT
#undef LINE_TERMINATOR
#undef LINE_TERMINATOR_ANSI
#undef DLLEXPORT
#undef DLLIMPORT
#undef LIKELY
#undef UNLIKELY
#undef RESTRICT
#undef MOBILE
#undef CONSOLE
#undef PLATFORM_WINDOWS
#undef PLATFORM_COMPILER_CLANG
#undef PLATFORM_APPLE
#undef PLATFORM_MAC
#undef PLATFORM_LINUX
#undef PLATFORM_FREEBSD
#undef PLATFORM_UNIX

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

// UE4 might use combination of compiler specific macros, which boost might not tolerate well.
// Sanitizing such macros here:

#define B_INCL_STR2(x) #x
#define B_INCL_STR(x) B_INCL_STR2(x)

// In case new errors regarding this come up, define this macro to see which compiler macros are actually active
// #define BUEST_DISPLAY_COMPILER_MACROS

#ifdef BUEST_DISPLAY_COMPILER_MACROS

#if defined(__INTEL_COMPILER)
#pragma message ("BUEST: __INTEL_COMPILER " B_INCL_STR(__INTEL_COMPILER))
#endif
#if defined(__ICL)
#pragma message ("BUEST: __ICL " B_INCL_STR(__ICL))
#endif
#if defined(__ICC)
#pragma message ("BUEST: __ICC " B_INCL_STR(__ICC))
#endif
#if defined(__ECC)
#pragma message ("BUEST: __ECC " B_INCL_STR(__ECC))
#endif
#if defined(__PGI)
#pragma message ("BUEST: __PGI " B_INCL_STR(__PGI))
#endif
#if defined(__GNUC__)
#pragma message ("BUEST: __GNUC__ " B_INCL_STR(__GNUC__))
#endif
#if defined(__ibmxl__)
#pragma message ("BUEST: __ibmxl__ " B_INCL_STR(__ibmxl__))
#endif
#if defined(_MSC_VER)
#pragma message ("BUEST: _MSC_VER " B_INCL_STR(_MSC_VER))
#endif

#endif

// prefer MSVC compiler macros over GCC if they're both present for some god forsaken reason
#if defined(_MSC_VER) && defined(__GNUC__)

#if _MSC_VER > 0
#pragma message ("BUEST: _MSC_VER - __GNUC__ macro collision detected, temporarily undefining __GNUC__ (GCC: " B_INCL_STR(__GNUC__) ", MSVC: " B_INCL_STR(_MSC_VER) ")")
#define BUEST_MSVC_GNUC_AVOIDANCE __GNUC__
#pragma push_macro("__GNUC__")
#undef __GNUC__
#endif

#endif

#undef B_INCL_STR
#undef B_INCL_STR2
