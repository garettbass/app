#pragma once
#include "app.inl"

//------------------------------------------------------------------------------

APP_EXTERN_C_BEGIN

//------------------------------------------------------------------------------

static app_point _app_mouse_delta;

static inline void
_app_mouse_delta_reset(void) {
    _app_mouse_delta = (app_point){0};
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static app_point _app_mouse_scroll;

static inline void
_app_mouse_scroll_reset(void) {
    _app_mouse_scroll = (app_point){0};
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

app_point
appMouseDelta(void) {
    return _app_mouse_delta;
}

app_point
appMouseScroll(void) {
    return _app_mouse_scroll;
}

//------------------------------------------------------------------------------

APP_EXTERN_C_END

//------------------------------------------------------------------------------
