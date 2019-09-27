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
    _app_delegate,
)

_app_objc_implementation(
    _app_delegate, _app_NSObject,
    obj(void,
        applicationDidFinishLaunching,_app_NSNotification*),
    obj(_app_NSApplicationTerminateReply,
        applicationShouldTerminate,_app_NSApplication*),
    obj(void,
        applicationWillTerminate,_app_NSNotification*),
)

_app_objc_method(
    void,
    _app_delegate,
    applicationDidFinishLaunching,_app_NSNotification*
) {
    (void)self;
    (void)cmd;
    (void)applicationDidFinishLaunching;
    puts(__func__);
}

_app_objc_method(
    _app_NSApplicationTerminateReply,
    _app_delegate,
    applicationShouldTerminate,_app_NSApplication*
) {
    (void)self;
    (void)cmd;
    (void)applicationShouldTerminate;
    puts(__func__);
    app_quit();
    return _app_NSApplicationTerminateCancel;
}

_app_objc_method(
    void,
    _app_delegate,
    applicationWillTerminate,_app_NSNotification*
) {
    (void)self;
    (void)cmd;
    (void)applicationWillTerminate;
    puts(__func__);
    app_quit();
}

//------------------------------------------------------------------------------

#if 0
_app_objc_cls_swizzle(_app_objc_id, _app_NSObject, alloc) {
    printf("%s.%s\n", class_getName(self), (const char*)cmd);
    return imp(self, cmd);
}

_app_objc_obj_swizzle(void, _app_NSObject, dealloc) {
    printf("%s.%s\n", class_getName(object_getClass(self)), (const char*)cmd);
    imp(self, cmd);
}
#endif

//------------------------------------------------------------------------------

void
app_activate(void) {
    _app_objc_obj(_app_NSApp,_app_NSApplication,activateIgnoringOtherApps,true);
}

bool
app_is_active(void) {
    return _app_objc_obj(_app_NSApp,_app_NSApplication,isActive);
}

//------------------------------------------------------------------------------

#if 0
_app_objc_obj_swizzle(void,_app_NSMenu,dealloc) {
    const char* title = _app_objc_cstr(_app_objc_autorelease(_app_objc_obj(self,_app_NSMenu,title)));
    printf("_app_NSMenu.%s: '%s'\n",(const char*)cmd, title);
    imp(self, cmd);
}
_app_objc_obj_swizzle(void,_app_NSMenuItem,dealloc) {
    const char* title = _app_objc_cstr(_app_objc_autorelease(_app_objc_obj(self,_app_NSMenuItem,title)));
    printf("_app_NSMenuItem.%s: '%s'\n",(const char*)cmd, title);
    imp(self, cmd);
}
#endif

_app_objc_obj_swizzle(void,_app_NSApplication,terminate,_app_objc_id) {
    printf("_app_NSApplication.%s\n",(const char*)cmd);
    imp(self, cmd, terminate);
}

typedef void (*AppMenuCallback)(void);

_app_objc_interface(
    AppMenuItem,
    cls(_app_NSMenuItem*,    menuItemWithTitle,_app_NSString*,
                        callback,AppMenuCallback,
                        keyEquivalent,_app_NSString*),
    obj(void,           invokeCallback),
    obj(bool,           validateMenuItem,_app_NSMenuItem*),
)

_app_objc_implementation(
    AppMenuItem, _app_NSMenuItem,
    var(AppMenuCallback,    callback),
    cls(_app_NSMenuItem*,        menuItemWithTitle,_app_NSString*,
                            callback,AppMenuCallback,
                            keyEquivalent,_app_NSString*),
    obj(void,               invokeCallback),
    obj(bool,               validateMenuItem,_app_NSMenuItem*),
)

