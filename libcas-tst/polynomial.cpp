#include "polynomial.hpp"
#include <gtest/gtest.h>

TEST(POLYNOMIAL, IO)
{
    using pair = std::pair<const char*, const char*>;
    for (auto [input, expected] :
        {
            pair { "100", "100" },
            pair { "0", "0" },
            pair { "100x", "100x" },
            pair { "0x^2", "0" },
            pair { "13x^1000", "13x^1000" },
            pair { "x^3 + 3x + 100x^40 + 5x^30", "3x + x^3 + 5x^30 + 100x^40"},
            pair { "(5)x^5 + 7x^6 + (8)x^10", "5x^5 + 7x^6 + 8x^10"},
            pair { "-10x - 3x^2", "-10x - 3x^2" },
            pair { "5 + 2 + 3x + 5x", "7 + 8x" },
            pair { "5 - 2 + 3x - 5x", "3 - 2x" }
        })  
    {
        Polynomial<int, 0, 1> polynomial(input);
        ASSERT_EQ(polynomial.asString(), expected);
    }
}

TEST(POLYNOMIAL, DEG)
{
    using pair = std::pair<const char*, const int>;
    for (auto [input, expected] : 
        {
            pair { "0", 0 },
            pair { "1", 0 },
            pair { "x", 1 },
            pair { "42x^100 + 67x^90 + 29", 100 }
        })
    {
        Polynomial<int, 0, 1> polynomial(input);
        ASSERT_EQ(polynomial.deg(), expected);
    }
}

TEST(POLYNOMIAL, LEAD)
{
    using pair = std::pair<const char*, const int>;
    for (auto [input, expected] : 
        {
            pair { "0", 0 },
            pair { "1", 1 },
            pair { "2x", 2 },
            pair { "19x^71 + 83x^67 + 17", 19 }
        })
    {
        Polynomial<int, 0, 1> polynomial(input);
        ASSERT_EQ(polynomial.lead(), expected);
    }
}
