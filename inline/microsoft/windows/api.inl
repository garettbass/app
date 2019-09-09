#pragma once
#include "../../../app_dll.h"

//------------------------------------------------------------------------------

typedef uint16_t       ATOM;
typedef uint8_t        BYTE;
typedef int32_t        BOOL;
typedef uint32_t       UINT;
typedef char*          LPSTR;
typedef const char*    LPCSTR;
typedef uint16_t       WORD;
typedef uint32_t       DWORD;
typedef uint32_t       LONG;
typedef uint64_t       LONGLONG;
typedef uintptr_t      DWORD_PTR;
typedef intptr_t       INT_PTR;
typedef intptr_t       LONG_PTR;
typedef uintptr_t      UINT_PTR;
typedef uint32_t       HRESULT;
typedef void*          FARPROC;
typedef struct MODULE* HMODULE;
typedef LONG_PTR       LRESULT;
typedef void*          LPVOID;

//------------------------------------------------------------------------------

typedef struct DC*        HDC;
typedef struct MENU*      HMENU;
typedef struct ICON*      HICON;
typedef struct BRUSH*     HBRUSH;
typedef struct CURSOR*    HCURSOR;
typedef struct GDIOBJ*    HGDIOBJ;
typedef struct INSTANCE*  HINSTANCE;
typedef struct MONITOR*   HMONITOR;
typedef struct WND*       HWND;

//------------------------------------------------------------------------------

#define HWND_BOTTOM    ((HWND) 1);
#define HWND_NOTOPMOST ((HWND)-2);
#define HWND_TOP       ((HWND) 0);
#define HWND_TOPMOST   ((HWND)-1);

typedef struct WNDCLASSEXA WNDCLASSEXA;

//------------------------------------------------------------------------------

typedef struct POINT {
    LONG x, y;
} POINT, *PPOINT;

typedef union RECT {
    struct { LONG left, top, right, bottom; };
    struct { POINT min, max; };
} RECT, *LPRECT;
typedef const RECT *LPCRECT;

//------------------------------------------------------------------------------

typedef enum CS {
    CS_NONE            = 0,
    CS_VREDRAW         = 0x00000001,
    CS_HREDRAW         = 0x00000002,
    CS_DBLCLKS         = 0x00000008,
    CS_OWNDC           = 0x00000020,
    CS_CLASSDC         = 0x00000040,
    CS_PARENTDC        = 0x00000080,
    CS_NOCLOSE         = 0x00000200,
    CS_SAVEBITS        = 0x00000800,
    CS_BYTEALIGNCLIENT = 0x00001000,
    CS_BYTEALIGNWINDOW = 0x00002000,
    CS_GLOBALCLASS     = 0x00004000,
    CS_DROPSHADOW      = 0x00020000,
} CS;

//------------------------------------------------------------------------------

typedef enum CLR {
    CLR_ACTIVEBORDER            = 10,
    CLR_ACTIVECAPTION           = 2,
    CLR_APPWORKSPACE            = 12,
    CLR_BACKGROUND              = 1,
    CLR_BTNFACE                 = 15,
    CLR_BTNHIGHLIGHT            = 20,
    CLR_BTNSHADOW               = 16,
    CLR_BTNTEXT                 = 18,
    CLR_CAPTIONTEXT             = 9,
    CLR_DESKTOP                 = 1,
    CLR_DKSHADOW_3D             = 21,
    CLR_FACE_3D                 = 15,
    CLR_GRADIENTACTIVECAPTION   = 27,
    CLR_GRADIENTINACTIVECAPTION = 28,
    CLR_GRAYTEXT                = 17,
    CLR_HIGHLIGHT               = 13,
    CLR_HIGHLIGHT_3D            = 20,
    CLR_HIGHLIGHTTEXT           = 14,
    CLR_HOTLIGHT                = 26,
    CLR_INACTIVEBORDER          = 11,
    CLR_INACTIVECAPTION         = 3,
    CLR_INACTIVECAPTIONTEXT     = 19,
    CLR_INFOBK                  = 24,
    CLR_INFOTEXT                = 23,
    CLR_LIGHT_3D                = 22,
    CLR_MENU                    = 4,
    CLR_MENUBAR                 = 30,
    CLR_MENUHILIGHT             = 29,
    CLR_MENUTEXT                = 7,
    CLR_SCROLLBAR               = 0,
    CLR_SHADOW_3D               = 16,
    CLR_WINDOW                  = 5,
    CLR_WINDOWFRAME             = 6,
    CLR_WINDOWTEXT              = 8,
} CLR;

//------------------------------------------------------------------------------

typedef enum GWL {
    GWL_WNDPROC    = -4,
    GWL_HINSTANCE  = -6,
    GWL_HWNDPARENT = -8,
    GWL_STYLE      = -16,
    GWL_EXSTYLE    = -20,
    GWL_USERDATA   = -21,
    GWL_ID         = -12,
} GWL;

//------------------------------------------------------------------------------

typedef enum IDC {
    IDC_APPSTARTING = 32650,
    IDC_ARROW       = 32512,
    IDC_CROSS       = 32515,
    IDC_HAND        = 32649,
    IDC_HELP        = 32651,
    IDC_IBEAM       = 32513,
    IDC_ICON        = 32641,
    IDC_NO          = 32648,
    IDC_SIZE        = 32640,
    IDC_SIZEALL     = 32646,
    IDC_SIZENESW    = 32643,
    IDC_SIZENS      = 32645,
    IDC_SIZENWSE    = 32642,
    IDC_SIZEWE      = 32644,
    IDC_UPARROW     = 32516,
    IDC_WAIT        = 32514,
} IDC;

//------------------------------------------------------------------------------

typedef enum IDI {
    IDI_APPLICATION     = 32512,
    IDI_HAND            = 32513,
    IDI_QUESTION        = 32514,
    IDI_EXCLAMATION     = 32515,
    IDI_ASTERISK        = 32516,
    IDI_WINLOGO         = 32517,
    IDI_SHIELD          = 32518,
} IDI;

//------------------------------------------------------------------------------

typedef enum PDA {
    PDA_UNAWARE           = 0,
    PDA_SYSTEM_DPI_AWARE  = 1,
    PDA_MONITOR_DPI_AWARE = 2,
} PDA;

