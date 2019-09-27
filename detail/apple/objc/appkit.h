#pragma once
#include "coregraphics.h"

//------------------------------------------------------------------------------

_app_objc_framework(_app_AppKit, "AppKit.framework/AppKit")

_app_objc_class(_app_NSApplication);
_app_objc_class(_app_NSCursor);
_app_objc_class(_app_NSDate);
_app_objc_class(_app_NSEvent);
_app_objc_class(_app_NSGraphicsContext);
_app_objc_class(_app_NSMenu);
_app_objc_class(_app_NSMenuItem);
_app_objc_class(_app_NSNotificationCenter);
_app_objc_class(_app_NSPersistentUIManager);
_app_objc_class(_app_NSScreen);
_app_objc_class(_app_NSView);
_app_objc_class(_app_NSWindow);

//------------------------------------------------------------------------------

typedef enum _app_NSApplicationTerminateReply {
    _app_NSApplicationTerminateCancel = 0,
    _app_NSApplicationTerminateNow    = 1,
    _app_NSApplicationTerminateLater  = 2,
} _app_NSApplicationTerminateReply;

//------------------------------------------------------------------------------

typedef enum _app_NSEventType {
    _app_NSEventTypeLeftMouseDown      = 1,
    _app_NSEventTypeLeftMouseUp        = 2,
    _app_NSEventTypeRightMouseDown     = 3,
    _app_NSEventTypeRightMouseUp       = 4,
    _app_NSEventTypeMouseMoved         = 5,
    _app_NSEventTypeLeftMouseDragged   = 6,
    _app_NSEventTypeRightMouseDragged  = 7,
    _app_NSEventTypeMouseEntered       = 8,
    _app_NSEventTypeMouseExited        = 9,
    _app_NSEventTypeKeyDown            = 10,
    _app_NSEventTypeKeyUp              = 11,
    _app_NSEventTypeFlagsChanged       = 12,
    _app_NSEventTypeAppKitDefined      = 13,
    _app_NSEventTypeSystemDefined      = 14,
    _app_NSEventTypeApplicationDefined = 15,
    _app_NSEventTypePeriodic           = 16,
    _app_NSEventTypeCursorUpdate       = 17,
    _app_NSEventTypeScrollWheel        = 22,
    _app_NSEventTypeTabletPoint        = 23,
    _app_NSEventTypeTabletProximity    = 24,
    _app_NSEventTypeOtherMouseDown     = 25,
    _app_NSEventTypeOtherMouseUp       = 26,
    _app_NSEventTypeOtherMouseDragged  = 27,
    _app_NSEventTypeGesture            = 29,
    _app_NSEventTypeMagnify            = 30,
    _app_NSEventTypeSwipe              = 31,
    _app_NSEventTypeRotate             = 18,
    _app_NSEventTypeBeginGesture       = 19,
    _app_NSEventTypeEndGesture         = 20,
    _app_NSEventTypeSmartMagnify       = 32,
    _app_NSEventTypeQuickLook          = 33,
    _app_NSEventTypePressure           = 34,
    _app_NSEventTypeDirectTouch        = 37,
} _app_NSEventType;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

typedef enum _app_NSEventModifierFlags {
    _app_NSEventModifierFlagCapsLock   = 1 << 16,
    _app_NSEventModifierFlagShift      = 1 << 17,
    _app_NSEventModifierFlagControl    = 1 << 18,
    _app_NSEventModifierFlagOption     = 1 << 19,
    _app_NSEventModifierFlagCommand    = 1 << 20,
    _app_NSEventModifierFlagNumericPad = 1 << 21,
    _app_NSEventModifierFlagHelp       = 1 << 22,
    _app_NSEventModifierFlagFunction   = 1 << 23,
} _app_NSEventModifierFlags;

// Used to retrieve only the device-independent modifier flags,
// allowing applications to mask off the device-dependent modifier flags,
// including event coalescing information.
#define _app_NSEventModifierFlagDeviceIndependentFlagsMask (0xffff0000UL)

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

typedef enum _app_NSWindowStyleMask {
    _app_NSWindowStyleMaskBorderless             = 0,
    _app_NSWindowStyleMaskTitled                 = 1 << 0,
    _app_NSWindowStyleMaskClosable               = 1 << 1,
    _app_NSWindowStyleMaskMiniaturizable         = 1 << 2,
    _app_NSWindowStyleMaskResizable              = 1 << 3,
    _app_NSWindowStyleMaskUtilityWindow          = 1 << 4,
    _app_NSWindowStyleMaskDocModalWindow         = 1 << 6,
    _app_NSWindowStyleMaskNonactivatingPanel     = 1 << 7,
    _app_NSWindowStyleMaskUnifiedTitleAndToolbar = 1 << 12,
    _app_NSWindowStyleMaskFullScreen             = 1 << 14,
    _app_NSWindowStyleMaskFullSizeContentView    = 1 << 15,
    _app_NSWindowStyleMaskHUDWindow              = 1 << 13,
} _app_NSWindowStyleMask;

