#pragma once

//------------------------------------------------------------------------------

#ifdef __cplusplus

    class _app_objc_id {
        void* _p = nullptr;
    public:
        _app_objc_id() = default;
        _app_objc_id(void* p) : _p(p) {}
        operator void*() const { return _p; }
        template<typename T> operator T*() const { return (T*)_p; }
    };

    template<typename T>
    bool operator==(const _app_objc_id& a, const T* const b) {
        return (void*)a == (void*)b;
    }
    bool operator==(const _app_objc_id& a, const void* const b) {
        return (void*)a == (void*)b;
    }
    template<typename T>
    bool operator==(const T* const a, const _app_objc_id& b) {
        return (void*)a == (void*)b;
    }
    bool operator==(const void* const a, const _app_objc_id& b) {
        return (void*)a == (void*)b;
    }

    template<typename T>
    bool operator!=(const _app_objc_id& a, const T* const b) {
        return (void*)a != (void*)b;
    }
    bool operator!=(const _app_objc_id& a, const void* const b) {
        return (void*)a != (void*)b;
    }
    template<typename T>
    bool operator!=(const T* const a, const _app_objc_id& b) {
        return (void*)a != (void*)b;
    }
    bool operator!=(const void* const a, const _app_objc_id& b) {
        return (void*)a != (void*)b;
    }

#else // C ---------------------------------------------------------------------

    typedef void* _app_objc_id;

#endif // __cplusplus / C

//------------------------------------------------------------------------------
