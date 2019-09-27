#pragma once
#include <iso646.h>
#include "../app.h"
#include "cursor.inl"
#include "dll.inl"
#include "key.inl"
#include "mouse.inl"
#include "platform.h"

//------------------------------------------------------------------------------

#if APP_OS_IOS
#include "apple/ios/app.inl"
#elif APP_OS_MACOS
#include "apple/macos/app.inl"
#elif APP_OS_WINDOWS
#include "windows/app.inl"
#endif

//------------------------------------------------------------------------------