//------------------------------------------------------------------------------

_app_objc_interface(
    _app_NSApplication,
    cls(_app_NSApplication*, sharedApplication),
    obj(void,                activateIgnoringOtherApps,bool),
    obj(_app_objc_id,        delegate),
    obj(void,                finishLaunching),
    obj(bool,                isActive),
    obj(_app_NSWindow*,      keyWindow),
    obj(_app_NSMenu*,        mainMenu),
    obj(_app_NSEvent*,       nextEventMatchingMask,unsigned,
                             untilDate,_app_NSDate*,
                             inMode,_app_NSString*,
                             dequeue,bool),
    obj(void,                sendEvent,_app_NSEvent*),
    obj(void,                setActivationPolicy,size_t),
    obj(void,                setDelegate,_app_objc_id),
    obj(void,                setMainMenu,_app_NSMenu*),
    obj(void,                terminate,_app_objc_id),
    obj(void,                updateWindows),
    obj(_app_NSArray*,       windows),
)

#define _app_NSApp (_app_objc_cls(_app_NSApplication, sharedApplication))

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

_app_objc_interface(
    _app_NSCursor,
    cls(_app_NSCursor*, currentCursor),
    cls(_app_NSCursor*, currentSystemCursor),
    cls(_app_NSCursor*, arrowCursor),
    cls(_app_NSCursor*, IBeamCursor),
    cls(_app_NSCursor*, crosshairCursor),
    cls(_app_NSCursor*, closedHandCursor),
    cls(_app_NSCursor*, openHandCursor),
    cls(_app_NSCursor*, pointingHandCursor),
    cls(_app_NSCursor*, resizeLeftCursor),
    cls(_app_NSCursor*, resizeRightCursor),
    cls(_app_NSCursor*, resizeLeftRightCursor),
    cls(_app_NSCursor*, resizeUpCursor),
    cls(_app_NSCursor*, resizeDownCursor),
    cls(_app_NSCursor*, resizeUpDownCursor),
    cls(_app_NSCursor*, disappearingItemCursor),
    cls(_app_NSCursor*, IBeamCursorForVerticalLayout),
    cls(_app_NSCursor*, operationNotAllowedCursor),
    cls(_app_NSCursor*, dragLinkCursor),
    cls(_app_NSCursor*, dragCopyCursor),
    cls(_app_NSCursor*, contextualMenuCursor),
    cls(_app_NSCursor*, hide),
    cls(_app_NSCursor*, unhide),
    obj(_app_NSCursor*, initWithCGImage,_app_objc_id,size,_app_NSSize),
    obj(void,      push),
    obj(void,      pop),
    obj(void,      set),
)

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

_app_objc_interface(
    _app_NSDate,
    cls(_app_NSDate*, date),
    cls(_app_NSDate*, dateWithTimeIntervalSinceNow,_app_NSTimeInterval),
    cls(_app_NSDate*, dateWithTimeInterval,_app_NSTimeInterval,sinceDate,_app_NSDate*),
    cls(_app_NSDate*, distantPast),
    cls(_app_NSDate*, distantFuture),
    obj(_app_NSDate*, initWithTimeInterval,_app_NSTimeInterval,sinceDate,_app_NSDate*),
)

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

_app_objc_interface(
    _app_NSEvent,
    cls(_app_NSTimeInterval,         doubleClickInterval),
    cls(_app_NSTimeInterval,         keyRepeatDelay),
    cls(_app_NSTimeInterval,         keyRepeatInterval),
    cls(_app_NSUInteger,             pressedMouseButtons),
    cls(_app_NSPoint,                mouseLocation),
    obj(_app_NSInteger,              buttonNumber),
    obj(_app_NSInteger,              clickCount),
    obj(_app_NSPoint,                locationInWindow),
    obj(CGFloat,                deltaX),
    obj(CGFloat,                deltaY),
    obj(CGFloat,                deltaZ),
    obj(_app_NSInteger,              absoluteX),
    obj(_app_NSInteger,              absoluteY),
    obj(_app_NSInteger,              absoluteZ),
    obj(CGFloat,                scrollingDeltaX),
    obj(CGFloat,                scrollingDeltaY),
    obj(_app_NSEventModifierFlags,   modifierFlags),
    obj(_app_NSTimeInterval,         timestamp),
    obj(_app_NSEventType,       type),
    obj(_app_NSWindow*,              window),
    obj(_app_NSString*,              characters),
    obj(_app_NSString*,              charactersIgnoringModifiers),
    obj(bool,                   isARepeat),
    obj(unsigned short,         keyCode),
)

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

