#pragma once
#include "objc.h"

//------------------------------------------------------------------------------

typedef long CFIndex;

typedef struct CFRange { CFIndex location, length; } CFRange;

//------------------------------------------------------------------------------

typedef struct CFAllocator        CFAllocator;
typedef struct NSArray            CFArray;
typedef struct NSDictionary       CFDictionary;
typedef struct NSString           CFString;
typedef struct NSAttributedString CFAttributedString;

typedef enum CFStringBuiltInEncodings {
   kCFStringEncodingMacRoman      = 0,
   kCFStringEncodingWindowsLatin1 = 0x0500,
   kCFStringEncodingISOLatin1     = 0x0201,
   kCFStringEncodingNextStepLatin = 0x0B01,
   kCFStringEncodingASCII         = 0x0600,
   kCFStringEncodingUnicode       = 0x0100,
   kCFStringEncodingUTF8          = 0x08000100,
   kCFStringEncodingNonLossyASCII = 0x0BFF
} CFStringBuiltInEncodings, CFStringEncoding;

static CFAllocator* const kCFAllocatorDefault = NULL;

//------------------------------------------------------------------------------

_app_objc_import(CoreFoundation,

    pointer(CFAllocator*, kCFAllocatorNull),

    // CFArray \\...............................................................

    function(CFIndex,CFArrayGetCount,(CFArray*)),

    function(_app_objc_id,CFArrayGetValueAtIndex,(CFArray*, CFIndex)),

    // CFAttributedString \\....................................................


    function(
        CFAttributedString*,
        CFAttributedStringCreate,(
            CFAllocator*,
            CFString*,
            CFDictionary* attributes)),

    function(
        CFAttributedString*,
        CFAttributedStringCreateMutable,(
            CFAllocator*,
            CFIndex maxLength)),

    function(
        void,
        CFAttributedStringReplaceString,(
            CFAttributedString*,
            CFRange,
            CFString*)),

    function(
        void,
        CFAttributedStringSetAttribute,(
            CFAttributedString*,
            CFRange,
            CFString* attrName,
            void*     value)),

    // CFString \\..............................................................

    function(
        CFString*,
        CFStringCreateWithBytesNoCopy,(
            CFAllocator*,
            const void*      bytes,
            CFIndex          numBytes,
            CFStringEncoding encoding,
            bool             isExternalRepresentation /* hasBOM */,
            CFAllocator*     contentsDeallocator)),

) // _app_objc_import(CoreFoundation, ...)

//------------------------------------------------------------------------------

#define _app_objc_array_for(ITEM_TYPE, ITEM, ARRAY)\
        for(CFArray* _app_objc_array_for_array = (ARRAY);\
            _app_objc_array_for_array;\
            _app_objc_array_for_array = NULL)\
        for(int _app_objc_array_for_i = 0;\
            _app_objc_array_for_i == 0;\
            _app_objc_array_for_i += 1)\
        for(ITEM_TYPE ITEM = NULL;\
            _app_objc_array_for_i < CFArrayGetCount(_app_objc_array_for_array) &&\
            (ITEM=CFArrayGetValueAtIndex(_app_objc_array_for_array,_app_objc_array_for_i),1);\
            _app_objc_array_for_i += 1)
