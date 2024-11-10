#include "rznumbers/natural.hpp"
#include <gtest/gtest.h>
#include <sstream>
#include <stdexcept>

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

TEST(NATURAL, MULBYDIGIT) 
{
    using tuple = std::tuple<const char*, Natural::Digit, const char*>;
    for (auto [input, digit, expected] : {
        tuple { "123", 9, "1107" },
        tuple { "521", 0, "0" },
        tuple { "0", 0, "0" },
        tuple { "0", 5, "0" },
        tuple { "5", 5, "25" },
        tuple { "10", 6, "60" },
        tuple { "999", 1, "999" },
    })
    {
        Natural n(input);
        EXPECT_EQ((n * digit).asString(), expected);
        
        n *= digit;
        EXPECT_EQ(n.asString(), expected);
    }
}

TEST(NATURAL, MULBY10K)
{
    using pair = std::pair<const char*, const char*>;
    for (auto [input, expected] : {
        pair { "100 1", "1000" },
        pair { "1 1", "10" },
        pair { "123 0", "123" },
        pair { "137 2", "13700" },
        pair { "321 2", "32100" },
        pair { "0 2", "0" },
    })
    {
        std::stringstream ss;
        ss << input;
        
        Natural n;
        size_t k;
        ss >> n >> k;

        std::stringstream output;
        output << (n << k);
        EXPECT_EQ(output.str(), expected);
    }
}

TEST(NATURAL, MUL)
{
    using tuple = std::tuple<const char*, const char*, const char*>;
    for (auto [input1, input2, expected] : {
        tuple { "100", "10", "1000" },
        tuple { "12", "12", "144" },
        tuple { "12", "0", "0" },
        tuple { "0", "0", "0" },
        tuple { "12", "123", "1476" },
        tuple { "123", "12", "1476" },
        tuple { "1", "1", "1" },
        tuple { "999", "1", "999" },
    })
    {
        Natural n1(input1), n2(input2);
        EXPECT_EQ((n1 * n2).asString(), expected);

        n1 *= n2;
        EXPECT_EQ(n1.asString(), expected);
    }
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

    EXPECT_THROW(Natural("0")--, std::runtime_error);
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

TEST(NATURAL, DIVDK)
{
    using tuple = std::tuple<const char*, const char*, const char*>;
    for (auto [input1, input2, expected] : {
        tuple { "100", "10", "10" },
        tuple { "1", "1", "1" },
        tuple { "50", "3", "10" },
        tuple { "39900", "5", "7000" },
        tuple { "1019", "34", "20" },
    })
    {
        Natural n1(input1), n2(input2);
        EXPECT_EQ((getDivDigitInPower(n1, n2)).asString(), expected);
    }
}

TEST(NATURAL, SUBNDN) 
{
    using tuple = std::tuple<const char*, const char *, Natural::Digit, const char*>;
    for (auto [input1, input2, digit, expected] : {
        tuple { "12", "3", 4, "0" },
        tuple { "100", "5", 0, "100"},
        tuple { "100", "5", 12, "40"}
    })
    {
        Natural n1(input1);
        Natural n2(input2);
        EXPECT_EQ(subNDN(n1, n2, digit).asString(), expected);
    }

    Natural n1("100"), n2("50");
    EXPECT_THROW(subNDN(n1, n2, 3), std::runtime_error);
}

TEST(NATURAL, DIV)
{
    using tuple = std::tuple<const char*, const char*, const char*>;
    for (auto [input1, input2, expected] : {
        tuple { "100", "11", "9" },
        tuple { "12", "12", "1" },
        tuple { "12", "13", "0" },
        tuple { "0", "1", "0" },
    })
    {
        Natural n1(input1), n2(input2);
        EXPECT_EQ((n1 / n2).asString(), expected);

        n1 /= n2;
        EXPECT_EQ(n1.asString(), expected);
    }

    Natural n1("100"), n2("0");
    EXPECT_THROW(n1/n2, std::runtime_error);
}

TEST(NATURAL, MOD)
{
    using tuple = std::tuple<const char*, const char*, const char*>;
    for (auto [input1, input2, expected] : {
        tuple { "100", "11", "1" },
        tuple { "12", "12", "0" },
        tuple { "12", "13", "12" },
        tuple { "0", "1", "0" },
    })
    {
        Natural n1(input1), n2(input2);
        EXPECT_EQ((n1 % n2).asString(), expected);

        n1 %= n2;
        EXPECT_EQ(n1.asString(), expected);
    }

    Natural n1("100"), n2("0");
    EXPECT_THROW(n1%n2, std::runtime_error);
}

TEST(NATURAL, GCF)
{
    using tuple = std::tuple<const char*, const char*, const char*>;
    for (auto [input1, input2, expected] : {
        tuple { "100", "11", "1" },
        tuple { "12", "18", "6" },
        tuple { "13", "13", "13" },
        tuple { "16", "256", "16" }
    })
    {
        Natural n1(input1), n2(input2);
        EXPECT_EQ(greatCommDiv(n1, n2).asString(), expected);

    }
}

TEST(NATURAL, LCM)
{
    using tuple = std::tuple<const char*, const char*, const char*>;
    for (auto [input1, input2, expected] : {
        tuple { "100", "11", "1100" },
        tuple { "12", "18", "36" },
        tuple { "13", "13", "13" },
        tuple { "16", "256", "256" }
    })
    {
        Natural n1(input1), n2(input2);
        EXPECT_EQ(leastCommMul(n1, n2).asString(), expected);

    }
}
