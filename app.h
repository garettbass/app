#pragma once
#include <assert.h>
#include <iso646.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

//------------------------------------------------------------------------------

#define APP_VERSION_MAJOR 0
#define APP_VERSION_MINOR 0
#define APP_VERSION_PATCH 0
#define APP_VERSION\
        _APP_VERSION(APP_VERSION_MAJOR,APP_VERSION_MINOR,APP_VERSION_PATCH)
#define _APP_VERSION(X, Y, Z) __APP_VERSION(X, Y, Z)
#define __APP_VERSION(X, Y, Z) "app "#X"."#Y"."#Z""

//------------------------------------------------------------------------------

#ifdef __cplusplus
    #define APP_EXTERN_C       extern "C"
    #define APP_EXTERN_C_BEGIN extern "C" {
    #define APP_EXTERN_C_END   } // extern "C"
#else
    #define APP_EXTERN_C       /* extern "C" */
    #define APP_EXTERN_C_BEGIN /* extern "C" { */
    #define APP_EXTERN_C_END   /* } // extern "C" */
#endif // __cplusplus

//------------------------------------------------------------------------------

typedef struct app_point { float x, y; } app_point;

typedef struct app_rect {
    union {
        struct { float   x, y,   w, h; };
        struct { app_point origin, size; };
    };
} app_rect;

typedef struct app_window app_window;

//------------------------------------------------------------------------------

APP_EXTERN_C_BEGIN

//------------------------------------------------------------------------------

void
app_activate(void);

bool
app_is_active(void);

bool
app_update(void);

void
app_quit(void);

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

typedef enum app_key {
    APP_KEY_NONE,

    APP_KEY_MOUSE_1, APP_KEY_LMOUSE = APP_KEY_MOUSE_1,
    APP_KEY_MOUSE_2, APP_KEY_RMOUSE = APP_KEY_MOUSE_2,
    APP_KEY_MOUSE_3, APP_KEY_MMOUSE = APP_KEY_MOUSE_3,
    APP_KEY_MOUSE_4,
    APP_KEY_MOUSE_5,
    APP_KEY_MOUSE_6,
    APP_KEY_MOUSE_7,
    APP_KEY_MOUSE_8,
    APP_KEY_MOUSE_9,
    APP_KEY_MOUSE_10,

    APP_KEY_ESCAPE,
    APP_KEY_F1,
    APP_KEY_F2,
    APP_KEY_F3,
    APP_KEY_F4,
    APP_KEY_F5,
    APP_KEY_F6,
    APP_KEY_F7,
    APP_KEY_F8,
    APP_KEY_F9,
    APP_KEY_F10,
    APP_KEY_F11,
    APP_KEY_F12,

    APP_KEY_F13,
    APP_KEY_F14,
    APP_KEY_F15,
    APP_KEY_F16,
    APP_KEY_F17,
    APP_KEY_F18,
    APP_KEY_F19,
    APP_KEY_F20,
    APP_KEY_F21,
    APP_KEY_F22,
    APP_KEY_F23,
    APP_KEY_F24,

    APP_KEY_TILDE,
    APP_KEY_1,
    APP_KEY_2,
    APP_KEY_3,
    APP_KEY_4,
    APP_KEY_5,
    APP_KEY_6,
    APP_KEY_7,
    APP_KEY_8,
    APP_KEY_9,
    APP_KEY_0,
    APP_KEY_MINUS,
    APP_KEY_EQUAL,
    APP_KEY_BACKSPACE,

    APP_KEY_TAB,
    APP_KEY_Q,
    APP_KEY_W,
    APP_KEY_E,
    APP_KEY_R,
    APP_KEY_T,
    APP_KEY_Y,
    APP_KEY_U,
    APP_KEY_I,
    APP_KEY_O,
    APP_KEY_P,
    APP_KEY_LBRACKET,
    APP_KEY_RBRACKET,
    APP_KEY_BACKSLASH,

    APP_KEY_CAPSLOCK,
    APP_KEY_A,
    APP_KEY_S,
    APP_KEY_D,
    APP_KEY_F,
    APP_KEY_G,
    APP_KEY_H,
    APP_KEY_J,
    APP_KEY_K,
    APP_KEY_L,
    APP_KEY_SEMICOLON,
    APP_KEY_QUOTE,
    APP_KEY_ENTER,

    APP_KEY_LSHIFT,
    APP_KEY_Z,
    APP_KEY_X,
    APP_KEY_C,
    APP_KEY_V,
    APP_KEY_B,
    APP_KEY_N,
    APP_KEY_M,
    APP_KEY_COMMA,
    APP_KEY_PERIOD,
    APP_KEY_SLASH,
    APP_KEY_RSHIFT,

    APP_KEY_LCTRL,
    APP_KEY_LALT,
    APP_KEY_LSUPER,
    APP_KEY_SPACE,
    APP_KEY_MENU,
    APP_KEY_RSUPER,
    APP_KEY_RALT,
    APP_KEY_RCTRL,

    APP_KEY_LEFT,
    APP_KEY_UP,
    APP_KEY_DOWN,
    APP_KEY_RIGHT,

    APP_KEY_HOME,
    APP_KEY_END,
    APP_KEY_INSERT,
    APP_KEY_DELETE,
    APP_KEY_PAGEUP,
    APP_KEY_PAGEDOWN,

    APP_KEY_SCROLL_LOCK,
    APP_KEY_NUMLOCK,
    APP_KEY_PRINT_SCREEN,
    APP_KEY_PAUSE,

    APP_KEY_PAD_0,
    APP_KEY_PAD_1,
    APP_KEY_PAD_2,
    APP_KEY_PAD_3,
    APP_KEY_PAD_4,
    APP_KEY_PAD_5,
    APP_KEY_PAD_6,
    APP_KEY_PAD_7,
    APP_KEY_PAD_8,
    APP_KEY_PAD_9,
    APP_KEY_PAD_DOT,
    APP_KEY_PAD_DIV,
    APP_KEY_PAD_MUL,
    APP_KEY_PAD_SUB,
    APP_KEY_PAD_ADD,
    APP_KEY_PAD_ENTER,
    APP_KEY_PAD_EQUAL,

    APP_KEY_LAST = APP_KEY_PAD_EQUAL,
} app_key;

bool
app_key_is_down(app_key);

const char*
app_key_name(app_key);

app_key
app_key_parse(const char*);

//------------------------------------------------------------------------------

app_point
app_mouse_delta(void);

app_point
app_mouse_scroll(void);

//------------------------------------------------------------------------------

const char*
app_text_input(void);

//------------------------------------------------------------------------------

typedef enum app_window_features {
    APP_WINDOW_FEATURES_NONE     = 0,
    APP_WINDOW_FEATURES_CLOSE    = 1 << 0,
    APP_WINDOW_FEATURES_MINIMIZE = 1 << 1,
    APP_WINDOW_FEATURES_RESIZE   = 1 << 2,
    APP_WINDOW_FEATURES_TITLEBAR = 1 << 3,
    APP_WINDOW_FEATURES_MENUBAR  = 1 << 4,
} app_window_features;

#define app_window_features(EXPR) ((app_window_features)(EXPR))

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
