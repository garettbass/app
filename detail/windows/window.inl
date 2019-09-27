#pragma once
#include "app.inl"

//------------------------------------------------------------------------------

APP_EXTERN_C_BEGIN

//------------------------------------------------------------------------------

static void* _app_hcursor[] = {
    /* APP_CURSOR_NONE      */ NULL,
    /* APP_CURSOR_DEFAULT   */ NULL,
    /* APP_CURSOR_ARROW     */ NULL,
    /* APP_CURSOR_CROSSHAIR */ NULL,
    /* APP_CURSOR_TEXT      */ NULL,
    /* APP_CURSOR_LINK      */ NULL,
    /* APP_CURSOR_DRAG_NS   */ NULL,
    /* APP_CURSOR_DRAG_EW   */ NULL,
};

static size_t __stdcall
_app_wndproc(
    app_window* const window,
    unsigned    const msg,
    size_t      const wParam,
    size_t      const lParam
) {
    switch (msg) {
        case _APP_WM_CLOSE: {
            enum { _APP_SW_HIDE = 0 };
            _app_ShowWindow(window, _APP_SW_HIDE);
            return 0;
        }
        case _APP_WM_CHAR: {
            uint16_t utf16[2] = { (uint16_t)(wParam & 0xFFFF) };
            char utf8[8] = {0};
            enum { _APP_CP_UTF8 = 65001 };
            _app_WideCharToMultiByte(_APP_CP_UTF8, 0, utf16, 1, utf8, 7, NULL, NULL);
            if (utf8[0] == '\r') utf8[0] = '\n';
            _app_text_input_append_string(utf8);
            break;
        }
        case _APP_WM_UNICHAR: {
            const uint32_t u = wParam & 0xFFFFFFFF;
            _app_text_input_append_utf32(u);
            enum { _APP_UNICODE_NOCHAR = 65535};
            return wParam == _APP_UNICODE_NOCHAR;
        }
        case _APP_WM_SETCURSOR: {
            if (app_cursor_is_inside(app_window_get_viewport(window), NULL)) {
                switch (_app_cursor) {
                    case APP_CURSOR_NONE:
                        _app_SetCursor(NULL);
                        return true;
                    case APP_CURSOR_DEFAULT:
                    case APP_CURSOR_ARROW:
                        break;
                    case APP_CURSOR_CROSSHAIR:
                    case APP_CURSOR_TEXT:
                    case APP_CURSOR_LINK:
                    case APP_CURSOR_DRAG_NS:
                    case APP_CURSOR_DRAG_EW:
                        _app_SetCursor(_app_hcursor[_app_cursor]);
                        return true;
                }
            }
            break;
        }
    }
    return _app_DefWindowProcA(window, msg, wParam, lParam);
}

//------------------------------------------------------------------------------

