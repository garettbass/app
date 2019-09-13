#pragma once
#include "platform/platform.h"

//------------------------------------------------------------------------------

#define APP_BUILD ""\
        APP_VERSION " "\
        APP_COMPILER_NAME " "\
        APP_OS_NAME " "\
        APP_CPU_NAME " (" APP_ENDIAN_NAME ") "\
        __DATE__ " " __TIME__ ""

//------------------------------------------------------------------------------

#include "platform/common/app.inl"
#if APP_OS_IOS
#include "platform/apple/ios/app.inl"
#elif APP_OS_MACOS
#include "platform/apple/macos/app.inl"
#elif APP_OS_WINDOWS
#include "platform/windows/app.inl"
#endif

//------------------------------------------------------------------------------

#if APP_DEBUG
    APP_EXTERN_C_BEGIN
    app_static_initializer(app_build) {
        extern int puts(const char*);
        puts(APP_BUILD);
    }
    APP_EXTERN_C_END
#endif

//------------------------------------------------------------------------------

#define main app_main

//------------------------------------------------------------------------------