//------------------------------------------------------------------------------

typedef enum WS {
    WS_NONE             = 0L,
    WS_BORDER           = 0x00800000L,
    WS_CAPTION          = 0x00C00000L,
    WS_CHILD            = 0x40000000L,
    WS_CHILDWINDOW      = 0x40000000L,
    WS_CLIPCHILDREN     = 0x02000000L,
    WS_CLIPSIBLINGS     = 0x04000000L,
    WS_DISABLED         = 0x08000000L,
    WS_DLGFRAME         = 0x00400000L,
    WS_GROUP            = 0x00020000L,
    WS_HSCROLL          = 0x00100000L,
    WS_ICONIC           = 0x20000000L,
    WS_MAXIMIZE         = 0x01000000L,
    WS_MAXIMIZEBOX      = 0x00010000L,
    WS_MINIMIZE         = 0x20000000L,
    WS_MINIMIZEBOX      = 0x00020000L,
    WS_OVERLAPPED       = 0x00000000L,
    WS_POPUP            = 0x80000000L,
    WS_SIZEBOX          = 0x00040000L,
    WS_SYSMENU          = 0x00080000L,
    WS_TABSTOP          = 0x00010000L,
    WS_THICKFRAME       = 0x00040000L,
    WS_TILED            = 0x00000000L,
    WS_VISIBLE          = 0x10000000L,
    WS_VSCROLL          = 0x00200000L,
    WS_OVERLAPPEDWINDOW = WS_CAPTION
                        | WS_SYSMENU
                        | WS_THICKFRAME
                        | WS_MINIMIZEBOX
                        | WS_MAXIMIZEBOX,
    WS_POPUPWINDOW      = WS_POPUP
                        | WS_BORDER
                        | WS_SYSMENU,
    WS_TILEDWINDOW      = WS_CAPTION
                        | WS_SYSMENU
                        | WS_THICKFRAME
                        | WS_MINIMIZEBOX
                        | WS_MAXIMIZEBOX,
} WS;

//------------------------------------------------------------------------------

typedef enum WS_EX {
    WS_EX_NONE                = 0L,
    WS_EX_ACCEPTFILES         = 0x00000010L,
    WS_EX_app_window           = 0x00040000L,
    WS_EX_CLIENTEDGE          = 0x00000200L,
    WS_EX_COMPOSITED          = 0x02000000L,
    WS_EX_CONTEXTHELP         = 0x00000400L,
    WS_EX_CONTROLPARENT       = 0x00010000L,
    WS_EX_DLGMODALFRAME       = 0x00000001L,
    WS_EX_LAYERED             = 0x00080000,
    WS_EX_LAYOUTRTL           = 0x00400000L,
    WS_EX_LEFT                = 0x00000000L,
    WS_EX_LEFTSCROLLBAR       = 0x00004000L,
    WS_EX_LTRREADING          = 0x00000000L,
    WS_EX_MDICHILD            = 0x00000040L,
    WS_EX_NOACTIVATE          = 0x08000000L,
    WS_EX_NOINHERITLAYOUT     = 0x00100000L,
    WS_EX_NOPARENTNOTIFY      = 0x00000004L,
    WS_EX_NOREDIRECTIONBITMAP = 0x00200000L,
    WS_EX_RIGHT               = 0x00001000L,
    WS_EX_RIGHTSCROLLBAR      = 0x00000000L,
    WS_EX_RTLREADING          = 0x00002000L,
    WS_EX_STATICEDGE          = 0x00020000L,
    WS_EX_TOOLWINDOW          = 0x00000080L,
    WS_EX_TOPMOST             = 0x00000008L,
    WS_EX_TRANSPARENT         = 0x00000020L,
    WS_EX_WINDOWEDGE          = 0x00000100L,
    WS_EX_OVERLAPPEDWINDOW    = WS_EX_WINDOWEDGE | WS_EX_CLIENTEDGE,
    WS_EX_PALETTEWINDOW       = WS_EX_WINDOWEDGE | WS_EX_TOOLWINDOW | WS_EX_TOPMOST,
} WS_EX;

//------------------------------------------------------------------------------

typedef enum WPF {
    WPF_NONE                 = 0x0000,
    WPF_SETMINPOSITION       = 0x0001,
    WPF_RESTORETOMAXIMIZED   = 0x0002,
    WPF_ASYNCWINDOWPLACEMENT = 0x0004,
} WPF;

//------------------------------------------------------------------------------

typedef enum GWLP {
    GWLP_EXSTYLE   = -20,
    GWLP_HINSTANCE =  -6,
    GWLP_ID        = -12,
    GWLP_STYLE     = -16,
    GWLP_USERDATA  = -21,
    GWLP_WNDPROC   =  -4,
} GWLP;

//------------------------------------------------------------------------------

typedef enum MI {
    MI_NONE    = 0,
    MI_PRIMARY = 0x00000001,
} MI;

//------------------------------------------------------------------------------

typedef enum MONITOR_DEFAULT {
    MONITOR_DEFAULTTONONE    = 0,
    MONITOR_DEFAULTTOPRIMARY = 0x00000001,
    MONITOR_DEFAULTTONEAREST = 0x00000002,
} MONITOR_DEFAULT;

//------------------------------------------------------------------------------

typedef enum PM {
    PM_NOREMOVE = 0x0000,
    PM_REMOVE   = 0x0001,
    PM_NOYIELD  = 0x0002,
} PM;

//------------------------------------------------------------------------------

typedef enum OBJ {
    OBJ_ANSI_FIXED_FONT     = 11,
    OBJ_ANSI_VAR_FONT       = 12,
    OBJ_BLACK_BRUSH         = 4,
    OBJ_BLACK_PEN           = 7,
    OBJ_DC_BRUSH            = 18,
    OBJ_DC_PEN              = 19,
    OBJ_DEFAULT_GUI_FONT    = 17,
    OBJ_DEVICE_DEFAULT_FONT = 14,
    OBJ_DKGRAY_BRUSH        = 3,
    OBJ_GRAY_BRUSH          = 2,
    OBJ_LTGRAY_BRUSH        = 1,
    OBJ_NULL_BRUSH          = 5,
    OBJ_NULL_PEN            = 8,
    OBJ_OEM_FIXED_FONT      = 10,
    OBJ_SYSTEM_FIXED_FONT   = 16,
    OBJ_SYSTEM_FONT         = 13,
    OBJ_WHITE_BRUSH         = 0,
    OBJ_WHITE_PEN           = 6,
} OBJ;

