// @author G. Hemingway, copyright 2018 - All rights reserved
//
#include "AllocationTracker.h"

uint32_t AllocationTracker::mCount = 0;

std::ostream& operator<<(std::ostream& stream, const AllocationTracker&)
{
    stream << AllocationTracker::getCount() << std::endl;
    return stream;
}
