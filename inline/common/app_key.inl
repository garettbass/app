#pragma once
#include "app.inl"
#include <ctype.h>
#include <stdio.h>

//------------------------------------------------------------------------------

APP_EXTERN_C_BEGIN

//------------------------------------------------------------------------------

typedef uint64_t app_keyBlock;

enum {
    app_keyCount      = APP_KEY_LAST + 1,
    app_keyBlockSize  = sizeof(app_keyBlock),
    app_keyBlockBits  = app_keyBlockSize * 8,
    app_keyBlockCount = app_keyCount / app_keyBlockBits,
};

static_assert(app_keyBlockSize == 8, "?");

static app_keyBlock _app_key_blocks[app_keyBlockCount] = { 0 };

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static inline void
_app_key_set(app_key key, bool down) {
    const int blockIndex = key >> 6;
    const int bitIndex = key & 0x3F;
    const app_keyBlock bitMask = ((app_keyBlock)0x1) << bitIndex;
    const app_keyBlock oldBlock = _app_key_blocks[blockIndex];
    const app_keyBlock newBlock =
        down
        ? (oldBlock |  bitMask)
        : (oldBlock & ~bitMask);
    _app_key_blocks[blockIndex] = newBlock;
    if (oldBlock != newBlock) {
        extern int printf(const char*, ...);
        // printf("%s: %s\n", app.key.toString(key), down ? "down" : "up");
    }
}

