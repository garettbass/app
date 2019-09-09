#pragma once
#include "app.h"

//------------------------------------------------------------------------------

APP_EXTERN_C_BEGIN

//------------------------------------------------------------------------------

app_window*
app_window_acquire(void);

void
app_window_release(app_window*);

void
app_window_set_title(app_window*, const char*);

void
app_window_set_features(app_window*, app_window_features);

app_rect
app_window_get_frame(app_window*);

void
app_window_set_frame(app_window*, app_rect);

app_rect
app_window_get_viewport(app_window*);

void
app_window_set_viewport(app_window*, app_rect);

void
app_window_activate(app_window*);

app_window*
app_window_get_active(void);

bool
app_window_is_active(app_window*);

bool
app_window_is_open(app_window*);

void
app_window_set_open(app_window*, bool);

bool
app_window_is_fullscreen(app_window*);

void
app_window_set_fullscreen(app_window*, bool);

//------------------------------------------------------------------------------

APP_EXTERN_C_END

//------------------------------------------------------------------------------
