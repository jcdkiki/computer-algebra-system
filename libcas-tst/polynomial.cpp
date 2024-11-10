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

TEST(POLYNOMIAL, MUL_T) 
{
    using pair = std::pair<const char*, const char*>;

    int zero = 0;
    int one = 1;
    int not_zero = 2;

    Polynomial<int, 0, 1> p_zero("0");
    Polynomial<int, 0, 1> p_not_zero("42x^1000 + 13x^100 + 7");

    ASSERT_EQ((p_zero * zero).asString(),     "0");
    ASSERT_EQ((p_zero * one).asString(),      "0");
    ASSERT_EQ((p_zero * not_zero).asString(), "0");
    
    ASSERT_EQ((p_not_zero * zero).asString(),       "0");
    ASSERT_EQ((p_not_zero * one).asString(),        "7 + 13x^100 + 42x^1000");
    ASSERT_EQ((p_not_zero * not_zero).asString(),   "14 + 26x^100 + 84x^1000");


    ASSERT_EQ((p_zero *= not_zero).asString(), "0");
    ASSERT_EQ((p_zero *= one).asString(),      "0");
    ASSERT_EQ((p_zero *= zero).asString(),     "0");
    
    ASSERT_EQ((p_not_zero *= not_zero).asString(),   "14 + 26x^100 + 84x^1000");
    ASSERT_EQ((p_not_zero *= one).asString(),        "14 + 26x^100 + 84x^1000");
    ASSERT_EQ((p_not_zero *= zero).asString(),       "0");
}

TEST(POLYNOMIAL, ADD) 
{
    using tuple = std::tuple<const char*, const char*, const char*>;
    using poly = Polynomial<int, 0, 1>;
    for (auto [input1, input2, expected] : {
        tuple { "0", "0", "0" },
        tuple { "1 + x^2", "7", "8 + x^2" },
        tuple { "2 + x^3", "3 + 5x^3", "5 + 6x^3" },
        tuple { "19x", "1 + 20x + 3x^2", "1 + 39x + 3x^2" },
        tuple { "19x^2", "1 + x^3", "1 + 19x^2 + x^3" },
        tuple { "-x^3", "x^3", "0" },
        tuple { "2x^2 + x^3", "2x^2 - x^3", "4x^2" },
    })
    {
        poly p1(input1), p2(input2), result = p1 + p2;
        ASSERT_EQ(result.asString(), expected);
    }

    for (auto [input1, input2, expected] : {
        tuple { "0", "0", "0" },
        tuple { "1 + x^2", "7", "8 + x^2" },
        tuple { "2 + x^3", "3 + 5x^3", "5 + 6x^3" },
        tuple { "19x", "1 + 20x + 3x^2", "1 + 39x + 3x^2" },
        tuple { "19x^2", "1 + x^3", "1 + 19x^2 + x^3" },
        tuple { "-x^3", "x^3", "0" },
        tuple { "2x^2 + x^3", "2x^2 - x^3", "4x^2" },
    })
    {
        poly p1(input1), p2(input2);
        p1 += p2;
        ASSERT_EQ(p1.asString(), expected);
    }

}

TEST(POLYNOMIAL, SUB) 
{
    using tuple = std::tuple<const char*, const char*, const char*>;
    using poly = Polynomial<int, 0, 1>;
    for (auto [input1, input2, expected] : {
        tuple { "0", "0", "0" },
        tuple { "1 + x^2", "7", "-6 + x^2" },
        tuple { "2 + x^3", "3 + 5x^3", "-1 - 4x^3" },
        tuple { "19x", "1 + 20x + 3x^2", "-1 - x - 3x^2" },
        tuple { "19x^2", "1 + x^3", "-1 + 19x^2 - x^3" },
        tuple { "x^3", "x^3", "0" },
        tuple { "-2x^2 + x^3", "2x^2 + x^3", "-4x^2" },
    })
    {
        poly p1(input1), p2(input2), result = p1 - p2;
        ASSERT_EQ(result.asString(), expected);
    }

    for (auto [input1, input2, expected] : {
        tuple { "0", "0", "0" },
        tuple { "1 + x^2", "7", "-6 + x^2" },
        tuple { "2 + x^3", "3 + 5x^3", "-1 - 4x^3" },
        tuple { "19x", "1 + 20x + 3x^2", "-1 - x - 3x^2" },
        tuple { "19x^2", "1 + x^3", "-1 + 19x^2 - x^3" },
        tuple { "x^3", "x^3", "0" },
        tuple { "-2x^2 + x^3", "2x^2 + x^3", "-4x^2" },
    })
    {
        poly p1(input1), p2(input2);
        p1 -= p2;
        ASSERT_EQ(p1.asString(), expected);
    }

}
