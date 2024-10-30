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

TEST(NATURAL, MUL)
{
    using pair = std::pair<const char*, const char*>;
    for (auto [input, expected] : {
        pair { "100 10", "1000" },
        pair { "12 12", "144" },
        pair { "12 0", "0" },
        pair { "0 0", "0" },
        pair { "12 123", "1476" },
        pair { "123 12", "1476" },
        pair { "1 1", "1" },
        pair { "999 1", "999" },
    })
    {
        std::stringstream ss;
        ss << input;

        Natural n1, n2;
        ss >> n1 >> n2;

        std::stringstream output;
        output << (n1 * n2);
        EXPECT_EQ(output.str(), expected);
    }
}