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

TEST(NATURAL, MULBYDIGIT) 
{
    using pair = std::pair<const char*, const char*>;
    for (auto [input, expected] : {
        pair { "123 9", "1107" },
        pair { "521 0", "0" },
        pair { "0 0", "0" },
        pair { "0 5", "0" },
        pair { "5 5", "25" },
        pair { "10 6", "60" },
        pair { "999 1", "999" },
    })
    {
        std::stringstream ss;
        ss << input;
        Natural n1;
        char n2;
        ss >> n1 >> n2;

        std::stringstream output;
        n2 -= '0';
        output << (n1 *= n2);
        EXPECT_EQ(output.str(), expected);
    }
}
