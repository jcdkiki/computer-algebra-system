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
        ASSERT_EQ(number.as_string(), str);
    }

    ASSERT_EQ(Integer("-0").as_string(), "0");
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
        ASSERT_EQ(number2.as_string(), number1.as_string());
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
        ASSERT_EQ(number2.as_string(), number1.as_string());
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
        EXPECT_EQ(result.as_string(), expected);
    }
}

TEST(Integer, CMP)
{
    using pair = std::pair<const char*, const char*>;
    for (auto [input1, input2] : {
        pair { "321",       "322" },
        pair { "-521",       "522" },
        pair { "-1",         "0" },
        pair { "-987654321", "987654322" },
        pair { "123456789", "123456790" },
        pair { "-99",        "100" },
        pair { "999",       "1000" },
        pair { "-100",      "-99" },
        pair { "0",        "124" },
    }){
        Integer n1(input1), n2(input2);

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
        EXPECT_EQ((n1).as_string(), expected);
        EXPECT_EQ((++n2).as_string(), expected);
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
        pair { "1", 1 },
        pair { "-1", -1 },
        pair { "0", 0 },
        pair { "-0", 0 },
    })
    {
        Integer number(input);
        EXPECT_EQ(sign(number), expected);
    }
}

TEST(INTEGER, ABS) 
{
    using pair = std::pair<const char*, const char*>;
    for (auto [input, expected] : {
        pair { "1",  "1" },
        pair { "0",  "0" },
        pair { "-1", "1" },
    })
    {
        Integer number(input);
        Natural res = abs(number);
        EXPECT_EQ(res.as_string(), expected);
    }
}

TEST(INTEGER, MUL)
{
    using tuple = std::tuple<const char*, const char*, const char*>;
    for (auto [input1, input2, expected] : {
        tuple { "-100", "10", "-1000" },
        tuple { "12", "-12", "-144" },
        tuple { "-12", "0", "0" },
        tuple { "0", "0", "0" },
        tuple { "12", "123", "1476" },
        tuple { "-123", "-12", "1476" },
        tuple { "1", "-1", "-1" },
        tuple { "-999", "-1", "999" },
        tuple { "-99999999", "999", "-99899999001" },
    })
    {
        Integer n1(input1), n2(input2);
        EXPECT_EQ((n1 * n2).as_string(), expected);

        n1 *= n2;
        EXPECT_EQ(n1.as_string(), expected);
    }
}

TEST(INTEGER, NEG) 
{
    using pair = std::pair<const char*, const char*>;
    for (auto [input, expected] : {
        pair { "1",  "-1" },
        pair { "0",  "0" },
        pair { "-1", "1" },
        pair { "12551251", "-12551251" },
        pair { "-99999999", "99999999" },
    })
    {
        Integer number(input);
        number = -number;
        EXPECT_EQ(number.as_string(), expected);
    }
}

TEST(INTEGER, DIV)
{
    using tuple = std::tuple<const char*, const char*, const char*>;
    for (auto [input1, input2, expected] : {
        tuple { "-100", "11", "-9" },
        tuple { "12", "-12", "-1" },
        tuple { "-12", "13", "0" },
        tuple { "0", "-1", "0" },
        tuple { "-1", "-1", "1" },
        tuple { "-123", "-1", "123" },
    })
    {
        Integer n1(input1), n2(input2);
        EXPECT_EQ((n1 / n2).as_string(), expected);

        n1 /= n2;
        EXPECT_EQ(n1.as_string(), expected);
    }

    Integer n1("100"), n2("0");
    EXPECT_THROW(n1/n2, std::runtime_error);
}

TEST(INTEGER, MOD)
{
    using tuple = std::tuple<const char*, const char*, const char*>;
    for (auto [input1, input2, expected] : {
        tuple { "100", "-11", "1" },
        tuple { "12", "-12", "0" },
        tuple { "-12", "13", "1" },
        tuple { "0", "1", "0" },
        tuple { "12", "13", "12" },
        tuple { "12", "-13", "12" },
        tuple { "-12556", "12", "8"},
        tuple { "-15", "-7", "6"}
    })
    {
        Integer n1(input1), n2(input2);
        EXPECT_EQ((n1 % n2).as_string(), expected);

        n1 %= n2;
        EXPECT_EQ(n1.as_string(), expected);
    }

    Integer n1("100"), n2("0");
    EXPECT_THROW(n1%n2, std::runtime_error);
}

TEST(INTEGER_TO_NATURAL, CONVERT)
{
    for (Integer number1 :
        {
            Integer("0"), Integer("200"), Integer("999999999999999999999999999999999999999999"),
            Integer("0123"), Integer("123457"), Integer("000000000")
        })
    {
        Natural number2 = number1;
        ASSERT_EQ(number2.as_string(), number1.as_string());
    }
    Natural number2;
    EXPECT_THROW((number2 = Integer("-12")), std::runtime_error);
    EXPECT_THROW((number2 = Integer("-999999999999999999")), std::runtime_error);
}
