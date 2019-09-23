#pragma once
#include "platform.h"
#include <assert.h>
#include <stdio.h>

//------------------------------------------------------------------------------

APP_EXTERN_C_BEGIN

//------------------------------------------------------------------------------

typedef struct app_dll app_dll;

app_dll*
app_dll_acquire(const char* path);

void
app_dll_release(app_dll* dll);

void*
app_dll_find_symbol(app_dll* dll, const char* symbol);

//------------------------------------------------------------------------------

APP_EXTERN_C_END

//------------------------------------------------------------------------------

#define app_dll(DLL, PATH)\
        APP_EXTERN_C_BEGIN\
        app_dll* DLL(void) {\
            static app_dll* _##DLL = NULL;\
            if (_##DLL == NULL) {\
                _##DLL = app_dll_acquire(PATH);\
                APP_DEBUG_ONLY(printf("%s @ %p\n", PATH, (void*)_##DLL));\
                assert(_##DLL != NULL);\
            }\
            return _##DLL;\
        }\
        APP_EXTERN_C_END

//------------------------------------------------------------------------------

#define app_dllimport(DLL, /*SYMBOLS*/...)\
        _app_dllimport(__COUNTER__, DLL, __VA_ARGS__)

#define _app_dllimport(COUNTER, DLL, /*SYMBOLS*/...)\
        __app_dllimport(COUNTER, DLL, __VA_ARGS__)

#define __app_dllimport(COUNTER, DLL, /*SYMBOLS*/...)\
        _app_dllimport_declarations(__VA_ARGS__)\
        app_static_initializer(_app_dllimport_initializer_##DLL##_##COUNTER) {\
            app_dll* const _dll = DLL();\
            _app_dllimport_initializers(__VA_ARGS__)\
        }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#define _app_dllimport_declarations(/*SYMBOLS*/...)\
        APP_VA_APPLY(_app_dllimport_declaration, __VA_ARGS__)

#define _app_dllimport_declaration(SYMBOL)\
        APP_DEFER(APP_CONCAT(_app_dllimport_declaration,_##SYMBOL))

#define _app_dllimport_declaration_

#define _app_dllimport_declaration_cdecl(RESULT, NAME, PARAMS)\
        _app_dllimport_declaration_function(RESULT, __cdecl, NAME, PARAMS)

#define _app_dllimport_declaration_fastcall(RESULT, NAME, PARAMS)\
        _app_dllimport_declaration_function(RESULT, __fastcall, NAME, PARAMS)

#define _app_dllimport_declaration_stdcall(RESULT, NAME, PARAMS)\
        _app_dllimport_declaration_function(RESULT, __stdcall, NAME, PARAMS)

#define _app_dllimport_declaration_thiscall(RESULT, NAME, PARAMS)\
        _app_dllimport_declaration_function(RESULT, __thiscall, NAME, PARAMS)

#define _app_dllimport_declaration_vectorcall(RESULT, NAME, PARAMS)\
        _app_dllimport_declaration_function(RESULT, __vectorcall, NAME, PARAMS)

#define _app_dllimport_declaration_function(RESULT, CALLTYPE, NAME, PARAMS)\
        typedef RESULT (CALLTYPE * NAME##_t)PARAMS;\
        static NAME##_t NAME = NULL;

#define _app_dllimport_declaration_cdecl_alias(RESULT, ALIAS, NAME, PARAMS)\
        _app_dllimport_declaration_function_alias(RESULT, __cdecl, ALIAS, NAME, PARAMS)

#define _app_dllimport_declaration_fastcall_alias(RESULT, ALIAS, NAME, PARAMS)\
        _app_dllimport_declaration_function_alias(RESULT, __fastcall, ALIAS, NAME, PARAMS)

#define _app_dllimport_declaration_stdcall_alias(RESULT, ALIAS, NAME, PARAMS)\
        _app_dllimport_declaration_function_alias(RESULT, __stdcall, ALIAS, NAME, PARAMS)

#define _app_dllimport_declaration_thiscall_alias(RESULT, ALIAS, NAME, PARAMS)\
        _app_dllimport_declaration_function_alias(RESULT, __thiscall, ALIAS, NAME, PARAMS)

#define _app_dllimport_declaration_vectorcall_alias(RESULT, ALIAS, NAME, PARAMS)\
        _app_dllimport_declaration_function_alias(RESULT, __vectorcall, ALIAS, NAME, PARAMS)

#define _app_dllimport_declaration_function_alias(RESULT, CALLTYPE, ALIAS, NAME, PARAMS)\
        typedef RESULT (CALLTYPE * ALIAS##_t)PARAMS;\
        static ALIAS##_t ALIAS = NULL;

#define _app_dllimport_declaration_pointer(TYPE, NAME)\
        static TYPE NAME = NULL;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#define _app_dllimport_initializers(/*SYMBOLS*/...)\
        APP_VA_APPLY(_app_dllimport_initializer, __VA_ARGS__)

#define _app_dllimport_initializer(SYMBOL)\
        APP_DEFER(APP_CONCAT(_app_dllimport_initializer,_##SYMBOL))

#define _app_dllimport_initializer_

#define _app_dllimport_initializer_cdecl(RESULT, NAME, PARAMS)\
        _app_dllimport_initializer_function(RESULT, __cdecl, NAME, PARAMS)

#define _app_dllimport_initializer_fastcall(RESULT, NAME, PARAMS)\
        _app_dllimport_initializer_function(RESULT, __fastcall, NAME, PARAMS)

#define _app_dllimport_initializer_stdcall(RESULT, NAME, PARAMS)\
        _app_dllimport_initializer_function(RESULT, __stdcall, NAME, PARAMS)

#define _app_dllimport_initializer_thiscall(RESULT, NAME, PARAMS)\
        _app_dllimport_initializer_function(RESULT, __thiscall, NAME, PARAMS)

#define _app_dllimport_initializer_vectorcall(RESULT, NAME, PARAMS)\
        _app_dllimport_initializer_function(RESULT, __vectorcall, NAME, PARAMS)

#define _app_dllimport_initializer_function(RESULT, CALLTYPE, NAME, PARAMS)\
        assert(NAME == NULL);\
        NAME = (NAME##_t)app_dll_find_symbol(_dll, #NAME);\
        APP_DEBUG_ONLY(printf("    %s @ %p\n", #NAME, NAME));\
        assert(NAME);\

#define _app_dllimport_initializer_cdecl_alias(RESULT, ALIAS, NAME, PARAMS)\
        _app_dllimport_initializer_function_alias(RESULT, __cdecl, ALIAS, NAME, PARAMS)

#define _app_dllimport_initializer_fastcall_alias(RESULT, ALIAS, NAME, PARAMS)\
        _app_dllimport_initializer_function_alias(RESULT, __fastcall, ALIAS, NAME, PARAMS)

#define _app_dllimport_initializer_stdcall_alias(RESULT, ALIAS, NAME, PARAMS)\
        _app_dllimport_initializer_function_alias(RESULT, __stdcall, ALIAS, NAME, PARAMS)

#define _app_dllimport_initializer_thiscall_alias(RESULT, ALIAS, NAME, PARAMS)\
        _app_dllimport_initializer_function_alias(RESULT, __thiscall, ALIAS, NAME, PARAMS)

#define _app_dllimport_initializer_vectorcall_alias(RESULT, ALIAS, NAME, PARAMS)\
        _app_dllimport_initializer_function_alias(RESULT, __vectorcall, ALIAS, NAME, PARAMS)

#define _app_dllimport_initializer_function_alias(RESULT, CALLTYPE, ALIAS, NAME, PARAMS)\
        assert(ALIAS == NULL);\
        ALIAS = (ALIAS##_t)app_dll_find_symbol(_dll, #NAME);\
        APP_DEBUG_ONLY(printf("    %s @ %p\n", #ALIAS, ALIAS));\
        assert(ALIAS);\

#define _app_dllimport_initializer_pointer(TYPE, NAME)\
        assert(NAME == NULL);\
        NAME = (TYPE)*(void**)app_dll_find_symbol(_dll, #NAME);\
        APP_DEBUG_ONLY(printf("    %s %s @ %p\n", #TYPE, #NAME, NAME));\
        assert(NAME);\

//------------------------------------------------------------------------------
