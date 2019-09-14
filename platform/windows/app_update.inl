#pragma once
#include "app.inl"

//------------------------------------------------------------------------------

APP_EXTERN_C_BEGIN

//------------------------------------------------------------------------------

static inline void
_app_log_event(unsigned const msg) {
    switch (msg) {
        #define _app_log_event(WM) case _APP_##WM: puts(#WM); break;
        _app_log_event(WM_NONE)
        _app_log_event(WM_CREATE)
        _app_log_event(WM_DESTROY)
        _app_log_event(WM_MOVE)
        _app_log_event(WM_SIZE)
        _app_log_event(WM_ACTIVATE)
        _app_log_event(WM_SETFOCUS)
        _app_log_event(WM_KILLFOCUS)
        _app_log_event(WM_ENABLE)
        _app_log_event(WM_SETREDRAW)
        _app_log_event(WM_SETTEXT)
        _app_log_event(WM_GETTEXT)
        _app_log_event(WM_GETTEXTLENGTH)
        _app_log_event(WM_PAINT)
        _app_log_event(WM_CLOSE)
        _app_log_event(WM_QUERYENDSESSION)
        _app_log_event(WM_QUERYOPEN)
        _app_log_event(WM_ENDSESSION)
        _app_log_event(WM_QUIT)
        _app_log_event(WM_ERASEBKGND)
        _app_log_event(WM_SYSCOLORCHANGE)
        _app_log_event(WM_SHOWWINDOW)
        _app_log_event(WM_SETTINGCHANGE)
        _app_log_event(WM_DEVMODECHANGE)
        _app_log_event(WM_ACTIVATEAPP)
        _app_log_event(WM_FONTCHANGE)
        _app_log_event(WM_TIMECHANGE)
        _app_log_event(WM_CANCELMODE)
        _app_log_event(WM_SETCURSOR)
        _app_log_event(WM_MOUSEACTIVATE)
        _app_log_event(WM_CHILDACTIVATE)
        _app_log_event(WM_QUEUESYNC)
        _app_log_event(WM_GETMINMAXINFO)
        _app_log_event(WM_PAINTICON)
        _app_log_event(WM_ICONERASEBKGND)
        _app_log_event(WM_NEXTDLGCTL)
        _app_log_event(WM_SPOOLERSTATUS)
        _app_log_event(WM_DRAWITEM)
        _app_log_event(WM_MEASUREITEM)
        _app_log_event(WM_DELETEITEM)
        _app_log_event(WM_VKEYTOITEM)
        _app_log_event(WM_CHARTOITEM)
        _app_log_event(WM_SETFONT)
        _app_log_event(WM_GETFONT)
        _app_log_event(WM_SETHOTKEY)
        _app_log_event(WM_GETHOTKEY)
        _app_log_event(WM_QUERYDRAGICON)
        _app_log_event(WM_COMPAREITEM)
        _app_log_event(WM_GETOBJECT)
        _app_log_event(WM_COMPACTING)
        _app_log_event(WM_COMMNOTIFY)
        _app_log_event(WM_WINDOWPOSCHANGING)
        _app_log_event(WM_WINDOWPOSCHANGED)
        _app_log_event(WM_POWER)
        _app_log_event(WM_COPYDATA)
        _app_log_event(WM_CANCELJOURNAL)
        _app_log_event(WM_NOTIFY)
        _app_log_event(WM_INPUTLANGCHANGEREQUEST)
        _app_log_event(WM_INPUTLANGCHANGE)
        _app_log_event(WM_TCARD)
        _app_log_event(WM_HELP)
        _app_log_event(WM_USERCHANGED)
        _app_log_event(WM_NOTIFYFORMAT)
        _app_log_event(WM_CONTEXTMENU)
        _app_log_event(WM_STYLECHANGING)
        _app_log_event(WM_STYLECHANGED)
        _app_log_event(WM_DISPLAYCHANGE)
        _app_log_event(WM_GETICON)
        _app_log_event(WM_SETICON)
        _app_log_event(WM_NCCREATE)
        _app_log_event(WM_NCDESTROY)
        _app_log_event(WM_NCCALCSIZE)
        _app_log_event(WM_NCHITTEST)
        _app_log_event(WM_NCPAINT)
        _app_log_event(WM_NCACTIVATE)
        _app_log_event(WM_GETDLGCODE)
        _app_log_event(WM_SYNCPAINT)
        _app_log_event(WM_NCMOUSEMOVE)
        _app_log_event(WM_NCLBUTTONDOWN)
        _app_log_event(WM_NCLBUTTONUP)
        _app_log_event(WM_NCLBUTTONDBLCLK)
        _app_log_event(WM_NCRBUTTONDOWN)
        _app_log_event(WM_NCRBUTTONUP)
        _app_log_event(WM_NCRBUTTONDBLCLK)
        _app_log_event(WM_NCMBUTTONDOWN)
        _app_log_event(WM_NCMBUTTONUP)
        _app_log_event(WM_NCMBUTTONDBLCLK)
        _app_log_event(WM_NCXBUTTONDOWN)
        _app_log_event(WM_NCXBUTTONUP)
        _app_log_event(WM_NCXBUTTONDBLCLK)
        _app_log_event(WM_INPUT_DEVICE_CHANGE)
        _app_log_event(WM_INPUT)
        _app_log_event(WM_KEYDOWN)
        _app_log_event(WM_KEYUP)
        _app_log_event(WM_CHAR)
        _app_log_event(WM_DEADCHAR)
        _app_log_event(WM_SYSKEYDOWN)
        _app_log_event(WM_SYSKEYUP)
        _app_log_event(WM_SYSCHAR)
        _app_log_event(WM_SYSDEADCHAR)
        _app_log_event(WM_UNICHAR)
        _app_log_event(WM_IME_STARTCOMPOSITION)
        _app_log_event(WM_IME_ENDCOMPOSITION)
        _app_log_event(WM_IME_COMPOSITION)
        _app_log_event(WM_INITDIALOG)
        _app_log_event(WM_COMMAND)
        _app_log_event(WM_SYSCOMMAND)
        _app_log_event(WM_TIMER)
        _app_log_event(WM_HSCROLL)
        _app_log_event(WM_VSCROLL)
        _app_log_event(WM_INITMENU)
        _app_log_event(WM_INITMENUPOPUP)
        _app_log_event(WM_MENUSELECT)
        _app_log_event(WM_MENUCHAR)
        _app_log_event(WM_ENTERIDLE)
        _app_log_event(WM_MENURBUTTONUP)
        _app_log_event(WM_MENUDRAG)
        _app_log_event(WM_MENUGETOBJECT)
        _app_log_event(WM_UNINITMENUPOPUP)
        _app_log_event(WM_MENUCOMMAND)
        _app_log_event(WM_CHANGEUISTATE)
        _app_log_event(WM_UPDATEUISTATE)
        _app_log_event(WM_QUERYUISTATE)
        _app_log_event(WM_CTLCOLORMSGBOX)
        _app_log_event(WM_CTLCOLOREDIT)
        _app_log_event(WM_CTLCOLORLISTBOX)
        _app_log_event(WM_CTLCOLORBTN)
        _app_log_event(WM_CTLCOLORDLG)
        _app_log_event(WM_CTLCOLORSCROLLBAR)
        _app_log_event(WM_CTLCOLORSTATIC)
        _app_log_event(WM_MOUSEMOVE)
        _app_log_event(WM_LBUTTONDOWN)
        _app_log_event(WM_LBUTTONUP)
        _app_log_event(WM_LBUTTONDBLCLK)
        _app_log_event(WM_RBUTTONDOWN)
        _app_log_event(WM_RBUTTONUP)
        _app_log_event(WM_RBUTTONDBLCLK)
        _app_log_event(WM_MBUTTONDOWN)
        _app_log_event(WM_MBUTTONUP)
        _app_log_event(WM_MBUTTONDBLCLK)
        _app_log_event(WM_MOUSEWHEEL)
        _app_log_event(WM_XBUTTONDOWN)
        _app_log_event(WM_XBUTTONUP)
        _app_log_event(WM_XBUTTONDBLCLK)
        _app_log_event(WM_MOUSEHWHEEL)
        _app_log_event(WM_PARENTNOTIFY)
        _app_log_event(WM_ENTERMENULOOP)
        _app_log_event(WM_EXITMENULOOP)
        _app_log_event(WM_NEXTMENU)
        _app_log_event(WM_SIZING)
        _app_log_event(WM_CAPTURECHANGED)
        _app_log_event(WM_MOVING)
        _app_log_event(WM_POWERBROADCAST)
        _app_log_event(WM_DEVICECHANGE)
        _app_log_event(WM_MDICREATE)
        _app_log_event(WM_MDIDESTROY)
        _app_log_event(WM_MDIACTIVATE)
        _app_log_event(WM_MDIRESTORE)
        _app_log_event(WM_MDINEXT)
        _app_log_event(WM_MDIMAXIMIZE)
        _app_log_event(WM_MDITILE)
        _app_log_event(WM_MDICASCADE)
        _app_log_event(WM_MDIICONARRANGE)
        _app_log_event(WM_MDIGETACTIVE)
        _app_log_event(WM_MDISETMENU)
        _app_log_event(WM_ENTERSIZEMOVE)
        _app_log_event(WM_EXITSIZEMOVE)
        _app_log_event(WM_DROPFILES)
        _app_log_event(WM_MDIREFRESHMENU)
        _app_log_event(WM_IME_SETCONTEXT)
        _app_log_event(WM_IME_NOTIFY)
        _app_log_event(WM_IME_CONTROL)
        _app_log_event(WM_IME_COMPOSITIONFULL)
        _app_log_event(WM_IME_SELECT)
        _app_log_event(WM_IME_CHAR)
        _app_log_event(WM_IME_REQUEST)
        _app_log_event(WM_IME_KEYDOWN)
        _app_log_event(WM_IME_KEYUP)
        _app_log_event(WM_MOUSEHOVER)
        _app_log_event(WM_MOUSELEAVE)
        _app_log_event(WM_NCMOUSEHOVER)
        _app_log_event(WM_NCMOUSELEAVE)
        _app_log_event(WM_WTSSESSION_CHANGE)
        _app_log_event(WM_TABLET_FIRST)
        _app_log_event(WM_TABLET_LAST)
        _app_log_event(WM_CUT)
        _app_log_event(WM_COPY)
        _app_log_event(WM_PASTE)
        _app_log_event(WM_CLEAR)
        _app_log_event(WM_UNDO)
        _app_log_event(WM_RENDERFORMAT)
        _app_log_event(WM_RENDERALLFORMATS)
        _app_log_event(WM_DESTROYCLIPBOARD)
        _app_log_event(WM_DRAWCLIPBOARD)
        _app_log_event(WM_PAINTCLIPBOARD)
        _app_log_event(WM_VSCROLLCLIPBOARD)
        _app_log_event(WM_SIZECLIPBOARD)
        _app_log_event(WM_ASKCBFORMATNAME)
        _app_log_event(WM_CHANGECBCHAIN)
        _app_log_event(WM_HSCROLLCLIPBOARD)
        _app_log_event(WM_QUERYNEWPALETTE)
        _app_log_event(WM_PALETTEISCHANGING)
        _app_log_event(WM_PALETTECHANGED)
        _app_log_event(WM_HOTKEY)
        _app_log_event(WM_PRINT)
        _app_log_event(WM_PRINTCLIENT)
        _app_log_event(WM_APPCOMMAND)
        _app_log_event(WM_THEMECHANGED)
        _app_log_event(WM_CLIPBOARDUPDATE)
        _app_log_event(WM_DWMCOMPOSITIONCHANGED)
        _app_log_event(WM_DWMNCRENDERINGCHANGED)
        _app_log_event(WM_DWMCOLORIZATIONCOLORCHANGED)
        _app_log_event(WM_DWMWINDOWMAXIMIZEDCHANGE)
        _app_log_event(WM_GETTITLEBARINFOEX)
        _app_log_event(WM_HANDHELDFIRST)
        _app_log_event(WM_HANDHELDLAST)
        _app_log_event(WM_AFXFIRST)
        _app_log_event(WM_AFXLAST)
        _app_log_event(WM_PENWINFIRST)
        _app_log_event(WM_PENWINLAST)
        _app_log_event(WM_APP)
        _app_log_event(WM_USER)
        _app_log_event(WM_CPL_LAUNCH)
        _app_log_event(WM_CPL_LAUNCHED)
        _app_log_event(WM_SYSTIMER)
        #undef _app_log_event
        default: printf("(WM)%u\n", msg); break;
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static bool _app_quit_requested = false;

bool
app_update(void) {
    _app_text_input_reset();
    _app_mouse_delta_reset();
    _app_mouse_scroll_reset();
    struct {
        void*    hwnd;
        unsigned message;
        size_t   wParam;
        size_t   lParam;
        unsigned time;
        struct { int x, y; } pt;
        unsigned lPrivate;
    } msg;
    enum { _APP_PM_REMOVE = 1 };
    while (_app_PeekMessageA(&msg, 0, 0, 0, _APP_PM_REMOVE)) {
        // _app_log_event(msg.message);
        if (msg.message ==  _APP_WM_QUIT) {
            app_quit();
            break;
        }
        _app_TranslateMessage(&msg);
        _app_DispatchMessageA(&msg);
    }
    _app_keys_update();
    return not _app_quit_requested;
}

//------------------------------------------------------------------------------

void
app_quit(void) {
    puts(__func__);
    _app_quit_requested = true;
}

#pragma GCC poison _app_quit_requested

//------------------------------------------------------------------------------

APP_EXTERN_C_END

//------------------------------------------------------------------------------
