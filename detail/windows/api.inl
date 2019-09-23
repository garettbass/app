#pragma once
#include "../dll.h"

//------------------------------------------------------------------------------

typedef enum VK {
     _APP_VK_LBUTTON              = 0x01, // Left mouse button
     _APP_VK_RBUTTON              = 0x02, // Right mouse button
     _APP_VK_CANCEL               = 0x03, // Control-break processing
     _APP_VK_MBUTTON              = 0x04, // Middle mouse button (three-button mouse)
     _APP_VK_XBUTTON1             = 0x05, // X1 mouse button
     _APP_VK_XBUTTON2             = 0x06, // X2 mouse button
     _APP_VK_0x07                 = 0x07, // Undefined
     _APP_VK_BACK                 = 0x08, // BACKSPACE key
     _APP_VK_TAB                  = 0x09, // TAB key
     _APP_VK_0x0A                 = 0x0A, // Reserved
     _APP_VK_0x0B                 = 0x0B, // Reserved
     _APP_VK_CLEAR                = 0x0C, // CLEAR key
     _APP_VK_RETURN               = 0x0D, // ENTER key
     _APP_VK_0x0E                 = 0x0E, // Undefined
     _APP_VK_0x0F                 = 0x0F, // Undefined
     _APP_VK_SHIFT                = 0x10, // SHIFT key
     _APP_VK_CONTROL              = 0x11, // CTRL key
     _APP_VK_MENU                 = 0x12, // ALT key
     _APP_VK_PAUSE                = 0x13, // PAUSE key
     _APP_VK_CAPITAL              = 0x14, // CAPS LOCK key
     _APP_VK_KANA                 = 0x15, // IME Kana mode
     _APP_VK_HANGUL               = 0x15, // IME Hangul mode
     _APP_VK_0x16                 = 0x16, // Undefined
     _APP_VK_JUNJA                = 0x17, // IME Junja mode
     _APP_VK_FINAL                = 0x18, // IME final mode
     _APP_VK_HANJA                = 0x19, // IME Hanja mode
     _APP_VK_KANJI                = 0x19, // IME Kanji mode
     _APP_VK_0x1A                 = 0x1A, // Undefined
     _APP_VK_ESCAPE               = 0x1B, // ESC key
     _APP_VK_CONVERT              = 0x1C, // IME convert
     _APP_VK_NONCONVERT           = 0x1D, // IME nonconvert
     _APP_VK_ACCEPT               = 0x1E, // IME accept
     _APP_VK_MODECHANGE           = 0x1F, // IME mode change request
     _APP_VK_SPACE                = 0x20, // SPACEBAR
     _APP_VK_PRIOR                = 0x21, // PAGE UP key
     _APP_VK_NEXT                 = 0x22, // PAGE DOWN key
     _APP_VK_END                  = 0x23, // END key
     _APP_VK_HOME                 = 0x24, // HOME key
     _APP_VK_LEFT                 = 0x25, // LEFT ARROW key
     _APP_VK_UP                   = 0x26, // UP ARROW key
     _APP_VK_RIGHT                = 0x27, // RIGHT ARROW key
     _APP_VK_DOWN                 = 0x28, // DOWN ARROW key
     _APP_VK_SELECT               = 0x29, // SELECT key
     _APP_VK_PRINT                = 0x2A, // PRINT key
     _APP_VK_EXECUTE              = 0x2B, // EXECUTE key
     _APP_VK_SNAPSHOT             = 0x2C, // PRINT SCREEN key
     _APP_VK_INSERT               = 0x2D, // INS key
     _APP_VK_DELETE               = 0x2E, // DEL key
     _APP_VK_HELP                 = 0x2F, // HELP key
     _APP_VK_0                    = 0x30, // 0 key
     _APP_VK_1                    = 0x31, // 1 key
     _APP_VK_2                    = 0x32, // 2 key
     _APP_VK_3                    = 0x33, // 3 key
     _APP_VK_4                    = 0x34, // 4 key
     _APP_VK_5                    = 0x35, // 5 key
     _APP_VK_6                    = 0x36, // 6 key
     _APP_VK_7                    = 0x37, // 7 key
     _APP_VK_8                    = 0x38, // 8 key
     _APP_VK_9                    = 0x39, // 9 key
     _APP_VK_0x3A                 = 0x3A, // Undefined
     _APP_VK_0x3B                 = 0x3B, // Undefined
     _APP_VK_0x3C                 = 0x3C, // Undefined
     _APP_VK_0x3D                 = 0x3D, // Undefined
     _APP_VK_0x3E                 = 0x3E, // Undefined
     _APP_VK_0x3F                 = 0x3F, // Undefined
     _APP_VK_0x40                 = 0x40, // Undefined
     _APP_VK_A                    = 0x41, // A key
     _APP_VK_B                    = 0x42, // B key
     _APP_VK_C                    = 0x43, // C key
     _APP_VK_D                    = 0x44, // D key
     _APP_VK_E                    = 0x45, // E key
     _APP_VK_F                    = 0x46, // F key
     _APP_VK_G                    = 0x47, // G key
     _APP_VK_H                    = 0x48, // H key
     _APP_VK_I                    = 0x49, // I key
     _APP_VK_J                    = 0x4A, // J key
     _APP_VK_K                    = 0x4B, // K key
     _APP_VK_L                    = 0x4C, // L key
     _APP_VK_M                    = 0x4D, // M key
     _APP_VK_N                    = 0x4E, // N key
     _APP_VK_O                    = 0x4F, // O key
     _APP_VK_P                    = 0x50, // P key
     _APP_VK_Q                    = 0x51, // Q key
     _APP_VK_R                    = 0x52, // R key
     _APP_VK_S                    = 0x53, // S key
     _APP_VK_T                    = 0x54, // T key
     _APP_VK_U                    = 0x55, // U key
     _APP_VK_V                    = 0x56, // V key
     _APP_VK_W                    = 0x57, // W key
     _APP_VK_X                    = 0x58, // X key
     _APP_VK_Y                    = 0x59, // Y key
     _APP_VK_Z                    = 0x5A, // Z key
     _APP_VK_LWIN                 = 0x5B, // Left Windows key (Natural keyboard) 
     _APP_VK_RWIN                 = 0x5C, // Right Windows key (Natural keyboard)
     _APP_VK_APPS                 = 0x5D, // Applications key (Natural keyboard)
     _APP_VK_0x5E                 = 0x5E, // Reserved
     _APP_VK_SLEEP                = 0x5F, // Computer Sleep key
     _APP_VK_NUMPAD0              = 0x60, // Numeric keypad 0 key
     _APP_VK_NUMPAD1              = 0x61, // Numeric keypad 1 key
     _APP_VK_NUMPAD2              = 0x62, // Numeric keypad 2 key
     _APP_VK_NUMPAD3              = 0x63, // Numeric keypad 3 key
     _APP_VK_NUMPAD4              = 0x64, // Numeric keypad 4 key
     _APP_VK_NUMPAD5              = 0x65, // Numeric keypad 5 key
     _APP_VK_NUMPAD6              = 0x66, // Numeric keypad 6 key
     _APP_VK_NUMPAD7              = 0x67, // Numeric keypad 7 key
     _APP_VK_NUMPAD8              = 0x68, // Numeric keypad 8 key
     _APP_VK_NUMPAD9              = 0x69, // Numeric keypad 9 key
     _APP_VK_MULTIPLY             = 0x6A, // Multiply key
     _APP_VK_ADD                  = 0x6B, // Add key
     _APP_VK_SEPARATOR            = 0x6C, // Separator key
     _APP_VK_SUBTRACT             = 0x6D, // Subtract key
     _APP_VK_DECIMAL              = 0x6E, // Decimal key
     _APP_VK_DIVIDE               = 0x6F, // Divide key
     _APP_VK_F1                   = 0x70, // F1 key
     _APP_VK_F2                   = 0x71, // F2 key
     _APP_VK_F3                   = 0x72, // F3 key
     _APP_VK_F4                   = 0x73, // F4 key
     _APP_VK_F5                   = 0x74, // F5 key
     _APP_VK_F6                   = 0x75, // F6 key
     _APP_VK_F7                   = 0x76, // F7 key
     _APP_VK_F8                   = 0x77, // F8 key
     _APP_VK_F9                   = 0x78, // F9 key
     _APP_VK_F10                  = 0x79, // F10 key
     _APP_VK_F11                  = 0x7A, // F11 key
     _APP_VK_F12                  = 0x7B, // F12 key
     _APP_VK_F13                  = 0x7C, // F13 key
     _APP_VK_F14                  = 0x7D, // F14 key
     _APP_VK_F15                  = 0x7E, // F15 key
     _APP_VK_F16                  = 0x7F, // F16 key
     _APP_VK_F17                  = 0x80, // F17 key
     _APP_VK_F18                  = 0x81, // F18 key
     _APP_VK_F19                  = 0x82, // F19 key
     _APP_VK_F20                  = 0x83, // F20 key
     _APP_VK_F21                  = 0x84, // F21 key
     _APP_VK_F22                  = 0x85, // F22 key
     _APP_VK_F23                  = 0x86, // F23 key
     _APP_VK_F24                  = 0x87, // F24 key
     _APP_VK_0x88                 = 0x88, // Unassigned
     _APP_VK_0x89                 = 0x89, // Unassigned
     _APP_VK_0x8A                 = 0x8A, // Unassigned
     _APP_VK_0x8B                 = 0x8B, // Unassigned
     _APP_VK_0x8C                 = 0x8C, // Unassigned
     _APP_VK_0x8D                 = 0x8D, // Unassigned
     _APP_VK_0x8E                 = 0x8E, // Unassigned
     _APP_VK_0x8F                 = 0x8F, // Unassigned
     _APP_VK_NUMLOCK              = 0x90, // NUM LOCK key
     _APP_VK_SCROLL               = 0x91, // SCROLL LOCK key
     _APP_VK_0x92                 = 0x92, // OEM specific
     _APP_VK_0x93                 = 0x93, // OEM specific
     _APP_VK_0x94                 = 0x94, // OEM specific
     _APP_VK_0x95                 = 0x95, // OEM specific
     _APP_VK_0x96                 = 0x96, // OEM specific
     _APP_VK_0x97                 = 0x97, // Unassigned
     _APP_VK_0x98                 = 0x98, // Unassigned
     _APP_VK_0x99                 = 0x99, // Unassigned
     _APP_VK_0x9A                 = 0x9A, // Unassigned
     _APP_VK_0x9B                 = 0x9B, // Unassigned
     _APP_VK_0x9C                 = 0x9C, // Unassigned
     _APP_VK_0x9D                 = 0x9D, // Unassigned
     _APP_VK_0x9E                 = 0x9E, // Unassigned
     _APP_VK_0x9F                 = 0x9F, // Unassigned
     _APP_VK_LSHIFT               = 0xA0, // Left SHIFT key
     _APP_VK_RSHIFT               = 0xA1, // Right SHIFT key
     _APP_VK_LCONTROL             = 0xA2, // Left CONTROL key
     _APP_VK_RCONTROL             = 0xA3, // Right CONTROL key
     _APP_VK_LMENU                = 0xA4, // Left MENU key
     _APP_VK_RMENU                = 0xA5, // Right MENU key
     _APP_VK_BROWSER_BACK         = 0xA6, // Browser Back key
     _APP_VK_BROWSER_FORWARD      = 0xA7, // Browser Forward key
     _APP_VK_BROWSER_REFRESH      = 0xA8, // Browser Refresh key
     _APP_VK_BROWSER_STOP         = 0xA9, // Browser Stop key
     _APP_VK_BROWSER_SEARCH       = 0xAA, // Browser Search key 
     _APP_VK_BROWSER_FAVORITES    = 0xAB, // Browser Favorites key
     _APP_VK_BROWSER_HOME         = 0xAC, // Browser Start and Home key
     _APP_VK_VOLUME_MUTE          = 0xAD, // Volume Mute key
     _APP_VK_VOLUME_DOWN          = 0xAE, // Volume Down key
     _APP_VK_VOLUME_UP            = 0xAF, // Volume Up key
     _APP_VK_MEDIA_NEXT_TRACK     = 0xB0, // Next Track key
     _APP_VK_MEDIA_PREV_TRACK     = 0xB1, // Previous Track key
     _APP_VK_MEDIA_STOP           = 0xB2, // Stop Media key
     _APP_VK_MEDIA_PLAY_PAUSE     = 0xB3, // Play/Pause Media key
     _APP_VK_LAUNCH_MAIL          = 0xB4, // Start Mail key
     _APP_VK_LAUNCH_MEDIA_SELECT  = 0xB5, // Select Media key
     _APP_VK_LAUNCH_APP1          = 0xB6, // Start Application 1 key
     _APP_VK_LAUNCH_APP2          = 0xB7, // Start Application 2 key
     _APP_VK_0xB8                 = 0xB8, // Reserved
     _APP_VK_0xB9                 = 0xB9, // Reserved
     _APP_VK_OEM_1                = 0xBA, // Used for miscellaneous characters;
                                    // it can vary by keyboard.
                                    // For the US standard keyboard, the ';:' key
     _APP_VK_OEM_PLUS             = 0xBB, // For any country/region, the '+' key
     _APP_VK_OEM_COMMA            = 0xBC, // For any country/region, the ',' key
     _APP_VK_OEM_MINUS            = 0xBD, // For any country/region, the '-' key
     _APP_VK_OEM_PERIOD           = 0xBE, // For any country/region, the '.' key
     _APP_VK_OEM_2                = 0xBF, // Used for miscellaneous characters;
                                    // it can vary by keyboard.
                                    // For the US standard keyboard, the '/?' key
     _APP_VK_OEM_3                = 0xC0, // Used for miscellaneous characters;
                                    // it can vary by keyboard. 
                                    // For the US standard keyboard, the '`~' key
     _APP_VK_0xC1                 = 0xC1, // Reserved
     _APP_VK_0xC2                 = 0xC2, // Reserved
     _APP_VK_0xC3                 = 0xC3, // Reserved
     _APP_VK_0xC4                 = 0xC4, // Reserved
     _APP_VK_0xC5                 = 0xC5, // Reserved
     _APP_VK_0xC6                 = 0xC6, // Reserved
     _APP_VK_0xC7                 = 0xC7, // Reserved
     _APP_VK_0xC8                 = 0xC8, // Reserved
     _APP_VK_0xC9                 = 0xC9, // Reserved
     _APP_VK_0xCA                 = 0xCA, // Reserved
     _APP_VK_0xCB                 = 0xCB, // Reserved
     _APP_VK_0xCC                 = 0xCC, // Reserved
     _APP_VK_0xCD                 = 0xCD, // Reserved
     _APP_VK_0xCE                 = 0xCE, // Reserved
     _APP_VK_0xCF                 = 0xCF, // Reserved
     _APP_VK_0xD0                 = 0xD0, // Reserved
     _APP_VK_0xD1                 = 0xD1, // Reserved
     _APP_VK_0xD2                 = 0xD2, // Reserved
     _APP_VK_0xD3                 = 0xD3, // Reserved
     _APP_VK_0xD4                 = 0xD4, // Reserved
     _APP_VK_0xD5                 = 0xD5, // Reserved
     _APP_VK_0xD6                 = 0xD6, // Reserved
     _APP_VK_0xD7                 = 0xD7, // Reserved
     _APP_VK_0xD8                 = 0xD8, // Unassigned
     _APP_VK_0xD9                 = 0xD9, // Unassigned
     _APP_VK_0xDA                 = 0xDA, // Unassigned
     _APP_VK_OEM_4                = 0xDB, // Used for miscellaneous characters;
                                    // it can vary by keyboard.
                                    // For the US standard keyboard, the '[{' key
     _APP_VK_OEM_5                = 0xDC, // Used for miscellaneous characters;
                                    // it can vary by keyboard.
                                    // For the US standard keyboard, the '\|' key
     _APP_VK_OEM_6                = 0xDD, // Used for miscellaneous characters;
                                    // it can vary by keyboard.
                                    // For the US standard keyboard, the ']}' key
     _APP_VK_OEM_7                = 0xDE, // Used for miscellaneous characters;
                                    // it can vary by keyboard.
                                    // For the US standard keyboard, the 'single-quote/double-quote' key
     _APP_VK_OEM_8                = 0xDF, // Used for miscellaneous characters;
                                    // it can vary by keyboard.
     _APP_VK_0xE0                 = 0xE0, // Reserved
     _APP_VK_0xE1                 = 0xE1, // OEM specific
     _APP_VK_OEM_102              = 0xE2, // Either the angle bracket key or the backslash key on the RT 102-key keyboard
     _APP_VK_0xE3                 = 0xE3, // OEM specific
     _APP_VK_0xE4                 = 0xE4, // OEM specific
     _APP_VK_PROCESSKEY           = 0xE5, // IME PROCESS key
     _APP_VK_0xE6                 = 0xE6, // OEM specific
     _APP_VK_PACKET               = 0xE7, // Used to pass Unicode characters as if
                                    // they were keystrokes.
                                    // The  _APP_VK_PACKET key is the low word of a
                                    // 32-bit Virtual Key value used for
                                    // non-keyboard input methods.
                                    // For more information, see Remark in
                                    // KEYBDINPUT, SendInput,  _APP_WM_KEYDOWN,
                                    // and  _APP_WM_KEYUP
     _APP_VK_0xE8                 = 0xE8, // Unassigned
     _APP_VK_0xE9                 = 0xE9, // OEM specific
     _APP_VK_0xEA                 = 0xEA, // OEM specific
     _APP_VK_0xEB                 = 0xEB, // OEM specific
     _APP_VK_0xEC                 = 0xEC, // OEM specific
     _APP_VK_0xED                 = 0xED, // OEM specific
     _APP_VK_0xEE                 = 0xEE, // OEM specific
     _APP_VK_0xEF                 = 0xEF, // OEM specific
     _APP_VK_0xF0                 = 0xF0, // OEM specific
     _APP_VK_0xF1                 = 0xF1, // OEM specific
     _APP_VK_0xF2                 = 0xF2, // OEM specific
     _APP_VK_0xF3                 = 0xF3, // OEM specific
     _APP_VK_0xF4                 = 0xF4, // OEM specific
     _APP_VK_0xF5                 = 0xF5, // OEM specific
     _APP_VK_ATTN                 = 0xF6, // Attn key
     _APP_VK_CRSEL                = 0xF7, // CrSel key
     _APP_VK_EXSEL                = 0xF8, // ExSel key
     _APP_VK_EREOF                = 0xF9, // Erase EOF key
     _APP_VK_PLAY                 = 0xFA, // Play key
     _APP_VK_ZOOM                 = 0xFB, // Zoom key
     _APP_VK_NONAME               = 0xFC, // Reserved
     _APP_VK_PA1                  = 0xFD, // PA1 key
     _APP_VK_OEM_CLEAR            = 0xFE, // Clear key
} VK;

