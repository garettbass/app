#pragma once
#include "detail/app.inl"

//------------------------------------------------------------------------------

#define APP_BUILD ""\
        APP_VERSION " "\
        APP_COMPILER_NAME " "\
        APP_OS_NAME " "\
        APP_CPU_NAME " (" APP_ENDIAN_NAME ") "\
        __DATE__ " " __TIME__ ""

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