app_window*
app_window_acquire(void) {
    void* const hInstance = _app_GetModuleHandleA(NULL);
    static uint16_t wndClassAtom = 0;
    if (not wndClassAtom) {
        enum {
            _APP_CS_VREDRAW      = 0x01,
            _APP_CS_HREDRAW      = 0x02,
            _APP_CS_OWNDC        = 0x20,
            _APP_CLR_WINDOW      = 5,
            _APP_IDI_APPLICATION = 32512,
        };
        static struct {
            unsigned    cbSize;
            unsigned    style;
            void*       lpfnWndProc;
            int         cbClsExtra;
            int         cbWndExtra;
            void*       hInstance;
            void*       hIcon;
            void*       hCursor;
            void*       hbrBackground;
            const char* lpszMenuName;
            const char* lpszClassName;
            void*       hIconSm;
        } wndClassExA;
        wndClassExA.cbSize        = sizeof(wndClassExA);
        wndClassExA.style         = _APP_CS_HREDRAW | _APP_CS_VREDRAW | _APP_CS_OWNDC;
        wndClassExA.lpfnWndProc   = (void*)_app_wndproc;
        wndClassExA.cbClsExtra    = 0;
        wndClassExA.cbWndExtra    = 0;
        wndClassExA.hInstance     = hInstance;
        wndClassExA.hIcon         = _app_LoadIconA(NULL, (const char*)(size_t)_APP_IDI_APPLICATION);
        wndClassExA.hCursor       = _app_hcursor[APP_CURSOR_ARROW];
        wndClassExA.hbrBackground = (void*)(size_t)(_APP_CLR_WINDOW + 1);
        wndClassExA.lpszMenuName  = NULL;
        wndClassExA.lpszClassName = "app_window";
        wndClassExA.hIconSm       = _app_LoadIconA(NULL, (const char*)(size_t)_APP_IDI_APPLICATION);
        wndClassAtom = _app_RegisterClassExA(&wndClassExA);
    }

    enum {
        _APP_WS_CAPTION      = 0x00C00000L,
        _APP_WS_CLIPCHILDREN = 0x02000000L,
        _APP_WS_CLIPSIBLINGS = 0x04000000L,
        _APP_WS_MAXIMIZEBOX  = 0x00010000L,
        _APP_WS_MINIMIZEBOX  = 0x00020000L,
        _APP_WS_SIZEBOX      = 0x00040000L,
        _APP_WS_SYSMENU      = 0x00080000L,
        _APP_WS_THICKFRAME   = 0x00040000L,

    };
    const unsigned style =
        _APP_WS_CAPTION |
        _APP_WS_CLIPSIBLINGS |
        _APP_WS_CLIPCHILDREN |
        _APP_WS_MAXIMIZEBOX |
        _APP_WS_MINIMIZEBOX |
        _APP_WS_SIZEBOX |
        _APP_WS_SYSMENU |
        _APP_WS_THICKFRAME;

    enum { _APP_WS_EX_APPWINDOW = 0x00040000L };
    const unsigned exstyle = _APP_WS_EX_APPWINDOW; // show in taskbar

    typedef struct RECT { int left, top, right, bottom; } RECT;
    const RECT origin = {0,0,0,0};
    enum { _APP_MONITOR_DEFAULTTOPRIMARY = 1 };
    void* const hmon = _app_MonitorFromRect(&origin, _APP_MONITOR_DEFAULTTOPRIMARY);
    struct {
        unsigned cbSize;
        RECT     rcMonitor;
        RECT     rcWork;
        unsigned dwFlags;
    } mi = {sizeof(mi),{0,0,0,0},{0,0,0,0},0};
    _app_GetMonitorInfoA(hmon, &mi);

    const RECT desktop   = mi.rcWork;
    const int  desktop_w = desktop.right - desktop.left;
    const int  desktop_h = desktop.bottom - desktop.top;

    void* const hWnd = _app_CreateWindowExA(
        /* dwExStyle    */ exstyle,
        /* lpClassName  */ (const char*)(size_t)wndClassAtom,
        /* lpWindowName */ NULL,
        /* dwStyle      */ style,
        /* X            */ desktop_w / 4,
        /* Y            */ desktop_h / 6,
        /* nWidth       */ desktop_w / 2,
        /* nHeight      */ desktop_h / 2,
        /* hWndParent   */ NULL,
        /* hMenu        */ NULL,
        /* hInstance    */ hInstance,
        /* lpParam      */ 0
    );

    return (app_window*)hWnd;
}

