#pragma once
#include "app.inl"

//------------------------------------------------------------------------------

APP_EXTERN_C_BEGIN

//------------------------------------------------------------------------------

static LRESULT __stdcall
_app_wndproc(
    HWND hwnd,
    UINT msg,
    WPARAM wParam,
    LPARAM lParam)
{
    app_window* const window = (app_window*)hwnd;
    switch (msg) {
        case WM_CLOSE: {
            ShowWindow(hwnd, SW_HIDE);
            return 0;
        }
        case WM_CHAR: {
            const char c = wParam & 0xFF;
            _app_key_input_append_char(c);
            break;
        }
        case WM_UNICHAR: {
            const uint32_t u = wParam & 0xFFFFFFFF;
            _app_key_input_append_utf32(u);
            enum { UNICODE_NOCHAR = 65535};
            return wParam == UNICODE_NOCHAR;
        }
        case WM_SETCURSOR: {
            if (app_cursor_is_inside(app_window_get_viewport(window), NULL)) {
                switch (_app_cursor) {
                    case APP_CURSOR_NONE:
                        SetCursor(NULL);
                        return true;
                    case APP_CURSOR_DEFAULT:
                    case APP_CURSOR_ARROW:
                        break;
                    case APP_CURSOR_CROSSHAIR:
                    case APP_CURSOR_TEXT:
                    case APP_CURSOR_LINK:
                    case APP_CURSOR_DRAG_NS:
                    case APP_CURSOR_DRAG_EW:
                        SetCursor(_app_cursor_to_hcursor[_app_cursor]);
                        return true;
                }
            }
            break;
        }
    }
    return DefWindowProcA(hwnd, msg, wParam, lParam);
}

//------------------------------------------------------------------------------

app_window*
app_window_acquire(void) {
    extern void* __stdcall GetModuleHandleA(const char*);
    extern ATOM __stdcall RegisterClassExA(const WNDCLASSEXA*);
    static ATOM wcl = 0;
    if (not wcl) {
        static WNDCLASSEXA wclex = {0};
        wclex.cbSize        = sizeof(WNDCLASSEXA);
        wclex.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
        wclex.lpfnWndProc   = (WNDPROC)_app_wndproc;
        wclex.cbClsExtra    = 0;
        wclex.cbWndExtra    = 0;
        wclex.hInstance     = (HINSTANCE)GetModuleHandleA(NULL);
        wclex.hIcon         = LoadIconA(NULL, (LPCSTR)IDI_APPLICATION);
        wclex.hCursor       = LoadCursorA(NULL, (LPCSTR)IDC_ARROW);
        wclex.hbrBackground = (HBRUSH)(CLR_WINDOW + 1);
        wclex.lpszMenuName  = NULL;
        wclex.lpszClassName = "app_window";
        wcl = RegisterClassExA(&wclex);
    }

    const DWORD style =
        WS_OVERLAPPEDWINDOW |
        WS_CLIPSIBLINGS |
        WS_CLIPCHILDREN |
        WS_SIZEBOX;

    const DWORD exstyle =
        WS_EX_app_window; // show in taskbar

    const POINT origin = {0};
    HMONITOR hmon = MonitorFromPoint(origin, MONITOR_DEFAULTTOPRIMARY);
    MONITORINFO mi = {sizeof(MONITORINFO),0}; GetMonitorInfoA(hmon, &mi);

    const RECT desktop = mi.rcWork;
    int desktop_w = desktop.right - desktop.left;
    int desktop_h = desktop.bottom - desktop.top;

    const HWND hwnd = CreateWindowExA(
        /* dwExStyle    */ exstyle,
        /* lpClassName  */ (LPCSTR)(size_t)wcl,
        /* lpWindowName */ NULL,
        /* dwStyle      */ style,
        /* X            */ desktop_w / 4,
        /* Y            */ desktop_h / 6,
        /* nWidth       */ desktop_w / 2,
        /* nHeight      */ desktop_h / 2,
        /* hWndParent   */ NULL,
        /* hMenu        */ NULL,
        /* hInstance    */ (HINSTANCE)GetModuleHandleA(NULL),
        /* lpParam      */ 0
    );

    return (app_window*)hwnd;
}

