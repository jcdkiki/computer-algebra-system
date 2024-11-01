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

TEST(NATURAL, SUB)
{
    using pair = std::pair<const char*, const char*>;
    for (auto [input, expected] : {
        pair { "100 1", "99" },
        pair { "1 1", "0" },
        pair { "0 0", "0" },
        pair { "137 0", "137" },
        pair { "321 123", "198" },
        pair { "900 101", "799" },
        pair { "228 137", "91" },
        pair { "999 1", "998" },
    })
    {
        std::stringstream ss;
        ss << input;

        Natural n1, n2;
        ss >> n1 >> n2;

        std::stringstream output;
        output << (n1 - n2);
        EXPECT_EQ(output.str(), expected);
    }
}

TEST(NATURAL, DEC)
{
    using pair = std::pair<const char*, const char*>;
    for (auto [input, expected] : {
        pair { "100", "99" },
        pair { "1", "0" },
        pair { "321", "320" },
        pair { "10", "9" },
        pair { "999 1", "998" },
    })
    {
        std::stringstream ss;
        ss << input;

        Natural n1;
        ss >> n1;

        std::stringstream output;
        n1--;
        output << n1;
        EXPECT_EQ(output.str(), expected);
    }
}
TEST(NATURAL, ADDITION) 
{
    using tuple = std::tuple<const char*, const char*, const char*>;
    for (auto [input1, input2, expected] : {
        tuple { "123",          "321",          "444" },
        tuple { "0",            "521",          "521" },
        tuple { "521",          "0",            "521" },
        tuple { "12",           "987654321",    "987654333" },
        tuple { "123456789",    "98",           "123456887" },
        tuple { "900",          "101",          "1001" },
        tuple { "999",          "1",            "1000" },
        tuple { "0",            "0",            "0" }
    })
    {
        Natural n1(input1), n2(input2);
        Natural result = n1 + n2;
        EXPECT_EQ(result.asString(), expected);
    }
}

TEST(NATURAL, INC) 
{
    using pair = std::pair<const char*, const char*>;
    for (auto [input, expected] : {
        pair { "321",       "322" },
        pair { "521",       "522" },
        pair { "0",         "1" },
        pair { "987654321", "987654322" },
        pair { "123456789", "123456790" },
        pair { "99",        "100" },
        pair { "999",       "1000" }
    })
    {
        Natural n1(input);
        Natural n2(input);

        EXPECT_EQ(n1++, n2);
        EXPECT_EQ((++n2).asString(), expected);
    }
}

TEST(NATURAL, IO)
{
    for (const char *str : { "0", "200", "999999999999999999999999999999999999999999" }) {
        Natural number(str);
        ASSERT_EQ(number.asString(), str);
    }

    ASSERT_EQ(Natural("00001337").asString(), "1337");
    ASSERT_EQ(Natural("000000000").asString(), "0");
}
