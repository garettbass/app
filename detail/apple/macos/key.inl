#pragma once
#include "app.inl"

//------------------------------------------------------------------------------

static const unsigned char _app_key_from_key_code_map[] = {
    /*kVK_A*/               APP_KEY_A,
    /*kVK_S*/               APP_KEY_S,
    /*kVK_D*/               APP_KEY_D,
    /*kVK_F*/               APP_KEY_F,
    /*kVK_H*/               APP_KEY_H,
    /*kVK_G*/               APP_KEY_G,
    /*kVK_Z*/               APP_KEY_Z,
    /*kVK_X*/               APP_KEY_X,
    /*kVK_C*/               APP_KEY_C,
    /*kVK_V*/               APP_KEY_V,
    /*kVK_ISO_Section*/     0,
    /*kVK_B*/               APP_KEY_B,
    /*kVK_Q*/               APP_KEY_Q,
    /*kVK_W*/               APP_KEY_W,
    /*kVK_E*/               APP_KEY_E,
    /*kVK_R*/               APP_KEY_R,
    /*kVK_Y*/               APP_KEY_Y,
    /*kVK_T*/               APP_KEY_T,
    /*kVK_1*/               APP_KEY_1,
    /*kVK_2*/               APP_KEY_2,
    /*kVK_3*/               APP_KEY_3,
    /*kVK_4*/               APP_KEY_4,
    /*kVK_6*/               APP_KEY_6,
    /*kVK_5*/               APP_KEY_5,
    /*kVK_Equal*/           APP_KEY_EQUAL,
    /*kVK_9*/               APP_KEY_9,
    /*kVK_7*/               APP_KEY_7,
    /*kVK_Minus*/           APP_KEY_MINUS,
    /*kVK_8*/               APP_KEY_8,
    /*kVK_0*/               APP_KEY_0,
    /*kVK_RightBracket*/    APP_KEY_RBRACKET,
    /*kVK_O*/               APP_KEY_O,
    /*kVK_U*/               APP_KEY_U,
    /*kVK_LeftBracket*/     APP_KEY_LBRACKET,
    /*kVK_I*/               APP_KEY_I,
    /*kVK_P*/               APP_KEY_P,
    /*kVK_Return*/          APP_KEY_ENTER,
    /*kVK_L*/               APP_KEY_L,
    /*kVK_J*/               APP_KEY_J,
    /*kVK_Quote*/           APP_KEY_QUOTE,
    /*kVK_K*/               APP_KEY_K,
    /*kVK_Semicolon*/       APP_KEY_SEMICOLON,
    /*kVK_Backslash*/       APP_KEY_BACKSLASH,
    /*kVK_Comma*/           APP_KEY_COMMA,
    /*kVK_Slash*/           APP_KEY_SLASH,
    /*kVK_N*/               APP_KEY_N,
    /*kVK_M*/               APP_KEY_M,
    /*kVK_Period*/          APP_KEY_PERIOD,
    /*kVK_Tab*/             APP_KEY_TAB,
    /*kVK_Space*/           APP_KEY_SPACE,
    /*kVK_Grave*/           APP_KEY_TILDE,
    /*kVK_Delete*/          APP_KEY_BACKSPACE,
    /*kVK_0x34*/            0,
    /*kVK_Escape*/          APP_KEY_ESCAPE,
    /*kVK_0x36*/            0,
    /*kVK_Command*/         APP_KEY_LSUPER,
    /*kVK_Shift*/           APP_KEY_LSHIFT,
    /*kVK_CapsLock*/        APP_KEY_CAPSLOCK,
    /*kVK_Option*/          APP_KEY_LALT,
    /*kVK_Control*/         APP_KEY_LCTRL,
    /*kVK_RightShift*/      APP_KEY_RSHIFT,
    /*kVK_RightOption*/     APP_KEY_RALT,
    /*kVK_RightControl*/    APP_KEY_RCTRL,
    /*kVK_Function*/        0,
    /*kVK_F17*/             APP_KEY_F17,
    /*kVK_KeypadDecimal*/   APP_KEY_PAD_DOT,
    /*kVK_0x42*/            0,
    /*kVK_KeypadMultiply*/  APP_KEY_PAD_MUL,
    /*kVK_0x44*/            0,
    /*kVK_KeypadPlus*/      APP_KEY_PAD_ADD,
    /*kVK_0x46*/            0,
    /*kVK_KeypadClear*/     0,
    /*kVK_VolumeUp*/        0,
    /*kVK_VolumeDown*/      0,
    /*kVK_Mute*/            0,
    /*kVK_KeypadDivide*/    APP_KEY_PAD_DIV,
    /*kVK_KeypadEnter*/     APP_KEY_PAD_ENTER,
    /*kVK_KeypadMinus*/     APP_KEY_PAD_SUB,
    /*kVK_F18*/             APP_KEY_F18,
    /*kVK_F19*/             APP_KEY_F19,
    /*kVK_KeypadEquals*/    APP_KEY_PAD_EQUAL,
    /*kVK_Keypad0*/         APP_KEY_PAD_0,
    /*kVK_Keypad1*/         APP_KEY_PAD_1,
    /*kVK_Keypad2*/         APP_KEY_PAD_2,
    /*kVK_Keypad3*/         APP_KEY_PAD_3,
    /*kVK_Keypad4*/         APP_KEY_PAD_4,
    /*kVK_Keypad5*/         APP_KEY_PAD_5,
    /*kVK_Keypad6*/         APP_KEY_PAD_6,
    /*kVK_Keypad7*/         APP_KEY_PAD_7,
    /*kVK_F20*/             APP_KEY_F20,
    /*kVK_Keypad8*/         APP_KEY_PAD_8,
    /*kVK_Keypad9*/         APP_KEY_PAD_9,
    /*kVK_JIS_Yen*/         0,
    /*kVK_JIS_Underscore*/  0,
    /*kVK_JIS_KeypadComma*/ 0,
    /*kVK_F5*/              APP_KEY_F5,
    /*kVK_F6*/              APP_KEY_F6,
    /*kVK_F7*/              APP_KEY_F7,
    /*kVK_F3*/              APP_KEY_F3,
    /*kVK_F8*/              APP_KEY_F8,
    /*kVK_F9*/              APP_KEY_F9,
    /*kVK_JIS_Eisu*/        0,
    /*kVK_F11*/             APP_KEY_F11,
    /*kVK_JIS_Kana*/        0,
    /*kVK_F13*/             APP_KEY_F13,
    /*kVK_F16*/             APP_KEY_F16,
    /*kVK_F14*/             APP_KEY_F14,
    /*kVK_0x6C*/            0,
    /*kVK_F10*/             APP_KEY_F10,
    /*kVK_0x6E*/            0,
    /*kVK_F12*/             APP_KEY_F12,
    /*kVK_0x70*/            0,
    /*kVK_F15*/             APP_KEY_F15,
    /*kVK_Help*/            0,
    /*kVK_Home*/            APP_KEY_HOME,
    /*kVK_PageUp*/          APP_KEY_PAGEUP,
    /*kVK_ForwardDelete*/   APP_KEY_DELETE,
    /*kVK_F4*/              APP_KEY_F4,
    /*kVK_End*/             APP_KEY_END,
    /*kVK_F2*/              APP_KEY_F2,
    /*kVK_PageDown*/        APP_KEY_PAGEDOWN,
    /*kVK_F1*/              APP_KEY_F1,
    /*kVK_LeftArrow*/       APP_KEY_LEFT,
    /*kVK_RightArrow*/      APP_KEY_RIGHT,
    /*kVK_DownArrow*/       APP_KEY_DOWN,
    /*kVK_UpArrow*/         APP_KEY_UP,
};
static_assert(sizeof(_app_key_from_key_code_map) == 126, "?");

