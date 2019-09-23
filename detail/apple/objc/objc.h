#pragma once
#include "../../../app.h"

//------------------------------------------------------------------------------

#if __has_feature(objc_arc)
    #error "Objective-C Automatic Reference Counting is enabled"
#endif

//------------------------------------------------------------------------------

#include <assert.h>
#include <stdalign.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "detail/id.h"
#include "detail/utility.h"

//------------------------------------------------------------------------------

typedef struct _app_objc_class      _app_objc_class;
typedef struct _app_objc_ivar       _app_objc_ivar;
typedef struct _app_objc_method     _app_objc_method;
typedef struct _app_objc_selector   _app_objc_selector;
typedef struct _app_objc_property   _app_objc_property;
typedef struct _app_objc_super2     _app_objc_super2;

typedef _app_objc_id (*_app_objc_imp)(_app_objc_id, _app_objc_selector*, ...);

/*------------------------------------------------------------------------------
_app_objc_framework(FRAMEWORK) - load an Objective-C framework
_app_objc_import(FRAMEWORK, SYMBOLS...) - import symbols from a framework

Usage:

    _app_objc_framework(Foundation)
    _app_objc_import(
        Foundation,
        function(void,objc_release,(void*)),
        function(void,objc_retain,(void*)),
    )

*/
#define _app_objc_framework(FRAMEWORK) __app_objc_framework(FRAMEWORK)
#include "detail/framework.h"

#define _app_objc_import(FRAMEWORK, /*SYMBOLS*/...) __app_objc_import(FRAMEWORK, __VA_ARGS__)
#include "detail/import.h"

//------------------------------------------------------------------------------

_app_objc_framework(CoreFoundation)
_app_objc_import(
    CoreFoundation,
    function(signed long, CFGetRetainCount,(const void*)),
)

//------------------------------------------------------------------------------

_app_objc_framework(Foundation)
_app_objc_import(
    Foundation,
    function(bool,                class_addIvar,(_app_objc_class*, const char* name, size_t size, uint8_t alignment, const char* types)),
    function(bool,                class_addMethod,(_app_objc_class*, _app_objc_selector*, _app_objc_imp, const char* types)),
    function(_app_objc_method**,  class_copyMethodList,(_app_objc_class*, unsigned int *outCount)),
    function(_app_objc_ivar**,    class_copyIvarList,(_app_objc_class*, unsigned int *outCount)),
    function(_app_objc_method*,   class_getClassMethod,(_app_objc_class*, _app_objc_selector*)),
    function(_app_objc_method*,   class_getInstanceMethod,(_app_objc_class*, _app_objc_selector*)),
    function(size_t,              class_getInstanceSize,(_app_objc_class*)),
    function(_app_objc_ivar*,     class_getInstanceVariable,(_app_objc_class*, const char* name)),
    function(_app_objc_imp,       class_getMethodImplementation,(_app_objc_class*, _app_objc_selector*)),
    function(const char*,         class_getName,(_app_objc_class*)),
    function(_app_objc_class*,    class_getSuperclass,(_app_objc_class*)),
    function(const char*,         ivar_getName,(_app_objc_ivar*)),
    function(ptrdiff_t,           ivar_getOffset,(_app_objc_ivar*)),
    function(_app_objc_selector*, method_getName,(_app_objc_method* m)),
    function(const char*,         method_getTypeEncoding,(_app_objc_method*)),
    function(_app_objc_imp,       method_setImplementation,(_app_objc_method*, _app_objc_imp)),
    function(_app_objc_class*,    objc_allocateClassPair,(_app_objc_class*, const char* name, size_t extraBytes)),
    function(_app_objc_id,        objc_autorelease,(void*)),
    function(void,                objc_autoreleasePoolPop,(void*)),
    function(void*,               objc_autoreleasePoolPush,(void)),
    function(void*,               objc_constructInstance,(_app_objc_class*, void* bytes)),
    function(void,                objc_destructInstance,(void*)),
    function(_app_objc_class*,    objc_getClass,(const char* name)),
    function(void*,               objc_getProtocol,(const char* name)),
    function(void*,               objc_msgSend,(_app_objc_id, _app_objc_selector*, ...)),
    function(void,                objc_msgSend_stret,(_app_objc_id, _app_objc_selector*, ...)),
    function(void*,               objc_msgSendSuper2,(_app_objc_super2*, _app_objc_selector*, ...)),
    function(void,                objc_msgSendSuper2_stret,(_app_objc_super2*, _app_objc_selector*, ...)),
    function(void,                objc_registerClassPair,(_app_objc_class*)),
    function(void,                objc_release,(void*)),
    function(_app_objc_id,        objc_retain,(void*)),
    function(_app_objc_class*,    object_getClass,(void*)),
    function(const char*,         sel_getName,(_app_objc_selector*)),
    function(_app_objc_selector*, sel_getUid,(const char*)),
)

#if defined(__x86_64__) || defined(__i386__)

    _app_objc_import(
        Foundation,
        function(long double,objc_msgSend_fpret,(_app_objc_id, _app_objc_selector*, ...)),
    )

#elif defined(__arm__)

    #define objc_msgSend_fpret objc_msgSend

#endif

#define _app_objc_retain(obj)      (objc_retain(obj))
#define _app_objc_release(obj)     (objc_release(obj))
#define _app_objc_autorelease(obj) (objc_autorelease(obj))

/*------------------------------------------------------------------------------
_app_objc_autoreleasepool - scoped autorelease pool
*/

#define _app_objc_autoreleasepool\
    for(__attribute__((cleanup(_app_objc_autoreleasepool_cleanup)))\
        void* _app_objc_autoreleasepool = objc_autoreleasePoolPush();\
        _app_objc_autoreleasepool;\
        _app_objc_autoreleasepool_cleanup(&_app_objc_autoreleasepool))

