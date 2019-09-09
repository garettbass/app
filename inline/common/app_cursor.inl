#pragma once
#include "app.inl"

//------------------------------------------------------------------------------

APP_EXTERN_C_BEGIN

//------------------------------------------------------------------------------

bool
app_cursor_is_inside(app_rect rect, app_window* /*optional*/ window) {
    app_point position = app_cursor_get_position(window);
    return(position.x >= rect.x)
        & (position.y >= rect.y)
        & (position.x <= rect.x + rect.w)
        & (position.y <= rect.y + rect.h);
}

//------------------------------------------------------------------------------

APP_EXTERN_C_END

//------------------------------------------------------------------------------
