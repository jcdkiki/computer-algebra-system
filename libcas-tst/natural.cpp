#include "natural.hpp"
#include <gtest/gtest.h>
#include <sstream>

TEST(NATURAL, CMP)
{
    std::stringstream input;
    input << "123 321";

    Natural n1, n2;
    input >> n1 >> n2;

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

TEST(NATURAL, MUL_BY_DIGIT) 
{
    std::stringstream input;
    input << "123";

    Natural n1;
    input >> n1;

    Natural res1 = mul_natural_by_digit(n1, 0);
    Natural res2 = mul_natural_by_digit(n1, 1);
    Natural res3 = mul_natural_by_digit(n1, 2);

    std::stringstream output1;
    std::stringstream output2;
    std::stringstream output3;

    output1 << res1;
    output2 << res2;
    output3 << res3;

    ASSERT_EQ(output1.str(), "0");
    ASSERT_EQ(output2.str(), "123");
    ASSERT_EQ(output3.str(), "246");
}
