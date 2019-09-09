#pragma once
#include "app.h"

//------------------------------------------------------------------------------

#include "inline/common/app.inl"
#if APP_OS_IOS
#include "inline/apple/ios/app.inl"
#elif APP_OS_MACOS
#include "inline/apple/macos/app.inl"
#elif APP_OS_WINDOWS
#include "inline/microsoft/windows/app.inl"
#endif

//------------------------------------------------------------------------------

APP_DEBUG_ONLY(
    APP_EXTERN_C_BEGIN
    app_static_initializer(app_version) {
        extern int puts(const char*);
        puts(
            APP_VERSION" "
            APP_OS_NAME" "
            APP_CPU_NAME" "
            APP_ENDIAN_NAME" "
            APP_COMPILER_NAME
        );
    }
    APP_EXTERN_C_END
)

//------------------------------------------------------------------------------

#define main app_main

//------------------------------------------------------------------------------