//------------------------------------------------------------------------------

typedef enum SW {
    SW_HIDE            = 0,
    SW_SHOWNORMAL      = 1,
    SW_SHOWMINIMIZED   = 2,
    SW_SHOWMAXIMIZED   = 3,
    SW_MAXIMIZE        = 3,
    SW_SHOWNOACTIVATE  = 4,
    SW_SHOW            = 5,
    SW_MINIMIZE        = 6,
    SW_SHOWMINNOACTIVE = 7,
    SW_SHOWNA          = 8,
    SW_RESTORE         = 9,
    SW_SHOWDEFAULT     = 10,
    SW_FORCEMINIMIZE   = 11,
} SW;

//------------------------------------------------------------------------------

typedef enum SWP {
    SWP_ASYNCWINDOWPOS = 0x4000,
    SWP_DEFERERASE     = 0x2000,
    SWP_DRAWFRAME      = 0x0020,
    SWP_FRAMECHANGED   = 0x0020,
    SWP_HIDEWINDOW     = 0x0080,
    SWP_NOACTIVATE     = 0x0010,
    SWP_NOCOPYBITS     = 0x0100,
    SWP_NOMOVE         = 0x0002,
    SWP_NOOWNERZORDER  = 0x0200,
    SWP_NOREDRAW       = 0x0008,
    SWP_NOREPOSITION   = 0x0200,
    SWP_NOSENDCHANGING = 0x0400,
    SWP_NOSIZE         = 0x0001,
    SWP_NOZORDER       = 0x0004,
    SWP_SHOWWINDOW     = 0x0040,
} SWP;