enum {
    _app_key_from_key_code_map_length =
        sizeof(_app_key_from_key_code_map)/
        sizeof(_app_key_from_key_code_map[0]),
};

//------------------------------------------------------------------------------

APP_EXTERN_C_BEGIN

//------------------------------------------------------------------------------

static inline app_key
_app_key_from_key_code(unsigned key_code) {
    return
        (key_code < _app_key_from_key_code_map_length)
        ? (app_key)_app_key_from_key_code_map[key_code]
        : APP_KEY_NONE;
}

#pragma GCC poison _app_key_from_key_code_map
#pragma GCC poison _app_key_from_key_code_map_length

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static inline void
_app_keys_update(void) {
    HIKeyMap keyMap;
    GetKeys(keyMap);
    for (unsigned keyCode = 0; keyCode < kVK_Invalid; ++keyCode) {
        const unsigned blockIndex = keyCode >> 5;
        const unsigned block      = keyMap[blockIndex];
        const unsigned bitIndex   = keyCode & 0x1F;
        const bool isDown = (block >> bitIndex) & 0x01;
        const app_key key = _app_key_from_key_code(keyCode);
        _app_key_set(key, key and isDown);
    }
}

//------------------------------------------------------------------------------

APP_EXTERN_C_END

//------------------------------------------------------------------------------
