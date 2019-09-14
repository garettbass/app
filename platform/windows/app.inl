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
    enum { _APP_ATTACH_PARENT_PROCESS = -1 };
    typedef int (__stdcall * attach_console_t)(unsigned);
    app_dll* const kernel32 = app_dll_acquire("kernel32.dll");
    attach_console_t const attach_console = (
        (attach_console_t)app_dll_find_symbol(kernel32, "AttachConsole")
    );
    if (attach_console(_APP_ATTACH_PARENT_PROCESS)) {
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
    _app_SetForegroundWindow(_app_GetActiveWindow());
}

bool
app_is_active(void) {
    return _app_GetActiveWindow() == _app_GetForegroundWindow();
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

#ifdef WINAPI
int __stdcall WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
#else
int __stdcall WinMain(void* Instance, void* Previous, char* CmdLine, int nShowCmd)
#endif
{
    app_dll* const shcore = app_dll_acquire("shcore.dll");
    if (shcore) {
        typedef unsigned (__stdcall * set_process_dpi_awareness_t)(unsigned);
        set_process_dpi_awareness_t const set_process_dpi_awareness =
            (set_process_dpi_awareness_t)app_dll_find_symbol(shcore, "SetProcessDpiAwareness");
        if (set_process_dpi_awareness) {
            enum { _APP_PDA_MONITOR_DPI_AWARE = 2 };
            if (set_process_dpi_awareness(_APP_PDA_MONITOR_DPI_AWARE) == 0) {
                puts("SetProcessDpiAwareness(PDA_MONITOR_DPI_AWARE): OK");
            }
        }
    }

    enum {
        _app_IDC_ARROW       = 32512,
        _app_IDC_CROSS       = 32515,
        _app_IDC_IBEAM       = 32513,
        _app_IDC_HAND        = 32649,
        _app_IDC_SIZENS      = 32645,
        _app_IDC_SIZEWE      = 32644,
    };
    _app_hcursor[APP_CURSOR_DEFAULT]   =
    _app_hcursor[APP_CURSOR_ARROW]     = _app_LoadCursorA(NULL, (const char*)(size_t)_app_IDC_ARROW);
    _app_hcursor[APP_CURSOR_CROSSHAIR] = _app_LoadCursorA(NULL, (const char*)(size_t)_app_IDC_CROSS);
    _app_hcursor[APP_CURSOR_TEXT]      = _app_LoadCursorA(NULL, (const char*)(size_t)_app_IDC_IBEAM);
    _app_hcursor[APP_CURSOR_LINK]      = _app_LoadCursorA(NULL, (const char*)(size_t)_app_IDC_HAND);
    _app_hcursor[APP_CURSOR_DRAG_NS]   = _app_LoadCursorA(NULL, (const char*)(size_t)_app_IDC_SIZENS);
    _app_hcursor[APP_CURSOR_DRAG_EW]   = _app_LoadCursorA(NULL, (const char*)(size_t)_app_IDC_SIZEWE);

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

    const char*  const envs = _app_GetEnvironmentStringsA();
    const char** const envp = _app_alloc_envp(envs);

    const int result = app_main(argc, argv, envp);

    free(envp);
    _app_FreeEnvironmentStringsA(envs);

    // printf("result: %i\n", result);
    return result;
}

//------------------------------------------------------------------------------

APP_EXTERN_C_END

//------------------------------------------------------------------------------
