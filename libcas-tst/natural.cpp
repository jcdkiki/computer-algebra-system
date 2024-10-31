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

TEST(NATURAL, ADDITION) 
{
    using pair = std::pair<const char*, const char*>;
    for (auto [input, expected] : {
        pair { "123 321", "444" },
        pair { "0 521", "521" },
        pair { "521 0", "521" },
        pair { "12 987654321", "987654333" },
        pair { "123456789 98", "123456887" },
        pair { "900 101", "1001" },
        pair { "999 1", "1000" },
        pair { "0 0", "0" }
    })
    {
        std::stringstream ss;
        ss << input;

        Natural n1, n2;
        ss >> n1 >> n2;

        std::stringstream output;
        output << (n1 + n2);
        EXPECT_EQ(output.str(), expected);
    }
}

TEST(NATURAL, INC) 
{
    using pair = std::pair<const char*, const char*>;
    for (auto [input, expected] : {
        pair { "321", "322" },
        pair { "521", "522" },
        pair { "0", "1" },
        pair { "987654321", "987654322" },
        pair { "123456789", "123456790" },
        pair { "99", "100" },
        pair { "999", "1000" }
    })
    {
        std::stringstream ss;
        ss << input;

        Natural n1;
        ss >> n1;
        n1++;
        std::stringstream output;
        output << n1;
        EXPECT_EQ(output.str(), expected);
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
