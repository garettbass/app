#pragma once
#include "app.inl"

//------------------------------------------------------------------------------

APP_EXTERN_C_BEGIN

//------------------------------------------------------------------------------

static app_cursor _app_cursor = APP_CURSOR_DEFAULT;

void
app_cursor_set(app_cursor cursor) {
    _app_cursor = cursor;
}

//------------------------------------------------------------------------------

app_point
app_cursor_get_position(app_window* /*optional*/ window) {
    typedef struct POINT { int x, y; } POINT;
    POINT point = {0,0};
    _app_GetCursorPos(&point);
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
    (void)position;
    (void)window;
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
    (void)locked;
}

//------------------------------------------------------------------------------

APP_EXTERN_C_END

//------------------------------------------------------------------------------
