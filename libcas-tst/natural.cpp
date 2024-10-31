#include "natural.hpp"
#include <gtest/gtest.h>

TEST(NATURAL, CMP)
{
    Natural n1("123"), n2("321");

    ASSERT_LT(n1, n2);
    ASSERT_LE(n1, n2);
    ASSERT_NE(n1, n2);

    ASSERT_GT(n2, n1);
    ASSERT_GE(n2, n1);
    ASSERT_NE(n2, n1);
    
    ASSERT_LE(n1, n1);
    ASSERT_GE(n1, n1);
    ASSERT_EQ(n1, n1);

    ASSERT_LE(n2, n2);
    ASSERT_GE(n2, n2);
    ASSERT_EQ(n2, n2);
}

TEST(NATURAL, IO)
{
    for (const char *str : { "0", "200", "999999999999999999999999999999999999999999" }) {
        Natural number(str);
        ASSERT_EQ(number.asString(), str);
    }

    ASSERT_EQ(Natural("000000000").asString(), "0");
}
