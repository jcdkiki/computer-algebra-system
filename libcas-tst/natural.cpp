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