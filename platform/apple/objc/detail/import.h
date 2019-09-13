#pragma once

//------------------------------------------------------------------------------

#define __app_objc_import(FRAMEWORK, /*SYMBOLS*/...)\
        __app_objc_symbol_declarations(__VA_ARGS__)\
        APP_EXTERN_C_BEGIN\
        __attribute__((constructor)) static inline void\
        _app_objc_concat_2(__app_objc_framework_symbols_initializer_##FRAMEWORK##_,__COUNTER__)(void) {\
            extern void* dlsym(void*,const char*);\
            assert(FRAMEWORK);\
            void* const framework = FRAMEWORK;\
            __app_objc_symbol_initializers(__VA_ARGS__)\
        }\
        APP_EXTERN_C_END\
        /**/

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#define __app_objc_symbol_declarations(/*SYMBOLS*/...)\
        __app_objc_map(__app_objc_symbol_declaration, __VA_ARGS__)

#define __app_objc_symbol_declaration(SYMBOL)\
        __app_objc_defer(_app_objc_concat_2(__app_objc_symbol_declaration,_##SYMBOL))

#define __app_objc_symbol_declaration_function(RESULT, NAME, PARAMS)\
        typedef RESULT (*NAME##_t)PARAMS;\
        static NAME##_t NAME = NULL;\
        /**/

#define __app_objc_symbol_declaration_function_alias(RESULT, ALIAS, NAME, PARAMS)\
        typedef RESULT (*ALIAS##_t)PARAMS;\
        static ALIAS##_t ALIAS = NULL;\
        /**/

#define __app_objc_symbol_declaration_pointer(TYPE, NAME)\
        static TYPE NAME = NULL;\
        /**/

#define __app_objc_symbol_declaration_

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#define __app_objc_symbol_initializers(/*SYMBOLS*/...)\
        __app_objc_map(__app_objc_symbol_initializer, __VA_ARGS__)

#define __app_objc_symbol_initializer(SYMBOL)\
        __app_objc_defer(_app_objc_concat_2(__app_objc_symbol_initializer,_##SYMBOL))

#define __app_objc_symbol_initializer_function(RESULT, NAME, PARAMS)\
        assert(NAME == NULL);\
        NAME = (NAME##_t)dlsym(framework, #NAME);\
        assert(NAME);\
        /**/

#define __app_objc_symbol_initializer_function_alias(RESULT, ALIAS, NAME, PARAMS)\
        assert(ALIAS == NULL);\
        ALIAS = (ALIAS##_t)dlsym(framework, #NAME);\
        assert(ALIAS);\
        /**/

#define __app_objc_symbol_initializer_pointer(TYPE, NAME)\
        assert(NAME == NULL);\
        NAME = (TYPE)*(void**)dlsym(framework, #NAME);\
        assert(NAME);\
        /**/

#define __app_objc_symbol_initializer_
