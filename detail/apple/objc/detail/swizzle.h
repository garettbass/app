#pragma once
#include "message.h"

//------------------------------------------------------------------------------

typedef void* (*__app_objc_msg_swizzle_imp)(
    _app_objc_imp,
    _app_objc_id,
    _app_objc_selector*, ...);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#define __app_objc_swizzle_prefix(CLASS, /*PARAMS*/...)\
        __app_objc_msg_identifier(__app_objc_swizzle_, CLASS, __VA_ARGS__)

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#define __app_objc_swizzle_args(CLASS, /*PARAMS*/...)\
        _app_objc_concat_2(___app_objc_swizzle_args_,__app_objc_va_len(__VA_ARGS__))\
            (CLASS, __VA_ARGS__)
#define ___app_objc_swizzle_args_1(CLASS, P1)\
        _app_objc_sel(CLASS,P1)
#define ___app_objc_swizzle_args_2(CLASS, P1,T1)\
        _app_objc_sel(CLASS,P1,T1), P1
#define ___app_objc_swizzle_args_4(CLASS, P1,T1, P2,T2)\
        _app_objc_sel(CLASS,P1,T1,P2,T2), P1, P2
#define ___app_objc_swizzle_args_6(CLASS, P1,T1, P2,T2, P3,T3)\
        _app_objc_sel(CLASS,P1,T1,P2,T2,P3,T3), P1, P2, P3
#define ___app_objc_swizzle_args_8(CLASS, P1,T1, P2,T2, P3,T3, P4,T4)\
        _app_objc_sel(CLASS,P1,T1,P2,T2,P3,T3,P4,T4), P1, P2, P3, P4
#define ___app_objc_swizzle_args_10(CLASS, P1,T1, P2,T2, P3,T3, P4,T4, P5,T5)\
        _app_objc_sel(CLASS,P1,T1,P2,T2,P3,T3,P4,T4,P5,T5), P1, P2, P3, P4, P5
#define ___app_objc_swizzle_args_12(CLASS, P1,T1, P2,T2, P3,T3, P4,T4, P5,T5, P6,T6)\
        _app_objc_sel(CLASS,P1,T1,P2,T2,P3,T3,P4,T4,P5,T5), P1, P2, P3, P4, P5, P6
#define ___app_objc_swizzle_args_14(CLASS, P1,T1, P2,T2, P3,T3, P4,T4, P5,T5, P6,T6, P7,T7)\
        _app_objc_sel(CLASS,P1,T1,P2,T2,P3,T3,P4,T4,P5,T5), P1, P2, P3, P4, P5, P6, P7
#define ___app_objc_swizzle_args_16(CLASS, P1,T1, P2,T2, P3,T3, P4,T4, P5,T5, P6,T6, P7,T7, P8,T8)\
        _app_objc_sel(CLASS,P1,T1,P2,T2,P3,T3,P4,T4,P5,T5), P1, P2, P3, P4, P5, P6, P7, P8

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#define __app_objc_msg_swizzle(RESULT, CLASS, TSELF, METHOD_TYPE, /*PARAMS*/...)\
        ___app_objc_msg_swizzle(\
            RESULT,\
            CLASS,\
            METHOD_TYPE,\
            __app_objc_msg_send_t(CLASS, __VA_ARGS__),\
            _app_objc_concat_3(__app_objc_swizzle_prefix(CLASS, __VA_ARGS__),_,__COUNTER__),\
            _app_objc_sel(CLASS, __VA_ARGS__),\
            __app_objc_msg_params(TSELF, __VA_ARGS__),\
            __app_objc_swizzle_args(CLASS, __VA_ARGS__))
#define ___app_objc_msg_swizzle(RESULT, CLASS, METHOD_TYPE, MSG_SEND_T, PREFIX, MSG_SEL, PARAMS, /*ARGS*/...)\
        ____app_objc_msg_swizzle(RESULT, CLASS, METHOD_TYPE, MSG_SEND_T, PREFIX, MSG_SEL, PARAMS, __VA_ARGS__)
#define ____app_objc_msg_swizzle(RESULT, CLASS, METHOD_TYPE, MSG_SEND_T, PREFIX, MSG_SEL, PARAMS, /*ARGS*/...)\
        APP_EXTERN_C_BEGIN\
        static inline RESULT PREFIX##_callback(MSG_SEND_T imp, __app_objc_unpack(PARAMS));\
        static MSG_SEND_T PREFIX##_imp = NULL;\
        static void* PREFIX##_swizzle_imp PARAMS {\
            return ((__app_objc_msg_swizzle_imp)PREFIX##_callback)((_app_objc_imp)PREFIX##_imp, self, __VA_ARGS__);\
        }\
        __attribute__((constructor))\
        static inline void\
        PREFIX##_initializer(void) {\
            PREFIX##_imp = (MSG_SEND_T)___app_objc_msg_swizzle_initializer(\
                CLASS##_class,\
                MSG_SEL,\
                class_get##METHOD_TYPE,\
                (_app_objc_imp)PREFIX##_swizzle_imp);\
        }\
        APP_EXTERN_C_END\
        static inline RESULT PREFIX##_callback(MSG_SEND_T imp, __app_objc_unpack(PARAMS))

        APP_EXTERN_C_BEGIN
        static inline _app_objc_imp
        ___app_objc_msg_swizzle_initializer(
            _app_objc_class* cls,
            _app_objc_selector* const sel,
            _app_objc_method* (*getMethod)(_app_objc_class*,_app_objc_selector*),
            _app_objc_imp const imp
        ) {
            _app_objc_method* const method = getMethod(cls, sel);
            assert(method);
            return method_setImplementation(method, imp);
        }
        APP_EXTERN_C_END

//------------------------------------------------------------------------------
