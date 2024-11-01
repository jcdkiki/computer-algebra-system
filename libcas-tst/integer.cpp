#include "integer.hpp"
#include <gtest/gtest.h>

TEST(INTEGER, IO)
{
    for (const char *str :
        {
            "0", "200", "999999999999999999999999999999999999999999",
            "-200", "-999999999999999999999999999999999999999999"
        })
    {
        Integer number(str);
        ASSERT_EQ(number.asString(), str);
    }

    ASSERT_EQ(Integer("-0").asString(), "0");
}

TEST(NATURAL_TO_INTEGER, CONVERT)
{
    for (Natural number1 :
        {
            Natural("0"), Natural("200"), Natural("999999999999999999999999999999999999999999"),
            Natural("0123"), Natural("123457"), Natural("000000000")
        })
    {
        Integer number2(number1);
        ASSERT_EQ(number2.asString(), number1.asString());
    }
}