//------------------------------------------------------------------------------

enum {
    _APP_WM_NONE                        = 0,
    _APP_WM_CREATE                      = 0x0001,
    _APP_WM_DESTROY                     = 0x0002,
    _APP_WM_MOVE                        = 0x0003,
    _APP_WM_SIZE                        = 0x0005,
    _APP_WM_ACTIVATE                    = 0x0006,
    _APP_WM_SETFOCUS                    = 0x0007,
    _APP_WM_KILLFOCUS                   = 0x0008,
    _APP_WM_ENABLE                      = 0x000A,
    _APP_WM_SETREDRAW                   = 0x000B,
    _APP_WM_SETTEXT                     = 0x000C,
    _APP_WM_GETTEXT                     = 0x000D,
    _APP_WM_GETTEXTLENGTH               = 0x000E,
    _APP_WM_PAINT                       = 0x000F,
    _APP_WM_CLOSE                       = 0x0010,
    _APP_WM_QUERYENDSESSION             = 0x0011,
    _APP_WM_QUERYOPEN                   = 0x0013,
    _APP_WM_ENDSESSION                  = 0x0016,
    _APP_WM_QUIT                        = 0x0012,
    _APP_WM_ERASEBKGND                  = 0x0014,
    _APP_WM_SYSCOLORCHANGE              = 0x0015,
    _APP_WM_SHOWWINDOW                  = 0x0018,
    _APP_WM_WININICHANGE                = 0x001A,
    _APP_WM_SETTINGCHANGE               =  _APP_WM_WININICHANGE,
    _APP_WM_DEVMODECHANGE               = 0x001B,
    _APP_WM_ACTIVATEAPP                 = 0x001C,
    _APP_WM_FONTCHANGE                  = 0x001D,
    _APP_WM_TIMECHANGE                  = 0x001E,
    _APP_WM_CANCELMODE                  = 0x001F,
    _APP_WM_SETCURSOR                   = 0x0020,
    _APP_WM_MOUSEACTIVATE               = 0x0021,
    _APP_WM_CHILDACTIVATE               = 0x0022,
    _APP_WM_QUEUESYNC                   = 0x0023,
    _APP_WM_GETMINMAXINFO               = 0x0024,
    _APP_WM_PAINTICON                   = 0x0026,
    _APP_WM_ICONERASEBKGND              = 0x0027,
    _APP_WM_NEXTDLGCTL                  = 0x0028,
    _APP_WM_SPOOLERSTATUS               = 0x002A,
    _APP_WM_DRAWITEM                    = 0x002B,
    _APP_WM_MEASUREITEM                 = 0x002C,
    _APP_WM_DELETEITEM                  = 0x002D,
    _APP_WM_VKEYTOITEM                  = 0x002E,
    _APP_WM_CHARTOITEM                  = 0x002F,
    _APP_WM_SETFONT                     = 0x0030,
    _APP_WM_GETFONT                     = 0x0031,
    _APP_WM_SETHOTKEY                   = 0x0032,
    _APP_WM_GETHOTKEY                   = 0x0033,
    _APP_WM_QUERYDRAGICON               = 0x0037,
    _APP_WM_COMPAREITEM                 = 0x0039,
    _APP_WM_GETOBJECT                   = 0x003D,
    _APP_WM_COMPACTING                  = 0x0041,
    _APP_WM_COMMNOTIFY                  = 0x0044,
    _APP_WM_WINDOWPOSCHANGING           = 0x0046,
    _APP_WM_WINDOWPOSCHANGED            = 0x0047,
    _APP_WM_POWER                       = 0x0048,
    _APP_WM_COPYDATA                    = 0x004A,
    _APP_WM_CANCELJOURNAL               = 0x004B,
    _APP_WM_NOTIFY                      = 0x004E,
    _APP_WM_INPUTLANGCHANGEREQUEST      = 0x0050,
    _APP_WM_INPUTLANGCHANGE             = 0x0051,
    _APP_WM_TCARD                       = 0x0052,
    _APP_WM_HELP                        = 0x0053,
    _APP_WM_USERCHANGED                 = 0x0054,
    _APP_WM_NOTIFYFORMAT                = 0x0055,
    _APP_WM_CONTEXTMENU                 = 0x007B,
    _APP_WM_STYLECHANGING               = 0x007C,
    _APP_WM_STYLECHANGED                = 0x007D,
    _APP_WM_DISPLAYCHANGE               = 0x007E,
    _APP_WM_GETICON                     = 0x007F,
    _APP_WM_SETICON                     = 0x0080,
    _APP_WM_NCCREATE                    = 0x0081,
    _APP_WM_NCDESTROY                   = 0x0082,
    _APP_WM_NCCALCSIZE                  = 0x0083,
    _APP_WM_NCHITTEST                   = 0x0084,
    _APP_WM_NCPAINT                     = 0x0085,
    _APP_WM_NCACTIVATE                  = 0x0086,
    _APP_WM_GETDLGCODE                  = 0x0087,
    _APP_WM_SYNCPAINT                   = 0x0088,
    _APP_WM_NCMOUSEMOVE                 = 0x00A0,
    _APP_WM_NCLBUTTONDOWN               = 0x00A1,
    _APP_WM_NCLBUTTONUP                 = 0x00A2,
    _APP_WM_NCLBUTTONDBLCLK             = 0x00A3,
    _APP_WM_NCRBUTTONDOWN               = 0x00A4,
    _APP_WM_NCRBUTTONUP                 = 0x00A5,
    _APP_WM_NCRBUTTONDBLCLK             = 0x00A6,
    _APP_WM_NCMBUTTONDOWN               = 0x00A7,
    _APP_WM_NCMBUTTONUP                 = 0x00A8,
    _APP_WM_NCMBUTTONDBLCLK             = 0x00A9,
    _APP_WM_NCXBUTTONDOWN               = 0x00AB,
    _APP_WM_NCXBUTTONUP                 = 0x00AC,
    _APP_WM_NCXBUTTONDBLCLK             = 0x00AD,
    _APP_WM_INPUT_DEVICE_CHANGE         = 0x00FE,
    _APP_WM_INPUT                       = 0x00FF,
    _APP_WM_KEYDOWN                     = 0x0100,
    _APP_WM_KEYFIRST                    =  _APP_WM_KEYDOWN,
    _APP_WM_KEYUP                       = 0x0101,
    _APP_WM_CHAR                        = 0x0102,
    _APP_WM_DEADCHAR                    = 0x0103,
    _APP_WM_SYSKEYDOWN                  = 0x0104,
    _APP_WM_SYSKEYUP                    = 0x0105,
    _APP_WM_SYSCHAR                     = 0x0106,
    _APP_WM_SYSDEADCHAR                 = 0x0107,
    _APP_WM_UNICHAR                     = 0x0109,
    _APP_WM_KEYLAST                     =  _APP_WM_UNICHAR,
    _APP_WM_IME_STARTCOMPOSITION        = 0x010D,
    _APP_WM_IME_ENDCOMPOSITION          = 0x010E,
    _APP_WM_IME_COMPOSITION             = 0x010F,
    _APP_WM_IME_KEYLAST                 = 0x010F,
    _APP_WM_INITDIALOG                  = 0x0110,
    _APP_WM_COMMAND                     = 0x0111,
    _APP_WM_SYSCOMMAND                  = 0x0112,
    _APP_WM_TIMER                       = 0x0113,
    _APP_WM_HSCROLL                     = 0x0114,
    _APP_WM_VSCROLL                     = 0x0115,
    _APP_WM_INITMENU                    = 0x0116,
    _APP_WM_INITMENUPOPUP               = 0x0117,
    _APP_WM_MENUSELECT                  = 0x011F,
    _APP_WM_MENUCHAR                    = 0x0120,
    _APP_WM_ENTERIDLE                   = 0x0121,
    _APP_WM_MENURBUTTONUP               = 0x0122,
    _APP_WM_MENUDRAG                    = 0x0123,
    _APP_WM_MENUGETOBJECT               = 0x0124,
    _APP_WM_UNINITMENUPOPUP             = 0x0125,
    _APP_WM_MENUCOMMAND                 = 0x0126,
    _APP_WM_CHANGEUISTATE               = 0x0127,
    _APP_WM_UPDATEUISTATE               = 0x0128,
    _APP_WM_QUERYUISTATE                = 0x0129,
    _APP_WM_CTLCOLORMSGBOX              = 0x0132,
    _APP_WM_CTLCOLOREDIT                = 0x0133,
    _APP_WM_CTLCOLORLISTBOX             = 0x0134,
    _APP_WM_CTLCOLORBTN                 = 0x0135,
    _APP_WM_CTLCOLORDLG                 = 0x0136,
    _APP_WM_CTLCOLORSCROLLBAR           = 0x0137,
    _APP_WM_CTLCOLORSTATIC              = 0x0138,
    _APP_WM_MOUSEMOVE                   = 0x0200,
    _APP_WM_MOUSEFIRST                  =  _APP_WM_MOUSEMOVE,
    _APP_WM_LBUTTONDOWN                 = 0x0201,
    _APP_WM_LBUTTONUP                   = 0x0202,
    _APP_WM_LBUTTONDBLCLK               = 0x0203,
    _APP_WM_RBUTTONDOWN                 = 0x0204,
    _APP_WM_RBUTTONUP                   = 0x0205,
    _APP_WM_RBUTTONDBLCLK               = 0x0206,
    _APP_WM_MBUTTONDOWN                 = 0x0207,
    _APP_WM_MBUTTONUP                   = 0x0208,
    _APP_WM_MBUTTONDBLCLK               = 0x0209,
    _APP_WM_MOUSEWHEEL                  = 0x020A,
    _APP_WM_XBUTTONDOWN                 = 0x020B,
    _APP_WM_XBUTTONUP                   = 0x020C,
    _APP_WM_XBUTTONDBLCLK               = 0x020D,
    _APP_WM_MOUSEHWHEEL                 = 0x020E,
    _APP_WM_MOUSELAST                   =  _APP_WM_MOUSEHWHEEL,
    _APP_WM_PARENTNOTIFY                = 0x0210,
    _APP_WM_ENTERMENULOOP               = 0x0211,
    _APP_WM_EXITMENULOOP                = 0x0212,
    _APP_WM_NEXTMENU                    = 0x0213,
    _APP_WM_SIZING                      = 0x0214,
    _APP_WM_CAPTURECHANGED              = 0x0215,
    _APP_WM_MOVING                      = 0x0216,
    _APP_WM_POWERBROADCAST              = 0x0218,
    _APP_WM_DEVICECHANGE                = 0x0219,
    _APP_WM_MDICREATE                   = 0x0220,
    _APP_WM_MDIDESTROY                  = 0x0221,
    _APP_WM_MDIACTIVATE                 = 0x0222,
    _APP_WM_MDIRESTORE                  = 0x0223,
    _APP_WM_MDINEXT                     = 0x0224,
    _APP_WM_MDIMAXIMIZE                 = 0x0225,
    _APP_WM_MDITILE                     = 0x0226,
    _APP_WM_MDICASCADE                  = 0x0227,
    _APP_WM_MDIICONARRANGE              = 0x0228,
    _APP_WM_MDIGETACTIVE                = 0x0229,
    _APP_WM_MDISETMENU                  = 0x0230,
    _APP_WM_ENTERSIZEMOVE               = 0x0231,
    _APP_WM_EXITSIZEMOVE                = 0x0232,
    _APP_WM_DROPFILES                   = 0x0233,
    _APP_WM_MDIREFRESHMENU              = 0x0234,
    _APP_WM_IME_SETCONTEXT              = 0x0281,
    _APP_WM_IME_NOTIFY                  = 0x0282,
    _APP_WM_IME_CONTROL                 = 0x0283,
    _APP_WM_IME_COMPOSITIONFULL         = 0x0284,
    _APP_WM_IME_SELECT                  = 0x0285,
    _APP_WM_IME_CHAR                    = 0x0286,
    _APP_WM_IME_REQUEST                 = 0x0288,
    _APP_WM_IME_KEYDOWN                 = 0x0290,
    _APP_WM_IME_KEYUP                   = 0x0291,
    _APP_WM_MOUSEHOVER                  = 0x02A1,
    _APP_WM_MOUSELEAVE                  = 0x02A3,
    _APP_WM_NCMOUSEHOVER                = 0x02A0,
    _APP_WM_NCMOUSELEAVE                = 0x02A2,
    _APP_WM_WTSSESSION_CHANGE           = 0x02B1,
    _APP_WM_TABLET_FIRST                = 0x02c0,
    _APP_WM_TABLET_LAST                 = 0x02df,
    _APP_WM_CUT                         = 0x0300,
    _APP_WM_COPY                        = 0x0301,
    _APP_WM_PASTE                       = 0x0302,
    _APP_WM_CLEAR                       = 0x0303,
    _APP_WM_UNDO                        = 0x0304,
    _APP_WM_RENDERFORMAT                = 0x0305,
    _APP_WM_RENDERALLFORMATS            = 0x0306,
    _APP_WM_DESTROYCLIPBOARD            = 0x0307,
    _APP_WM_DRAWCLIPBOARD               = 0x0308,
    _APP_WM_PAINTCLIPBOARD              = 0x0309,
    _APP_WM_VSCROLLCLIPBOARD            = 0x030A,
    _APP_WM_SIZECLIPBOARD               = 0x030B,
    _APP_WM_ASKCBFORMATNAME             = 0x030C,
    _APP_WM_CHANGECBCHAIN               = 0x030D,
    _APP_WM_HSCROLLCLIPBOARD            = 0x030E,
    _APP_WM_QUERYNEWPALETTE             = 0x030F,
    _APP_WM_PALETTEISCHANGING           = 0x0310,
    _APP_WM_PALETTECHANGED              = 0x0311,
    _APP_WM_HOTKEY                      = 0x0312,
    _APP_WM_PRINT                       = 0x0317,
    _APP_WM_PRINTCLIENT                 = 0x0318,
    _APP_WM_APPCOMMAND                  = 0x0319,
    _APP_WM_THEMECHANGED                = 0x031A,
    _APP_WM_CLIPBOARDUPDATE             = 0x031D,
    _APP_WM_DWMCOMPOSITIONCHANGED       = 0x031E,
    _APP_WM_DWMNCRENDERINGCHANGED       = 0x031F,
    _APP_WM_DWMCOLORIZATIONCOLORCHANGED = 0x0320,
    _APP_WM_DWMWINDOWMAXIMIZEDCHANGE    = 0x0321,
    _APP_WM_GETTITLEBARINFOEX           = 0x033F,
    _APP_WM_HANDHELDFIRST               = 0x0358,
    _APP_WM_HANDHELDLAST                = 0x035F,
    _APP_WM_AFXFIRST                    = 0x0360,
    _APP_WM_AFXLAST                     = 0x037F,
    _APP_WM_PENWINFIRST                 = 0x0380,
    _APP_WM_PENWINLAST                  = 0x038F,
    _APP_WM_APP                         = 0x8000,
    _APP_WM_USER                        = 0x0400,
    _APP_WM_CPL_LAUNCH                  =  _APP_WM_USER + 0x1000,
    _APP_WM_CPL_LAUNCHED                =  _APP_WM_USER + 0x1001,
    _APP_WM_SYSTIMER                    = 0x118,
};