typedef enum VK {
    VK_LBUTTON              = 0x01, // Left mouse button
    VK_RBUTTON              = 0x02, // Right mouse button
    VK_CANCEL               = 0x03, // Control-break processing
    VK_MBUTTON              = 0x04, // Middle mouse button (three-button mouse)
    VK_XBUTTON1             = 0x05, // X1 mouse button
    VK_XBUTTON2             = 0x06, // X2 mouse button
    VK_0x07                 = 0x07, // Undefined
    VK_BACK                 = 0x08, // BACKSPACE key
    VK_TAB                  = 0x09, // TAB key
    VK_0x0A                 = 0x0A, // Reserved
    VK_0x0B                 = 0x0B, // Reserved
    VK_CLEAR                = 0x0C, // CLEAR key
    VK_RETURN               = 0x0D, // ENTER key
    VK_0x0E                 = 0x0E, // Undefined
    VK_0x0F                 = 0x0F, // Undefined
    VK_SHIFT                = 0x10, // SHIFT key
    VK_CONTROL              = 0x11, // CTRL key
    VK_MENU                 = 0x12, // ALT key
    VK_PAUSE                = 0x13, // PAUSE key
    VK_CAPITAL              = 0x14, // CAPS LOCK key
    VK_KANA                 = 0x15, // IME Kana mode
    VK_HANGUL               = 0x15, // IME Hangul mode
    VK_0x16                 = 0x16, // Undefined
    VK_JUNJA                = 0x17, // IME Junja mode
    VK_FINAL                = 0x18, // IME final mode
    VK_HANJA                = 0x19, // IME Hanja mode
    VK_KANJI                = 0x19, // IME Kanji mode
    VK_0x1A                 = 0x1A, // Undefined
    VK_ESCAPE               = 0x1B, // ESC key
    VK_CONVERT              = 0x1C, // IME convert
    VK_NONCONVERT           = 0x1D, // IME nonconvert
    VK_ACCEPT               = 0x1E, // IME accept
    VK_MODECHANGE           = 0x1F, // IME mode change request
    VK_SPACE                = 0x20, // SPACEBAR
    VK_PRIOR                = 0x21, // PAGE UP key
    VK_NEXT                 = 0x22, // PAGE DOWN key
    VK_END                  = 0x23, // END key
    VK_HOME                 = 0x24, // HOME key
    VK_LEFT                 = 0x25, // LEFT ARROW key
    VK_UP                   = 0x26, // UP ARROW key
    VK_RIGHT                = 0x27, // RIGHT ARROW key
    VK_DOWN                 = 0x28, // DOWN ARROW key
    VK_SELECT               = 0x29, // SELECT key
    VK_PRINT                = 0x2A, // PRINT key
    VK_EXECUTE              = 0x2B, // EXECUTE key
    VK_SNAPSHOT             = 0x2C, // PRINT SCREEN key
    VK_INSERT               = 0x2D, // INS key
    VK_DELETE               = 0x2E, // DEL key
    VK_HELP                 = 0x2F, // HELP key
    VK_0                    = 0x30, // 0 key
    VK_1                    = 0x31, // 1 key
    VK_2                    = 0x32, // 2 key
    VK_3                    = 0x33, // 3 key
    VK_4                    = 0x34, // 4 key
    VK_5                    = 0x35, // 5 key
    VK_6                    = 0x36, // 6 key
    VK_7                    = 0x37, // 7 key
    VK_8                    = 0x38, // 8 key
    VK_9                    = 0x39, // 9 key
    VK_0x3A                 = 0x3A, // Undefined
    VK_0x3B                 = 0x3B, // Undefined
    VK_0x3C                 = 0x3C, // Undefined
    VK_0x3D                 = 0x3D, // Undefined
    VK_0x3E                 = 0x3E, // Undefined
    VK_0x3F                 = 0x3F, // Undefined
    VK_0x40                 = 0x40, // Undefined
    VK_A                    = 0x41, // A key
    VK_B                    = 0x42, // B key
    VK_C                    = 0x43, // C key
    VK_D                    = 0x44, // D key
    VK_E                    = 0x45, // E key
    VK_F                    = 0x46, // F key
    VK_G                    = 0x47, // G key
    VK_H                    = 0x48, // H key
    VK_I                    = 0x49, // I key
    VK_J                    = 0x4A, // J key
    VK_K                    = 0x4B, // K key
    VK_L                    = 0x4C, // L key
    VK_M                    = 0x4D, // M key
    VK_N                    = 0x4E, // N key
    VK_O                    = 0x4F, // O key
    VK_P                    = 0x50, // P key
    VK_Q                    = 0x51, // Q key
    VK_R                    = 0x52, // R key
    VK_S                    = 0x53, // S key
    VK_T                    = 0x54, // T key
    VK_U                    = 0x55, // U key
    VK_V                    = 0x56, // V key
    VK_W                    = 0x57, // W key
    VK_X                    = 0x58, // X key
    VK_Y                    = 0x59, // Y key
    VK_Z                    = 0x5A, // Z key
    VK_LWIN                 = 0x5B, // Left Windows key (Natural keyboard) 
    VK_RWIN                 = 0x5C, // Right Windows key (Natural keyboard)
    VK_APPS                 = 0x5D, // Applications key (Natural keyboard)
    VK_0x5E                 = 0x5E, // Reserved
    VK_SLEEP                = 0x5F, // Computer Sleep key
    VK_NUMPAD0              = 0x60, // Numeric keypad 0 key
    VK_NUMPAD1              = 0x61, // Numeric keypad 1 key
    VK_NUMPAD2              = 0x62, // Numeric keypad 2 key
    VK_NUMPAD3              = 0x63, // Numeric keypad 3 key
    VK_NUMPAD4              = 0x64, // Numeric keypad 4 key
    VK_NUMPAD5              = 0x65, // Numeric keypad 5 key
    VK_NUMPAD6              = 0x66, // Numeric keypad 6 key
    VK_NUMPAD7              = 0x67, // Numeric keypad 7 key
    VK_NUMPAD8              = 0x68, // Numeric keypad 8 key
    VK_NUMPAD9              = 0x69, // Numeric keypad 9 key
    VK_MULTIPLY             = 0x6A, // Multiply key
    VK_ADD                  = 0x6B, // Add key
    VK_SEPARATOR            = 0x6C, // Separator key
    VK_SUBTRACT             = 0x6D, // Subtract key
    VK_DECIMAL              = 0x6E, // Decimal key
    VK_DIVIDE               = 0x6F, // Divide key
    VK_F1                   = 0x70, // F1 key
    VK_F2                   = 0x71, // F2 key
    VK_F3                   = 0x72, // F3 key
    VK_F4                   = 0x73, // F4 key
    VK_F5                   = 0x74, // F5 key
    VK_F6                   = 0x75, // F6 key
    VK_F7                   = 0x76, // F7 key
    VK_F8                   = 0x77, // F8 key
    VK_F9                   = 0x78, // F9 key
    VK_F10                  = 0x79, // F10 key
    VK_F11                  = 0x7A, // F11 key
    VK_F12                  = 0x7B, // F12 key
    VK_F13                  = 0x7C, // F13 key
    VK_F14                  = 0x7D, // F14 key
    VK_F15                  = 0x7E, // F15 key
    VK_F16                  = 0x7F, // F16 key
    VK_F17                  = 0x80, // F17 key
    VK_F18                  = 0x81, // F18 key
    VK_F19                  = 0x82, // F19 key
    VK_F20                  = 0x83, // F20 key
    VK_F21                  = 0x84, // F21 key
    VK_F22                  = 0x85, // F22 key
    VK_F23                  = 0x86, // F23 key
    VK_F24                  = 0x87, // F24 key
    VK_0x88                 = 0x88, // Unassigned
    VK_0x89                 = 0x89, // Unassigned
    VK_0x8A                 = 0x8A, // Unassigned
    VK_0x8B                 = 0x8B, // Unassigned
    VK_0x8C                 = 0x8C, // Unassigned
    VK_0x8D                 = 0x8D, // Unassigned
    VK_0x8E                 = 0x8E, // Unassigned
    VK_0x8F                 = 0x8F, // Unassigned
    VK_NUMLOCK              = 0x90, // NUM LOCK key
    VK_SCROLL               = 0x91, // SCROLL LOCK key
    VK_0x92                 = 0x92, // OEM specific
    VK_0x93                 = 0x93, // OEM specific
    VK_0x94                 = 0x94, // OEM specific
    VK_0x95                 = 0x95, // OEM specific
    VK_0x96                 = 0x96, // OEM specific
    VK_0x97                 = 0x97, // Unassigned
    VK_0x98                 = 0x98, // Unassigned
    VK_0x99                 = 0x99, // Unassigned
    VK_0x9A                 = 0x9A, // Unassigned
    VK_0x9B                 = 0x9B, // Unassigned
    VK_0x9C                 = 0x9C, // Unassigned
    VK_0x9D                 = 0x9D, // Unassigned
    VK_0x9E                 = 0x9E, // Unassigned
    VK_0x9F                 = 0x9F, // Unassigned
    VK_LSHIFT               = 0xA0, // Left SHIFT key
    VK_RSHIFT               = 0xA1, // Right SHIFT key
    VK_LCONTROL             = 0xA2, // Left CONTROL key
    VK_RCONTROL             = 0xA3, // Right CONTROL key
    VK_LMENU                = 0xA4, // Left MENU key
    VK_RMENU                = 0xA5, // Right MENU key
    VK_BROWSER_BACK         = 0xA6, // Browser Back key
    VK_BROWSER_FORWARD      = 0xA7, // Browser Forward key
    VK_BROWSER_REFRESH      = 0xA8, // Browser Refresh key
    VK_BROWSER_STOP         = 0xA9, // Browser Stop key
    VK_BROWSER_SEARCH       = 0xAA, // Browser Search key 
    VK_BROWSER_FAVORITES    = 0xAB, // Browser Favorites key
    VK_BROWSER_HOME         = 0xAC, // Browser Start and Home key
    VK_VOLUME_MUTE          = 0xAD, // Volume Mute key
    VK_VOLUME_DOWN          = 0xAE, // Volume Down key
    VK_VOLUME_UP            = 0xAF, // Volume Up key
    VK_MEDIA_NEXT_TRACK     = 0xB0, // Next Track key
    VK_MEDIA_PREV_TRACK     = 0xB1, // Previous Track key
    VK_MEDIA_STOP           = 0xB2, // Stop Media key
    VK_MEDIA_PLAY_PAUSE     = 0xB3, // Play/Pause Media key
    VK_LAUNCH_MAIL          = 0xB4, // Start Mail key
    VK_LAUNCH_MEDIA_SELECT  = 0xB5, // Select Media key
    VK_LAUNCH_APP1          = 0xB6, // Start Application 1 key
    VK_LAUNCH_APP2          = 0xB7, // Start Application 2 key
    VK_0xB8                 = 0xB8, // Reserved
    VK_0xB9                 = 0xB9, // Reserved
    VK_OEM_1                = 0xBA, // Used for miscellaneous characters;
                                    // it can vary by keyboard.
                                    // For the US standard keyboard, the ';:' key
    VK_OEM_PLUS             = 0xBB, // For any country/region, the '+' key
    VK_OEM_COMMA            = 0xBC, // For any country/region, the ',' key
    VK_OEM_MINUS            = 0xBD, // For any country/region, the '-' key
    VK_OEM_PERIOD           = 0xBE, // For any country/region, the '.' key
    VK_OEM_2                = 0xBF, // Used for miscellaneous characters;
                                    // it can vary by keyboard.
                                    // For the US standard keyboard, the '/?' key
    VK_OEM_3                = 0xC0, // Used for miscellaneous characters;
                                    // it can vary by keyboard. 
                                    // For the US standard keyboard, the '`~' key
    VK_0xC1                 = 0xC1, // Reserved
    VK_0xC2                 = 0xC2, // Reserved
    VK_0xC3                 = 0xC3, // Reserved
    VK_0xC4                 = 0xC4, // Reserved
    VK_0xC5                 = 0xC5, // Reserved
    VK_0xC6                 = 0xC6, // Reserved
    VK_0xC7                 = 0xC7, // Reserved
    VK_0xC8                 = 0xC8, // Reserved
    VK_0xC9                 = 0xC9, // Reserved
    VK_0xCA                 = 0xCA, // Reserved
    VK_0xCB                 = 0xCB, // Reserved
    VK_0xCC                 = 0xCC, // Reserved
    VK_0xCD                 = 0xCD, // Reserved
    VK_0xCE                 = 0xCE, // Reserved
    VK_0xCF                 = 0xCF, // Reserved
    VK_0xD0                 = 0xD0, // Reserved
    VK_0xD1                 = 0xD1, // Reserved
    VK_0xD2                 = 0xD2, // Reserved
    VK_0xD3                 = 0xD3, // Reserved
    VK_0xD4                 = 0xD4, // Reserved
    VK_0xD5                 = 0xD5, // Reserved
    VK_0xD6                 = 0xD6, // Reserved
    VK_0xD7                 = 0xD7, // Reserved
    VK_0xD8                 = 0xD8, // Unassigned
    VK_0xD9                 = 0xD9, // Unassigned
    VK_0xDA                 = 0xDA, // Unassigned
    VK_OEM_4                = 0xDB, // Used for miscellaneous characters;
                                    // it can vary by keyboard.
                                    // For the US standard keyboard, the '[{' key
    VK_OEM_5                = 0xDC, // Used for miscellaneous characters;
                                    // it can vary by keyboard.
                                    // For the US standard keyboard, the '\|' key
    VK_OEM_6                = 0xDD, // Used for miscellaneous characters;
                                    // it can vary by keyboard.
                                    // For the US standard keyboard, the ']}' key
    VK_OEM_7                = 0xDE, // Used for miscellaneous characters;
                                    // it can vary by keyboard.
                                    // For the US standard keyboard, the 'single-quote/double-quote' key
    VK_OEM_8                = 0xDF, // Used for miscellaneous characters;
                                    // it can vary by keyboard.
    VK_0xE0                 = 0xE0, // Reserved
    VK_0xE1                 = 0xE1, // OEM specific
    VK_OEM_102              = 0xE2, // Either the angle bracket key or the backslash key on the RT 102-key keyboard
    VK_0xE3                 = 0xE3, // OEM specific
    VK_0xE4                 = 0xE4, // OEM specific
    VK_PROCESSKEY           = 0xE5, // IME PROCESS key
    VK_0xE6                 = 0xE6, // OEM specific
    VK_PACKET               = 0xE7, // Used to pass Unicode characters as if
                                    // they were keystrokes.
                                    // The VK_PACKET key is the low word of a
                                    // 32-bit Virtual Key value used for
                                    // non-keyboard input methods.
                                    // For more information, see Remark in
                                    // KEYBDINPUT, SendInput, WM_KEYDOWN,
                                    // and WM_KEYUP
    VK_0xE8                 = 0xE8, // Unassigned
    VK_0xE9                 = 0xE9, // OEM specific
    VK_0xEA                 = 0xEA, // OEM specific
    VK_0xEB                 = 0xEB, // OEM specific
    VK_0xEC                 = 0xEC, // OEM specific
    VK_0xED                 = 0xED, // OEM specific
    VK_0xEE                 = 0xEE, // OEM specific
    VK_0xEF                 = 0xEF, // OEM specific
    VK_0xF0                 = 0xF0, // OEM specific
    VK_0xF1                 = 0xF1, // OEM specific
    VK_0xF2                 = 0xF2, // OEM specific
    VK_0xF3                 = 0xF3, // OEM specific
    VK_0xF4                 = 0xF4, // OEM specific
    VK_0xF5                 = 0xF5, // OEM specific
    VK_ATTN                 = 0xF6, // Attn key
    VK_CRSEL                = 0xF7, // CrSel key
    VK_EXSEL                = 0xF8, // ExSel key
    VK_EREOF                = 0xF9, // Erase EOF key
    VK_PLAY                 = 0xFA, // Play key
    VK_ZOOM                 = 0xFB, // Zoom key
    VK_NONAME               = 0xFC, // Reserved
    VK_PA1                  = 0xFD, // PA1 key
    VK_OEM_CLEAR            = 0xFE, // Clear key
} VK;

