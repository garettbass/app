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
        #ifndef LoadLibrary
            extern void* __stdcall LoadLibraryA(const char*);
        #endif
        typedef void* (__stdcall * load_library_t)(const char*);
        const load_library_t load_library = (load_library_t)LoadLibraryA;
        return (app_dll*)load_library(path);
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
        #ifndef LoadLibrary
            extern int __stdcall FreeLibrary(void*);
        #endif
        typedef int (__stdcall * free_library_t)(void*);
        const free_library_t free_library = (free_library_t)FreeLibrary;
        free_library(dll);
    #else
        extern int dlclose(void*);
        dlclose(dll);
    #endif
}

void*
app_dll_find_symbol(app_dll* dll, const char* symbol) {
    assert(symbol);
    assert(symbol[0]);
    #if APP_OS_MICROSOFT
        #ifndef LoadLibrary
            extern void* __stdcall GetProcAddress(void*,const char*);
            extern void* __stdcall GetModuleHandleA(const char*);
        #endif
        typedef void* (__stdcall * get_proc_address_t)(void*, const char*);
        typedef void* (__stdcall * get_module_handle_t)(const char*);
        const get_proc_address_t get_proc_address = (get_proc_address_t)GetProcAddress;
        const get_module_handle_t get_module_handle = (get_module_handle_t)GetModuleHandleA;
        if (dll == NULL) {
            dll = (app_dll*)get_module_handle(NULL);
        }
        return get_proc_address(dll, symbol);
    #else
        extern void* dlsym(void*,const char*);
        return dlsym(dll, symbol);
    #endif
}

//------------------------------------------------------------------------------

APP_EXTERN_C_END

//------------------------------------------------------------------------------
