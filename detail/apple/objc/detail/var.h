#pragma once
#include "message.h"

//------------------------------------------------------------------------------

#define __app_objc_var(SELF, CLASS, NAME)\
        ___app_objc_var(SELF, __app_objc_var_thunk_t(CLASS, NAME), __app_objc_var_offset(CLASS, NAME))
#define ___app_objc_var(SELF, THUNK_T, VAR_OFFSET)\
        (((THUNK_T)__app_objc_var_thunk)(SELF, VAR_OFFSET)[0])

        APP_EXTERN_C_BEGIN
        static inline void*
        __app_objc_var_thunk(void* const self, const size_t var_offset) {
            return ((char*)self) + var_offset;
        }
        APP_EXTERN_C_END

//------------------------------------------------------------------------------

#define __app_objc_var_thunk_t(CLASS, NAME)\
        __app_objc_var_thunk_t_##CLASS##_##NAME

#define __app_objc_var_offset(CLASS, NAME)\
        __app_objc_var_offset_##CLASS##_##NAME

//------------------------------------------------------------------------------

#define __app_objc_var_declaration(CLASS, TYPE, NAME)\
        typedef TYPE* (*__app_objc_var_thunk_t(CLASS, NAME))(CLASS* const, const size_t);\
        static size_t __app_objc_var_offset(CLASS, NAME) = 0;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#define __app_objc_var_initializer(CLASS, TYPE, NAME)\
        ___app_objc_var_initializer(\
            &__app_objc_var_offset(CLASS, NAME),\
            CLASS##_class,\
            #NAME,\
            sizeof(TYPE),\
            alignof(TYPE));

        APP_EXTERN_C_BEGIN
        static inline void
        ___app_objc_var_initializer(
            size_t* const pvar_offset,
            _app_objc_class* const   cls,
            const char    name[],
            const size_t  size,
            const size_t  align
        ) {
            assert(*pvar_offset == 0);
            const bool added = class_addIvar(cls, name, size, align, "?");
            assert(added);(void)added;
            *pvar_offset = ivar_getOffset(class_getInstanceVariable(cls, name));
        }
        APP_EXTERN_C_END

//------------------------------------------------------------------------------
