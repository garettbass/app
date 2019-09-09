#pragma once
#include "app.inl"
#include <ctype.h>
#include <stdio.h>

//------------------------------------------------------------------------------

APP_EXTERN_C_BEGIN

//------------------------------------------------------------------------------

typedef uint64_t app_keyBlock;

enum {
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
    /*APP_KEY_None*/        "None",
    /*APP_KEY_Mouse1*/      "MouseLeft",
    /*APP_KEY_Mouse2*/      "MouseRight",
    /*APP_KEY_Mouse3*/      "MouseMiddle",
    /*APP_KEY_Mouse4*/      "Mouse4",
    /*APP_KEY_Mouse5*/      "Mouse5",
    /*APP_KEY_Mouse6*/      "Mouse6",
    /*APP_KEY_Mouse7*/      "Mouse7",
    /*APP_KEY_Mouse8*/      "Mouse8",
    /*APP_KEY_Mouse9*/      "Mouse9",
    /*APP_KEY_Mouse10*/     "Mouse10",
    /*APP_KEY_Escape*/      "Escape",
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
    /*APP_KEY_Tilde*/       "Tilde",
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
    /*APP_KEY_Minus*/       "Minus",
    /*APP_KEY_Equal*/       "Equal",
    /*APP_KEY_Backspace*/   "Backspace",
    /*APP_KEY_Tab*/         "Tab",
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
    /*APP_KEY_LBracket*/    "LBracket",
    /*APP_KEY_RBracket*/    "RBracket",
    /*APP_KEY_Backslash*/   "Backslash",
    /*APP_KEY_CapsLock*/    "CapsLock",
    /*APP_KEY_A*/           "A",
    /*APP_KEY_S*/           "S",
    /*APP_KEY_D*/           "D",
    /*APP_KEY_F*/           "F",
    /*APP_KEY_G*/           "G",
    /*APP_KEY_H*/           "H",
    /*APP_KEY_J*/           "J",
    /*APP_KEY_K*/           "K",
    /*APP_KEY_L*/           "L",
    /*APP_KEY_Semicolon*/   "Semicolon",
    /*APP_KEY_Quote*/       "Quote",
    /*APP_KEY_Enter*/       "Enter",
    /*APP_KEY_LShift*/      "LShift",
    /*APP_KEY_Z*/           "Z",
    /*APP_KEY_X*/           "X",
    /*APP_KEY_C*/           "C",
    /*APP_KEY_V*/           "V",
    /*APP_KEY_B*/           "B",
    /*APP_KEY_N*/           "N",
    /*APP_KEY_M*/           "M",
    /*APP_KEY_Comma*/       "Comma",
    /*APP_KEY_Period*/      "Period",
    /*APP_KEY_Slash*/       "Slash",
    /*APP_KEY_RShift*/      "RShift",
    /*APP_KEY_LCtrl*/       "LCtrl",
    /*APP_KEY_LAlt*/        "LAlt",
    /*APP_KEY_LSuper*/      "LSuper",
    /*APP_KEY_Space*/       "Space",
    /*APP_KEY_Menu*/        "Menu",
    /*APP_KEY_RSuper*/      "RSuper",
    /*APP_KEY_RAlt*/        "RAlt",
    /*APP_KEY_RCtrl*/       "RCtrl",
    /*APP_KEY_Left*/        "Left",
    /*APP_KEY_Up*/          "Up",
    /*APP_KEY_Down*/        "Down",
    /*APP_KEY_Right*/       "Right",
    /*APP_KEY_Home*/        "Home",
    /*APP_KEY_End*/         "End",
    /*APP_KEY_Insert*/      "Insert",
    /*APP_KEY_Delete*/      "Delete",
    /*APP_KEY_PageUp*/      "PageUp",
    /*APP_KEY_PageDown*/    "PageDown",
    /*APP_KEY_ScrollLock*/  "ScrollLock",
    /*APP_KEY_NumLock*/     "NumLock",
    /*APP_KEY_PrintScreen*/ "PrintScreen",
    /*APP_KEY_Pause*/       "Pause",
    /*APP_KEY_Pad0*/        "Pad0",
    /*APP_KEY_Pad1*/        "Pad1",
    /*APP_KEY_Pad2*/        "Pad2",
    /*APP_KEY_Pad3*/        "Pad3",
    /*APP_KEY_Pad4*/        "Pad4",
    /*APP_KEY_Pad5*/        "Pad5",
    /*APP_KEY_Pad6*/        "Pad6",
    /*APP_KEY_Pad7*/        "Pad7",
    /*APP_KEY_Pad8*/        "Pad8",
    /*APP_KEY_Pad9*/        "Pad9",
    /*APP_KEY_PadDot*/      "PadDot",
    /*APP_KEY_PadDiv*/      "PadDiv",
    /*APP_KEY_PadMul*/      "PadMul",
    /*APP_KEY_PadSub*/      "PadSub",
    /*APP_KEY_PadAdd*/      "PadAdd",
    /*APP_KEY_PadEnter*/    "PadEnter",
    /*APP_KEY_PadEqual*/    "PadEqual",
};

static char _app_key_nameBuffer[] = "(app_key)00000000000000000000000";

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const char*
app_key_name(app_key key) {
    if (key < app_keyCount)
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
    return APP_KEY_None;
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
