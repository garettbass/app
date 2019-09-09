#pragma once

//------------------------------------------------------------------------------

#define __app_objc_framework(FRAMEWORK)\
        static void* FRAMEWORK = NULL;\
        APP_EXTERN_C_BEGIN\
        __attribute__((constructor)) static inline void\
        __app_objc_framework_initializer_##FRAMEWORK(void) {\
            const char path[] = #FRAMEWORK".framework/"#FRAMEWORK;\
            ___app_objc_framework_initializer(&FRAMEWORK, path);\
        }\
        APP_EXTERN_C_END

        APP_EXTERN_C_BEGIN
        static inline void
        ___app_objc_framework_initializer(void** pframework, const char path[]) {
            assert(*pframework == NULL);
            enum { RTLD_LAZY_LOCAL = 0x1 | 0x4 };
            extern void* dlopen(const char*,int);
            *pframework = dlopen(path, RTLD_LAZY_LOCAL);
            assert(*pframework);
        }
        APP_EXTERN_C_END

//------------------------------------------------------------------------------
