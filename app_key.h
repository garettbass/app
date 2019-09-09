#pragma once
#include "app.h"

//------------------------------------------------------------------------------

typedef enum app_key {
    APP_KEY_None,

    APP_KEY_Mouse1, APP_KEY_MouseLeft   = APP_KEY_Mouse1,
    APP_KEY_Mouse2, APP_KEY_MouseRight  = APP_KEY_Mouse2,
    APP_KEY_Mouse3, APP_KEY_MouseMiddle = APP_KEY_Mouse3,
    APP_KEY_Mouse4,
    APP_KEY_Mouse5,
    APP_KEY_Mouse6,
    APP_KEY_Mouse7,
    APP_KEY_Mouse8,
    APP_KEY_Mouse9,
    APP_KEY_Mouse10,

    APP_KEY_Escape,
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

    APP_KEY_Tilde,
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
    APP_KEY_Minus,
    APP_KEY_Equal,
    APP_KEY_Backspace,

    APP_KEY_Tab,
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
    APP_KEY_LBracket,
    APP_KEY_RBracket,
    APP_KEY_Backslash,

    APP_KEY_CapsLock,
    APP_KEY_A,
    APP_KEY_S,
    APP_KEY_D,
    APP_KEY_F,
    APP_KEY_G,
    APP_KEY_H,
    APP_KEY_J,
    APP_KEY_K,
    APP_KEY_L,
    APP_KEY_Semicolon,
    APP_KEY_Quote,
    APP_KEY_Enter,

    APP_KEY_LShift,
    APP_KEY_Z,
    APP_KEY_X,
    APP_KEY_C,
    APP_KEY_V,
    APP_KEY_B,
    APP_KEY_N,
    APP_KEY_M,
    APP_KEY_Comma,
    APP_KEY_Period,
    APP_KEY_Slash,
    APP_KEY_RShift,

    APP_KEY_LCtrl,
    APP_KEY_LAlt,
    APP_KEY_LSuper,
    APP_KEY_Space,
    APP_KEY_Menu,
    APP_KEY_RSuper,
    APP_KEY_RAlt,
    APP_KEY_RCtrl,

    APP_KEY_Left,
    APP_KEY_Up,
    APP_KEY_Down,
    APP_KEY_Right,

    APP_KEY_Home,
    APP_KEY_End,
    APP_KEY_Insert,
    APP_KEY_Delete,
    APP_KEY_PageUp,
    APP_KEY_PageDown,

    APP_KEY_ScrollLock,
    APP_KEY_NumLock,
    APP_KEY_PrintScreen,
    APP_KEY_Pause,

    APP_KEY_Pad0,
    APP_KEY_Pad1,
    APP_KEY_Pad2,
    APP_KEY_Pad3,
    APP_KEY_Pad4,
    APP_KEY_Pad5,
    APP_KEY_Pad6,
    APP_KEY_Pad7,
    APP_KEY_Pad8,
    APP_KEY_Pad9,
    APP_KEY_PadDot,
    APP_KEY_PadDiv,
    APP_KEY_PadMul,
    APP_KEY_PadSub,
    APP_KEY_PadAdd,
    APP_KEY_PadEnter,
    APP_KEY_PadEqual,

    app_keyCount,
} app_key;

//------------------------------------------------------------------------------

APP_EXTERN_C_BEGIN

//------------------------------------------------------------------------------

const char*
app_key_input(void);

bool
app_key_is_down(app_key);

const char*
app_key_name(app_key);

app_key
app_key_parse(const char*);

//------------------------------------------------------------------------------

APP_EXTERN_C_END

//------------------------------------------------------------------------------
