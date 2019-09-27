#pragma once
#include "../app.inl"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//------------------------------------------------------------------------------

APP_EXTERN_C_BEGIN
app_static_initializer(_app_console_io) {
    app_dll* const kernel32 = app_dll_acquire("kernel32.dll");

    typedef int (__stdcall * attach_console_t)(unsigned);
    attach_console_t const attach_console = (
        (attach_console_t)
        app_dll_find_symbol(kernel32, "AttachConsole")
    );
    enum { _APP_ATTACH_PARENT_PROCESS = -1 };
    if (attach_console(_APP_ATTACH_PARENT_PROCESS)) {
        freopen("CON", "r", stdin);
        freopen("CON", "w", stdout);
        freopen("CON", "w", stderr);
    }

    typedef int (__stdcall * set_console_output_cp_t)(unsigned);
    set_console_output_cp_t const set_console_output_cp = (
        (set_console_output_cp_t)
        app_dll_find_symbol(kernel32, "SetConsoleOutputCP")
    );
    enum { _APP_CP_UTF8 = 65001 };
    set_console_output_cp(_APP_CP_UTF8);
}
APP_EXTERN_C_END

//------------------------------------------------------------------------------

#include "api.inl"
#include "cursor.inl"
#include "key.inl"
#include "update.inl"
#include "window.inl"

//------------------------------------------------------------------------------

APP_EXTERN_C_BEGIN

//------------------------------------------------------------------------------

app_parameters _app_parameters;

app_parameters
app_get_parameters(void) {
    return _app_parameters;
}

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

#if APP_COMPILER_MICROSOFT
#pragma comment(linker, "/subsystem:windows")
#endif

#ifdef WINAPI
int __stdcall WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
#else
int __stdcall WinMain(void* hInstance, void* hPrevInstance, char* lpCmdLine, int nShowCmd)
#endif
{
    (void)hInstance;
    (void)hPrevInstance;
    (void)lpCmdLine;
    (void)nShowCmd;
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
        _APP_IDC_ARROW       = 32512,
        _APP_IDC_CROSS       = 32515,
        _APP_IDC_IBEAM       = 32513,
        _APP_IDC_HAND        = 32649,
        _APP_IDC_SIZENS      = 32645,
        _APP_IDC_SIZEWE      = 32644,
    };
    _app_hcursor[APP_CURSOR_DEFAULT]   =
    _app_hcursor[APP_CURSOR_ARROW]     = _app_LoadCursorA(NULL, (const char*)(size_t)_APP_IDC_ARROW);
    _app_hcursor[APP_CURSOR_CROSSHAIR] = _app_LoadCursorA(NULL, (const char*)(size_t)_APP_IDC_CROSS);
    _app_hcursor[APP_CURSOR_TEXT]      = _app_LoadCursorA(NULL, (const char*)(size_t)_APP_IDC_IBEAM);
    _app_hcursor[APP_CURSOR_LINK]      = _app_LoadCursorA(NULL, (const char*)(size_t)_APP_IDC_HAND);
    _app_hcursor[APP_CURSOR_DRAG_NS]   = _app_LoadCursorA(NULL, (const char*)(size_t)_APP_IDC_SIZENS);
    _app_hcursor[APP_CURSOR_DRAG_EW]   = _app_LoadCursorA(NULL, (const char*)(size_t)_APP_IDC_SIZEWE);

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

    _app_parameters = (app_parameters){ argc, argv, envp };
    const int result = app_main();

    free(envp);
    _app_FreeEnvironmentStringsA(envs);

    // printf("result: %i\n", result);
    return result;
}

//------------------------------------------------------------------------------

APP_EXTERN_C_END

//------------------------------------------------------------------------------