//------------------------------------------------------------------------------

typedef enum WM {
    WM_NONE                        = 0,
    WM_CREATE                      = 0x0001,
    WM_DESTROY                     = 0x0002,
    WM_MOVE                        = 0x0003,
    WM_SIZE                        = 0x0005,
    WM_ACTIVATE                    = 0x0006,
    WM_SETFOCUS                    = 0x0007,
    WM_KILLFOCUS                   = 0x0008,
    WM_ENABLE                      = 0x000A,
    WM_SETREDRAW                   = 0x000B,
    WM_SETTEXT                     = 0x000C,
    WM_GETTEXT                     = 0x000D,
    WM_GETTEXTLENGTH               = 0x000E,
    WM_PAINT                       = 0x000F,
    WM_CLOSE                       = 0x0010,
    WM_QUERYENDSESSION             = 0x0011,
    WM_QUERYOPEN                   = 0x0013,
    WM_ENDSESSION                  = 0x0016,
    WM_QUIT                        = 0x0012,
    WM_ERASEBKGND                  = 0x0014,
    WM_SYSCOLORCHANGE              = 0x0015,
    WM_SHOWWINDOW                  = 0x0018,
    WM_WININICHANGE                = 0x001A,
    WM_SETTINGCHANGE               = WM_WININICHANGE,
    WM_DEVMODECHANGE               = 0x001B,
    WM_ACTIVATEAPP                 = 0x001C,
    WM_FONTCHANGE                  = 0x001D,
    WM_TIMECHANGE                  = 0x001E,
    WM_CANCELMODE                  = 0x001F,
    WM_SETCURSOR                   = 0x0020,
    WM_MOUSEACTIVATE               = 0x0021,
    WM_CHILDACTIVATE               = 0x0022,
    WM_QUEUESYNC                   = 0x0023,
    WM_GETMINMAXINFO               = 0x0024,
    WM_PAINTICON                   = 0x0026,
    WM_ICONERASEBKGND              = 0x0027,
    WM_NEXTDLGCTL                  = 0x0028,
    WM_SPOOLERSTATUS               = 0x002A,
    WM_DRAWITEM                    = 0x002B,
    WM_MEASUREITEM                 = 0x002C,
    WM_DELETEITEM                  = 0x002D,
    WM_VKEYTOITEM                  = 0x002E,
    WM_CHARTOITEM                  = 0x002F,
    WM_SETFONT                     = 0x0030,
    WM_GETFONT                     = 0x0031,
    WM_SETHOTKEY                   = 0x0032,
    WM_GETHOTKEY                   = 0x0033,
    WM_QUERYDRAGICON               = 0x0037,
    WM_COMPAREITEM                 = 0x0039,
    WM_GETOBJECT                   = 0x003D,
    WM_COMPACTING                  = 0x0041,
    WM_COMMNOTIFY                  = 0x0044,
    WM_WINDOWPOSCHANGING           = 0x0046,
    WM_WINDOWPOSCHANGED            = 0x0047,
    WM_POWER                       = 0x0048,
    WM_COPYDATA                    = 0x004A,
    WM_CANCELJOURNAL               = 0x004B,
    WM_NOTIFY                      = 0x004E,
    WM_INPUTLANGCHANGEREQUEST      = 0x0050,
    WM_INPUTLANGCHANGE             = 0x0051,
    WM_TCARD                       = 0x0052,
    WM_HELP                        = 0x0053,
    WM_USERCHANGED                 = 0x0054,
    WM_NOTIFYFORMAT                = 0x0055,
    WM_CONTEXTMENU                 = 0x007B,
    WM_STYLECHANGING               = 0x007C,
    WM_STYLECHANGED                = 0x007D,
    WM_DISPLAYCHANGE               = 0x007E,
    WM_GETICON                     = 0x007F,
    WM_SETICON                     = 0x0080,
    WM_NCCREATE                    = 0x0081,
    WM_NCDESTROY                   = 0x0082,
    WM_NCCALCSIZE                  = 0x0083,
    WM_NCHITTEST                   = 0x0084,
    WM_NCPAINT                     = 0x0085,
    WM_NCACTIVATE                  = 0x0086,
    WM_GETDLGCODE                  = 0x0087,
    WM_SYNCPAINT                   = 0x0088,
    WM_NCMOUSEMOVE                 = 0x00A0,
    WM_NCLBUTTONDOWN               = 0x00A1,
    WM_NCLBUTTONUP                 = 0x00A2,
    WM_NCLBUTTONDBLCLK             = 0x00A3,
    WM_NCRBUTTONDOWN               = 0x00A4,
    WM_NCRBUTTONUP                 = 0x00A5,
    WM_NCRBUTTONDBLCLK             = 0x00A6,
    WM_NCMBUTTONDOWN               = 0x00A7,
    WM_NCMBUTTONUP                 = 0x00A8,
    WM_NCMBUTTONDBLCLK             = 0x00A9,
    WM_NCXBUTTONDOWN               = 0x00AB,
    WM_NCXBUTTONUP                 = 0x00AC,
    WM_NCXBUTTONDBLCLK             = 0x00AD,
    WM_INPUT_DEVICE_CHANGE         = 0x00FE,
    WM_INPUT                       = 0x00FF,
    WM_KEYDOWN                     = 0x0100,
    WM_KEYFIRST                    = WM_KEYDOWN,
    WM_KEYUP                       = 0x0101,
    WM_CHAR                        = 0x0102,
    WM_DEADCHAR                    = 0x0103,
    WM_SYSKEYDOWN                  = 0x0104,
    WM_SYSKEYUP                    = 0x0105,
    WM_SYSCHAR                     = 0x0106,
    WM_SYSDEADCHAR                 = 0x0107,
    WM_UNICHAR                     = 0x0109,
    WM_KEYLAST                     = WM_UNICHAR,
    WM_IME_STARTCOMPOSITION        = 0x010D,
    WM_IME_ENDCOMPOSITION          = 0x010E,
    WM_IME_COMPOSITION             = 0x010F,
    WM_IME_KEYLAST                 = 0x010F,
    WM_INITDIALOG                  = 0x0110,
    WM_COMMAND                     = 0x0111,
    WM_SYSCOMMAND                  = 0x0112,
    WM_TIMER                       = 0x0113,
    WM_HSCROLL                     = 0x0114,
    WM_VSCROLL                     = 0x0115,
    WM_INITMENU                    = 0x0116,
    WM_INITMENUPOPUP               = 0x0117,
    WM_MENUSELECT                  = 0x011F,
    WM_MENUCHAR                    = 0x0120,
    WM_ENTERIDLE                   = 0x0121,
    WM_MENURBUTTONUP               = 0x0122,
    WM_MENUDRAG                    = 0x0123,
    WM_MENUGETOBJECT               = 0x0124,
    WM_UNINITMENUPOPUP             = 0x0125,
    WM_MENUCOMMAND                 = 0x0126,
    WM_CHANGEUISTATE               = 0x0127,
    WM_UPDATEUISTATE               = 0x0128,
    WM_QUERYUISTATE                = 0x0129,
    WM_CTLCOLORMSGBOX              = 0x0132,
    WM_CTLCOLOREDIT                = 0x0133,
    WM_CTLCOLORLISTBOX             = 0x0134,
    WM_CTLCOLORBTN                 = 0x0135,
    WM_CTLCOLORDLG                 = 0x0136,
    WM_CTLCOLORSCROLLBAR           = 0x0137,
    WM_CTLCOLORSTATIC              = 0x0138,
    WM_MOUSEMOVE                   = 0x0200,
    WM_MOUSEFIRST                  = WM_MOUSEMOVE,
    WM_LBUTTONDOWN                 = 0x0201,
    WM_LBUTTONUP                   = 0x0202,
    WM_LBUTTONDBLCLK               = 0x0203,
    WM_RBUTTONDOWN                 = 0x0204,
    WM_RBUTTONUP                   = 0x0205,
    WM_RBUTTONDBLCLK               = 0x0206,
    WM_MBUTTONDOWN                 = 0x0207,
    WM_MBUTTONUP                   = 0x0208,
    WM_MBUTTONDBLCLK               = 0x0209,
    WM_MOUSEWHEEL                  = 0x020A,
    WM_XBUTTONDOWN                 = 0x020B,
    WM_XBUTTONUP                   = 0x020C,
    WM_XBUTTONDBLCLK               = 0x020D,
    WM_MOUSEHWHEEL                 = 0x020E,
    WM_MOUSELAST                   = WM_MOUSEHWHEEL,
    WM_PARENTNOTIFY                = 0x0210,
    WM_ENTERMENULOOP               = 0x0211,
    WM_EXITMENULOOP                = 0x0212,
    WM_NEXTMENU                    = 0x0213,
    WM_SIZING                      = 0x0214,
    WM_CAPTURECHANGED              = 0x0215,
    WM_MOVING                      = 0x0216,
    WM_POWERBROADCAST              = 0x0218,
    WM_DEVICECHANGE                = 0x0219,
    WM_MDICREATE                   = 0x0220,
    WM_MDIDESTROY                  = 0x0221,
    WM_MDIACTIVATE                 = 0x0222,
    WM_MDIRESTORE                  = 0x0223,
    WM_MDINEXT                     = 0x0224,
    WM_MDIMAXIMIZE                 = 0x0225,
    WM_MDITILE                     = 0x0226,
    WM_MDICASCADE                  = 0x0227,
    WM_MDIICONARRANGE              = 0x0228,
    WM_MDIGETACTIVE                = 0x0229,
    WM_MDISETMENU                  = 0x0230,
    WM_ENTERSIZEMOVE               = 0x0231,
    WM_EXITSIZEMOVE                = 0x0232,
    WM_DROPFILES                   = 0x0233,
    WM_MDIREFRESHMENU              = 0x0234,
    WM_IME_SETCONTEXT              = 0x0281,
    WM_IME_NOTIFY                  = 0x0282,
    WM_IME_CONTROL                 = 0x0283,
    WM_IME_COMPOSITIONFULL         = 0x0284,
    WM_IME_SELECT                  = 0x0285,
    WM_IME_CHAR                    = 0x0286,
    WM_IME_REQUEST                 = 0x0288,
    WM_IME_KEYDOWN                 = 0x0290,
    WM_IME_KEYUP                   = 0x0291,
    WM_MOUSEHOVER                  = 0x02A1,
    WM_MOUSELEAVE                  = 0x02A3,
    WM_NCMOUSEHOVER                = 0x02A0,
    WM_NCMOUSELEAVE                = 0x02A2,
    WM_WTSSESSION_CHANGE           = 0x02B1,
    WM_TABLET_FIRST                = 0x02c0,
    WM_TABLET_LAST                 = 0x02df,
    WM_CUT                         = 0x0300,
    WM_COPY                        = 0x0301,
    WM_PASTE                       = 0x0302,
    WM_CLEAR                       = 0x0303,
    WM_UNDO                        = 0x0304,
    WM_RENDERFORMAT                = 0x0305,
    WM_RENDERALLFORMATS            = 0x0306,
    WM_DESTROYCLIPBOARD            = 0x0307,
    WM_DRAWCLIPBOARD               = 0x0308,
    WM_PAINTCLIPBOARD              = 0x0309,
    WM_VSCROLLCLIPBOARD            = 0x030A,
    WM_SIZECLIPBOARD               = 0x030B,
    WM_ASKCBFORMATNAME             = 0x030C,
    WM_CHANGECBCHAIN               = 0x030D,
    WM_HSCROLLCLIPBOARD            = 0x030E,
    WM_QUERYNEWPALETTE             = 0x030F,
    WM_PALETTEISCHANGING           = 0x0310,
    WM_PALETTECHANGED              = 0x0311,
    WM_HOTKEY                      = 0x0312,
    WM_PRINT                       = 0x0317,
    WM_PRINTCLIENT                 = 0x0318,
    WM_APPCOMMAND                  = 0x0319,
    WM_THEMECHANGED                = 0x031A,
    WM_CLIPBOARDUPDATE             = 0x031D,
    WM_DWMCOMPOSITIONCHANGED       = 0x031E,
    WM_DWMNCRENDERINGCHANGED       = 0x031F,
    WM_DWMCOLORIZATIONCOLORCHANGED = 0x0320,
    WM_DWMWINDOWMAXIMIZEDCHANGE    = 0x0321,
    WM_GETTITLEBARINFOEX           = 0x033F,
    WM_HANDHELDFIRST               = 0x0358,
    WM_HANDHELDLAST                = 0x035F,
    WM_AFXFIRST                    = 0x0360,
    WM_AFXLAST                     = 0x037F,
    WM_PENWINFIRST                 = 0x0380,
    WM_PENWINLAST                  = 0x038F,
    WM_APP                         = 0x8000,
    WM_USER                        = 0x0400,
    WM_CPL_LAUNCH                  = WM_USER + 0x1000,
    WM_CPL_LAUNCHED                = WM_USER + 0x1001,
    WM_SYSTIMER                    = 0x118,
} WM;