void
app_window_release(app_window* const window) {
    assert(window);
    HWND hwnd = (HWND)window;
    DestroyWindow(hwnd);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void
app_window_set_title(app_window* const window, const char* const title) {
    assert(window);
    HWND hwnd = (HWND)window;
    SetWindowTextA(hwnd, title);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void
app_window_set_features(
    app_window* const window,
    const app_window_features features
) {
    assert(window);
    HWND hwnd = (HWND)window;
    DWORD style = 0;

    if (features & APP_WINDOW_FEATURES_CLOSE)
        style |= WS_CAPTION | WS_SYSMENU;
    if (features & APP_WINDOW_FEATURES_MINIMIZE)
        style |= WS_CAPTION | WS_MINIMIZEBOX;
    if (features & APP_WINDOW_FEATURES_RESIZE)
        style |= WS_THICKFRAME | WS_MAXIMIZEBOX;
    if (features & APP_WINDOW_FEATURES_TITLEBAR)
        style |= WS_CAPTION;

    SetWindowLongPtrA(hwnd, GWL_STYLE, (LONG_PTR)style);
    UINT flags =
        SWP_NOMOVE |
        SWP_NOSIZE |
        SWP_NOZORDER |
        SWP_NOREPOSITION |
        SWP_FRAMECHANGED;
    SetWindowPos(hwnd, 0, 0, 0, 0, 0, flags);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

app_rect
app_window_get_frame(app_window* const window) {
    assert(window);
    HWND hwnd = (HWND)window;
    RECT rc;
    GetWindowRect(hwnd, &rc);
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
    HWND hwnd = (HWND)window;
    WINDOWPLACEMENT wpl = {sizeof(WINDOWPLACEMENT)};
    GetWindowPlacement(hwnd, &wpl);
    wpl.rcNormalPosition.left = (LONG)frame.x;
    wpl.rcNormalPosition.top = (LONG)frame.y;
    wpl.rcNormalPosition.right = (LONG)(frame.x + frame.w);
    wpl.rcNormalPosition.bottom = (LONG)(frame.y + frame.h);
    SetWindowPlacement(hwnd, &wpl);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

app_rect
app_window_get_viewport(app_window* const window) {
    assert(window);
    HWND hwnd = (HWND)window;
    RECT rc;
    GetClientRect(hwnd, &rc);
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
    HWND hwnd = (HWND)window;
    const DWORD style = (DWORD)GetWindowLongPtrA(hwnd, GWL_STYLE);
    const DWORD exstyle = (DWORD)GetWindowLongPtrA(hwnd, GWL_EXSTYLE);
    WINDOWPLACEMENT wpl = {sizeof(WINDOWPLACEMENT)};
    GetWindowPlacement(hwnd, &wpl);
    wpl.rcNormalPosition.left = (LONG)viewport.x;
    wpl.rcNormalPosition.top = (LONG)viewport.y;
    wpl.rcNormalPosition.right = (LONG)(viewport.x + viewport.w);
    wpl.rcNormalPosition.bottom = (LONG)(viewport.y + viewport.h);
    AdjustWindowRectEx(&wpl.rcNormalPosition, style, false, exstyle);
    SetWindowPlacement(hwnd, &wpl);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool
app_window_is_active(app_window* window) {
    assert(window);
    HWND hwnd = (HWND)window;
    return hwnd == GetActiveWindow();
}

app_window*
app_window_get_active(void) {
    return (app_window*)GetActiveWindow();
}

void
app_window_activate(app_window* window) {
    assert(window);
    HWND hwnd = (HWND)window;
    if (!IsWindowVisible(hwnd)) {
        ShowWindow(hwnd, SW_SHOWNOACTIVATE);
    }
    SetActiveWindow(hwnd);
    SetForegroundWindow(hwnd);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool
app_window_is_open(app_window* const window) {
    assert(window);
    HWND hwnd = (HWND)window;
    return IsWindowVisible(hwnd);
}

void
app_window_set_open(
    app_window* const window,
    const bool open
) {
    assert(window);
    HWND hwnd = (HWND)window;
    if (open != app_window_is_open(window)) {
        ShowWindow(hwnd, open ? SW_SHOW : SW_HIDE);
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
}

//------------------------------------------------------------------------------

APP_EXTERN_C_END

//------------------------------------------------------------------------------
