#ifndef ARRAY_LIST_ITER_CPP
#define ARRAY_LIST_ITER_CPP

template <typename T>
ArrayListIterator<T>::ArrayListIterator(T* ptr)
    : mPtr(ptr) {};

template <typename T> bool ArrayListIterator<T>::operator==(const ArrayListIterator<T>& rhs) const
{
    return this->mPtr == rhs.mPtr;
}

template <typename T> bool ArrayListIterator<T>::operator!=(const ArrayListIterator<T>& rhs) const
{
    return this->mPtr != rhs.mPtr;
}

template <typename T> T& ArrayListIterator<T>::operator*()
{
    return *mPtr;
}

template <typename T> const T& ArrayListIterator<T>::operator*() const
{
    return *mPtr;
}

template <typename T> T* ArrayListIterator<T>::operator->()
{
    return mPtr;
}

template <typename T> const T* ArrayListIterator<T>::operator->() const
{
    return mPtr;
}

template <typename T> ArrayListIterator<T>& ArrayListIterator<T>::operator++()
{
    ++mPtr;
    return *this;
}

template <typename T> ArrayListIterator<T> ArrayListIterator<T>::operator++(int)
{
    ArrayListIterator<T> __tmp(*this);
    ++(*this);
    return __tmp;
}

template <typename T> ArrayListIterator<T>& ArrayListIterator<T>::operator--()
{
    --mPtr;
    return *this;
}

template <typename T> ArrayListIterator<T> ArrayListIterator<T>::operator--(int)
{
    ArrayListIterator<T> __tmp(*this);
    --(*this);
    return __tmp;
}

template <typename T> ArrayListIterator<T>& ArrayListIterator<T>::operator+=(const int& offset)
{
    mPtr += offset;
    return *this;
}

template <typename T> ArrayListIterator<T> ArrayListIterator<T>::operator+(int offset) const
{
    ArrayListIterator<T> __w(*this);
    __w += offset;
    return __w;
}

template <typename T> ArrayListIterator<T>& ArrayListIterator<T>::operator-=(const int& offset)
{
    mPtr -= offset;
    return *this;
}

template <typename T> ArrayListIterator<T> ArrayListIterator<T>::operator-(int offset) const
{
    ArrayListIterator<T> __w(*this);
    __w -= offset;
    return __w;
}

template <typename T> T& ArrayListIterator<T>::operator[](const int& index)
{
    return mPtr[index];
}

template <typename T> const T& ArrayListIterator<T>::operator[](int index) const
{
    return mPtr[index];
}

template <typename T> int ArrayListIterator<T>::operator-(const ArrayListIterator<T>& rhs) const
{
    int diff = (mPtr - rhs.mPtr) / sizeof(mPtr);
    return diff;
}

template <typename T> ArrayListIterator<T> operator+(int offset, const ArrayListIterator<T>& iter)
{
    return ArrayListIterator<T>(iter.mPtr + offset);
}

#endif