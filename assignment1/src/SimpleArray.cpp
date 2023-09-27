#include "SimpleArray.h"
#include "AllocationTracker.h"
#include <_types/_uint32_t.h>

SimpleArray::SimpleArray(AllocationTracker* ptr)
{
    mArray = ptr;
}

SimpleArray::~SimpleArray()
{
    delete[] mArray;
}

AllocationTracker& SimpleArray::getReference(const uint32_t i) const
{
    return mArray[i];
}

AllocationTracker* SimpleArray::get() const
{
    return mArray;
}

bool SimpleArray::isNonNull() const
{
    return mArray->getCount() != 0U;
}

void SimpleArray::swap(SimpleArray& rhs)
{
    std::swap(mArray, rhs.mArray);
}

void SimpleArray::reset(AllocationTracker* rhs)
{
    delete[] mArray;
    mArray = rhs;
}

AllocationTracker* SimpleArray::release()
{
    AllocationTracker* rtn(mArray);
    mArray = nullptr;
    return rtn;
}