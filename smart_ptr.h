/**
 * Simple smart pointer implementation
 */
#ifndef SMART_PTR_H
#define SMART_PTR_H

#include <stdexcept>

template <typename T>
class smart_ptr
{
private:

    T* m_ptr;

public:

    smart_ptr(T* ptr = nullptr) : m_ptr(ptr) {}

    smart_ptr(smart_ptr& ptr) : m_ptr(ptr.release()) {}

    template <typename T1>
    smart_ptr(smart_ptr<T1>& ptr) : m_ptr(ptr.release()) {}

    ~smart_ptr() { delete m_ptr; }

    smart_ptr& operator=(smart_ptr& ptr)
    {
        reset(ptr.release());
        return *this;
    }

    template <typename T1>
    smart_ptr& operator=(smart_ptr<T1>& ptr)
    {
        reset(ptr.release());
        return *this;
    }

    T& operator*()
    {
        if (m_ptr == nullptr)
            throw std::runtime_error("ptr is null");
        return *m_ptr;
    }

    T* operator->()
    {
        if (m_ptr == nullptr)
            throw std::runtime_error("ptr is null");
        return m_ptr;
    }

    T* get() { return m_ptr; }

    T* release()
    {
        T* tmp = m_ptr;
        m_ptr = nullptr;
        return tmp;
    }

    void reset(T* ptr = nullptr)
    {
        if (ptr != m_ptr)
        {
            delete m_ptr;
            m_ptr = ptr;
        }
    }
};

#endif // !SMART_PTR_H