//------------------------------------------------------------------------------

APP_EXTERN_C_BEGIN

//------------------------------------------------------------------------------

app_dll(_app_kernel32, "kernel32.dll")

app_dllimport(
    _app_kernel32,
    stdcall_alias(int,         _app_FreeEnvironmentStringsA, FreeEnvironmentStringsA,(const char*)),
    stdcall_alias(const char*, _app_GetEnvironmentStringsA,  GetEnvironmentStringsA,(void)),
    stdcall_alias(void*,       _app_GetModuleHandleA,        GetModuleHandleA,(const char*)),
    stdcall_alias(int,         _app_WideCharToMultiByte,     WideCharToMultiByte,(unsigned CodePage, unsigned dwFlags, const uint16_t* lpWideCharStr, int cchWideChar, char* lpMultiByteStr, int cbMultiByte, const char* lpDefaultChar, bool* lpUsedDefaultChar)),
)

//------------------------------------------------------------------------------

app_dll(_app_user32, "user32.dll")

app_dllimport(
    _app_user32,
    stdcall_alias(int,      _app_AdjustWindowRectEx,  AdjustWindowRectEx,(void* lpRect, unsigned, int, unsigned)),
    stdcall_alias(void*,    _app_CreateWindowExA,     CreateWindowExA,(unsigned dwExStyle, const char* lpClassName, const char* lpWindowName, unsigned dwStyle, int X, int Y, int nWidth, int nHeight, void* hWndParent, void* hMenu, void* hInstance, void* lpParam)),
    stdcall_alias(size_t,   _app_DefWindowProcA,      DefWindowProcA,(void* hWnd, unsigned, size_t, size_t)),
    stdcall_alias(int,      _app_DestroyWindow,       DestroyWindow,(void* hWnd)),
    stdcall_alias(size_t,   _app_DispatchMessageA,    DispatchMessageA,(const void* lpMsg)),
    stdcall_alias(void*,    _app_GetActiveWindow,     GetActiveWindow,(void)),
    stdcall_alias(int,      _app_GetClientRect,       GetClientRect,(void* hWnd, void* lpRect)),
    stdcall_alias(int,      _app_GetCursorPos,        GetCursorPos,(void* lpPoint)),
    stdcall_alias(void*,    _app_GetForegroundWindow, GetForegroundWindow,(void)),
    stdcall_alias(size_t,   _app_GetWindowLongPtrA,   GetWindowLongPtrA,(void* hWnd, int nIndex)),
    stdcall_alias(int,      _app_GetWindowPlacement,  GetWindowPlacement,(void* hWnd, void* lpwndpl)),
    stdcall_alias(int,      _app_GetWindowRect,       GetWindowRect,(void* hWnd, void* lpRect)),
    stdcall_alias(int,      _app_IsWindowVisible,     IsWindowVisible,(void* hWnd)),
    stdcall_alias(int,      _app_PeekMessageA,        PeekMessageA,(void* lpMsg, void* hWnd, unsigned wMsgFilterMin, unsigned wMsgFilterMax, unsigned wRemoveMsg)),
    stdcall_alias(uint16_t, _app_RegisterClassExA,    RegisterClassExA,(const void* wndClassExA)),
    stdcall_alias(int,      _app_SetActiveWindow,     SetActiveWindow,(void* hWnd)),
    stdcall_alias(int,      _app_SetForegroundWindow, SetForegroundWindow,(void* hWnd)),
    stdcall_alias(size_t,   _app_SetWindowLongPtrA,   SetWindowLongPtrA,(void* hWnd, int nIndex, size_t)),
    stdcall_alias(int,      _app_SetWindowPlacement,  SetWindowPlacement,(void* hWnd, const void* lpwndpl)),
    stdcall_alias(int,      _app_SetWindowPos,        SetWindowPos,(void* hWnd, void* hWndInsertAfter, int X, int Y, int cx, int cy, unsigned uFlags)),
    stdcall_alias(int,      _app_SetWindowTextA,      SetWindowTextA,(void* hWnd, const char*)),
    stdcall_alias(int,      _app_ShowWindow,          ShowWindow,(void* hWnd, int nCmdShow)),
    stdcall_alias(size_t,   _app_TranslateMessage,    TranslateMessage,(const void* lpMsg)),

    stdcall_alias(int,      _app_GetKeyboardState,    GetKeyboardState,(void*)),
    stdcall_alias(int,      _app_GetMonitorInfoA,     GetMonitorInfoA,(void* hMonitor, void* lpmi)),
    stdcall_alias(void*,    _app_MonitorFromRect,     MonitorFromRect,(const void* lprc, unsigned dwFlags)),
    stdcall_alias(void*,    _app_LoadCursorA,         LoadCursorA,(void* hInstance, const char* lpCursorName)),
    stdcall_alias(void*,    _app_LoadIconA,           LoadIconA,(void* hInstance, const char* lpCursorName)),
    stdcall_alias(void*,    _app_SetCursor,           SetCursor,(void* hCursor)),
)

//------------------------------------------------------------------------------

APP_EXTERN_C_END

//------------------------------------------------------------------------------
