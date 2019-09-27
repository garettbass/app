#pragma once
#include "app.inl"

//------------------------------------------------------------------------------

APP_EXTERN_C_BEGIN

//------------------------------------------------------------------------------

static bool _app_cursor_is_hidden;

static inline void
_app_cursor_set_hidden(bool hidden) {
    if (_app_cursor_is_hidden != hidden) {
        _app_cursor_is_hidden = hidden;
        if (hidden) {
            _app_objc_cls(_app_NSCursor,hide);
            puts("hide cursor");
        } else {
            _app_objc_cls(_app_NSCursor,unhide);
            puts("show cursor");
        }
    }
}

#pragma GCC poison _app_cursor_is_hidden

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static app_cursor _app_cursor = APP_CURSOR_DEFAULT;

void
app_cursor_set(app_cursor cursor) {
    _app_cursor = cursor;
}

//------------------------------------------------------------------------------

app_point
app_cursor_get_position(app_window* /*optional*/ window) {
    CGPoint point = {0,0};
    HIGetMousePosition(kHICoordSpaceScreenPixel, NULL, &point);
    app_point position = (app_point){ (float)point.x, (float)point.y };
    if (window) {
        app_rect const windowViewport = app_window_get_viewport(window);
        position.x -= windowViewport.x;
        position.y -= windowViewport.y;
    }
    return position;
}

void
app_cursor_set_position(app_point position, app_window* /*optional*/ window) {
    // TODO
    assert(false);
    (void)position;
    (void)window;
}

//------------------------------------------------------------------------------

static _app_NSCursor* const _APP_NSCURSOR_NONE = (_app_NSCursor*)0x1;

static _app_NSCursor* _app_nscursor;

static inline void
_app_nscursor_pop(void) {
    if (_app_nscursor) {
        if (_app_nscursor == _APP_NSCURSOR_NONE) {
            _app_cursor_set_hidden(false);
        } else {
            _app_objc_obj(_app_nscursor,_app_NSCursor,pop);
        }
        _app_nscursor = NULL;
    }
}

static inline void
_app_nscursor_push(_app_NSCursor* cursor) {
    if (_app_nscursor != cursor) {
        _app_nscursor_pop();
        _app_nscursor = cursor;
        if (_app_nscursor == _APP_NSCURSOR_NONE) {
            _app_cursor_set_hidden(true);
        } else {
            _app_objc_obj(_app_nscursor,_app_NSCursor,push);
            _app_cursor_set_hidden(false);
        }
    }
}

static inline _app_NSCursor*
_app_nscursor_get(app_cursor cursor) {
    switch (cursor) {
        case APP_CURSOR_NONE:
            return _APP_NSCURSOR_NONE;
        default:
        case APP_CURSOR_DEFAULT:
        case APP_CURSOR_ARROW:
            return _app_objc_cls(_app_NSCursor,arrowCursor);
        case APP_CURSOR_CROSSHAIR:
            return _app_objc_cls(_app_NSCursor,crosshairCursor);
        case APP_CURSOR_TEXT:
            return _app_objc_cls(_app_NSCursor,IBeamCursor);
        case APP_CURSOR_LINK:
            return _app_objc_cls(_app_NSCursor,pointingHandCursor);
        case APP_CURSOR_DRAG_NS:
            return _app_objc_cls(_app_NSCursor,resizeUpDownCursor);
        case APP_CURSOR_DRAG_EW:
            return _app_objc_cls(_app_NSCursor,resizeLeftRightCursor);
    }
}

//------------------------------------------------------------------------------

static inline void
_app_cursor_update(void) {
    if (app_is_active()) {
        app_window* const activeWindow = app_window_get_active();
        if (activeWindow) {
            app_rect const viewport = app_window_get_viewport(activeWindow);
            if (app_cursor_is_inside(viewport, NULL)) {
                _app_NSCursor* const cursor = _app_nscursor_get(_app_cursor);
                _app_nscursor_push(cursor);
                return;
            }
        }
    }
    _app_nscursor_pop();
}

#pragma GCC poison _app_nscursor

//------------------------------------------------------------------------------

static bool _app_cursor_is_locked;

bool
app_cursor_is_locked(void) {
    return _app_cursor_is_locked;
}

void
app_cursor_set_locked(bool locked) {
    _app_cursor_is_locked = locked;
    CGAssociateMouseAndMouseCursorPosition(locked);
}

//------------------------------------------------------------------------------

APP_EXTERN_C_END

//------------------------------------------------------------------------------
