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

TEST(INTEGER, ADDITION) 
{
    using tuple = std::tuple<const char*, const char*, const char*>;
    for (auto [input1, input2, expected] : {
        tuple { "123",          "321",          "444" },
        tuple { "0",            "-521",          "-521" },
        tuple { "521",          "0",            "521" },
        tuple { "12",           "-987654321",    "-987654309" },
        tuple { "-123456789",    "98",           "-123456691" },
        tuple { "900",          "101",          "1001" },
        tuple { "999",          "-1",            "998" },
        tuple { "0",            "0",            "0" },
        tuple { "-67",          "67",           "0" },
        tuple { "67",           "-67",          "0" }
    })
    {
        Integer n1(input1), n2(input2);
        Integer result = n1 + n2;
        EXPECT_EQ(result.asString(), expected);
    }
}

TEST(INTEGER, INC) 
{
    using pair = std::pair<const char*, const char*>;
    for (auto [input, expected] : {
        pair { "321",       "322" },
        pair { "521",       "522" },
        pair { "0",         "1" },
        pair { "987654321", "987654322" },
        pair { "123456789", "123456790" },
        pair { "99",        "100" },
        pair { "999",       "1000" },
        pair { "-100",      "-99" },
        pair { "-1",        "0" }
    })
    {
        Integer n1(input);
        Integer n2(input);
        n1++;
        EXPECT_EQ((n1).asString(), expected);
        EXPECT_EQ((++n2).asString(), expected);
    }
}

TEST(INTEGER, SUB)
{
    using pair = std::pair<const char*, const char*>;
    for (auto [input, expected] : {
        pair { "100 1", "99" },
        pair { "1 1", "0" },
        pair { "0 -55", "55" },
        pair { "137 155", "-18" },
        pair { "321 -123", "444" },
        pair { "-900 -101", "-799" },
        pair { "-228 137", "-365" },
        pair { "100 101", "-1" },
        pair { "-100 -125", "25" },
        pair { "0 0", "0"},
        pair { "55 0", "55"},
        pair { "-12 0", "-12"}
    })
    {
        std::stringstream ss;
        ss << input;

        Integer n1, n2;
        ss >> n1 >> n2;

        std::stringstream output;
        output << (n1 - n2);
        EXPECT_EQ(output.str(), expected);
    }
}

TEST(INTEGER, POZ)
{
    using pair = std::pair<const char*, int>;
    for (auto [input, expected] : {
        pair { "1", 2 },
        pair { "-1", 1 },
        pair { "0", 0 },
        pair { "-0", 0 },
    })
    {
        Integer number(input);
        EXPECT_EQ(number.positivity(), expected);
    }
}
