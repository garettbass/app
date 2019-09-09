#pragma once
#include "app.inl"

//------------------------------------------------------------------------------

APP_EXTERN_C_BEGIN

//------------------------------------------------------------------------------

static app_cursor _app_cursor = APP_CURSOR_DEFAULT;

static HCURSOR _app_cursor_to_hcursor[] = {
    /* APP_CURSOR_NONE      */ NULL,
    /* APP_CURSOR_DEFAULT   */ NULL,
    /* APP_CURSOR_ARROW     */ NULL,
    /* APP_CURSOR_CROSSHAIR */ NULL,
    /* APP_CURSOR_TEXT      */ NULL,
    /* APP_CURSOR_LINK      */ NULL,
    /* APP_CURSOR_DRAG_NS   */ NULL,
    /* APP_CURSOR_DRAG_EW   */ NULL,
};

app_static_initializer(_app_cursor_to_hcursor_load) {
    _app_cursor_to_hcursor[APP_CURSOR_DEFAULT] =
    _app_cursor_to_hcursor[APP_CURSOR_ARROW] =
        LoadCursorA(NULL, (LPCSTR)IDC_ARROW);
    _app_cursor_to_hcursor[APP_CURSOR_CROSSHAIR] =
        LoadCursorA(NULL, (LPCSTR)IDC_CROSS);
    _app_cursor_to_hcursor[APP_CURSOR_TEXT] =
        LoadCursorA(NULL, (LPCSTR)IDC_IBEAM);
    _app_cursor_to_hcursor[APP_CURSOR_LINK] =
        LoadCursorA(NULL, (LPCSTR)IDC_HAND);
    _app_cursor_to_hcursor[APP_CURSOR_DRAG_NS] =
        LoadCursorA(NULL, (LPCSTR)IDC_SIZENS);
    _app_cursor_to_hcursor[APP_CURSOR_DRAG_EW] =
        LoadCursorA(NULL, (LPCSTR)IDC_SIZEWE);
}

void
app_cursor_set(app_cursor cursor) {
    _app_cursor = cursor;
}

//------------------------------------------------------------------------------

app_point
app_cursor_get_position(app_window* /*optional*/ window) {
    POINT point = {0};
    GetCursorPos(&point);
    app_point position = (app_point){ (float)point.x, (float)point.y };
    if (window) {
        app_rect const viewport = app_window_get_viewport(window);
        position.x -= viewport.x;
        position.y -= viewport.y;
    }
    return position;
}

void
app_cursor_set_position(app_point position, app_window* /*optional*/ window) {
    // TODO
    assert(false);
}

//------------------------------------------------------------------------------

bool
app_cursor_is_locked(void) {
    // TODO
    assert(false);
    return false;
}

void
app_cursor_set_locked(bool locked) {
    // TODO
    assert(false);
}

//------------------------------------------------------------------------------

APP_EXTERN_C_END

//------------------------------------------------------------------------------
