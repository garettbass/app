#pragma once
#include "../../app.inl"
#include "../objc/appkit.h"
#include "../objc/carbon.h"
#include "../objc/coregraphics.h"

//------------------------------------------------------------------------------

static void* _app_autoreleasepool = NULL;

static inline void
_app_autoreleasepool_push() {
    assert(_app_autoreleasepool == NULL);
    _app_autoreleasepool = objc_autoreleasePoolPush();
}

static inline void
_app_autoreleasepool_pop() {
    assert(_app_autoreleasepool);
    objc_autoreleasePoolPop(_app_autoreleasepool);
    _app_autoreleasepool = NULL;
}

static inline void
_app_autoreleasepool_popPush() {
    _app_autoreleasepool_pop();
    _app_autoreleasepool_push();
}

#pragma GCC poison _app_autoreleasepool

//------------------------------------------------------------------------------

#include "cursor.inl"
#include "key.inl"
#include "update.inl"
#include "window.inl"

//------------------------------------------------------------------------------

APP_EXTERN_C_BEGIN

//------------------------------------------------------------------------------

_app_objc_interface(
    AppDelegate,
)

_app_objc_implementation(
    AppDelegate, NSObject,
    obj(void,
        applicationDidFinishLaunching,NSNotification*),
    obj(NSApplicationTerminateReply,
        applicationShouldTerminate,NSApplication*),
    obj(void,
        applicationWillTerminate,NSNotification*),
)

_app_objc_method(
    void,
    AppDelegate,
    applicationDidFinishLaunching,NSNotification*
) {
    puts(__func__);
}

_app_objc_method(
    NSApplicationTerminateReply,
    AppDelegate,
    applicationShouldTerminate,NSApplication*
) {
    puts(__func__);
    app_quit();
    return NSApplicationTerminateCancel;
}

_app_objc_method(
    void,
    AppDelegate,
    applicationWillTerminate,NSNotification*
) {
    puts(__func__);
    app_quit();
}

//------------------------------------------------------------------------------

#if 0
_app_objc_cls_swizzle(_app_objc_id, NSObject, alloc) {
    printf("%s.%s\n", class_getName(self), (const char*)cmd);
    return imp(self, cmd);
}

_app_objc_obj_swizzle(void, NSObject, dealloc) {
    printf("%s.%s\n", class_getName(object_getClass(self)), (const char*)cmd);
    imp(self, cmd);
}
#endif

//------------------------------------------------------------------------------

void
app_activate(void) {
    _app_objc_obj(NSApp,NSApplication,activateIgnoringOtherApps,true);
}

bool
app_is_active(void) {
    return _app_objc_obj(NSApp,NSApplication,isActive);
}

//------------------------------------------------------------------------------

#if 0
_app_objc_obj_swizzle(void,NSMenu,dealloc) {
    const char* title = _app_objc_cstr(_app_objc_autorelease(_app_objc_obj(self,NSMenu,title)));
    printf("NSMenu.%s: '%s'\n",(const char*)cmd, title);
    imp(self, cmd);
}
_app_objc_obj_swizzle(void,NSMenuItem,dealloc) {
    const char* title = _app_objc_cstr(_app_objc_autorelease(_app_objc_obj(self,NSMenuItem,title)));
    printf("NSMenuItem.%s: '%s'\n",(const char*)cmd, title);
    imp(self, cmd);
}
#endif

_app_objc_obj_swizzle(void,NSApplication,terminate,_app_objc_id) {
    printf("NSApplication.%s\n",(const char*)cmd);
    imp(self, cmd, terminate);
}

typedef void (*AppMenuCallback)(void);

_app_objc_interface(
    AppMenuItem,
    cls(NSMenuItem*,    menuItemWithTitle,NSString*,
                        callback,AppMenuCallback,
                        keyEquivalent,NSString*),
    obj(void,           invokeCallback),
    obj(bool,           validateMenuItem,NSMenuItem*),
)

