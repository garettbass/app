#pragma once
#include "message.h"

//------------------------------------------------------------------------------

#define __app_objc_method(RESULT, CLASS, /*PARAMS*/...)\
        static RESULT\
        __app_objc_msg_method(CLASS, __VA_ARGS__)\
        __app_objc_msg_params(__app_objc_msg_self_t(CLASS, __VA_ARGS__), __VA_ARGS__)

//------------------------------------------------------------------------------

#define __app_objc_method_declaration(CLASS, TSELF, RESULT, /*PARAMS*/...)\
        typedef TSELF __app_objc_msg_self_t(CLASS, __VA_ARGS__);\
        static RESULT\
        __app_objc_msg_method(CLASS, __VA_ARGS__)\
        __app_objc_msg_params(__app_objc_msg_self_t(CLASS, __VA_ARGS__), __VA_ARGS__);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#define __app_objc_method_initializer(CLASS, METHOD_TYPE, RESULT, /*PARAMS*/...)\
        ___app_objc_method_initializer(\
            (_app_objc_imp)__app_objc_msg_method(CLASS, __VA_ARGS__),\
            __app_objc_msg_string(CLASS, __VA_ARGS__),\
            CLASS##_class,\
            class_add##METHOD_TYPE);

        APP_EXTERN_C_BEGIN
        static inline bool
        class_addClassMethod(_app_objc_class* cls, _app_objc_selector* sel, _app_objc_imp imp) {
            _app_objc_class* const mcls = object_getClass(cls);
            return class_addMethod(mcls, sel, imp, "v");
        }

        static inline bool
        class_addInstanceMethod(_app_objc_class* cls, _app_objc_selector* sel, _app_objc_imp imp) {
            return class_addMethod(cls, sel, imp, "v");
        }

        static inline void
        ___app_objc_method_initializer(
            const _app_objc_imp   imp,
            const char  msg_string[],
            _app_objc_class* const cls,
            bool (*addMethod)(_app_objc_class*, _app_objc_selector*, _app_objc_imp)
        ) {
            assert(imp);
            _app_objc_selector* const sel = sel_getUid(msg_string);
            const bool added = addMethod(cls, sel, imp);
            assert(added);(void)added;
        }
        APP_EXTERN_C_END

//------------------------------------------------------------------------------