void
app_window_release(app_window* const window) {
    assert(window);
    _app_DestroyWindow(window);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void
app_window_set_title(app_window* const window, const char* const title) {
    assert(window);
    _app_SetWindowTextA(window, title);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void
app_window_set_features(
    app_window* const window,
    const app_window_features features
) {
    assert(window);
    unsigned style = 0;

    enum {
        _APP_WS_CAPTION          = 0x00C00000L,
        _APP_WS_MAXIMIZEBOX      = 0x00010000L,
        _APP_WS_MINIMIZEBOX      = 0x00020000L,
        _APP_WS_SYSMENU          = 0x00080000L,
        _APP_WS_THICKFRAME       = 0x00040000L,
    };
    if (features & APP_WINDOW_FEATURES_CLOSE)
        style |= _APP_WS_CAPTION | _APP_WS_SYSMENU;
    if (features & APP_WINDOW_FEATURES_MINIMIZE)
        style |= _APP_WS_CAPTION | _APP_WS_MINIMIZEBOX;
    if (features & APP_WINDOW_FEATURES_RESIZE)
        style |= _APP_WS_THICKFRAME | _APP_WS_MAXIMIZEBOX;
    if (features & APP_WINDOW_FEATURES_TITLEBAR)
        style |= _APP_WS_CAPTION;

    enum { _APP_GWL_STYLE = -16 };
    _app_SetWindowLongPtrA(window, _APP_GWL_STYLE, style);
    enum {
        _APP_SWP_NOMOVE         = 0x0002,
        _APP_SWP_NOSIZE         = 0x0001,
        _APP_SWP_NOZORDER       = 0x0004,
        _APP_SWP_FRAMECHANGED   = 0x0020,
        _APP_SWP_NOREPOSITION   = 0x0200,
    };
    const unsigned flags =
        _APP_SWP_NOMOVE |
        _APP_SWP_NOSIZE |
        _APP_SWP_NOZORDER |
        _APP_SWP_FRAMECHANGED |
        _APP_SWP_NOREPOSITION;
    _app_SetWindowPos(window, 0, 0, 0, 0, 0, flags);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

app_rect
app_window_get_frame(app_window* const window) {
    assert(window);
    struct { int left, top, right, bottom; } rc;
    _app_GetWindowRect(window, &rc);
    app_rect frame;
    frame.x = rc.left;
    frame.y = rc.top;
    frame.w = rc.right - rc.left;
    frame.h = rc.bottom - rc.top;
    return frame;
}

void
app_window_set_frame(app_window* const window, app_rect frame) {
    assert(window);
    typedef struct POINT { int x, y; } POINT;
    typedef struct RECT { int left, top, right, bottom; } RECT;
    struct {
        unsigned cbSize;
        unsigned flags;
        unsigned showCmd;
        POINT    rcMinPosition;
        POINT    rcMaxPosition;
        RECT     rcNormalPosition;
    } wpl = {sizeof(wpl),0,0,{0,0},{0,0},{0,0,0,0}};
    _app_GetWindowPlacement(window, &wpl);
    wpl.rcNormalPosition.left = (int)frame.x;
    wpl.rcNormalPosition.top = (int)frame.y;
    wpl.rcNormalPosition.right = (int)(frame.x + frame.w);
    wpl.rcNormalPosition.bottom = (int)(frame.y + frame.h);
    _app_SetWindowPlacement(window, &wpl);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

app_rect
app_window_get_viewport(app_window* const window) {
    assert(window);
    struct { int left, top, right, bottom; } rc;
    _app_GetClientRect(window, &rc);
    app_rect viewport;
    viewport.x = rc.left;
    viewport.y = rc.top;
    viewport.w = rc.right - rc.left;
    viewport.h = rc.bottom - rc.top;
    return viewport;
}

void
app_window_set_viewport(app_window* const window, app_rect viewport) {
    assert(window);
    enum { _APP_GWL_STYLE = -16, _APP_GWL_EXSTYLE = -20 };
    const unsigned style = (unsigned)_app_GetWindowLongPtrA(window, _APP_GWL_STYLE);
    const unsigned exstyle = (unsigned)_app_GetWindowLongPtrA(window, _APP_GWL_EXSTYLE);
    typedef struct POINT { int x, y; } POINT;
    typedef struct RECT { int left, top, right, bottom; } RECT;
    struct {
        unsigned cbSize;
        unsigned flags;
        unsigned showCmd;
        POINT    rcMinPosition;
        POINT    rcMaxPosition;
        RECT     rcNormalPosition;
    } wpl = {sizeof(wpl),0,0,{0,0},{0,0},{0,0,0,0}};
    _app_GetWindowPlacement(window, &wpl);
    wpl.rcNormalPosition.left = (int)viewport.x;
    wpl.rcNormalPosition.top = (int)viewport.y;
    wpl.rcNormalPosition.right = (int)(viewport.x + viewport.w);
    wpl.rcNormalPosition.bottom = (int)(viewport.y + viewport.h);
    _app_AdjustWindowRectEx(&wpl.rcNormalPosition, style, false, exstyle);
    _app_SetWindowPlacement(window, &wpl);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool
app_window_is_active(app_window* window) {
    return _app_GetActiveWindow() == window;
}

app_window*
app_window_get_active(void) {
    return (app_window*)_app_GetActiveWindow();
}

void
app_window_activate(app_window* window) {
    assert(window);
    if (!_app_IsWindowVisible(window)) {
        enum { _APP_SW_SHOWNOACTIVATE = 4 };
        _app_ShowWindow(window, _APP_SW_SHOWNOACTIVATE);
    }
    _app_SetActiveWindow(window);
    _app_SetForegroundWindow(window);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool
app_window_is_open(app_window* const window) {
    assert(window);
    return _app_IsWindowVisible(window);
}

void
app_window_set_open(
    app_window* const window,
    const bool open
) {
    assert(window);
    if (app_window_is_open(window) != open) {
        enum { _APP_SW_HIDE = 0, _APP_SW_SHOW = 5 };
        _app_ShowWindow(window, open ? _APP_SW_SHOW : _APP_SW_HIDE);
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool
app_window_is_fullscreen(app_window* window) {
    assert(window);
    assert(false);
    return false;
}

void
app_window_set_fullscreen(app_window* window, bool fullscreen) {
    assert(window);
    assert(false);
    (void)fullscreen;
}

//------------------------------------------------------------------------------

APP_EXTERN_C_END

//------------------------------------------------------------------------------
