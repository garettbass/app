#pragma once
#include "message.h"

//------------------------------------------------------------------------------

#define __app_objc_interface(CLASS, /*SYMBOLS*/...)\
        ___app_objc_interface(CLASS,\
            cls(_app_objc_class*,  class),\
            cls(CLASS*, new),\
            cls(CLASS*, alloc),\
            obj(void,   dealloc),\
            obj(CLASS*, init),\
            obj(CLASS*, copy),\
            obj(CLASS*, autorelease),\
            obj(void,   release),\
            obj(CLASS*, retain),\
            obj(size_t, retainCount),\
            __VA_ARGS__)
#define ___app_objc_interface(CLASS, /*SYMBOLS*/...)\
        _app_objc_class(CLASS);\
        static _app_objc_class* CLASS##_class = NULL;\
        __app_objc_interface_symbol_declarations(CLASS, __VA_ARGS__)\
        APP_EXTERN_C_BEGIN\
        __attribute__((constructor))\
        static inline void\
        __app_objc_interface_initializer_##CLASS(void) {\
            __app_objc_interface_initializer(&CLASS##_class, #CLASS);\
            __app_objc_interface_symbol_initializers(CLASS, __VA_ARGS__)\
        }\
        APP_EXTERN_C_END

        APP_EXTERN_C_BEGIN
        static inline void
        __app_objc_interface_initializer(_app_objc_class** pcls, const char* name) {
            assert(*pcls == NULL);
            if (strstr(name, "_app_") == name) { name += strlen("_app_"); }
            *pcls = objc_getClass(name);
        }
        APP_EXTERN_C_END

//------------------------------------------------------------------------------

#define __app_objc_interface_symbol_suffix(SYMBOL)\
        __app_objc_defer(_app_objc_concat_2(__app_objc_interface_symbol_suffix,_##SYMBOL))
#define __app_objc_interface_symbol_suffix_cls(...) cls
#define __app_objc_interface_symbol_suffix_obj(...) obj
#define __app_objc_interface_symbol_suffix_         end

//------------------------------------------------------------------------------

#define __app_objc_interface_symbol_params(SYMBOL)\
        __app_objc_defer(_app_objc_concat_2(__app_objc_interface_symbol_params,_##SYMBOL))
#define __app_objc_interface_symbol_params_cls(...) __VA_ARGS__
#define __app_objc_interface_symbol_params_obj(...) __VA_ARGS__
#define __app_objc_interface_symbol_params_(...)    __VA_ARGS__

//------------------------------------------------------------------------------

#define __app_objc_interface_symbol_declarations(CLASS, /*SYMBOLS*/...)\
        __app_objc_map1(__app_objc_interface_symbol_declaration, CLASS, __VA_ARGS__)
#define __app_objc_interface_symbol_declaration(CLASS, SYMBOL)\
        ___app_objc_interface_symbol_declaration_(CLASS,\
            __app_objc_interface_symbol_suffix(SYMBOL),\
            __app_objc_interface_symbol_params(SYMBOL))
#define ___app_objc_interface_symbol_declaration_(CLASS, SUFFIX, /*PARAMS*/...)\
        __app_objc_defer(_app_objc_concat_2(___app_objc_interface_symbol_declaration_,SUFFIX))\
            (CLASS, __VA_ARGS__)

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#define ___app_objc_interface_symbol_declaration_cls(/*CLASS, RESULT,*/...)\
        ____app_objc_interface_symbol_declaration_cls(__VA_ARGS__)
#define ____app_objc_interface_symbol_declaration_cls(CLASS, RESULT, ...)\
        __app_objc_msg_sel_declaration(CLASS, __VA_ARGS__)\
        __app_objc_msg_declaration(CLASS, RESULT, _app_objc_class*, __VA_ARGS__)

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#define ___app_objc_interface_symbol_declaration_obj(/*CLASS, RESULT,*/...)\
        ____app_objc_interface_symbol_declaration_obj(__VA_ARGS__)
#define ____app_objc_interface_symbol_declaration_obj(CLASS, RESULT, ...)\
        __app_objc_msg_sel_declaration(CLASS, __VA_ARGS__)\
        __app_objc_msg_declaration(CLASS, RESULT, CLASS*, __VA_ARGS__)

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#define ___app_objc_interface_symbol_declaration_end(...)

//------------------------------------------------------------------------------

#define __app_objc_interface_symbol_initializers(CLASS, /*SYMBOLS*/...)\
        __app_objc_map1(__app_objc_interface_symbol_initializer, CLASS, __VA_ARGS__)
#define __app_objc_interface_symbol_initializer(CLASS, SYMBOL)\
        __app_objc_interface_symbol_initializer_(CLASS,\
            __app_objc_interface_symbol_suffix(SYMBOL),\
            __app_objc_interface_symbol_params(SYMBOL))
#define __app_objc_interface_symbol_initializer_(CLASS, SUFFIX, /*PARAMS*/...)\
        __app_objc_defer(_app_objc_concat_2(__app_objc_interface_symbol_initializer_,SUFFIX))\
            (CLASS, __VA_ARGS__)

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#define __app_objc_interface_symbol_initializer_cls(/*CLASS, RESULT,*/...)\
        ___app_objc_interface_symbol_initializer_cls(__VA_ARGS__)
#define ___app_objc_interface_symbol_initializer_cls(CLASS, RESULT, ...)\
        __app_objc_msg_sel_initializer(CLASS, ClassMethod, __VA_ARGS__);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#define __app_objc_interface_symbol_initializer_obj(/*CLASS, RESULT,*/...)\
        ___app_objc_interface_symbol_initializer_obj(__VA_ARGS__)
#define ___app_objc_interface_symbol_initializer_obj(CLASS, RESULT, ...)\
        __app_objc_msg_sel_initializer(CLASS, InstanceMethod, __VA_ARGS__);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#define __app_objc_interface_symbol_initializer_end(...)

//------------------------------------------------------------------------------
