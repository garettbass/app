#pragma once
#pragma comment(linker, "/subsystem:windows")
#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#include "app.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//------------------------------------------------------------------------------

APP_EXTERN_C_BEGIN
app_static_initializer(_app_console_io) {
    enum { ATTACH_PARENT_PROCESS = -1 };
    extern int32_t __stdcall AttachConsole(uint32_t ProcessId);
    if (AttachConsole(ATTACH_PARENT_PROCESS)) {
        freopen("CON", "r", stdin);
        freopen("CON", "w", stdout);
        freopen("CON", "w", stderr);
    }
}
APP_EXTERN_C_END

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
    extern struct WND* __stdcall GetActiveWindow(void);
    SetForegroundWindow(GetActiveWindow());
}

bool
app_is_active(void) {
    extern struct WND* __stdcall GetActiveWindow(void);
    extern struct WND* __stdcall GetForegroundWindow(void);
    return GetActiveWindow() == GetForegroundWindow();
}

//------------------------------------------------------------------------------

static inline const char**
_app_alloc_envp(const char* const envs) {
    int n = 0;
    for (const char* e = envs; *e; e += strlen(e) + 1, ++n);
    const char** const envp = (const char**)calloc(n + 1, sizeof(void*));
    int i = 0;
    for (const char* e = envs; *e; e += strlen(e) + 1, ++i) envp[i] = e;
    return envp;
}

//------------------------------------------------------------------------------

extern int app_main(int, const char*[], const char*[]);

int __stdcall
WinMain(void* Instance, void* Previous, char* CmdLine, int nShowCmd) {
    // puts(__func__);

    #ifndef __argc
        // MinGW gcc does not #define __argc (*__p___argc())
        extern int __argc;
    #endif
    const int argc = __argc;

    #ifndef __argv
        // MinGW gcc does not #define __argv (*__p___argv())
        extern const char** __argv;
    #endif
    const char** argv = (const char**)__argv;

    extern const char* __stdcall GetEnvironmentStringsA(void);
    extern BOOL        __stdcall FreeEnvironmentStringsA(const char*);
    const char*  const envs = GetEnvironmentStringsA();
    const char** const envp = _app_alloc_envp(envs);

    const int result = app_main(argc, argv, envp);

    free(envp);
    FreeEnvironmentStringsA(envs);

    // printf("result: %i\n", result);
    return result;
}

//------------------------------------------------------------------------------

APP_EXTERN_C_END

//------------------------------------------------------------------------------