static inline void _app_objc_autoreleasepool_cleanup(void** ppool) {
    if (*ppool) { objc_autoreleasePoolPop(*ppool); *ppool = NULL; }
}

/*------------------------------------------------------------------------------
_app_objc_class(NAME) - forward declare an Objective-C class
*/
#define _app_objc_class(NAME) typedef struct NAME NAME

_app_objc_class(NSObject);

/*------------------------------------------------------------------------------
_app_objc_interface(CLASS, SYMBOLS...) - declare an Objective-C class interface

Usage:

    _app_objc_interface(
        NSDate,
        cls(NSDate*, date),
        cls(NSDate*, dateWithTimeIntervalSinceNow,NSTimeInterval),
        cls(NSDate*, dateWithTimeInterval,NSTimeInterval,sinceDate,NSDate*),
        cls(NSDate*, distantPast),
        cls(NSDate*, distantFuture),
        obj(NSDate*, initWithTimeInterval,NSTimeInterval,sinceDate,NSDate*),
    )

*/
#include "detail/message.h"
#include "detail/interface.h"
#define _app_objc_interface(CLASS, /*SYMBOLS*/...)\
        __app_objc_interface(CLASS, __VA_ARGS__)

_app_objc_interface(
    NSObject,
)

/*------------------------------------------------------------------------------
_app_objc_implementation(CLASS, SUPERCLASS, SYMBOLS...) - define an Objective-C class
_app_objc_method(RESULT, CLASS, PARAMS...) - define a class method implementation

Usage:

    _app_objc_interface(
        AppDelegate,
    )

    _app_objc_implementation(
        AppDelegate, NSObject,
        obj(NSApplicationTerminateReply,
            applicationShouldTerminate,NSApplication*),
    )

    _app_objc_method(
        NSApplicationTerminateReply,
        AppDelegate,
        applicationShouldTerminate,NSApplication*
    ) {
        puts(__func__);
        app_quit();
        return NSApplicationTerminateCancel;
    }

*/
#include "detail/implementation.h"
#define _app_objc_implementation(CLASS, SUPERCLASS, /*SYMBOLS*/...)\
        __app_objc_implementation(CLASS, SUPERCLASS, __VA_ARGS__)

#include "detail/method.h"
#define _app_objc_method(RESULT, CLASS, /*PARAMS*/...)\
        __app_objc_method(RESULT, CLASS, __VA_ARGS__)

/*------------------------------------------------------------------------------
_app_objc_cls(CLASS, PARAMS...) - call an Objective-C class method

Usage:

    NSWindow* const nsWindow = _app_objc_cls(NSWindow,new);

*/
#define _app_objc_cls(CLASS, /*PARAMS*/...)\
        __app_objc_msg_send(CLASS##_class, CLASS, __VA_ARGS__)

/*------------------------------------------------------------------------------
_app_objc_obj(CLASS, PARAMS...) - call an Objective-C object method

Usage:

    _app_objc_obj(nsWindow,NSWindow,setReleasedWhenClosed,false);

*/
#define _app_objc_obj(SELF, CLASS, /*PARAMS*/...)\
        __app_objc_msg_send(SELF, CLASS, __VA_ARGS__)

/*------------------------------------------------------------------------------
_app_objc_super(CLASS, PARAMS...) - call an Objective-C super method

Usage:

    _app_objc_method(app_window*,app_window,alloc) {
        puts((const char*)cmd);
        return _app_objc_super(app_window,alloc);
    }

*/
#define _app_objc_super(CLASS, /*PARAMS*/...)\
        __app_objc_msg_send_super(CLASS, __VA_ARGS__)

/*------------------------------------------------------------------------------
_app_objc_var(SELF, CLASS, NAME) - get/set an Objective-C object member variable

Usage:

    _app_objc_implementation(
        AppMenuItem, NSMenuItem,
        var(AppMenuCallback,    callback),
        cls(NSMenuItem*,        menuItemWithTitle,NSString*,
                                callback,AppMenuCallback,
                                keyEquivalent,NSString*),
        obj(void,               invokeCallback),
        obj(bool,               validateMenuItem,NSMenuItem*),
    )

    //...

    _app_objc_var(item,AppMenuItem,callback) = callback;

*/
#include "detail/var.h"
#define _app_objc_var(SELF, CLASS, NAME)\
        __app_objc_var(SELF, CLASS, NAME)


/*------------------------------------------------------------------------------
_app_objc_cls_swizzle(RESULT, CLASS, PARAMS...) - replace class method implementation
_app_objc_obj_swizzle(RESULT, CLASS, PARAMS...) - replace object method implementation

Usage:

    _app_objc_cls_swizzle(_app_objc_id, NSObject, alloc) {
        printf("%s.%s\n", class_getName(self), (const char*)cmd);
        return imp(self, cmd);
    }

    _app_objc_obj_swizzle(void, NSObject, dealloc) {
        printf("%s.%s\n", class_getName(object_getClass(self)), (const char*)cmd);
        imp(self, cmd);
    }

*/
#include "detail/swizzle.h"
#define _app_objc_cls_swizzle(RESULT, CLASS, /*PARAMS*/...)\
        __app_objc_msg_swizzle(RESULT, CLASS, _app_objc_class*, ClassMethod, __VA_ARGS__)

#define _app_objc_obj_swizzle(RESULT, CLASS, /*PARAMS*/...)\
        __app_objc_msg_swizzle(RESULT, CLASS, CLASS*, InstanceMethod, __VA_ARGS__)

//------------------------------------------------------------------------------
