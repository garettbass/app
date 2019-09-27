#pragma once
#include "app.inl"

//------------------------------------------------------------------------------

APP_EXTERN_C_BEGIN

//------------------------------------------------------------------------------

static inline void
_app_log_event(_app_NSEventType const eventType) {
    switch (eventType) {
        #define _app_log_event(EVENT) case EVENT: puts(#EVENT); break;
        _app_log_event(_app_NSEventTypeLeftMouseDown)
        _app_log_event(_app_NSEventTypeLeftMouseUp)
        _app_log_event(_app_NSEventTypeRightMouseDown)
        _app_log_event(_app_NSEventTypeRightMouseUp)
        _app_log_event(_app_NSEventTypeMouseMoved)
        _app_log_event(_app_NSEventTypeLeftMouseDragged)
        _app_log_event(_app_NSEventTypeRightMouseDragged)
        _app_log_event(_app_NSEventTypeMouseEntered)
        _app_log_event(_app_NSEventTypeMouseExited)
        _app_log_event(_app_NSEventTypeKeyDown)
        _app_log_event(_app_NSEventTypeKeyUp)
        _app_log_event(_app_NSEventTypeFlagsChanged)
        _app_log_event(_app_NSEventTypeAppKitDefined)
        _app_log_event(_app_NSEventTypeSystemDefined)
        _app_log_event(_app_NSEventTypeApplicationDefined)
        _app_log_event(_app_NSEventTypePeriodic)
        _app_log_event(_app_NSEventTypeCursorUpdate)
        _app_log_event(_app_NSEventTypeScrollWheel)
        _app_log_event(_app_NSEventTypeTabletPoint)
        _app_log_event(_app_NSEventTypeTabletProximity)
        _app_log_event(_app_NSEventTypeOtherMouseDown)
        _app_log_event(_app_NSEventTypeOtherMouseUp)
        _app_log_event(_app_NSEventTypeOtherMouseDragged)
        _app_log_event(_app_NSEventTypeGesture)
        _app_log_event(_app_NSEventTypeMagnify)
        _app_log_event(_app_NSEventTypeSwipe)
        _app_log_event(_app_NSEventTypeRotate)
        _app_log_event(_app_NSEventTypeBeginGesture)
        _app_log_event(_app_NSEventTypeEndGesture)
        _app_log_event(_app_NSEventTypeSmartMagnify)
        _app_log_event(_app_NSEventTypeQuickLook)
        _app_log_event(_app_NSEventTypePressure)
        _app_log_event(_app_NSEventTypeDirectTouch)
        #undef _app_log_event
        default: printf("(_app_NSEventType)%u", eventType); break;
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static _app_NSDate* _app_update_timeout = NULL;

app_static_initializer(_app_update_timeout_initializer) {
    assert(_app_update_timeout == NULL);
    _app_update_timeout = _app_objc_cls(_app_NSDate,date);
}

static inline _app_NSDate*
_app_updateGetNextTimeout(const _app_NSTimeInterval interval) {
    assert(_app_update_timeout);
    _app_NSDate* const oldUpdateTimeout = _app_update_timeout;
    _app_update_timeout =
        _app_objc_cls(_app_NSDate,
            dateWithTimeInterval,interval,
            sinceDate,oldUpdateTimeout);
    _app_objc_obj(oldUpdateTimeout,_app_NSDate,release);
    return _app_objc_obj(_app_update_timeout,_app_NSDate,retain);
}

#pragma GCC poison _app_update_timeout

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static _app_NSTimeInterval _app_update_interval = 0;

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

_app_objc_import(CoreFoundation, pointer(_app_NSString*,_app_NSDefaultRunLoopMode))

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static inline bool
_app_update_process_event(_app_NSDate* const timeout) {
    enum { _app_NSEventMaskAny = ~0u };
    _app_NSEvent* const event =
        _app_objc_obj(_app_NSApp,_app_NSApplication,
            nextEventMatchingMask,_app_NSEventMaskAny,
            untilDate,timeout,
            inMode,_app_NSDefaultRunLoopMode,
            dequeue,true);
    if (event == NULL)
        return false;

    _app_objc_obj(_app_NSApp,_app_NSApplication,sendEvent,event);
    _app_objc_obj(_app_NSApp,_app_NSApplication,updateWindows);

    const _app_NSEventType eventType = _app_objc_obj(event,_app_NSEvent,type);
    // _app_log_event(eventType);

    switch (eventType) {

        case _app_NSEventTypeKeyDown: {
            _app_NSString* const characters = _app_objc_obj(event,_app_NSEvent,characters);
            if (characters) {
                const char* const text = _app_objc_obj(characters,_app_NSString,UTF8String);
                _app_text_input_append_string(text);
            }
        } break;

        case _app_NSEventTypeKeyUp:
        case _app_NSEventTypeFlagsChanged:
            break;

        case _app_NSEventTypeLeftMouseUp:
        case _app_NSEventTypeLeftMouseDown:
        case _app_NSEventTypeRightMouseUp:
        case _app_NSEventTypeRightMouseDown:
        case _app_NSEventTypeOtherMouseUp:
        case _app_NSEventTypeOtherMouseDown: {
            const _app_NSInteger buttonNumber = _app_objc_obj(event,_app_NSEvent,buttonNumber);
            const app_key appKey = (app_key)(APP_KEY_MOUSE_1 + buttonNumber);
            if (appKey >= APP_KEY_MOUSE_1 and appKey <= APP_KEY_MOUSE_10) {
                const bool isDown = eventType & 0x1;
                _app_key_set(appKey, isDown);
            }
        } break;

        case _app_NSEventTypeMouseMoved:
        case _app_NSEventTypeLeftMouseDragged:
        case _app_NSEventTypeRightMouseDragged:
        case _app_NSEventTypeOtherMouseDragged: {
            const CGFloat dx = _app_objc_obj(event,_app_NSEvent,deltaX);
            const CGFloat dy = _app_objc_obj(event,_app_NSEvent,deltaY);
            _app_mouse_delta.x += (float)dx;
            _app_mouse_delta.y += (float)dy;
        } break;

        case _app_NSEventTypeScrollWheel: {
            const CGFloat dx = _app_objc_obj(event,_app_NSEvent,scrollingDeltaX);
            const CGFloat dy = _app_objc_obj(event,_app_NSEvent,scrollingDeltaY);
            _app_mouse_scroll.x += (float)dx;
            _app_mouse_scroll.y += (float)dy;
        } break;

        case _app_NSEventTypeMouseEntered:
        case _app_NSEventTypeMouseExited:
        case _app_NSEventTypeAppKitDefined:
        case _app_NSEventTypeApplicationDefined:
        case _app_NSEventTypeBeginGesture:
        case _app_NSEventTypeEndGesture:
        case _app_NSEventTypeCursorUpdate:
        case _app_NSEventTypeDirectTouch:
        case _app_NSEventTypeGesture:
        case _app_NSEventTypeMagnify:
        case _app_NSEventTypePeriodic:
        case _app_NSEventTypePressure:
        case _app_NSEventTypeQuickLook:
        case _app_NSEventTypeRotate:
        case _app_NSEventTypeSmartMagnify:
        case _app_NSEventTypeSwipe:
        case _app_NSEventTypeSystemDefined:
        case _app_NSEventTypeTabletPoint:
        case _app_NSEventTypeTabletProximity:
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
    _app_NSDate* const timeout = _app_updateGetNextTimeout(_app_update_interval);
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

    // _app_NSArray* windows = _app_objc_autorelease(_app_objc_obj(_app_NSApp,_app_NSApplication,windows));
    // const int n = _app_objc_obj(windows,_app_NSArray,count);
    // for (int i = 0; i < n; ++i) {
    //     _app_NSWindow* window = _app_objc_obj(windows,_app_NSArray,objectAtIndex,i);
    //     _app_objc_obj(window,_app_NSWindow,close);
    // }
}

#pragma GCC poison _app_quit_requested

//------------------------------------------------------------------------------

APP_EXTERN_C_END

//------------------------------------------------------------------------------