_app_objc_method(_app_NSMenuItem*,AppMenuItem,
    menuItemWithTitle,_app_NSString*,
    callback,AppMenuCallback,
    keyEquivalent,_app_NSString*
) {
    _app_objc_selector* const action = _app_objc_sel(AppMenuItem,invokeCallback);
    AppMenuItem* const item = _app_objc_autorelease(_app_objc_cls(AppMenuItem,alloc));
    _app_objc_obj((_app_NSMenuItem*)item,_app_NSMenuItem,
        initWithTitle,menuItemWithTitle,
        action,action,
        keyEquivalent,keyEquivalent);
    _app_objc_obj((_app_NSMenuItem*)item,_app_NSMenuItem,setTarget,item);
    _app_objc_var(item,AppMenuItem,callback) = callback;
    return (_app_NSMenuItem*)item;
}

_app_objc_method(void,AppMenuItem,invokeCallback) {
    AppMenuCallback const callback = _app_objc_var(self,AppMenuItem,callback);
    if (callback) callback();
}

_app_objc_method(bool,AppMenuItem,validateMenuItem,_app_NSMenuItem*) {
    assert((size_t)self == (size_t)validateMenuItem);
    AppMenuCallback const callback = _app_objc_var(self,AppMenuItem,callback);
    return callback;
}

//------------------------------------------------------------------------------

static inline void
_appMenuCreate(void) {
    _app_objc_id mainMenu = _app_objc_autorelease(_app_objc_cls(_app_NSMenu,new));
    _app_objc_id appItem  = _app_objc_autorelease(_app_objc_cls(_app_NSMenuItem,new));
    _app_objc_id appMenu  = _app_objc_autorelease(_app_objc_cls(_app_NSMenu,new));

    _app_objc_id quitItem =
        _app_objc_cls(AppMenuItem,
            menuItemWithTitle,_app_objc_str("Quit"),
            callback,app_quit,
            keyEquivalent,_app_objc_str("q"));
    _app_objc_obj(appMenu,_app_NSMenu,addItem,quitItem);

    _app_objc_obj(appItem,_app_NSMenuItem,setSubmenu,appMenu);
    _app_objc_obj(mainMenu,_app_NSMenu,addItem,appItem);
    _app_objc_obj(_app_NSApp,_app_NSApplication,setMainMenu,mainMenu);
}

static inline void
_appMenuDestroy(void) {
    puts(__func__);
    _app_objc_id mainMenu = _app_objc_obj(_app_NSApp,_app_NSApplication,mainMenu);
    _app_objc_obj(_app_NSApp,_app_NSApplication,setMainMenu,NULL);
}

//------------------------------------------------------------------------------

int main(int argc, const char* argv[], const char* envp[]) {
    // UI Persistence causes code-created _app_NSWindows to be invisible!
    _app_objc_id const manager = _app_objc_cls(_app_NSPersistentUIManager,sharedManager);
    if (manager) {
        // puts("_app_NSPersistentUIManager,disableRestorableStateWriting");
        _app_objc_obj(manager,_app_NSPersistentUIManager,
            disableRestorableStateWriting);
        // puts("_app_NSPersistentUIManager,ignoreAnyPreexistingPersistentState");
        _app_objc_obj(manager,_app_NSPersistentUIManager,
            ignoreAnyPreexistingPersistentState);
    }

    _app_autoreleasepool_push();
    _appMenuCreate();

    _app_objc_obj(_app_NSApp,_app_NSApplication,finishLaunching);
    app_activate();

    extern int app_main(int, const char*[], const char*[]);
    const int result = app_main(argc, argv, envp);

    _appMenuDestroy();
    _app_autoreleasepool_pop();

    // printf("result: %i\n", result);
    return result;
}

#pragma GCC poison _app_delegate
#pragma GCC poison _app_autoreleasepool_push
#pragma GCC poison _app_autoreleasepool_pop
#pragma GCC poison _app_autoreleasepool_popPush

//------------------------------------------------------------------------------

APP_EXTERN_C_END

//------------------------------------------------------------------------------
