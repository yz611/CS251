#ifndef SCOPED_ARRAY_CPP
#define SCOPED_ARRAY_CPP

template <typename T> ScopedArray<T>::~ScopedArray()
{
    delete[] mArray;
}

template <typename T> T* ScopedArray<T>::get() const
{
    return mArray;
}

template <typename T> void ScopedArray<T>::reset(T* rhs) noexcept
{
    if (rhs == mArray)
        return;
    delete[] mArray;
    mArray = rhs;
}

template <typename T> void ScopedArray<T>::swap(ScopedArray<T>& rhs) noexcept
{
    std::swap(mArray, rhs.mArray);
}

template <typename T> T* ScopedArray<T>::release() noexcept
{
    T* temp(mArray);
    mArray = nullptr;
    return temp;
}

template <typename T> const T& ScopedArray<T>::operator[](const uint32_t i) const
{
    return mArray[i];
}

template <typename T> T& ScopedArray<T>::operator[](const uint32_t i)
{
    return mArray[i];
}

#endif