_app_objc_implementation(
    AppMenuItem, NSMenuItem,
    var(AppMenuCallback,    callback),
    cls(NSMenuItem*,        menuItemWithTitle,NSString*,
                            callback,AppMenuCallback,
                            keyEquivalent,NSString*),
    obj(void,               invokeCallback),
    obj(bool,               validateMenuItem,NSMenuItem*),
)

_app_objc_method(NSMenuItem*,AppMenuItem,
    menuItemWithTitle,NSString*,
    callback,AppMenuCallback,
    keyEquivalent,NSString*
) {
    _app_objc_selector* const action = _app_objc_sel(AppMenuItem,invokeCallback);
    AppMenuItem* const item = _app_objc_autorelease(_app_objc_cls(AppMenuItem,alloc));
    _app_objc_obj((NSMenuItem*)item,NSMenuItem,
        initWithTitle,menuItemWithTitle,
        action,action,
        keyEquivalent,keyEquivalent);
    _app_objc_obj((NSMenuItem*)item,NSMenuItem,setTarget,item);
    _app_objc_var(item,AppMenuItem,callback) = callback;
    return (NSMenuItem*)item;
}

_app_objc_method(void,AppMenuItem,invokeCallback) {
    AppMenuCallback const callback = _app_objc_var(self,AppMenuItem,callback);
    if (callback) callback();
}

_app_objc_method(bool,AppMenuItem,validateMenuItem,NSMenuItem*) {
    assert((size_t)self == (size_t)validateMenuItem);
    AppMenuCallback const callback = _app_objc_var(self,AppMenuItem,callback);
    return callback;
}

//------------------------------------------------------------------------------

static inline void
_appMenuCreate(void) {
    NSMenu*         mainMenu = _app_objc_autorelease(_app_objc_cls(NSMenu,new));
    NSMenuItem*     appItem  = _app_objc_autorelease(_app_objc_cls(NSMenuItem,new));
    NSMenu*         appMenu  = _app_objc_autorelease(_app_objc_cls(NSMenu,new));

    NSMenuItem* quitItem =
        _app_objc_cls(AppMenuItem,
            menuItemWithTitle,_app_objc_str("Quit"),
            callback,app_quit,
            keyEquivalent,_app_objc_str("q"));
    _app_objc_obj(appMenu,NSMenu,addItem,quitItem);

    _app_objc_obj(appItem,NSMenuItem,setSubmenu,appMenu);
    _app_objc_obj(mainMenu,NSMenu,addItem,appItem);
    _app_objc_obj(NSApp,NSApplication,setMainMenu,mainMenu);
}

static inline void
_appMenuDestroy(void) {
    puts(__func__);
    NSMenu* mainMenu = _app_objc_obj(NSApp,NSApplication,mainMenu);
    _app_objc_obj(NSApp,NSApplication,setMainMenu,NULL);
}

//------------------------------------------------------------------------------

int main(int argc, const char* argv[], const char* envp[]) {
    // UI Persistence causes code-created NSWindows to be invisible!
    _app_objc_id const manager = _app_objc_cls(NSPersistentUIManager,sharedManager);
    if (manager) {
        // puts("NSPersistentUIManager,disableRestorableStateWriting");
        _app_objc_obj(manager,NSPersistentUIManager,
            disableRestorableStateWriting);
        // puts("NSPersistentUIManager,ignoreAnyPreexistingPersistentState");
        _app_objc_obj(manager,NSPersistentUIManager,
            ignoreAnyPreexistingPersistentState);
    }

    _app_autoreleasepool_push();
    _appMenuCreate();

    _app_objc_obj(NSApp,NSApplication,finishLaunching);
    app_activate();

    extern int app_main(int, const char*[], const char*[]);
    const int result = app_main(argc, argv, envp);

    _appMenuDestroy();
    _app_autoreleasepool_pop();

    // printf("result: %i\n", result);
    return result;
}

#pragma GCC poison AppDelegate
#pragma GCC poison _app_autoreleasepool_push
#pragma GCC poison _app_autoreleasepool_pop
#pragma GCC poison _app_autoreleasepool_popPush

//------------------------------------------------------------------------------

APP_EXTERN_C_END

//------------------------------------------------------------------------------
