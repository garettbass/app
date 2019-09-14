#pragma once
#include "app.inl"

//------------------------------------------------------------------------------

APP_EXTERN_C_BEGIN

//------------------------------------------------------------------------------

static inline void
_app_log_event(NSEventType const eventType) {
    switch (eventType) {
        #define _app_log_event(EVENT) case EVENT: puts(#EVENT); break;
        _app_log_event(NSEventTypeLeftMouseDown)
        _app_log_event(NSEventTypeLeftMouseUp)
        _app_log_event(NSEventTypeRightMouseDown)
        _app_log_event(NSEventTypeRightMouseUp)
        _app_log_event(NSEventTypeMouseMoved)
        _app_log_event(NSEventTypeLeftMouseDragged)
        _app_log_event(NSEventTypeRightMouseDragged)
        _app_log_event(NSEventTypeMouseEntered)
        _app_log_event(NSEventTypeMouseExited)
        _app_log_event(NSEventTypeKeyDown)
        _app_log_event(NSEventTypeKeyUp)
        _app_log_event(NSEventTypeFlagsChanged)
        _app_log_event(NSEventTypeAppKitDefined)
        _app_log_event(NSEventTypeSystemDefined)
        _app_log_event(NSEventTypeApplicationDefined)
        _app_log_event(NSEventTypePeriodic)
        _app_log_event(NSEventTypeCursorUpdate)
        _app_log_event(NSEventTypeScrollWheel)
        _app_log_event(NSEventTypeTabletPoint)
        _app_log_event(NSEventTypeTabletProximity)
        _app_log_event(NSEventTypeOtherMouseDown)
        _app_log_event(NSEventTypeOtherMouseUp)
        _app_log_event(NSEventTypeOtherMouseDragged)
        _app_log_event(NSEventTypeGesture)
        _app_log_event(NSEventTypeMagnify)
        _app_log_event(NSEventTypeSwipe)
        _app_log_event(NSEventTypeRotate)
        _app_log_event(NSEventTypeBeginGesture)
        _app_log_event(NSEventTypeEndGesture)
        _app_log_event(NSEventTypeSmartMagnify)
        _app_log_event(NSEventTypeQuickLook)
        _app_log_event(NSEventTypePressure)
        _app_log_event(NSEventTypeDirectTouch)
        #undef _app_log_event
        default: printf("(NSEventType)%u", eventType); break;
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static NSDate* _app_update_timeout = NULL;

app_static_initializer(_app_update_timeout_initializer) {
    assert(_app_update_timeout == NULL);
    _app_update_timeout = _app_objc_cls(NSDate,date);
}

static inline NSDate*
_app_updateGetNextTimeout(const NSTimeInterval interval) {
    assert(_app_update_timeout);
    NSDate* const oldUpdateTimeout = _app_update_timeout;
    _app_update_timeout =
        _app_objc_cls(NSDate,
            dateWithTimeInterval,interval,
            sinceDate,oldUpdateTimeout);
    _app_objc_obj(oldUpdateTimeout,NSDate,release);
    return _app_objc_obj(_app_update_timeout,NSDate,retain);
}

#pragma GCC poison _app_update_timeout

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static NSTimeInterval _app_update_interval = 0;

app_static_initializer(_app_update_interval_initializer) {
    assert(_app_update_interval == 0);
    CGDisplayMode* displayMode = CGDisplayCopyDisplayMode(CGMainDisplayID());
    double refreshRate = CGDisplayModeGetRefreshRate(displayMode);
    if (refreshRate < 30.0)
        refreshRate = 30.0;
    _app_update_interval = 1.0 / refreshRate;
    CGDisplayModeRelease(displayMode);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

_app_objc_import(CoreFoundation, pointer(NSString*,NSDefaultRunLoopMode))

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static inline bool
_app_update_process_event(NSDate* const timeout) {
    NSEvent* const event =
        _app_objc_obj(NSApp,NSApplication,
            nextEventMatchingMask,NSEventMaskAny,
            untilDate,timeout,
            inMode,NSDefaultRunLoopMode,
            dequeue,true);
    if (event == NULL)
        return false;

    _app_objc_obj(NSApp,NSApplication,sendEvent,event);
    _app_objc_obj(NSApp,NSApplication,updateWindows);

    const NSEventType eventType = _app_objc_obj(event,NSEvent,type);
    // _app_log_event(eventType);

    switch (eventType) {

        case NSEventTypeKeyDown: {
            NSString* const characters = _app_objc_obj(event,NSEvent,characters);
            if (characters) {
                const char* const text = _app_objc_obj(characters,NSString,UTF8String);
                _app_text_input_append_string(text);
            }
        } break;

        case NSEventTypeKeyUp:
        case NSEventTypeFlagsChanged:
            break;

        case NSEventTypeLeftMouseUp:
        case NSEventTypeLeftMouseDown:
        case NSEventTypeRightMouseUp:
        case NSEventTypeRightMouseDown:
        case NSEventTypeOtherMouseUp:
        case NSEventTypeOtherMouseDown: {
            const NSInteger buttonNumber = _app_objc_obj(event,NSEvent,buttonNumber);
            const app_key appKey = (app_key)(APP_KEY_MOUSE_1 + buttonNumber);
            if (appKey >= APP_KEY_MOUSE_1 and appKey <= APP_KEY_MOUSE_10) {
                const bool isDown = eventType & 0x1;
                _app_key_set(appKey, isDown);
            }
        } break;

        case NSEventTypeMouseMoved:
        case NSEventTypeLeftMouseDragged:
        case NSEventTypeRightMouseDragged:
        case NSEventTypeOtherMouseDragged: {
            const CGFloat dx = _app_objc_obj(event,NSEvent,deltaX);
            const CGFloat dy = _app_objc_obj(event,NSEvent,deltaY);
            _app_mouse_delta.x += (float)dx;
            _app_mouse_delta.y += (float)dy;
        } break;

        case NSEventTypeScrollWheel: {
            const CGFloat dx = _app_objc_obj(event,NSEvent,scrollingDeltaX);
            const CGFloat dy = _app_objc_obj(event,NSEvent,scrollingDeltaY);
            _app_mouse_scroll.x += (float)dx;
            _app_mouse_scroll.y += (float)dy;
        } break;

        case NSEventTypeMouseEntered:
        case NSEventTypeMouseExited:
        case NSEventTypeAppKitDefined:
        case NSEventTypeApplicationDefined:
        case NSEventTypeBeginGesture:
        case NSEventTypeEndGesture:
        case NSEventTypeCursorUpdate:
        case NSEventTypeDirectTouch:
        case NSEventTypeGesture:
        case NSEventTypeMagnify:
        case NSEventTypePeriodic:
        case NSEventTypePressure:
        case NSEventTypeQuickLook:
        case NSEventTypeRotate:
        case NSEventTypeSmartMagnify:
        case NSEventTypeSwipe:
        case NSEventTypeSystemDefined:
        case NSEventTypeTabletPoint:
        case NSEventTypeTabletProximity:
            break;

    }
    return true;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static bool _app_quit_requested = false;

bool
app_update(void) {
    _app_text_input_reset();
    _app_mouse_delta_reset();
    _app_mouse_scroll_reset();
    _app_autoreleasepool_popPush();
    NSDate* const timeout = _app_updateGetNextTimeout(_app_update_interval);
    while (_app_update_process_event(timeout)) {
        _app_autoreleasepool_popPush();
    }
    _app_keys_update();
    _app_cursor_update();
    return not _app_quit_requested;
}

#pragma GCC poison _app_update_interval
#pragma GCC poison _app_updateGetNextTimeout
#pragma GCC poison _app_update_getNextEvent

//------------------------------------------------------------------------------

void app_quit(void) {
    puts(__func__);
    _app_quit_requested = true;

    // NSArray* windows = _app_objc_autorelease(_app_objc_obj(NSApp,NSApplication,windows));
    // const int n = _app_objc_obj(windows,NSArray,count);
    // for (int i = 0; i < n; ++i) {
    //     NSWindow* window = _app_objc_obj(windows,NSArray,objectAtIndex,i);
    //     _app_objc_obj(window,NSWindow,close);
    // }
}

#pragma GCC poison _app_quit_requested

//------------------------------------------------------------------------------

APP_EXTERN_C_END

//------------------------------------------------------------------------------
