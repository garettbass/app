#pragma once
#include "../dll.h"
#include <assert.h>
#include <stdio.h>

//------------------------------------------------------------------------------

APP_EXTERN_C_BEGIN

//------------------------------------------------------------------------------

app_dll*
app_dll_acquire(const char* path) {
    assert(path);
    assert(path[0]);
    #if APP_OS_MICROSOFT
        extern void* __stdcall LoadLibraryA(const char*);
        return (app_dll*)LoadLibraryA(path);
    #else
        enum { RTLD_LAZY = 0x1, RTLD_LOCAL = 0x4 };
        extern void* dlopen(const char*, int);
        return (app_dll*)dlopen(path, RTLD_LAZY | RTLD_LOCAL);
    #endif
}

void
app_dll_release(app_dll* dll) {
    assert(dll);
    #if APP_OS_MICROSOFT
        extern int __stdcall FreeLibrary(void*);
        FreeLibrary(dll);
    #else
        extern int dlclose(void*);
        dlclose(dll);
    #endif
}

void*
app_dll_find_symbol(app_dll* dll, const char* symbol) {
    assert(dll);
    assert(symbol);
    assert(symbol[0]);
    #if APP_OS_MICROSOFT
        extern void* __stdcall GetProcAddress(void*,const char*);
        if (dll == NULL) {
            extern void* __stdcall GetModuleHandleA(const char*);
            dll = (app_dll*)GetModuleHandleA(NULL);
        }
        return GetProcAddress(dll, symbol);
    #else
        extern void* dlsym(void*,const char*);
        return dlsym(dll, symbol);
    #endif
}

//------------------------------------------------------------------------------

APP_EXTERN_C_END

//------------------------------------------------------------------------------