static inline bool
_app_key_get(app_key key) {
    const int blockIndex = key >> 6;
    const int bitIndex = key & 0x3F;
    const app_keyBlock block = _app_key_blocks[blockIndex];
    return (block >> bitIndex) & 0x1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static inline bool
app_key_isDown(app_key key) {
    return _app_key_get(key);
}

//------------------------------------------------------------------------------

static const char* _app_key_names[] = {
    /*APP_KEY_NONE*/        "None",
    /*APP_KEY_MOUSE_1*/      "MouseLeft",
    /*APP_KEY_MOUSE_2*/      "MouseRight",
    /*APP_KEY_MOUSE_3*/      "MouseMiddle",
    /*APP_KEY_MOUSE_4*/      "Mouse4",
    /*APP_KEY_MOUSE_5*/      "Mouse5",
    /*APP_KEY_MOUSE_6*/      "Mouse6",
    /*APP_KEY_MOUSE_7*/      "Mouse7",
    /*APP_KEY_MOUSE_8*/      "Mouse8",
    /*APP_KEY_MOUSE_9*/      "Mouse9",
    /*APP_KEY_MOUSE_10*/     "Mouse10",
    /*APP_KEY_ESCAPE*/      "Escape",
    /*APP_KEY_F1*/          "F1",
    /*APP_KEY_F2*/          "F2",
    /*APP_KEY_F3*/          "F3",
    /*APP_KEY_F4*/          "F4",
    /*APP_KEY_F5*/          "F5",
    /*APP_KEY_F6*/          "F6",
    /*APP_KEY_F7*/          "F7",
    /*APP_KEY_F8*/          "F8",
    /*APP_KEY_F9*/          "F9",
    /*APP_KEY_F10*/         "F10",
    /*APP_KEY_F11*/         "F11",
    /*APP_KEY_F12*/         "F12",
    /*APP_KEY_F13*/         "F13",
    /*APP_KEY_F14*/         "F14",
    /*APP_KEY_F15*/         "F15",
    /*APP_KEY_F16*/         "F16",
    /*APP_KEY_F17*/         "F17",
    /*APP_KEY_F18*/         "F18",
    /*APP_KEY_F19*/         "F19",
    /*APP_KEY_F20*/         "F20",
    /*APP_KEY_F21*/         "F21",
    /*APP_KEY_F22*/         "F22",
    /*APP_KEY_F23*/         "F23",
    /*APP_KEY_F24*/         "F24",
    /*APP_KEY_TILDE*/       "Tilde",
    /*APP_KEY_1*/           "1",
    /*APP_KEY_2*/           "2",
    /*APP_KEY_3*/           "3",
    /*APP_KEY_4*/           "4",
    /*APP_KEY_5*/           "5",
    /*APP_KEY_6*/           "6",
    /*APP_KEY_7*/           "7",
    /*APP_KEY_8*/           "8",
    /*APP_KEY_9*/           "9",
    /*APP_KEY_0*/           "0",
    /*APP_KEY_MINUS*/       "Minus",
    /*APP_KEY_EQUAL*/       "Equal",
    /*APP_KEY_BACKSPACE*/   "Backspace",
    /*APP_KEY_TAB*/         "Tab",
    /*APP_KEY_Q*/           "Q",
    /*APP_KEY_W*/           "W",
    /*APP_KEY_E*/           "E",
    /*APP_KEY_R*/           "R",
    /*APP_KEY_T*/           "T",
    /*APP_KEY_Y*/           "Y",
    /*APP_KEY_U*/           "U",
    /*APP_KEY_I*/           "I",
    /*APP_KEY_O*/           "O",
    /*APP_KEY_P*/           "P",
    /*APP_KEY_LBRACKET*/    "LBracket",
    /*APP_KEY_RBRACKET*/    "RBracket",
    /*APP_KEY_BACKSLASH*/   "Backslash",
    /*APP_KEY_CAPSLOCK*/    "CapsLock",
    /*APP_KEY_A*/           "A",
    /*APP_KEY_S*/           "S",
    /*APP_KEY_D*/           "D",
    /*APP_KEY_F*/           "F",
    /*APP_KEY_G*/           "G",
    /*APP_KEY_H*/           "H",
    /*APP_KEY_J*/           "J",
    /*APP_KEY_K*/           "K",
    /*APP_KEY_L*/           "L",
    /*APP_KEY_SEMICOLON*/   "Semicolon",
    /*APP_KEY_QUOTE*/       "Quote",
    /*APP_KEY_ENTER*/       "Enter",
    /*APP_KEY_LSHIFT*/      "LShift",
    /*APP_KEY_Z*/           "Z",
    /*APP_KEY_X*/           "X",
    /*APP_KEY_C*/           "C",
    /*APP_KEY_V*/           "V",
    /*APP_KEY_B*/           "B",
    /*APP_KEY_N*/           "N",
    /*APP_KEY_M*/           "M",
    /*APP_KEY_COMMA*/       "Comma",
    /*APP_KEY_PERIOD*/      "Period",
    /*APP_KEY_SLASH*/       "Slash",
    /*APP_KEY_RSHIFT*/      "RShift",
    /*APP_KEY_LCTRL*/       "LCtrl",
    /*APP_KEY_LALT*/        "LAlt",
    /*APP_KEY_LSUPER*/      "LSuper",
    /*APP_KEY_SPACE*/       "Space",
    /*APP_KEY_MENU*/        "Menu",
    /*APP_KEY_RSUPER*/      "RSuper",
    /*APP_KEY_RALT*/        "RAlt",
    /*APP_KEY_RCTRL*/       "RCtrl",
    /*APP_KEY_LEFT*/        "Left",
    /*APP_KEY_UP*/          "Up",
    /*APP_KEY_DOWN*/        "Down",
    /*APP_KEY_RIGHT*/       "Right",
    /*APP_KEY_HOME*/        "Home",
    /*APP_KEY_END*/         "End",
    /*APP_KEY_INSERT*/      "Insert",
    /*APP_KEY_DELETE*/      "Delete",
    /*APP_KEY_PAGEUP*/      "PageUp",
    /*APP_KEY_PAGEDOWN*/    "PageDown",
    /*APP_KEY_SCROLL_LOCK*/  "ScrollLock",
    /*APP_KEY_NUMLOCK*/     "NumLock",
    /*APP_KEY_PRINT_SCREEN*/ "PrintScreen",
    /*APP_KEY_PAUSE*/       "Pause",
    /*APP_KEY_PAD_0*/        "Pad0",
    /*APP_KEY_PAD_1*/        "Pad1",
    /*APP_KEY_PAD_2*/        "Pad2",
    /*APP_KEY_PAD_3*/        "Pad3",
    /*APP_KEY_PAD_4*/        "Pad4",
    /*APP_KEY_PAD_5*/        "Pad5",
    /*APP_KEY_PAD_6*/        "Pad6",
    /*APP_KEY_PAD_7*/        "Pad7",
    /*APP_KEY_PAD_8*/        "Pad8",
    /*APP_KEY_PAD_9*/        "Pad9",
    /*APP_KEY_PAD_DOT*/      "PadDot",
    /*APP_KEY_PAD_DIV*/      "PadDiv",
    /*APP_KEY_PAD_MUL*/      "PadMul",
    /*APP_KEY_PAD_SUB*/      "PadSub",
    /*APP_KEY_PAD_ADD*/      "PadAdd",
    /*APP_KEY_PAD_ENTER*/    "PadEnter",
    /*APP_KEY_PAD_EQUAL*/    "PadEqual",
};

static char _app_key_nameBuffer[] = "(app_key)00000000000000000000000";

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const char*
app_key_name(app_key key) {
    if ((int)key < (int)app_keyCount)
        return _app_key_names[key];

    snprintf(
        _app_key_nameBuffer,
        sizeof(_app_key_nameBuffer),
        "(app_key)%u",
        key);
    return _app_key_nameBuffer;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static inline bool
_app_streqi(const char* a, const char* b) {
    // skip all matching lowercase characters
    for(; *a and *b and tolower(*a) == tolower(*b); ++a, ++b);
    // strings are equal if we reached the null terminator of both
    return (not *a & not *b);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

app_key
app_key_parse(const char* keyName) {
    for (unsigned key = 0; key < app_keyCount; ++key)
        if (_app_streqi(keyName, _app_key_names[key]))
            return (app_key)key;
    return APP_KEY_NONE;
}

app_static_initializer(_app_key_string_test) {
    for (unsigned key = 0; key < app_keyCount; ++key) {
        assert(key == app_key_parse(app_key_name((app_key)key)));
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static struct _app_key_input {
    uint8_t length;
    char    begin[62];
    char    end[1];
} _app_key_input = {0};
static_assert(sizeof(_app_key_input) == 64, "?");

static inline void
_app_key_input_reset(void) {
    _app_key_input = (struct _app_key_input){0};
    assert(_app_key_input.length   == 0);
    assert(_app_key_input.begin[0] == 0);
    assert(_app_key_input.end[0]   == 0);
}

static inline void
_app_key_input_append_char(const char in) {
    printf("%s('%c')\n", __func__, in);
    char* out = _app_key_input.begin + _app_key_input.length;
    const char* const end = _app_key_input.end;
    if (in and out < end) {
        *out = in;
        ++out, ++_app_key_input.length;
    }
    assert(*out == '\0');
}

static inline void
_app_key_input_append_string(const char* in) {
    printf("%s(\"%s\")\n", __func__, in);
    char* out = _app_key_input.begin + _app_key_input.length;
    const char* const end = _app_key_input.end;
    for (; *in and out < end; ++in, ++out, ++_app_key_input.length) {
        *out = *in;
    }
    assert(*out == '\0');
}

static inline void
_app_key_input_append_utf32(const uint32_t u) {
    const uint32_t u_is_valid =
        ((u < 0x110000) &
        ((u < 0x00D800) | (u > 0x00DFFF)));
    if (u_is_valid) {
        const uint32_t is_length_1 = (u < 0x00000080u);
        const uint32_t is_length_2 = (u < 0x00000800u) & !is_length_1;
        const uint32_t is_length_3 = (u < 0x00010000u) & !is_length_2;
        const uint32_t is_length_4 = (u < 0x00110000u) & !is_length_3;
        const char a =
            (is_length_1 * (u)) +
            (is_length_2 * (0xC0 + (u >>  6))) +
            (is_length_3 * (0xE0 + (u >> 12))) +
            (is_length_4 * (0xF0 + (u >> 18)));
        const char b =
            (is_length_2 * (0x80 + (0x3F & (u)))) +
            (is_length_3 * (0x80 + (0x3F & (u >>  6)))) +
            (is_length_4 * (0x80 + (0x3F & (u >> 12))));
        const char c =
            (is_length_3 * (0x80 + (0x3F & (u)))) +
            (is_length_4 * (0x80 + (0x3F & (u >> 6))));
        const char d =
            (is_length_4 * (0x80 + (0x3F & (u))));
        char utf8[8] = {a, b, c, d, 0};
        _app_key_input_append_string(utf8);
    }
}

const char*
app_key_input(void) {
    return _app_key_input.begin;
}

//------------------------------------------------------------------------------

APP_EXTERN_C_END

//------------------------------------------------------------------------------
