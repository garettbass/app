#pragma once
#include <assert.h>
#include <iso646.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

//-----------------------------------------------------------------------------

#ifndef __cplusplus
#ifndef static_assert
#define static_assert _Static_assert
#endif
#endif

//------------------------------------------------------------------------------

#ifdef __cplusplus
    #define APP_EXTERN_C       extern "C"
    #define APP_EXTERN_C_BEGIN extern "C" {
    #define APP_EXTERN_C_END   } // extern "C"
#else
    #define APP_EXTERN_C       /* extern "C" */
    #define APP_EXTERN_C_BEGIN /* extern "C" { */
    #define APP_EXTERN_C_END   /* } // extern "C" */
#endif // __cplusplus

//------------------------------------------------------------------------------

#ifndef APP_DEBUG
    #if defined(DEBUG) || defined(_DEBUG)
        #define APP_DEBUG 1
    #elif defined(__GNUC__) && !defined(__OPTIMIZE)
        #define APP_DEBUG 1
    #endif
#endif

//------------------------------------------------------------------------------

#if APP_DEBUG
    #define APP_DEBUG_ONLY(...) __VA_ARGS__
#else
    #define APP_DEBUG_ONLY(...)
#endif

//-----------------------------------------------------------------------------

#define  APP_QUOTE(...) _APP_QUOTE(__VA_ARGS__)
#define _APP_QUOTE(...) #__VA_ARGS__

//------------------------------------------------------------------------------

#if defined(__clang__)

    #define APP_COMPILER_ID     clang
    #define APP_COMPILER_NAME   "clang " __clang_version__
    #define APP_COMPILER_CLANG  \
        (__clang_major__*10000+__clang_minor__*100+__clang_patchlevel__)

    #define app_static_initializer(NAME)\
        __attribute__((constructor))\
        static void NAME(void)

#elif defined(__GNUC__)

    #define APP_COMPILER_ID    gcc
    #define APP_COMPILER_NAME  "gcc " __VERSION__
    #define APP_COMPILER_GCC   \
        (__GNUC__*10000+__GNUC_MINOR__*100+__GNUC_PATCHLEVEL__)

    #define app_static_initializer(NAME)\
        __attribute__((constructor))\
        static void NAME(void)

