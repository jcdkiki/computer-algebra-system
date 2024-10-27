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

TEST(NATURAL, SUB) 
{
    std::stringstream input;
    input << "321 123 123 321";

    Natural n1, n2, n3, n4;
    input >> n1 >> n2 >> n3 >> n4;

    Natural res1 = n1 - n2;
    Natural res2 = n3 - n4;
    std::stringstream output1;
    std::stringstream output2;
    output1 << res1;
    output2 << res2;
    ASSERT_EQ(output1.str(), "198");
    ASSERT_EQ(output2.str(), "198");
}