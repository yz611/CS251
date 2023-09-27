#ifndef ARRAY_LIST_CPP
#define ARRAY_LIST_CPP

template <typename T>
ArrayList<T>::ArrayList()
    : mArray(nullptr)
    , mSize(0)
    , mCapacity(0)
{
}

template <typename T>
ArrayList<T>::ArrayList(const uint32_t& size, const T& value)
    : mArray(new T[size])
    , mSize(size)
    , mCapacity(size)
{
    // for (size_t i = 0; i != size; ++i) {
    //     mArray[i] = value;
    // }
    std::fill(mArray.get(), mArray.get() + mSize, value);
}

template <typename T>
ArrayList<T>::ArrayList(const ArrayList<T>& src)
    : mArray(new T[src.mCapacity])
    , mSize(src.mSize)
    , mCapacity(src.mCapacity)
{
    std::copy(src.mArray.get(), src.mArray.get() + mSize, mArray.get());
}

template <typename T>
ArrayList<T>::ArrayList(ArrayList<T>&& src) noexcept
    : mArray(src.mArray.release())
    , mSize(src.mSize)
    , mCapacity(src.mCapacity)
{
    src.mSize = src.mCapacity = 0;
}

template <typename T> ArrayList<T>& ArrayList<T>::operator=(const ArrayList<T>& src)
{
    if (this != &src) {
        ArrayList<T>(src).swap(*this);
    }
    return *this;
}

template <typename T> ArrayList<T>& ArrayList<T>::operator=(ArrayList<T>&& src) noexcept
{
    if (this != &src) {
        mSize = src.mSize;
        mCapacity = src.mCapacity;
        mArray.reset(src.mArray.release());
    }
    src.clear();
    return *this;
}

template <typename T> const uint32_t& ArrayList<T>::add(const T& value)
{
    return add(mSize, value);
}

template <typename T> bool ArrayList<T>::in_range(uint32_t index) const
{
    return index < this->mSize;
}

template <typename T> void ArrayList<T>::resize(uint32_t new_size) noexcept
{
    if (new_size > mCapacity) {
        if (mCapacity == 0)
            mCapacity = 1;
        while (mCapacity < new_size) {
            mCapacity *= 2;
        }
        uint32_t physical_size = mCapacity;
        ScopedArray<T> temp_array(new T[physical_size]);
        std::copy(mArray.get(), mArray.get() + mSize, temp_array.get());
        mCapacity = physical_size;
        temp_array.swap(mArray);
    } else if (mSize < new_size) {
        ScopedArray<T> temp_array(new T[new_size]);
        std::copy(mArray.get(), mArray.get() + mSize, temp_array.get());
        temp_array.swap(mArray);
    }
    this->mSize = new_size;
}

template <typename T> const uint32_t& ArrayList<T>::add(const uint32_t index, const T& value)
{
    if (in_range(index)) {
        resize(mSize + 1);
        uint32_t j = this->mSize - 1;
        for (uint32_t i = this->mSize - 2; i != index - 1; i--) {
            mArray[j--] = mArray[i];
        }
        this->mArray[index] = value;
    } else {
        resize(index + 1);
        this->mArray[index] = value;
    }
    return mCapacity;
}

template <typename T> void ArrayList<T>::clear()
{
    mSize = 0;
    mArray.reset();
    mCapacity = 0;
}

template <typename T> const T& ArrayList<T>::get(const uint32_t& index) const
{
    if (index <= mSize - 1 && mSize != 0) {
        return mArray[index];
    } else {
        throw std::out_of_range(std::to_string(index));
    }
}

template <typename T> T& ArrayList<T>::get(const uint32_t& index)
{
    if (index <= mSize - 1 && mSize != 0) {
        return mArray[index];
    } else {
        throw std::out_of_range(std::to_string(index));
    }
}

template <typename T> T& ArrayList<T>::operator[](const uint32_t& index)
{
    return mArray[index];
}

template <typename T> const T& ArrayList<T>::operator[](const uint32_t& index) const
{
    return mArray[index];
}

template <typename T> bool ArrayList<T>::isEmpty() const
{
    return mSize ? false : true;
}

template <typename T> T ArrayList<T>::remove(const uint32_t& index)
{
    T removed;
    if (index <= mSize - 1 && mSize != 0) {
        removed = mArray[index];
    } else {
        throw std::out_of_range(std::to_string(index));
    }
    ScopedArray<T> tmp(new T[mCapacity]);
    std::copy(mArray.get(), mArray.get() + index, tmp.get());
    std::copy(mArray.get() + index + 1, mArray.get() + mSize, tmp.get() + index);
    --mSize;
    mArray.swap(tmp);
    return removed;
}

template <typename T> void ArrayList<T>::set(const uint32_t& index, const T& value)
{
    if (index <= mCapacity - 1 && mSize != 0) {
        this->add(index, value);
    } else {
        throw std::out_of_range(std::to_string(index));
    }
}

template <typename T> uint32_t ArrayList<T>::size() const
{
    return mSize;
}

template <typename T> void ArrayList<T>::swap(ArrayList<T>& src) noexcept
{
    std::swap(mSize, src.mSize);
    std::swap(mCapacity, src.mCapacity);
    mArray.swap(src.mArray);
}

template <typename T> typename ArrayList<T>::iterator ArrayList<T>::begin()
{
    return ArrayListIterator<T>(mArray.get());
}

template <typename T> typename ArrayList<T>::iterator ArrayList<T>::end()
{
    return ArrayListIterator<T>(mArray.get() + mSize);
}

#endif