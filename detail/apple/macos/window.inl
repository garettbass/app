#pragma once
#include "app.inl"

//------------------------------------------------------------------------------

APP_EXTERN_C_BEGIN

//------------------------------------------------------------------------------

// _app_objc_obj_swizzle(_app_NSWindow*,_app_NSWindow,retain) {
//     printf("_app_NSWindow.%s\n",(const char*)cmd);
//     return imp(self, cmd);
// }

// _app_objc_obj_swizzle(void,_app_NSWindow,release) {
//     printf("_app_NSWindow.%s\n",(const char*)cmd);
//     imp(self, cmd);
// }

// _app_objc_obj_swizzle(void,_app_NSWindow,dealloc) {
//     printf("_app_NSWindow.%s\n",(const char*)cmd);
//     imp(self, cmd);
// }

_app_objc_obj_swizzle(void,_app_NSWindow,keyDown,_app_NSEvent*) {
    // NSWindow.keyDown will produce an error sound
    (void)imp;
    (void)self;
    (void)cmd;
    (void)keyDown;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static inline void
_app_orient_NSRect_to_desktop(_app_NSRect* nsrect) {
    _app_NSScreen* const mainScreen = _app_objc_cls(_app_NSScreen,mainScreen);
    _app_NSRect const desktop = _app_objc_obj(mainScreen,_app_NSScreen,frame);
    nsrect->origin.y =
        desktop.size.height -
        nsrect->size.height -
        nsrect->origin.y;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static inline void
_app_log_retain_count(void* obj) {
    const char* type = class_getName(object_getClass(obj));
    printf("retain count (%s)%p: %zu\n", type, obj, CFGetRetainCount(obj));
}

app_window*
app_window_acquire(void) {
    _app_NSScreen* const screen = _app_objc_cls(_app_NSScreen,mainScreen);
    const _app_NSRect screenRect = _app_objc_obj(screen,_app_NSScreen,frame);
    const _app_NSRect windowRect = {
        { screenRect.size.width / 8, screenRect.size.height / 8 },
        { screenRect.size.width / 4, screenRect.size.height / 4 },
    };
    const _app_NSWindowStyleMask windowStyle =
        (_app_NSWindowStyleMask)(
            _app_NSWindowStyleMaskClosable |
            _app_NSWindowStyleMaskMiniaturizable |
            _app_NSWindowStyleMaskResizable |
            _app_NSWindowStyleMaskTitled |
            _app_NSWindowStyleMaskFullSizeContentView |
            //_app_NSWindowStyleMaskUnifiedTitleAndToolbar |
            0);
    _app_NSWindow* const nswindow = _app_objc_cls(_app_NSWindow,new);
    _app_objc_obj(nswindow,_app_NSWindow,setRestorable,false);
    _app_objc_obj(nswindow,_app_NSWindow,setReleasedWhenClosed,false);
    _app_objc_obj(nswindow,_app_NSWindow,setStyleMask,windowStyle);
    _app_objc_obj(nswindow,_app_NSWindow,setFrame,windowRect,display,true);
    _app_objc_obj(nswindow,_app_NSWindow,setIsVisible,true);
    _app_objc_obj(nswindow,_app_NSWindow,center);
    // _app_log_retain_count(nswindow);
    return (app_window*)nswindow;
}

void
app_window_release(app_window* const window) {
    assert(window);
    _app_NSWindow* const nswindow = (_app_NSWindow*)window;
    _app_objc_obj(nswindow,_app_NSWindow,setReleasedWhenClosed,true);
    _app_objc_obj(nswindow,_app_NSWindow,setIsVisible,false);
    // _app_log_retain_count(nswindow);
    _app_objc_release(nswindow);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void
app_window_set_title(app_window* const window, const char* const title) {
    assert(window);
    _app_NSWindow* const nswindow = (_app_NSWindow*)window;
    _app_objc_obj(nswindow,_app_NSWindow,setTitle,_app_objc_str(title));
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void
app_window_set_features(
    app_window* const window,
    const app_window_features features
) {
    assert(window);
    _app_NSWindow* const nswindow = (_app_NSWindow*)window;
    _app_NSWindowStyleMask style = _app_objc_obj(nswindow,_app_NSWindow,styleMask);
    style =
        (features & APP_WINDOW_FEATURES_CLOSE)
        ? (_app_NSWindowStyleMask)(style | _app_NSWindowStyleMaskClosable)
        : (_app_NSWindowStyleMask)(style & ~_app_NSWindowStyleMaskClosable);
    style =
        (features & APP_WINDOW_FEATURES_MINIMIZE)
        ? (_app_NSWindowStyleMask)(style | _app_NSWindowStyleMaskMiniaturizable)
        : (_app_NSWindowStyleMask)(style & ~_app_NSWindowStyleMaskMiniaturizable);
    style =
        (features & APP_WINDOW_FEATURES_RESIZE)
        ? (_app_NSWindowStyleMask)(style | _app_NSWindowStyleMaskResizable)
        : (_app_NSWindowStyleMask)(style & ~_app_NSWindowStyleMaskResizable);
    const bool showTitlebar = features & APP_WINDOW_FEATURES_TITLEBAR;
    _app_objc_obj(nswindow,_app_NSWindow,setStyleMask,style);
    _app_objc_obj(nswindow,_app_NSWindow,setTitlebarAppearsTransparent,~showTitlebar);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

app_rect
app_window_get_frame(app_window* const window) {
    assert(window);
    _app_NSWindow* const nswindow = (_app_NSWindow*)window;

    _app_NSRect nsrect = _app_objc_obj(nswindow,_app_NSWindow,frame);
    _app_orient_NSRect_to_desktop(&nsrect);

    app_rect frame = {0,0,0,0};
    frame.x = (float)nsrect.origin.x;
    frame.y = (float)nsrect.origin.y;
    frame.w = (float)nsrect.size.width;
    frame.h = (float)nsrect.size.height;
    return frame;
}

void
app_window_set_frame(app_window* const window, app_rect frame) {
    assert(window);
    _app_NSWindow* const nswindow = (_app_NSWindow*)window;

    _app_NSRect nsrect = { {frame.x, frame.y}, {frame.w, frame.h} };
    _app_orient_NSRect_to_desktop(&nsrect);

    const bool isVisible = _app_objc_obj(nswindow,_app_NSWindow,isVisible);
    _app_objc_obj(nswindow,_app_NSWindow,setFrame,nsrect,display,isVisible);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

app_rect
app_window_get_viewport(app_window* const window) {
    assert(window);
    _app_NSWindow* const nswindow = (_app_NSWindow*)window;

    _app_NSRect nsrect = _app_objc_obj(nswindow,_app_NSWindow,frame);
    nsrect = _app_objc_obj(nswindow,_app_NSWindow,contentRectForFrameRect,nsrect);

    _app_orient_NSRect_to_desktop(&nsrect);

    app_rect viewport = {0,0,0,0};
    viewport.x = (float)nsrect.origin.x;
    viewport.y = (float)nsrect.origin.y;
    viewport.w = (float)nsrect.size.width;
    viewport.h = (float)nsrect.size.height;
    return viewport;
}

void
app_window_set_viewport(app_window* const window, app_rect viewport) {
    assert(window);
    _app_NSWindow* const nswindow = (_app_NSWindow*)window;

    _app_NSRect nsrect = { {viewport.x, viewport.y}, {viewport.w, viewport.h} };
    _app_orient_NSRect_to_desktop(&nsrect);

    nsrect = _app_objc_obj(nswindow,_app_NSWindow,frameRectForContentRect,nsrect);

    const bool isVisible = _app_objc_obj(nswindow,_app_NSWindow,isVisible);
    _app_objc_obj(nswindow,_app_NSWindow,setFrame,nsrect,display,isVisible);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool
app_window_is_active(app_window* window) {
    return (app_window*)_app_objc_obj(_app_NSApp,_app_NSApplication,keyWindow) == window;
}

app_window*
app_window_get_active(void) {
    return (app_window*)_app_objc_obj(_app_NSApp,_app_NSApplication,keyWindow);
}

void
app_window_activate(app_window* window) {
    assert(window);
    _app_NSWindow* const nswindow = (_app_NSWindow*)window;
    if (_app_objc_obj(nswindow,_app_NSWindow,isMiniaturized))
        _app_objc_obj(nswindow,_app_NSWindow,deminiaturize,window);
    _app_objc_obj(nswindow,_app_NSWindow,setIsVisible,true);
    _app_objc_obj(nswindow,_app_NSWindow,makeKeyAndOrderFront,window);
    _app_objc_obj(nswindow,_app_NSWindow,makeMainWindow);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool
app_window_is_open(app_window* const window) {
    assert(window);
    _app_NSWindow* const nswindow = (_app_NSWindow*)window;
    return _app_objc_obj(nswindow,_app_NSWindow,isVisible);
}

void
app_window_set_open(
    app_window* const window,
    const bool open
) {
    assert(window);
    _app_NSWindow* const nswindow = (_app_NSWindow*)window;
    if (open) {
        if (_app_objc_obj(_app_NSApp,_app_NSApplication,keyWindow) == NULL) {
            app_window_activate(window);
            return;
        }
        if (_app_objc_obj(nswindow,_app_NSWindow,isMiniaturized))
            _app_objc_obj(nswindow,_app_NSWindow,deminiaturize,window);
        _app_objc_obj(nswindow,_app_NSWindow,setIsVisible,true);
        _app_objc_obj(nswindow,_app_NSWindow,orderFront,window);
    }
    else {
        _app_objc_obj(nswindow,_app_NSWindow,setIsVisible,false);
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool
app_window_is_fullscreen(app_window* window) {
    assert(window);
    _app_NSWindow* const nswindow = (_app_NSWindow*)window;
    _app_NSWindowStyleMask style = _app_objc_obj(nswindow,_app_NSWindow,styleMask);
    return (style & _app_NSWindowStyleMaskFullScreen) == _app_NSWindowStyleMaskFullScreen;
}

void
app_window_set_fullscreen(app_window* window, bool fullscreen) {
    assert(window);
    _app_NSWindow* const nswindow = (_app_NSWindow*)window;
    _app_NSWindowStyleMask style = _app_objc_obj(nswindow,_app_NSWindow,styleMask);
    style =
        (fullscreen)
        ? (_app_NSWindowStyleMask)(style | _app_NSWindowStyleMaskFullScreen)
        : (_app_NSWindowStyleMask)(style & ~_app_NSWindowStyleMaskFullScreen);
    _app_objc_obj(nswindow,_app_NSWindow,setStyleMask,style);
}

//------------------------------------------------------------------------------

APP_EXTERN_C_END

//------------------------------------------------------------------------------
