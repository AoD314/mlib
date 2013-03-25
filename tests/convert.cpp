
#include <gtest/gtest.h>
#include <mlib/convert.hpp>

TEST(convert, to_str)
{
    ASSERT_EQ("123",     mlib::to_str(123));
    ASSERT_EQ("-123",    mlib::to_str(-123.25));
    ASSERT_EQ("-123.25", mlib::to_str(-123.25, 0, 2));
}
