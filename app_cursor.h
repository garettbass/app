#pragma once
#include "app.h"

//------------------------------------------------------------------------------

typedef enum app_cursor {
    APP_CURSOR_NONE      = 0,
    APP_CURSOR_DEFAULT   = 1,
    APP_CURSOR_ARROW     = 2,
    APP_CURSOR_CROSSHAIR = 3,
    APP_CURSOR_TEXT      = 4,
    APP_CURSOR_LINK      = 5,
    APP_CURSOR_DRAG_NS   = 6,
    APP_CURSOR_DRAG_EW   = 7,
} app_cursor;

//------------------------------------------------------------------------------

APP_EXTERN_C_BEGIN

//------------------------------------------------------------------------------

void
app_cursor_set(app_cursor);

app_point
app_cursor_get_position(app_window* /*optional*/);

void
app_cursor_set_position(app_point, app_window* /*optional*/);

bool
app_cursor_is_inside(app_rect, app_window* /*optional*/);

bool
app_cursor_is_locked(void);

void
app_cursor_set_locked(bool);

//------------------------------------------------------------------------------

APP_EXTERN_C_END

//------------------------------------------------------------------------------