typedef UINT_PTR WPARAM;
typedef LONG_PTR LPARAM;

typedef LRESULT(__stdcall* WNDPROC)(HWND,WM,WPARAM,LPARAM);

//------------------------------------------------------------------------------

typedef BOOL(__stdcall* MONITORENUMPROC)(HMONITOR,HDC,LPRECT,LPVOID);

typedef struct WNDCLASSEXA {
    UINT      cbSize;
    CS        style;
    WNDPROC   lpfnWndProc;
    int       cbClsExtra;
    int       cbWndExtra;
    HINSTANCE hInstance;
    HICON     hIcon;
    HCURSOR   hCursor;
    HBRUSH    hbrBackground;
    LPCSTR    lpszMenuName;
    LPCSTR    lpszClassName;
    HICON     hIconSm;
} WNDCLASSEXA;

typedef struct MSG {
    HWND   hwnd;
    WM     message;
    WPARAM wParam;
    LPARAM lParam;
    DWORD  time;
    POINT  point;
} MSG;

typedef struct WINDOWPLACEMENT {
    UINT  cbSize;
    WPF   flags;
    SW    showCmd;
    POINT rcMinPosition;
    POINT rcMaxPosition;
    RECT  rcNormalPosition;
} WINDOWPLACEMENT;

typedef struct MONITORINFO {
    DWORD        cbSize;
    RECT         rcMonitor;
    RECT         rcWork;
    MI           dwFlags;
} MONITORINFO;

