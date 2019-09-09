#pragma once
#pragma comment(linker, "/subsystem:windows")
#pragma comment(lib, "kernel32.lib")
#include "app.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//------------------------------------------------------------------------------

app_static_initializer(_app_console_io) {
    extern int32_t __stdcall AttachConsole(uint32_t ProcessId);
    enum { ATTACH_PARENT_PROCESS = -1 };
    if (AttachConsole(ATTACH_PARENT_PROCESS)) {
        freopen("CON", "r", stdin);
        freopen("CON", "w", stdout);
        freopen("CON", "w", stderr);
    }
}

//------------------------------------------------------------------------------

#include "api.inl"
#include "app_cursor.inl"
#include "app_key.inl"
#include "app_update.inl"
#include "app_window.inl"

//------------------------------------------------------------------------------

APP_EXTERN_C_BEGIN

//------------------------------------------------------------------------------

void
app_activate(void) {
    SetForegroundWindow(GetActiveWindow());
}

bool
app_is_active(void) {
    return GetActiveWindow() == GetForegroundWindow();
}

//------------------------------------------------------------------------------

int __stdcall
WinMain(void* Instance, void* Previous, char* CmdLine, int nShowCmd) {
    // puts(__func__);

    extern int* __cdecl __p___argc(void);
    const int argc = *__p___argc();

    extern char*** __cdecl __p___argv(void);
    const char** argv = (const char**)*__p___argv();

    extern const char* __stdcall GetEnvironmentStringsA(void);
    extern BOOL        __stdcall FreeEnvironmentStringsA(const char*);
    const char* const envs = GetEnvironmentStringsA();

    int envc = 0;
    for (const char* env = envs; *env; env += strlen(env) + 1, ++envc);
    const char** const envp = (const char**)calloc(envc + 1, sizeof(void*));
    int envi = 0;
    for (const char* env = envs; *env; env += strlen(env) + 1, ++envi) {
        envp[envi] = env;
    }

    extern int app_main(int, const char*[], const char*[]);
    const int result = app_main(argc, argv, envp);

    free(envp);
    FreeEnvironmentStringsA(envs);

    // printf("result: %i\n", result);
    return result;
}

//------------------------------------------------------------------------------

APP_EXTERN_C_END

//------------------------------------------------------------------------------
