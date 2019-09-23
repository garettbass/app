#pragma once
#include "app.inl"

//------------------------------------------------------------------------------

APP_EXTERN_C_BEGIN

//------------------------------------------------------------------------------

// _app_objc_obj_swizzle(NSWindow*,NSWindow,retain) {
//     printf("NSWindow.%s\n",(const char*)cmd);
//     return imp(self, cmd);
// }

// _app_objc_obj_swizzle(void,NSWindow,release) {
//     printf("NSWindow.%s\n",(const char*)cmd);
//     imp(self, cmd);
// }

_app_objc_obj_swizzle(void,NSWindow,dealloc) {
    printf("NSWindow.%s\n",(const char*)cmd);
    imp(self, cmd);
}

_app_objc_obj_swizzle(void,NSWindow,keyDown,NSEvent*) {
    // NSWindow.keyDown will produce an error sound
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static inline void
_app_orient_NSRect_to_desktop(NSRect* nsrect) {
    NSScreen* const mainScreen = _app_objc_cls(NSScreen,mainScreen);
    NSRect const desktop = _app_objc_obj(mainScreen,NSScreen,frame);
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
    NSScreen* const screen = _app_objc_cls(NSScreen,mainScreen);
    const NSRect screenRect = _app_objc_obj(screen,NSScreen,frame);
    const NSRect windowRect = {
        { screenRect.size.width / 8, screenRect.size.height / 8 },
        { screenRect.size.width / 4, screenRect.size.height / 4 },
    };
    const NSWindowStyleMask windowStyle =
        (NSWindowStyleMask)(
            NSWindowStyleMaskClosable |
            NSWindowStyleMaskMiniaturizable |
            NSWindowStyleMaskResizable |
            NSWindowStyleMaskTitled |
            NSWindowStyleMaskFullSizeContentView |
            //NSWindowStyleMaskUnifiedTitleAndToolbar |
            0);
    NSWindow* const nswindow = _app_objc_cls(NSWindow,new);
    _app_objc_obj(nswindow,NSWindow,setRestorable,false);
    _app_objc_obj(nswindow,NSWindow,setReleasedWhenClosed,false);
    _app_objc_obj(nswindow,NSWindow,setStyleMask,windowStyle);
    _app_objc_obj(nswindow,NSWindow,setFrame,windowRect,display,true);
    _app_objc_obj(nswindow,NSWindow,setIsVisible,true);
    _app_objc_obj(nswindow,NSWindow,center);
    // _app_log_retain_count(nswindow);
    return (app_window*)nswindow;
}

void
app_window_release(app_window* const window) {
    assert(window);
    NSWindow* const nswindow = (NSWindow*)window;
    _app_objc_obj(nswindow,NSWindow,setReleasedWhenClosed,true);
    _app_objc_obj(nswindow,NSWindow,setIsVisible,false);
    // _app_log_retain_count(nswindow);
    _app_objc_release(nswindow);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void
app_window_set_title(app_window* const window, const char* const title) {
    assert(window);
    NSWindow* const nswindow = (NSWindow*)window;
    _app_objc_obj(nswindow,NSWindow,setTitle,_app_objc_str(title));
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void
app_window_set_features(
    app_window* const window,
    const app_window_features features
) {
    assert(window);
    NSWindow* const nswindow = (NSWindow*)window;
    NSWindowStyleMask style = _app_objc_obj(nswindow,NSWindow,styleMask);
    style =
        (features & APP_WINDOW_FEATURES_CLOSE)
        ? (NSWindowStyleMask)(style | NSWindowStyleMaskClosable)
        : (NSWindowStyleMask)(style & ~NSWindowStyleMaskClosable);
    style =
        (features & APP_WINDOW_FEATURES_MINIMIZE)
        ? (NSWindowStyleMask)(style | NSWindowStyleMaskMiniaturizable)
        : (NSWindowStyleMask)(style & ~NSWindowStyleMaskMiniaturizable);
    style =
        (features & APP_WINDOW_FEATURES_RESIZE)
        ? (NSWindowStyleMask)(style | NSWindowStyleMaskResizable)
        : (NSWindowStyleMask)(style & ~NSWindowStyleMaskResizable);
    const bool showTitlebar = features & APP_WINDOW_FEATURES_TITLEBAR;
    _app_objc_obj(nswindow,NSWindow,setStyleMask,style);
    _app_objc_obj(nswindow,NSWindow,setTitlebarAppearsTransparent,~showTitlebar);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

app_rect
app_window_get_frame(app_window* const window) {
    assert(window);
    NSWindow* const nswindow = (NSWindow*)window;

    NSRect nsrect = _app_objc_obj(nswindow,NSWindow,frame);
    _app_orient_NSRect_to_desktop(&nsrect);

    app_rect frame = { 0 };
    frame.x = (float)nsrect.origin.x;
    frame.y = (float)nsrect.origin.y;
    frame.w = (float)nsrect.size.width;
    frame.h = (float)nsrect.size.height;
    return frame;
}

void
app_window_set_frame(app_window* const window, app_rect frame) {
    assert(window);
    NSWindow* const nswindow = (NSWindow*)window;

    NSRect nsrect = { {frame.x, frame.y}, {frame.w, frame.h} };
    _app_orient_NSRect_to_desktop(&nsrect);

    const bool isVisible = _app_objc_obj(nswindow,NSWindow,isVisible);
    _app_objc_obj(nswindow,NSWindow,setFrame,nsrect,display,isVisible);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

app_rect
app_window_get_viewport(app_window* const window) {
    assert(window);
    NSWindow* const nswindow = (NSWindow*)window;

    NSRect nsrect = _app_objc_obj(nswindow,NSWindow,frame);
    nsrect = _app_objc_obj(nswindow,NSWindow,contentRectForFrameRect,nsrect);

    _app_orient_NSRect_to_desktop(&nsrect);

    app_rect viewport = { 0 };
    viewport.x = (float)nsrect.origin.x;
    viewport.y = (float)nsrect.origin.y;
    viewport.w = (float)nsrect.size.width;
    viewport.h = (float)nsrect.size.height;
    return viewport;
}

void
app_window_set_viewport(app_window* const window, app_rect viewport) {
    assert(window);
    NSWindow* const nswindow = (NSWindow*)window;

    NSRect nsrect = { {viewport.x, viewport.y}, {viewport.w, viewport.h} };
    _app_orient_NSRect_to_desktop(&nsrect);

    nsrect = _app_objc_obj(nswindow,NSWindow,frameRectForContentRect,nsrect);

    const bool isVisible = _app_objc_obj(nswindow,NSWindow,isVisible);
    _app_objc_obj(nswindow,NSWindow,setFrame,nsrect,display,isVisible);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool
app_window_is_active(app_window* window) {
    return (app_window*)_app_objc_obj(NSApp,NSApplication,keyWindow) == window;
}

app_window*
app_window_get_active(void) {
    return (app_window*)_app_objc_obj(NSApp,NSApplication,keyWindow);
}

void
app_window_activate(app_window* window) {
    assert(window);
    NSWindow* const nswindow = (NSWindow*)window;
    if (_app_objc_obj(nswindow,NSWindow,isMiniaturized))
        _app_objc_obj(nswindow,NSWindow,deminiaturize,window);
    _app_objc_obj(nswindow,NSWindow,setIsVisible,true);
    _app_objc_obj(nswindow,NSWindow,makeKeyAndOrderFront,window);
    _app_objc_obj(nswindow,NSWindow,makeMainWindow);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool
app_window_is_open(app_window* const window) {
    assert(window);
    NSWindow* const nswindow = (NSWindow*)window;
    return _app_objc_obj(nswindow,NSWindow,isVisible);
}

void
app_window_set_open(
    app_window* const window,
    const bool open
) {
    assert(window);
    NSWindow* const nswindow = (NSWindow*)window;
    if (open) {
        if (_app_objc_obj(NSApp,NSApplication,keyWindow) == NULL) {
            app_window_activate(window);
            return;
        }
        if (_app_objc_obj(nswindow,NSWindow,isMiniaturized))
            _app_objc_obj(nswindow,NSWindow,deminiaturize,window);
        _app_objc_obj(nswindow,NSWindow,setIsVisible,true);
        _app_objc_obj(nswindow,NSWindow,orderFront,window);
    }
    else {
        _app_objc_obj(nswindow,NSWindow,setIsVisible,false);
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool
app_window_is_fullscreen(app_window* window) {
    assert(window);
    NSWindow* const nswindow = (NSWindow*)window;
    NSWindowStyleMask style = _app_objc_obj(nswindow,NSWindow,styleMask);
    return (style & NSWindowStyleMaskFullScreen) == NSWindowStyleMaskFullScreen;
}

void
app_window_set_fullscreen(app_window* window, bool fullscreen) {
    assert(window);
    NSWindow* const nswindow = (NSWindow*)window;
    NSWindowStyleMask style = _app_objc_obj(nswindow,NSWindow,styleMask);
    style =
        (fullscreen)
        ? (NSWindowStyleMask)(style | NSWindowStyleMaskFullScreen)
        : (NSWindowStyleMask)(style & ~NSWindowStyleMaskFullScreen);
    _app_objc_obj(nswindow,NSWindow,setStyleMask,style);
}

//------------------------------------------------------------------------------

APP_EXTERN_C_END

//------------------------------------------------------------------------------