typedef struct PAINTSTRUCT {
    HDC  hdc;
    BOOL fErase;
    RECT rcPaint;
    BOOL fRestore;
    BOOL fIncUpdate;
    BYTE rgbReserved[32];
} PAINTSTRUCT;

//------------------------------------------------------------------------------

APP_EXTERN_C_BEGIN

//------------------------------------------------------------------------------

#pragma comment(lib, "user32.lib")
BOOL     __stdcall AdjustWindowRectEx   (RECT*, WS, BOOL Menu, WS_EX);
HDC      __stdcall BeginPaint           (HWND, PAINTSTRUCT*);
HWND     __stdcall CreateWindowExA      (WS_EX, LPCSTR Class, LPCSTR Title,
                                         WS, int X, int Y, int W, int H,
                                         HWND Parent, HMENU, HINSTANCE, LPARAM);
BOOL     __stdcall DestroyWindow        (HWND);
LRESULT  __stdcall DefWindowProcA       (HWND, WM, WPARAM, LPARAM);
LRESULT  __stdcall DispatchMessageA     (const MSG*);
BOOL     __stdcall EndPaint             (HWND, const PAINTSTRUCT*);
BOOL     __stdcall EnumDisplayMonitors  (HDC, LPCRECT Clip, MONITORENUMPROC, LPARAM);
int      __stdcall FillRect             (HDC, const RECT*, HBRUSH);
HWND     __stdcall GetActiveWindow      (void);
BOOL     __stdcall GetClientRect        (HWND, RECT*);
BOOL     __stdcall GetCursorPos         (POINT*);
HDC      __stdcall GetDC                (HWND);
HWND     __stdcall GetForegroundWindow  (void);
BOOL     __stdcall GetKeyboardState     (BYTE*);
BOOL     __stdcall GetMonitorInfoA      (HMONITOR, MONITORINFO*);
DWORD    __stdcall GetSysColor          (int);
LONG_PTR __stdcall GetWindowLongPtrA    (HWND, GWL);
BOOL     __stdcall GetWindowPlacement   (HWND, WINDOWPLACEMENT*);
BOOL     __stdcall GetWindowRect        (HWND, RECT*);
int      __stdcall GetWindowTextA       (HWND, LPSTR, int);
int      __stdcall GetWindowTextLengthA (HWND);
BOOL     __stdcall IsWindowVisible      (HWND);
BOOL     __stdcall IsIconic             (HWND);
BOOL     __stdcall IsZoomed             (HWND);
HCURSOR  __stdcall LoadCursorA          (HINSTANCE, LPCSTR);
HICON    __stdcall LoadIconA            (HINSTANCE, LPCSTR);
int      __stdcall MapWindowPoints      (HWND from, HWND to, POINT*, UINT);
HMONITOR __stdcall MonitorFromPoint     (POINT, MONITOR_DEFAULT);
HMONITOR __stdcall MonitorFromRect      (const RECT*, MONITOR_DEFAULT);
BOOL     __stdcall PeekMessageA         (MSG*, HWND, WM min, WM max, PM);
ATOM     __stdcall RegisterClassExA     (const WNDCLASSEXA*);
LRESULT  __stdcall SendMessageA         (HWND, WM, WPARAM, LPARAM);
HCURSOR  __stdcall SetCursor            (HCURSOR);
HWND     __stdcall SetActiveWindow      (HWND);
BOOL     __stdcall SetForegroundWindow  (HWND);
LONG_PTR __stdcall SetWindowLongPtrA    (HWND, GWL, LONG_PTR);
BOOL     __stdcall SetWindowPlacement   (HWND, const WINDOWPLACEMENT*);
BOOL     __stdcall SetWindowPos         (HWND, HWND, int, int, int, int, SWP);
BOOL     __stdcall SetWindowTextA       (HWND, LPCSTR);
BOOL     __stdcall ShowWindow           (HWND, SW);
BOOL     __stdcall TranslateMessage     (const MSG*);

//------------------------------------------------------------------------------

#pragma comment(lib, "gdi32.lib")
HGDIOBJ  __stdcall GetStockObject       (OBJ);
DWORD    __stdcall SetDCBrushColor      (HDC,DWORD);

//------------------------------------------------------------------------------

// NOTE: this is not available prior to Win 10, and should be loaded dynamically
// app_dll(SHCore, "shcore.dll")
// app_dllimport(
//     SHCore,
//     stdcall(HRESULT,    SetProcessDpiAwareness, (PDA)),
// )

//------------------------------------------------------------------------------

APP_EXTERN_C_END

//------------------------------------------------------------------------------
