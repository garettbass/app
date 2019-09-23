#pragma once
#include "message.h"

//------------------------------------------------------------------------------

#define __app_objc_implementation(CLASS, SUPERCLASS, /*SYMBOLS*/...)\
        ___app_objc_implementation(CLASS, SUPERCLASS, __VA_ARGS__)
#define ___app_objc_implementation(CLASS, SUPERCLASS, /*SYMBOLS*/...)\
        __app_objc_implementation_symbol_declarations(CLASS, __VA_ARGS__)\
        APP_EXTERN_C_BEGIN\
        __attribute__((constructor)) static inline void\
        __app_objc_implementation_initializer_##CLASS(void) {\
            _app_objc_class* const super = SUPERCLASS##_class;\
            __app_objc_implementation_initializer(&CLASS##_class, super, #CLASS);\
            __app_objc_implementation_symbol_initializers(CLASS, __VA_ARGS__)\
            objc_registerClassPair(CLASS##_class);\
        }\
        APP_EXTERN_C_END

        APP_EXTERN_C_BEGIN
        static inline void
        __app_objc_implementation_initializer(_app_objc_class** pcls, _app_objc_class* super, const char name[]) {
            assert(super);
            assert(*pcls == NULL);
            *pcls = objc_allocateClassPair(super, name, 0);
        }
        APP_EXTERN_C_END

//------------------------------------------------------------------------------

#define __app_objc_implementation_symbol_suffix(SYMBOL)\
        __app_objc_defer(_app_objc_concat_2(__app_objc_implementation_symbol_suffix,_##SYMBOL))
#define __app_objc_implementation_symbol_suffix_var(...) var
#define __app_objc_implementation_symbol_suffix_cls(...) cls
#define __app_objc_implementation_symbol_suffix_obj(...) obj
#define __app_objc_implementation_symbol_suffix_         end

//------------------------------------------------------------------------------

#define __app_objc_implementation_symbol_params(SYMBOL)\
        __app_objc_defer(_app_objc_concat_2(__app_objc_implementation_symbol_params,_##SYMBOL))
#define __app_objc_implementation_symbol_params_var(...) __VA_ARGS__
#define __app_objc_implementation_symbol_params_cls(...) __VA_ARGS__
#define __app_objc_implementation_symbol_params_obj(...) __VA_ARGS__
#define __app_objc_implementation_symbol_params_(...)    __VA_ARGS__

//------------------------------------------------------------------------------

#define __app_objc_implementation_symbol_declarations(CLASS, /*SYMBOLS*/...)\
        __app_objc_map1(__app_objc_implementation_symbol_declaration, CLASS, __VA_ARGS__)
#define __app_objc_implementation_symbol_declaration(CLASS, SYMBOL)\
        ___app_objc_implementation_symbol_declaration_(CLASS,\
            __app_objc_implementation_symbol_suffix(SYMBOL),\
            __app_objc_implementation_symbol_params(SYMBOL))
#define ___app_objc_implementation_symbol_declaration_(CLASS, SUFFIX, /*PARAMS*/...)\
        __app_objc_defer(_app_objc_concat_2(___app_objc_implementation_symbol_declaration_,SUFFIX))\
            (CLASS, __VA_ARGS__)

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#define ___app_objc_implementation_symbol_declaration_var(CLASS, TYPE, NAME)\
        __app_objc_var_declaration(CLASS, TYPE, NAME)

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#define ___app_objc_implementation_symbol_declaration_cls(CLASS, RESULT, /*PARAMS*/...)\
        __app_objc_method_declaration(CLASS, _app_objc_class**, RESULT, __VA_ARGS__)

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#define ___app_objc_implementation_symbol_declaration_obj(CLASS, RESULT, /*PARAMS*/...)\
        __app_objc_method_declaration(CLASS, CLASS*, RESULT, __VA_ARGS__)

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#define ___app_objc_implementation_symbol_declaration_end(...) /**/

//------------------------------------------------------------------------------

#define __app_objc_implementation_symbol_initializers(CLASS, /*SYMBOLS*/...)\
        __app_objc_map1(__app_objc_implementation_symbol_initializer, CLASS, __VA_ARGS__)
#define __app_objc_implementation_symbol_initializer(CLASS, SYMBOL)\
        ___app_objc_implementation_symbol_initializer_(CLASS,\
            __app_objc_implementation_symbol_suffix(SYMBOL),\
            __app_objc_implementation_symbol_params(SYMBOL))
#define ___app_objc_implementation_symbol_initializer_(CLASS, SUFFIX, /*PARAMS*/...)\
        __app_objc_defer(_app_objc_concat_2(___app_objc_implementation_symbol_initializer_,SUFFIX))\
            (CLASS, __VA_ARGS__)

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#define ___app_objc_implementation_symbol_initializer_var(CLASS, TYPE, NAME)\
        __app_objc_var_initializer(CLASS, TYPE, NAME)

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#define ___app_objc_implementation_symbol_initializer_cls(CLASS, RESULT, /*PARAMS*/...)\
        __app_objc_method_initializer(CLASS, ClassMethod, RESULT, __VA_ARGS__)

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#define ___app_objc_implementation_symbol_initializer_obj(CLASS, RESULT, /*PARAMS*/...)\
        __app_objc_method_initializer(CLASS, InstanceMethod, RESULT, __VA_ARGS__)

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#define ___app_objc_implementation_symbol_initializer_end(...) /**/

//------------------------------------------------------------------------------
