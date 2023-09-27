#ifndef SCOPED_ARRAY_H
#define SCOPED_ARRAY_H

#include <cstdint>
#include <stdexcept>
#include <string>
#include <utility>

template <typename T> class ScopedArray {
public:
    explicit ScopedArray(T* ptr = nullptr)
        : mArray(ptr) {};
    ~ScopedArray();

    T* get() const;
    void reset(T* rhs = nullptr) noexcept;
    void swap(ScopedArray<T>& rhs) noexcept;
    T* release() noexcept;
    const T& operator[](const uint32_t i) const;
    T& operator[](const uint32_t i);

private:
    // Copy constructor and copy assignment are forbidden
    ScopedArray(const ScopedArray<T>&) = delete;
    const ScopedArray<T> operator=(const ScopedArray<T>&) = delete;

    // Data members
    T* mArray;
};

#include "../src/ScopedArray.cpp"
#endif