#elif defined(_MSC_VER)

    #define APP_COMPILER_ID    msvc
    #define APP_COMPILER_NAME  "msvc " APP_QUOTE(_MSC_FULL_VER)
    #define APP_COMPILER_MSVC  (_MSC_VER)

    #pragma section(".CRT$XCU",read)

    #ifdef _WIN64
        #define app_static_initializer(NAME)\
            static void NAME(void);\
            __pragma(allocate(".CRT$XCU"))\
            void (*NAME##_)(void) = NAME;\
            __pragma(comment(linker,"/include:" #NAME "_"))\
            static void NAME(void)
    #else
        #define app_static_initializer(NAME)\
            static void NAME(void);\
            __pragma(allocate(".CRT$XCU"))\
            void (*NAME##_)(void) = NAME;\
            __pragma(comment(linker,"/include:_" #NAME "_"))\
            static void NAME(void)
    #endif

#else

    #error "unrecognized compiler"

#endif

//------------------------------------------------------------------------------

#if defined(__ANDROID__)

    #define APP_OS_ANDROID    1
    #define APP_OS_ID         android
    #define APP_OS_NAME       "Android"

#elif defined(__linux)

    #define APP_OS_LINUX      1
    #define APP_OS_ID         linux
    #define APP_OS_NAME       "Linux"

#elif defined(__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__)

    #define APP_OS_APPLE      1
    #define APP_OS_IOS        1
    #define APP_OS_ID         ios
    #define APP_OS_NAME       "iOS"

#elif defined(__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__)

    #define APP_OS_APPLE      1
    #define APP_OS_MACOS      1
    #define APP_OS_ID         macos
    #define APP_OS_NAME       "macOS"

#elif __cplusplus_winrt

    #define APP_OS_MICROSOFT  1
    #define APP_OS_WINRT      1
    #define APP_OS_ID         winrt
    #define APP_OS_NAME       "WinRT"

#elif defined(_WIN32) || defined(__CYGWIN__)

    #define APP_OS_MICROSOFT  1
    #define APP_OS_WINDOWS    1
    #define APP_OS_ID         windows
    #define APP_OS_NAME       "Windows"

#else

    #error "unsupported platform"

#endif

//------------------------------------------------------------------------------

#if defined(__aarch64__)

    // ARM 64
    #define APP_CPU_ARM    1
    #define APP_CPU_ARM_64 1
    #define APP_CPU_ID     arm_64
    #define APP_CPU_NAME   "ARM64"
    #define APP_CPU_BITS   64

#elif \
    defined(ARM)     || \
    defined(_ARM)    || \
    defined(__arm)   || \
    defined(__arm__)

    // ARM 32
    #define APP_CPU_ARM    1
    #define APP_CPU_ARM_32 1
    #define APP_CPU_ID     arm_32
    #define APP_CPU_NAME   "ARM"
    #define APP_CPU_BITS   32

#elif \
    defined(__powerpc64__) || \
    defined(__ppc64__)

    // PPC 64
    #define APP_CPU_PPC    1
    #define APP_CPU_PPC_64 1
    #define APP_CPU_ID     ppc_64
    #define APP_CPU_NAME   "PowerPC 64"
    #define APP_CPU_BITS   64

#elif \
    defined(__POWERPC__) || \
    defined(__PPC__)     || \
    defined(__powerpc__) || \
    defined(__ppc__)     || \
    defined(_POWER)      || \
    defined(powerpc)

    // PPC 32
    #define APP_CPU_PPC    1
    #define APP_CPU_PPC_32 1
    #define APP_CPU_ID     ppc_32
    #define APP_CPU_NAME   "PowerPC"
    #define APP_CPU_BITS   32

#elif \
    defined(_M_X64)     || \
    defined(_M_AMD64)   || \
    defined(__x86_64__)

    // x86-64
    #define APP_CPU_X86    1
    #define APP_CPU_X86_64 1
    #define APP_CPU_ID     x86_64
    #define APP_CPU_NAME   "x86-64"
    #define APP_CPU_BITS   64

#elif \
    defined(_M_IX86)  || \
    defined(__386__)  || \
    defined(__i386__) || \
    defined(__X86__)  || \
    defined(i386)

    // x86
    #define APP_CPU_X86    1
    #define APP_CPU_X86_32 1
    #define APP_CPU_ID     x86_32
    #define APP_CPU_NAME   "x86"
    #define APP_CPU_BITS   32

#else

    #error "unrecognized CPU architecture"

#endif

//------------------------------------------------------------------------------

#if APP_CPU_X86 || APP_CPU_X86_64 || (APP_CPU_ARM && !__BIG_ENDIAN__)

    #define APP_ENDIAN_LE     0x01020304u
    #define APP_ENDIAN_BE     0
    #define APP_ENDIAN        APP_ENDIAN_LE
    #define APP_ENDIAN_NAME   "little endian"

#elif APP_CPU_PPC

    #define APP_ENDIAN_LE     0
    #define APP_ENDIAN_BE     0x04030201u
    #define APP_ENDIAN        APP_ENDIAN_BE
    #define APP_ENDIAN_NAME   "big endian"

#else

    #error "unrecognized endianness"

#endif

//------------------------------------------------------------------------------

#define APP_DEFER(...) _APP_DEFER(__VA_ARGS__)
#define _APP_DEFER(...) __VA_ARGS__

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#define APP_CONCAT(A,B) _APP_CONCAT(A,B)
#define _APP_CONCAT(A,B) A##B

//------------------------------------------------------------------------------

#define APP_VA_COUNT(...)\
        _APP_VA_COUNT(_APP_VA_COUNT_ARGS(__VA_ARGS__))
#define _APP_VA_COUNT(...)\
        APP_DEFER(__APP_VA_COUNT(__VA_ARGS__,\
            80,79,78,77,76,75,74,73,72,71,\
            70,69,68,67,66,65,64,63,62,61,\
            60,59,58,57,56,55,54,53,52,51,\
            50,49,48,47,46,45,44,43,42,41,\
            40,39,38,37,36,35,34,33,32,31,\
            30,29,28,27,26,25,24,23,22,21,\
            20,19,18,17,16,15,14,13,12,11,\
            10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0))
#define __APP_VA_COUNT(\
            _80,_79,_78,_77,_76,_75,_74,_73,_72,_71,\
            _70,_69,_68,_67,_66,_65,_64,_63,_62,_61,\
            _60,_59,_58,_57,_56,_55,_54,_53,_52,_51,\
            _50,_49,_48,_47,_46,_45,_44,_43,_42,_41,\
            _40,_39,_38,_37,_36,_35,_34,_33,_32,_31,\
            _30,_29,_28,_27,_26,_25,_24,_23,_22,_21,\
            _20,_19,_18,_17,_16,_15,_14,_13,_12,_11,\
            _10,__9,__8,__7,__6,__5,__4,__3,__2,__1,__0,COUNT,...) COUNT

#if APP_COMPILER_MICROSOFT
    #define _APP_VA_COUNT_ARGS(...) ,__VA_ARGS__
#else
    #define _APP_VA_COUNT_ARGS(...) __VA_ARGS__,
#endif

// ok on Windows clang 8.0.1, not ok on macOS clang 10.0.1 ???
// static_assert( 0 == APP_VA_COUNT(), "?");
static_assert( 1 == APP_VA_COUNT(1), "?");
static_assert( 2 == APP_VA_COUNT(1,2), "?");
static_assert( 3 == APP_VA_COUNT(1,2,3), "?");
static_assert( 4 == APP_VA_COUNT(1,2,3,4), "?");
static_assert( 5 == APP_VA_COUNT(1,2,3,4,5), "?");
static_assert( 6 == APP_VA_COUNT(1,2,3,4,5,6), "?");
static_assert( 7 == APP_VA_COUNT(1,2,3,4,5,6,7), "?");
static_assert( 8 == APP_VA_COUNT(1,2,3,4,5,6,7,8), "?");
static_assert( 9 == APP_VA_COUNT(1,2,3,4,5,6,7,8,9), "?");
static_assert(10 == APP_VA_COUNT(1,2,3,4,5,6,7,8,9,10), "?");
static_assert(80 == APP_VA_COUNT(1,2,3,4,5,6,7,8,9,10,
                                 1,2,3,4,5,6,7,8,9,20,
                                 1,2,3,4,5,6,7,8,9,30,
                                 1,2,3,4,5,6,7,8,9,40,
                                 1,2,3,4,5,6,7,8,9,50,
                                 1,2,3,4,5,6,7,8,9,60,
                                 1,2,3,4,5,6,7,8,9,70,
                                 1,2,3,4,5,6,7,8,9,80), "?");

//------------------------------------------------------------------------------

#define APP_VA_APPLY(M, ...)\
        _APP_VA_APPLY_(APP_VA_COUNT(__VA_ARGS__), M, __VA_ARGS__)
#define _APP_VA_APPLY_(N, M, ...)\
        APP_DEFER(APP_CONCAT(_APP_VA_APPLY_,N)(M, __VA_ARGS__))
#define _APP_VA_APPLY_0(M)
#define _APP_VA_APPLY_1(M, _1)       M(_1)
#define _APP_VA_APPLY_2(M, _1, ...)  M(_1)APP_DEFER(_APP_VA_APPLY_1(M, __VA_ARGS__))
#define _APP_VA_APPLY_3(M, _1, ...)  M(_1)APP_DEFER(_APP_VA_APPLY_2(M, __VA_ARGS__))
#define _APP_VA_APPLY_4(M, _1, ...)  M(_1)APP_DEFER(_APP_VA_APPLY_3(M, __VA_ARGS__))
#define _APP_VA_APPLY_5(M, _1, ...)  M(_1)APP_DEFER(_APP_VA_APPLY_4(M, __VA_ARGS__))
#define _APP_VA_APPLY_6(M, _1, ...)  M(_1)APP_DEFER(_APP_VA_APPLY_5(M, __VA_ARGS__))
#define _APP_VA_APPLY_7(M, _1, ...)  M(_1)APP_DEFER(_APP_VA_APPLY_6(M, __VA_ARGS__))
#define _APP_VA_APPLY_8(M, _1, ...)  M(_1)APP_DEFER(_APP_VA_APPLY_7(M, __VA_ARGS__))
#define _APP_VA_APPLY_9(M, _1, ...)  M(_1)APP_DEFER(_APP_VA_APPLY_8(M, __VA_ARGS__))
#define _APP_VA_APPLY_10(M, _1, ...) M(_1)APP_DEFER(_APP_VA_APPLY_9(M, __VA_ARGS__))
#define _APP_VA_APPLY_11(M, _1, ...) M(_1)APP_DEFER(_APP_VA_APPLY_10(M, __VA_ARGS__))
#define _APP_VA_APPLY_12(M, _1, ...) M(_1)APP_DEFER(_APP_VA_APPLY_11(M, __VA_ARGS__))
#define _APP_VA_APPLY_13(M, _1, ...) M(_1)APP_DEFER(_APP_VA_APPLY_12(M, __VA_ARGS__))
#define _APP_VA_APPLY_14(M, _1, ...) M(_1)APP_DEFER(_APP_VA_APPLY_13(M, __VA_ARGS__))
#define _APP_VA_APPLY_15(M, _1, ...) M(_1)APP_DEFER(_APP_VA_APPLY_14(M, __VA_ARGS__))
#define _APP_VA_APPLY_16(M, _1, ...) M(_1)APP_DEFER(_APP_VA_APPLY_15(M, __VA_ARGS__))
#define _APP_VA_APPLY_17(M, _1, ...) M(_1)APP_DEFER(_APP_VA_APPLY_16(M, __VA_ARGS__))
#define _APP_VA_APPLY_18(M, _1, ...) M(_1)APP_DEFER(_APP_VA_APPLY_17(M, __VA_ARGS__))
#define _APP_VA_APPLY_19(M, _1, ...) M(_1)APP_DEFER(_APP_VA_APPLY_18(M, __VA_ARGS__))
#define _APP_VA_APPLY_20(M, _1, ...) M(_1)APP_DEFER(_APP_VA_APPLY_19(M, __VA_ARGS__))
#define _APP_VA_APPLY_21(M, _1, ...) M(_1)APP_DEFER(_APP_VA_APPLY_20(M, __VA_ARGS__))
#define _APP_VA_APPLY_22(M, _1, ...) M(_1)APP_DEFER(_APP_VA_APPLY_21(M, __VA_ARGS__))
#define _APP_VA_APPLY_23(M, _1, ...) M(_1)APP_DEFER(_APP_VA_APPLY_22(M, __VA_ARGS__))
#define _APP_VA_APPLY_24(M, _1, ...) M(_1)APP_DEFER(_APP_VA_APPLY_23(M, __VA_ARGS__))
#define _APP_VA_APPLY_25(M, _1, ...) M(_1)APP_DEFER(_APP_VA_APPLY_24(M, __VA_ARGS__))
#define _APP_VA_APPLY_26(M, _1, ...) M(_1)APP_DEFER(_APP_VA_APPLY_25(M, __VA_ARGS__))
#define _APP_VA_APPLY_27(M, _1, ...) M(_1)APP_DEFER(_APP_VA_APPLY_26(M, __VA_ARGS__))
#define _APP_VA_APPLY_28(M, _1, ...) M(_1)APP_DEFER(_APP_VA_APPLY_27(M, __VA_ARGS__))
#define _APP_VA_APPLY_29(M, _1, ...) M(_1)APP_DEFER(_APP_VA_APPLY_28(M, __VA_ARGS__))
#define _APP_VA_APPLY_30(M, _1, ...) M(_1)APP_DEFER(_APP_VA_APPLY_29(M, __VA_ARGS__))
#define _APP_VA_APPLY_31(M, _1, ...) M(_1)APP_DEFER(_APP_VA_APPLY_30(M, __VA_ARGS__))
#define _APP_VA_APPLY_32(M, _1, ...) M(_1)APP_DEFER(_APP_VA_APPLY_31(M, __VA_ARGS__))
#define _APP_VA_APPLY_33(M, _1, ...) M(_1)APP_DEFER(_APP_VA_APPLY_32(M, __VA_ARGS__))
#define _APP_VA_APPLY_34(M, _1, ...) M(_1)APP_DEFER(_APP_VA_APPLY_33(M, __VA_ARGS__))
#define _APP_VA_APPLY_35(M, _1, ...) M(_1)APP_DEFER(_APP_VA_APPLY_34(M, __VA_ARGS__))
#define _APP_VA_APPLY_36(M, _1, ...) M(_1)APP_DEFER(_APP_VA_APPLY_35(M, __VA_ARGS__))
#define _APP_VA_APPLY_37(M, _1, ...) M(_1)APP_DEFER(_APP_VA_APPLY_36(M, __VA_ARGS__))
#define _APP_VA_APPLY_38(M, _1, ...) M(_1)APP_DEFER(_APP_VA_APPLY_37(M, __VA_ARGS__))
#define _APP_VA_APPLY_39(M, _1, ...) M(_1)APP_DEFER(_APP_VA_APPLY_38(M, __VA_ARGS__))
#define _APP_VA_APPLY_40(M, _1, ...) M(_1)APP_DEFER(_APP_VA_APPLY_39(M, __VA_ARGS__))
#define _APP_VA_APPLY_41(M, _1, ...) M(_1)APP_DEFER(_APP_VA_APPLY_40(M, __VA_ARGS__))
#define _APP_VA_APPLY_42(M, _1, ...) M(_1)APP_DEFER(_APP_VA_APPLY_41(M, __VA_ARGS__))
#define _APP_VA_APPLY_43(M, _1, ...) M(_1)APP_DEFER(_APP_VA_APPLY_42(M, __VA_ARGS__))
#define _APP_VA_APPLY_44(M, _1, ...) M(_1)APP_DEFER(_APP_VA_APPLY_43(M, __VA_ARGS__))
#define _APP_VA_APPLY_45(M, _1, ...) M(_1)APP_DEFER(_APP_VA_APPLY_44(M, __VA_ARGS__))
#define _APP_VA_APPLY_46(M, _1, ...) M(_1)APP_DEFER(_APP_VA_APPLY_45(M, __VA_ARGS__))
#define _APP_VA_APPLY_47(M, _1, ...) M(_1)APP_DEFER(_APP_VA_APPLY_46(M, __VA_ARGS__))
#define _APP_VA_APPLY_48(M, _1, ...) M(_1)APP_DEFER(_APP_VA_APPLY_47(M, __VA_ARGS__))
#define _APP_VA_APPLY_49(M, _1, ...) M(_1)APP_DEFER(_APP_VA_APPLY_48(M, __VA_ARGS__))
#define _APP_VA_APPLY_50(M, _1, ...) M(_1)APP_DEFER(_APP_VA_APPLY_49(M, __VA_ARGS__))
#define _APP_VA_APPLY_51(M, _1, ...) M(_1)APP_DEFER(_APP_VA_APPLY_50(M, __VA_ARGS__))
#define _APP_VA_APPLY_52(M, _1, ...) M(_1)APP_DEFER(_APP_VA_APPLY_51(M, __VA_ARGS__))
#define _APP_VA_APPLY_53(M, _1, ...) M(_1)APP_DEFER(_APP_VA_APPLY_52(M, __VA_ARGS__))
#define _APP_VA_APPLY_54(M, _1, ...) M(_1)APP_DEFER(_APP_VA_APPLY_53(M, __VA_ARGS__))
#define _APP_VA_APPLY_55(M, _1, ...) M(_1)APP_DEFER(_APP_VA_APPLY_54(M, __VA_ARGS__))
#define _APP_VA_APPLY_56(M, _1, ...) M(_1)APP_DEFER(_APP_VA_APPLY_55(M, __VA_ARGS__))
#define _APP_VA_APPLY_57(M, _1, ...) M(_1)APP_DEFER(_APP_VA_APPLY_56(M, __VA_ARGS__))
#define _APP_VA_APPLY_58(M, _1, ...) M(_1)APP_DEFER(_APP_VA_APPLY_57(M, __VA_ARGS__))
#define _APP_VA_APPLY_59(M, _1, ...) M(_1)APP_DEFER(_APP_VA_APPLY_58(M, __VA_ARGS__))
#define _APP_VA_APPLY_60(M, _1, ...) M(_1)APP_DEFER(_APP_VA_APPLY_59(M, __VA_ARGS__))
#define _APP_VA_APPLY_61(M, _1, ...) M(_1)APP_DEFER(_APP_VA_APPLY_60(M, __VA_ARGS__))
#define _APP_VA_APPLY_62(M, _1, ...) M(_1)APP_DEFER(_APP_VA_APPLY_61(M, __VA_ARGS__))
#define _APP_VA_APPLY_63(M, _1, ...) M(_1)APP_DEFER(_APP_VA_APPLY_62(M, __VA_ARGS__))
#define _APP_VA_APPLY_64(M, _1, ...) M(_1)APP_DEFER(_APP_VA_APPLY_63(M, __VA_ARGS__))
#define _APP_VA_APPLY_65(M, _1, ...) M(_1)APP_DEFER(_APP_VA_APPLY_64(M, __VA_ARGS__))
#define _APP_VA_APPLY_66(M, _1, ...) M(_1)APP_DEFER(_APP_VA_APPLY_65(M, __VA_ARGS__))
#define _APP_VA_APPLY_67(M, _1, ...) M(_1)APP_DEFER(_APP_VA_APPLY_66(M, __VA_ARGS__))
#define _APP_VA_APPLY_68(M, _1, ...) M(_1)APP_DEFER(_APP_VA_APPLY_67(M, __VA_ARGS__))
#define _APP_VA_APPLY_69(M, _1, ...) M(_1)APP_DEFER(_APP_VA_APPLY_68(M, __VA_ARGS__))
#define _APP_VA_APPLY_70(M, _1, ...) M(_1)APP_DEFER(_APP_VA_APPLY_69(M, __VA_ARGS__))
#define _APP_VA_APPLY_71(M, _1, ...) M(_1)APP_DEFER(_APP_VA_APPLY_70(M, __VA_ARGS__))
#define _APP_VA_APPLY_72(M, _1, ...) M(_1)APP_DEFER(_APP_VA_APPLY_71(M, __VA_ARGS__))
#define _APP_VA_APPLY_73(M, _1, ...) M(_1)APP_DEFER(_APP_VA_APPLY_72(M, __VA_ARGS__))
#define _APP_VA_APPLY_74(M, _1, ...) M(_1)APP_DEFER(_APP_VA_APPLY_73(M, __VA_ARGS__))
#define _APP_VA_APPLY_75(M, _1, ...) M(_1)APP_DEFER(_APP_VA_APPLY_74(M, __VA_ARGS__))
#define _APP_VA_APPLY_76(M, _1, ...) M(_1)APP_DEFER(_APP_VA_APPLY_75(M, __VA_ARGS__))
#define _APP_VA_APPLY_77(M, _1, ...) M(_1)APP_DEFER(_APP_VA_APPLY_76(M, __VA_ARGS__))
#define _APP_VA_APPLY_78(M, _1, ...) M(_1)APP_DEFER(_APP_VA_APPLY_77(M, __VA_ARGS__))
#define _APP_VA_APPLY_79(M, _1, ...) M(_1)APP_DEFER(_APP_VA_APPLY_78(M, __VA_ARGS__))
#define _APP_VA_APPLY_80(M, _1, ...) M(_1)APP_DEFER(_APP_VA_APPLY_79(M, __VA_ARGS__))

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#define APP_VA_APPLY_X(M, X, ...)\
        _APP_VA_APPLY_X_(APP_VA_COUNT(__VA_ARGS__), M, X, __VA_ARGS__)
#define _APP_VA_APPLY_X_(N, M, X, ...)\
        APP_DEFER(APP_CONCAT(_APP_VA_APPLY_X_,N)(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_0(M, X)
#define _APP_VA_APPLY_X_1(M, X, _1)       M(X,_1)
#define _APP_VA_APPLY_X_2(M, X, _1, ...)  M(X,_1)APP_DEFER(_APP_VA_APPLY_X_1(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_3(M, X, _1, ...)  M(X,_1)APP_DEFER(_APP_VA_APPLY_X_2(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_4(M, X, _1, ...)  M(X,_1)APP_DEFER(_APP_VA_APPLY_X_3(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_5(M, X, _1, ...)  M(X,_1)APP_DEFER(_APP_VA_APPLY_X_4(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_6(M, X, _1, ...)  M(X,_1)APP_DEFER(_APP_VA_APPLY_X_5(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_7(M, X, _1, ...)  M(X,_1)APP_DEFER(_APP_VA_APPLY_X_6(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_8(M, X, _1, ...)  M(X,_1)APP_DEFER(_APP_VA_APPLY_X_7(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_9(M, X, _1, ...)  M(X,_1)APP_DEFER(_APP_VA_APPLY_X_8(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_10(M, X, _1, ...) M(X,_1)APP_DEFER(_APP_VA_APPLY_X_9(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_11(M, X, _1, ...) M(X,_1)APP_DEFER(_APP_VA_APPLY_X_10(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_12(M, X, _1, ...) M(X,_1)APP_DEFER(_APP_VA_APPLY_X_11(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_13(M, X, _1, ...) M(X,_1)APP_DEFER(_APP_VA_APPLY_X_12(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_14(M, X, _1, ...) M(X,_1)APP_DEFER(_APP_VA_APPLY_X_13(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_15(M, X, _1, ...) M(X,_1)APP_DEFER(_APP_VA_APPLY_X_14(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_16(M, X, _1, ...) M(X,_1)APP_DEFER(_APP_VA_APPLY_X_15(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_17(M, X, _1, ...) M(X,_1)APP_DEFER(_APP_VA_APPLY_X_16(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_18(M, X, _1, ...) M(X,_1)APP_DEFER(_APP_VA_APPLY_X_17(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_19(M, X, _1, ...) M(X,_1)APP_DEFER(_APP_VA_APPLY_X_18(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_20(M, X, _1, ...) M(X,_1)APP_DEFER(_APP_VA_APPLY_X_19(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_21(M, X, _1, ...) M(X,_1)APP_DEFER(_APP_VA_APPLY_X_20(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_22(M, X, _1, ...) M(X,_1)APP_DEFER(_APP_VA_APPLY_X_21(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_23(M, X, _1, ...) M(X,_1)APP_DEFER(_APP_VA_APPLY_X_22(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_24(M, X, _1, ...) M(X,_1)APP_DEFER(_APP_VA_APPLY_X_23(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_25(M, X, _1, ...) M(X,_1)APP_DEFER(_APP_VA_APPLY_X_24(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_26(M, X, _1, ...) M(X,_1)APP_DEFER(_APP_VA_APPLY_X_25(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_27(M, X, _1, ...) M(X,_1)APP_DEFER(_APP_VA_APPLY_X_26(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_28(M, X, _1, ...) M(X,_1)APP_DEFER(_APP_VA_APPLY_X_27(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_29(M, X, _1, ...) M(X,_1)APP_DEFER(_APP_VA_APPLY_X_28(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_30(M, X, _1, ...) M(X,_1)APP_DEFER(_APP_VA_APPLY_X_29(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_31(M, X, _1, ...) M(X,_1)APP_DEFER(_APP_VA_APPLY_X_30(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_32(M, X, _1, ...) M(X,_1)APP_DEFER(_APP_VA_APPLY_X_31(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_33(M, X, _1, ...) M(X,_1)APP_DEFER(_APP_VA_APPLY_X_32(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_34(M, X, _1, ...) M(X,_1)APP_DEFER(_APP_VA_APPLY_X_33(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_35(M, X, _1, ...) M(X,_1)APP_DEFER(_APP_VA_APPLY_X_34(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_36(M, X, _1, ...) M(X,_1)APP_DEFER(_APP_VA_APPLY_X_35(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_37(M, X, _1, ...) M(X,_1)APP_DEFER(_APP_VA_APPLY_X_36(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_38(M, X, _1, ...) M(X,_1)APP_DEFER(_APP_VA_APPLY_X_37(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_39(M, X, _1, ...) M(X,_1)APP_DEFER(_APP_VA_APPLY_X_38(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_40(M, X, _1, ...) M(X,_1)APP_DEFER(_APP_VA_APPLY_X_39(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_41(M, X, _1, ...) M(X,_1)APP_DEFER(_APP_VA_APPLY_X_40(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_42(M, X, _1, ...) M(X,_1)APP_DEFER(_APP_VA_APPLY_X_41(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_43(M, X, _1, ...) M(X,_1)APP_DEFER(_APP_VA_APPLY_X_42(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_44(M, X, _1, ...) M(X,_1)APP_DEFER(_APP_VA_APPLY_X_43(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_45(M, X, _1, ...) M(X,_1)APP_DEFER(_APP_VA_APPLY_X_44(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_46(M, X, _1, ...) M(X,_1)APP_DEFER(_APP_VA_APPLY_X_45(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_47(M, X, _1, ...) M(X,_1)APP_DEFER(_APP_VA_APPLY_X_46(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_48(M, X, _1, ...) M(X,_1)APP_DEFER(_APP_VA_APPLY_X_47(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_49(M, X, _1, ...) M(X,_1)APP_DEFER(_APP_VA_APPLY_X_48(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_50(M, X, _1, ...) M(X,_1)APP_DEFER(_APP_VA_APPLY_X_49(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_51(M, X, _1, ...) M(X,_1)APP_DEFER(_APP_VA_APPLY_X_50(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_52(M, X, _1, ...) M(X,_1)APP_DEFER(_APP_VA_APPLY_X_51(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_53(M, X, _1, ...) M(X,_1)APP_DEFER(_APP_VA_APPLY_X_52(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_54(M, X, _1, ...) M(X,_1)APP_DEFER(_APP_VA_APPLY_X_53(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_55(M, X, _1, ...) M(X,_1)APP_DEFER(_APP_VA_APPLY_X_54(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_56(M, X, _1, ...) M(X,_1)APP_DEFER(_APP_VA_APPLY_X_55(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_57(M, X, _1, ...) M(X,_1)APP_DEFER(_APP_VA_APPLY_X_56(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_58(M, X, _1, ...) M(X,_1)APP_DEFER(_APP_VA_APPLY_X_57(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_59(M, X, _1, ...) M(X,_1)APP_DEFER(_APP_VA_APPLY_X_58(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_60(M, X, _1, ...) M(X,_1)APP_DEFER(_APP_VA_APPLY_X_59(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_61(M, X, _1, ...) M(X,_1)APP_DEFER(_APP_VA_APPLY_X_60(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_62(M, X, _1, ...) M(X,_1)APP_DEFER(_APP_VA_APPLY_X_61(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_63(M, X, _1, ...) M(X,_1)APP_DEFER(_APP_VA_APPLY_X_62(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_64(M, X, _1, ...) M(X,_1)APP_DEFER(_APP_VA_APPLY_X_63(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_65(M, X, _1, ...) M(X,_1)APP_DEFER(_APP_VA_APPLY_X_64(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_66(M, X, _1, ...) M(X,_1)APP_DEFER(_APP_VA_APPLY_X_65(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_67(M, X, _1, ...) M(X,_1)APP_DEFER(_APP_VA_APPLY_X_66(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_68(M, X, _1, ...) M(X,_1)APP_DEFER(_APP_VA_APPLY_X_67(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_69(M, X, _1, ...) M(X,_1)APP_DEFER(_APP_VA_APPLY_X_68(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_70(M, X, _1, ...) M(X,_1)APP_DEFER(_APP_VA_APPLY_X_69(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_71(M, X, _1, ...) M(X,_1)APP_DEFER(_APP_VA_APPLY_X_70(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_72(M, X, _1, ...) M(X,_1)APP_DEFER(_APP_VA_APPLY_X_71(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_73(M, X, _1, ...) M(X,_1)APP_DEFER(_APP_VA_APPLY_X_72(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_74(M, X, _1, ...) M(X,_1)APP_DEFER(_APP_VA_APPLY_X_73(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_75(M, X, _1, ...) M(X,_1)APP_DEFER(_APP_VA_APPLY_X_74(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_76(M, X, _1, ...) M(X,_1)APP_DEFER(_APP_VA_APPLY_X_75(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_77(M, X, _1, ...) M(X,_1)APP_DEFER(_APP_VA_APPLY_X_76(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_78(M, X, _1, ...) M(X,_1)APP_DEFER(_APP_VA_APPLY_X_77(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_79(M, X, _1, ...) M(X,_1)APP_DEFER(_APP_VA_APPLY_X_78(M, X, __VA_ARGS__))
#define _APP_VA_APPLY_X_80(M, X, _1, ...) M(X,_1)APP_DEFER(_APP_VA_APPLY_X_79(M, X, __VA_ARGS__))

//------------------------------------------------------------------------------

static inline
void
_APP_PRINT_MACRO(const char* s) {
    int indent = 0;
    bool newline = false;
    for (;*s;++s) {
        char c = *s;
        switch (c) {
            case '}':
                indent -= 1;
                break;
        }
        if (newline) {
            newline = false;
            fputc('\n', stdout);
            for (int i = 0; i < indent; ++i)
                fputs("    ", stdout);
        }
        fputc(c, stdout);
        switch (c) {
            case '}':
                newline = true;
                while (s[1] == ' ') ++s;
                break;
            case '{':
                indent += 1;
                newline = true;
                while (s[1] == ' ') ++s;
                break;
            case ';':
                newline = true;
                while (s[1] == ' ') ++s;
                break;
        }
    }
    fputc('\n', stdout);
    fputc('\n', stdout);
}

#define APP_PRINT_MACRO(...) _APP_PRINT_MACRO(__VA_ARGS__)
#define _APP_PRINT_MACRO(...) _APP_PRINT_MACRO(#__VA_ARGS__)
