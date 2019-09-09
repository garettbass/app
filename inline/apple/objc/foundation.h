#pragma once
#include "corefoundation.h"

//------------------------------------------------------------------------------

_app_objc_class(NSArray);
_app_objc_class(NSAutoreleasePool);
_app_objc_class(NSBundle);
_app_objc_class(NSData);
_app_objc_class(NSDictionary);
_app_objc_class(NSError);
_app_objc_class(NSMutableArray);
_app_objc_class(NSNotification);
_app_objc_class(NSString);

//------------------------------------------------------------------------------

#if defined(__LP64__) && __LP64__
    typedef double        CGFloat;
    typedef unsigned long NSUInteger;
    typedef signed long   NSInteger;
#else
    typedef float         CGFloat;
    typedef unsigned int  NSUInteger;
    typedef signed int    NSInteger;
#endif

typedef double NSTimeInterval;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

typedef struct CGPoint {
    CGFloat x;
    CGFloat y;
} CGPoint, NSPoint;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

typedef struct CGSize {
    CGFloat width;
    CGFloat height;
} CGSize, NSSize;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

typedef struct CGRect  {
    CGPoint origin;
    CGSize size;
} CGRect, NSRect;

APP_EXTERN_C_BEGIN
static inline NSRect
NSMakeRect(CGFloat x, CGFloat y, CGFloat w, CGFloat h) {
    NSRect result = { {x,y}, {w,h} };
    return result;
}
APP_EXTERN_C_END

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

typedef struct NSRange {
    NSUInteger location;
    NSUInteger length;
} NSRange;

//------------------------------------------------------------------------------

_app_objc_interface(
    NSArray,
    obj(NSUInteger, count),
    obj(_app_objc_id,         firstObject),
    obj(_app_objc_id,         lastObject),
    obj(_app_objc_id,         objectAtIndex,NSUInteger),
    obj(NSUInteger, indexOfObject,_app_objc_id),
)

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

_app_objc_interface(
    NSAutoreleasePool,
    cls(void, showPools),
    obj(void, drain),
)

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

_app_objc_interface(
    NSBundle,
    cls(NSBundle*,  mainBundle),
    obj(NSString*,  bundleIdentifier),
    obj(NSString*,  bundlePath),
)

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

_app_objc_interface(
    NSData,
    obj(const void*, bytes),
)

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

_app_objc_interface(
    NSDictionary,
    cls(NSDictionary*,
        dictionaryWithObjects,_app_objc_id*, 
        forKeys,NSString*,
        count,NSUInteger),
    obj(NSUInteger, count),
    obj(_app_objc_id,valueForKey,NSString*),
)

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

_app_objc_interface(
    NSCoder,
    obj(bool,           containsValueForKey,NSString*),

    obj(_app_objc_id,             decodeObjectForKey,NSString*),
    obj(bool,           decodeBoolForKey,NSString*),
    obj(int,            decodeIntForKey,NSString*),
    obj(int32_t,        decodeInt32ForKey,NSString*),
    obj(int64_t,        decodeInt64ForKey,NSString*),
    obj(NSInteger,      decodeIntegerForKey,NSString*),
    obj(float,          decodeFloatForKey,NSString*),
    obj(double,         decodeDoubleForKey,NSString*),
    obj(const char*,    decodeBytesForKey,NSString*,returnedLength,NSUInteger*),

    obj(void,           encodeObject,_app_objc_id,forKey,NSString*),
    obj(void,           encodeBool,bool,forKey,NSString*),
    obj(void,           encodeInt,int,forKey,NSString*),
    obj(void,           encodeInt32,int32_t,forKey,NSString*),
    obj(void,           encodeInt64,int64_t,forKey,NSString*),
    obj(void,           encodeInteger,NSInteger,forKey,NSString*),
    obj(void,           encodeFloat,float,forKey,NSString*),
    obj(void,           encodeDouble,double,forKey,NSString*),
    obj(void,           encodeBytes,const char*,length,NSUInteger),
)

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

_app_objc_interface(
    NSError,
    obj(NSUInteger, code),
    obj(NSString*,  domain),
    obj(NSString*,  localizedDescription),
    obj(NSString*,  localizedRecoveryOptions),
    obj(NSString*,  localizedRecoverySuggestion),
    obj(NSString*,  localizedFailureReason),
)

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

_app_objc_interface(
    NSMutableArray,
    cls(NSMutableArray*, arrayWithCapacity,NSUInteger),
    obj(void, addObject,_app_objc_id),
    obj(void, insertObject,_app_objc_id,atIndex,NSUInteger),
    obj(void, removeObjectAtIndex,NSUInteger),
    obj(void, removeLastObject),
    obj(void, replaceObjectAtIndex,NSUInteger,withObject,_app_objc_id)
)

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

_app_objc_interface(
    NSNotification,
    obj(NSString*, name),
)

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

_app_objc_interface(
    NSString,
    cls(NSString*,   stringWithUTF8String,const char*),
    obj(const char*, UTF8String),
)

#define _app_objc_str(CSTR) (_app_objc_cls(NSString,stringWithUTF8String,CSTR))

#define _app_objc_cstr(NSSTR) (_app_objc_obj(NSSTR,NSString,UTF8String))

//------------------------------------------------------------------------------
