// @author G. Hemingway, copyright 2018 - All rights reserved
//
/**
 * Graduate students must complete additional unit tests below
 */

#include "AllocationTracker.h"
#include "SimpleArray.h"
#include "gtest/gtest.h"
#include <cstddef>
#include <exception>
#include <gtest/gtest.h>
#include <new>

namespace {
// More testing for SimpleArray class.
class MoreTests : public ::testing::Test {
};

TEST_F(MoreTests, Test1)
{
    SimpleArray array(new AllocationTracker[10]);
    EXPECT_EQ(AllocationTracker::getCount(), 10);
}

TEST_F(MoreTests, Test2)
{
    AllocationTracker* directArray(new AllocationTracker[0]);
    const SimpleArray ca(directArray);
    EXPECT_EQ(AllocationTracker::getCount(), 0U);
    EXPECT_FALSE(ca.isNonNull());
}

TEST_F(MoreTests, Test3)
{
    SimpleArray arr1(new AllocationTracker[100]);
    SimpleArray arr2(new AllocationTracker[100]);
    EXPECT_NE(arr1.get(), arr2.get());
}

TEST_F(MoreTests, Test4)
{
    SimpleArray arr1(new AllocationTracker[50]);
    arr1.swap(arr1);
    EXPECT_EQ(AllocationTracker::getCount(), 50U);
}

TEST_F(MoreTests, Test5)
{
    AllocationTracker* directArray1 = new AllocationTracker[100];
    SimpleArray arr(directArray1);
    AllocationTracker* tmp = arr.release();
    EXPECT_EQ(arr.get(), nullptr);
    EXPECT_EQ(tmp, directArray1);
    EXPECT_NO_THROW(delete [] directArray1);
}

TEST_F(MoreTests, Test6)
{
    SimpleArray array;
    EXPECT_FALSE(array.isNonNull());

    AllocationTracker* directArray = new AllocationTracker[10];
    array.reset(directArray);
    EXPECT_NE(directArray, nullptr);
}
}
