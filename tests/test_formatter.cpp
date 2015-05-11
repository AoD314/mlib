
#include <gtest/gtest.h>
#include <mlib/formatter.hpp>

TEST(Print, print_time)
{
    ASSERT_EQ("0:00:02.500", mlib::Print::time(2500));
    ASSERT_EQ("0:01:33.483", mlib::Print::time(93483));
    ASSERT_EQ("0:00:00.000", mlib::Print::time(-1));
}

TEST(Print, percent)
{
    ASSERT_EQ("0.00%",   mlib::Print::percent(0, 1));
    ASSERT_EQ("0.00%",   mlib::Print::percent(-1, 7));
    ASSERT_EQ("50.00%",  mlib::Print::percent(1, 2));
    ASSERT_EQ("33.33%",  mlib::Print::percent(1, 3));
    ASSERT_EQ("100.00%", mlib::Print::percent(7, 7));
    ASSERT_EQ("100.00%", mlib::Print::percent(8, 7));
}

TEST(Print, print_size)
{
    ASSERT_EQ("0 byte",   mlib::Print::size(-2));
    ASSERT_EQ("666 byte", mlib::Print::size(666));
    ASSERT_EQ("1.000 Kb", mlib::Print::size(1024));
    ASSERT_EQ("1.001 Mb", mlib::Print::size(1024*1024 + 1024));
}
