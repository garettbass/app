#pragma once
#include "corefoundation.h"

//------------------------------------------------------------------------------

_app_objc_class(_app_NSArray);
_app_objc_class(_app_NSAutoreleasePool);
_app_objc_class(_app_NSBundle);
_app_objc_class(_app_NSData);
_app_objc_class(_app_NSDictionary);
_app_objc_class(_app_NSError);
_app_objc_class(_app_NSMutableArray);
_app_objc_class(_app_NSNotification);
_app_objc_class(_app_NSString);

//------------------------------------------------------------------------------

#if defined(__LP64__) && __LP64__
    typedef double        CGFloat;
    typedef unsigned long _app_NSUInteger;
    typedef signed long   _app_NSInteger;
#else
    typedef float         CGFloat;
    typedef unsigned int  _app_NSUInteger;
    typedef signed int    _app_NSInteger;
#endif

typedef double _app_NSTimeInterval;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

typedef struct CGPoint {
    CGFloat x;
    CGFloat y;
} CGPoint, _app_NSPoint;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

typedef struct CGSize {
    CGFloat width;
    CGFloat height;
} CGSize, _app_NSSize;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

typedef struct CGRect  {
    CGPoint origin;
    CGSize size;
} CGRect, _app_NSRect;

APP_EXTERN_C_BEGIN
static inline _app_NSRect
_app_NSMakeRect(CGFloat x, CGFloat y, CGFloat w, CGFloat h) {
    _app_NSRect result = { {x,y}, {w,h} };
    return result;
}
APP_EXTERN_C_END

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

typedef struct _app_NSRange {
    _app_NSUInteger location;
    _app_NSUInteger length;
} _app_NSRange;

//------------------------------------------------------------------------------

_app_objc_interface(
    _app_NSArray,
    obj(_app_NSUInteger, count),
    obj(_app_objc_id,         firstObject),
    obj(_app_objc_id,         lastObject),
    obj(_app_objc_id,         objectAtIndex,_app_NSUInteger),
    obj(_app_NSUInteger, indexOfObject,_app_objc_id),
)

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

_app_objc_interface(
    _app_NSAutoreleasePool,
    cls(void, showPools),
    obj(void, drain),
)

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

_app_objc_interface(
    _app_NSBundle,
    cls(_app_NSBundle*,  mainBundle),
    obj(_app_NSString*,  bundleIdentifier),
    obj(_app_NSString*,  bundlePath),
)

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

_app_objc_interface(
    _app_NSData,
    obj(const void*, bytes),
)

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

_app_objc_interface(
    _app_NSDictionary,
    cls(_app_NSDictionary*,
        dictionaryWithObjects,_app_objc_id*, 
        forKeys,_app_NSString*,
        count,_app_NSUInteger),
    obj(_app_NSUInteger, count),
    obj(_app_objc_id,valueForKey,_app_NSString*),
)

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

_app_objc_interface(
    _app_NSCoder,
    obj(bool,           containsValueForKey,_app_NSString*),

    obj(_app_objc_id,             decodeObjectForKey,_app_NSString*),
    obj(bool,           decodeBoolForKey,_app_NSString*),
    obj(int,            decodeIntForKey,_app_NSString*),
    obj(int32_t,        decodeInt32ForKey,_app_NSString*),
    obj(int64_t,        decodeInt64ForKey,_app_NSString*),
    obj(_app_NSInteger,      decodeIntegerForKey,_app_NSString*),
    obj(float,          decodeFloatForKey,_app_NSString*),
    obj(double,         decodeDoubleForKey,_app_NSString*),
    obj(const char*,    decodeBytesForKey,_app_NSString*,returnedLength,_app_NSUInteger*),

    obj(void,           encodeObject,_app_objc_id,forKey,_app_NSString*),
    obj(void,           encodeBool,bool,forKey,_app_NSString*),
    obj(void,           encodeInt,int,forKey,_app_NSString*),
    obj(void,           encodeInt32,int32_t,forKey,_app_NSString*),
    obj(void,           encodeInt64,int64_t,forKey,_app_NSString*),
    obj(void,           encodeInteger,_app_NSInteger,forKey,_app_NSString*),
    obj(void,           encodeFloat,float,forKey,_app_NSString*),
    obj(void,           encodeDouble,double,forKey,_app_NSString*),
    obj(void,           encodeBytes,const char*,length,_app_NSUInteger),
)

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

_app_objc_interface(
    _app_NSError,
    obj(_app_NSUInteger, code),
    obj(_app_NSString*,  domain),
    obj(_app_NSString*,  localizedDescription),
    obj(_app_NSString*,  localizedRecoveryOptions),
    obj(_app_NSString*,  localizedRecoverySuggestion),
    obj(_app_NSString*,  localizedFailureReason),
)

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

_app_objc_interface(
    _app_NSMutableArray,
    cls(_app_NSMutableArray*, arrayWithCapacity,_app_NSUInteger),
    obj(void, addObject,_app_objc_id),
    obj(void, insertObject,_app_objc_id,atIndex,_app_NSUInteger),
    obj(void, removeObjectAtIndex,_app_NSUInteger),
    obj(void, removeLastObject),
    obj(void, replaceObjectAtIndex,_app_NSUInteger,withObject,_app_objc_id)
)

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

_app_objc_interface(
    _app_NSNotification,
    obj(_app_NSString*, name),
)

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

_app_objc_interface(
    _app_NSString,
    cls(_app_NSString*,   stringWithUTF8String,const char*),
    obj(const char*, UTF8String),
)

#define _app_objc_str(CSTR) (_app_objc_cls(_app_NSString,stringWithUTF8String,CSTR))

#define _app_objc_cstr(_app_NSSTR) (_app_objc_obj(_app_NSSTR,_app_NSString,UTF8String))

//------------------------------------------------------------------------------