_app_objc_interface(
    _app_NSGraphicsContext,
    cls(_app_NSGraphicsContext*,graphicsContextWithWindow,_app_NSWindow*),
    cls(_app_NSGraphicsContext*, currentContext),
    cls(void,setCurrentContext,_app_NSGraphicsContext*),
    obj(CGContext*,CGContext),
)

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

_app_objc_interface(
    _app_NSMenu,
    obj(_app_NSMenu*,   initWithTitle,_app_NSString*),
    obj(void,      addItem,_app_NSMenuItem*),
    obj(_app_NSString*, title),
)

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

_app_objc_interface(
    _app_NSMenuItem,
    obj(_app_NSMenuItem*,    initWithTitle,_app_NSString*,
                        action,_app_objc_selector*,
                        keyEquivalent,_app_NSString*),
    obj(void,           setKeyEquivalentModifierMask,_app_NSEventModifierFlags),
    obj(void,           setSubmenu,_app_NSMenu*),
    obj(void,           setTarget,_app_objc_id),
    obj(_app_NSString*,      title),
)

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

_app_objc_interface(
    _app_NSNotificationCenter,
    cls(_app_NSNotificationCenter*,defaultCenter),
    obj(void,postNotificationName,_app_NSString*,object,_app_objc_id),
)

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

_app_objc_interface(
    _app_NSPersistentUIManager,
    cls(_app_NSPersistentUIManager*, sharedManager),
    obj(bool,                   shouldRestoreStateOnLaunch),
    obj(bool,                   promptToIgnorePersistentState),
    obj(void,                   ignoreAnyPreexistingPersistentState),
    obj(void,                   disableRestorableStateWriting),
    obj(void,                   invalidateStateDirectoryAtLaunch),
)

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

_app_objc_interface(
    _app_NSScreen,
    cls(_app_NSScreen*,   mainScreen),
    cls(_app_NSArray*,    screens),
    obj(_app_NSRect,      frame),
)

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

_app_objc_interface(
    _app_NSView,
    obj(_app_NSView*,    superview),
    obj(_app_NSArray*,   subviews),
    obj(_app_NSRect,     bounds),
    obj(void,       display),
    obj(_app_NSRect,     frame),
    obj(_app_NSWindow*,  window),
    obj(void,       drawRect,_app_NSRect),
    obj(void,       removeFromSuperview),
)

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

_app_objc_interface(
    _app_NSWindow,
    obj(void,               center),
    obj(void,               close),
    obj(_app_NSRect,             contentRectForFrameRect,_app_NSRect),
    obj(_app_NSView*,            contentView),
    obj(void,               deminiaturize,_app_objc_id),
    obj(void,               disableSnapshotRestoration),
    obj(_app_NSRect,             frame),
    obj(_app_NSRect,             frameRectForContentRect,_app_NSRect),
    obj(_app_NSGraphicsContext*, graphicsContext),
    obj(bool,               isDocumentEdited),
    obj(bool,               isKeyWindow),
    obj(bool,               isMainWindow),
    obj(bool,               isMiniaturized),
    obj(bool,               isRestorable),
    obj(bool,               isVisible),
    obj(bool,               isZoomed),
    obj(void,               keyDown,_app_NSEvent*),
    obj(void,               makeKeyAndOrderFront,_app_objc_id),
    obj(void,               makeMainWindow),
    obj(void,               orderFront,_app_objc_id),
    obj(void,               miniaturize,_app_objc_id),
    obj(void,               setAcceptsMouseMovedEvents,bool),
    obj(void,               setCollectionBehavior,size_t),
    obj(void,               setContentView,_app_NSView*),
    obj(void,               setDelegate,_app_objc_id),
    obj(void,               setDocumentEdited,bool),
    obj(void,               setFrame,_app_NSRect, display,bool),
    obj(void,               setRestorable,bool),
    obj(void,               setRestorationClass,_app_objc_class*),
    obj(void,               setIsVisible,bool),
    obj(void,               setReleasedWhenClosed,bool),
    obj(void,               setStyleMask,_app_NSWindowStyleMask),
    obj(void,               setTitle,_app_NSString*),
    obj(void,               setTitlebarAppearsTransparent,bool),
    obj(_app_NSWindowStyleMask,  styleMask),
    obj(bool,               titlebarAppearsTransparent),
    obj(void,               zoom,_app_objc_id),
)

//------------------------------------------------------------------------------
