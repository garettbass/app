#pragma once
#include "app_platform.h"

//------------------------------------------------------------------------------

#define APP_VERSION_MAJOR 0
#define APP_VERSION_MINOR 0
#define APP_VERSION_PATCH 0
#define APP_VERSION\
        APP_VERSION_(APP_VERSION_MAJOR,APP_VERSION_MINOR,APP_VERSION_PATCH)
#define APP_VERSION_(X, Y, Z) APP_VERSION__(X, Y, Z)
#define APP_VERSION__(X, Y, Z) "app "#X"."#Y"."#Z""

//------------------------------------------------------------------------------

#define APP_BUILD\
        APP_VERSION" "\
        APP_COMPILER_NAME" "\
        APP_OS_NAME" "\
        APP_CPU_NAME" ("APP_ENDIAN_NAME") "\
        __DATE__" "__TIME__

//------------------------------------------------------------------------------

#if APP_DEBUG
    #define APP_DEBUG_ONLY(...) __VA_ARGS__
#else
    #define APP_DEBUG_ONLY(...)
#endif

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

// TODO: menus
// # - super
// ! - alt
// ^ - ctrl
// + - shift

//------------------------------------------------------------------------------

APP_EXTERN_C_END

//------------------------------------------------------------------------------

#include "app_cursor.h"
#include "app_dll.h"
#include "app_key.h"
#include "app_mouse.h"
#include "app_window.h"

//------------------------------------------------------------------------------
