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

TEST(NATURAL_TO_INTEGER, CONSTRUCTOR)
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

TEST(NATURAL_TO_INTEGER, CONVERT)
{
    for (Natural number1 :
        {
            Natural("0"), Natural("200"), Natural("999999999999999999999999999999999999999999"),
            Natural("0123"), Natural("123457"), Natural("000000000")
        })
    {
        Integer number2 = number1;
        ASSERT_EQ(number2.asString(), number1.asString());
    }
}

TEST(INTEGER, POZ)
{
    using pair = std::pair<const char*, const char*>;
    for (auto [input, expected] : {
        pair { "1", "2" },
        pair { "-1", "1" },
        pair { "0", "0" },
        pair { "-0", "0" },
    })
    {
        std::stringstream ss;
        ss << input;

        Integer number;
        ss >> number;

        std::stringstream output;
        output << number.positivity();
        EXPECT_EQ(output.str(), expected);
    }
}