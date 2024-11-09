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

TEST(POLYNOMIAL, LEAD)
{
    using pair = std::pair<const char*, int>;
    for (auto [input, expected] :
        {
            pair { "0", 0 },
            pair { "42", 42 },
            pair { "23x + 19", 23 },
            pair { "1023x^100 + 47x^19 + 87", 1023 },
        })  
    {
        Polynomial<int, 0, 1> polynomial(input);
        ASSERT_EQ(polynomial.lead(), expected);
    }
}

TEST(POLYNOMIAL, DEG) 
{
    using pair = std::pair<const char*, size_t>;
    for (auto [input, expected] :
        {
            pair { "0", 0 },
            pair { "2x + 3", 1 },
            pair { "x^100 + 4x^50 + 7", 100 },
        })  
    {
        Polynomial<int, 0, 1> polynomial(input);
        ASSERT_EQ(polynomial.deg(), expected);
    }
}

TEST(POLYNOMIAL, MUL_XK) 
{
    Polynomial<int, 0, 1> p_zero("0");
    Polynomial<int, 0, 1> p_not_zero("3 + 7x^19 + 29x^31");

    size_t k_zero = 0;
    size_t k_not_zero = 3;

    ASSERT_EQ((p_zero >> k_zero).asString(),        "0");
    ASSERT_EQ((p_zero >> k_not_zero).asString(),    "0");

    ASSERT_EQ((p_not_zero >> k_zero).asString(),     "3 + 7x^19 + 29x^31");
    ASSERT_EQ((p_not_zero >> k_not_zero).asString(), "3x^3 + 7x^22 + 29x^34");
}
