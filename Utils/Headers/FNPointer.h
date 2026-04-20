#pragma once

template <typename T>
class Pointer;

template <typename R, typename... Args>
class Pointer<R(Args...)>
{
public:
    Pointer() = default; 
    explicit Pointer(uintptr_t offset) {
        m_Function = reinterpret_cast<R(*)(Args...)>(offset);
    }

    explicit Pointer(void* offset) {
        m_Function = reinterpret_cast<R(*)(Args...)>(offset);
    }

    // Assignment operator accepting an integer offset
    inline Pointer& operator=(uintptr_t offset) {
        m_Function = reinterpret_cast<R(*)(Args...)>(offset);
        return *this;
    }

    // Assignment operator accepting a function pointer
    inline Pointer& operator=(void* offset) {
        m_Function = reinterpret_cast<R(*)(Args...)>(offset);
        return *this;
    }

    inline Pointer& operator()(const char* klass, const SignaturePattern& pattern) {
        m_Function = reinterpret_cast<R(*)(Args...)>(Il2CppUtils::GetMethodPointer(GET_CLASS(klass), pattern));
        return *this;
    }

    inline Pointer& operator()(const char* klass, const char* methodname, int index = 0) {
        m_Function = reinterpret_cast<R(*)(Args...)>(Il2CppUtils::GetMethodPointerFromName(GET_CLASS(klass), methodname, index));
        return *this;
    }

    inline Pointer& operator()(Il2CppClass* klass, const SignaturePattern& pattern) {
        m_Function = reinterpret_cast<R(*)(Args...)>(Il2CppUtils::GetMethodPointer(klass, pattern));
        return *this;
    }

    inline Pointer& operator()(Il2CppClass* klass, const char* methodname, int index = 0) {
        m_Function = reinterpret_cast<R(*)(Args...)>(Il2CppUtils::GetMethodPointerFromName(klass, methodname, index));
        return *this;
    }

    // Call operator to invoke the function
    inline R operator()(Args... args) {
        return m_Function(std::forward<Args>(args)...);
    }

private:
    R(*m_Function)(Args...);
};