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