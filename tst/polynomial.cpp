#include "rznumbers/polynomial.hpp"
#include "rznumbers/rational.hpp"
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
            pair { "5x^5 + 7x^6 + 8x^10", "5x^5 + 7x^6 + 8x^10"},
            pair { "-10x - 3x^2", "-10x - 3x^2" },
            pair { "5 + 2 + 3x + 5x", "7 + 8x" },
            pair { "5 - 2 + 3x - 5x", "3 - 2x" }
        })  
    {
        Polynomial polynomial(input);
        ASSERT_EQ(polynomial.asString(), expected);
    }
}

TEST(POLYNOMIAL, LEAD)
{
    using pair = std::pair<const char*, Rational>;
    for (auto [input, expected] :
        {
            pair { "0", Rational(0) },
            pair { "42", Rational(42) },
            pair { "23x + 19", Rational(23) },
            pair { "1023x^100 + 47x^19 + 87", Rational(1023) },
        })  
    {
        Polynomial polynomial(input);
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
        Polynomial polynomial(input);
        ASSERT_EQ(polynomial.deg(), expected);
    }
}

TEST(POLYNOMIAL, MUL_XK) 
{
    Polynomial p_zero("0");
    Polynomial p_not_zero("3 + 7x^19 + 29x^31");

    size_t k_zero = 0;
    size_t k_not_zero = 3;

    ASSERT_EQ((p_zero << k_zero).asString(),        "0");
    ASSERT_EQ((p_zero << k_not_zero).asString(),    "0");

    ASSERT_EQ((p_not_zero << k_zero).asString(),     "3 + 7x^19 + 29x^31");
    ASSERT_EQ((p_not_zero << k_not_zero).asString(), "3x^3 + 7x^22 + 29x^34");


    ASSERT_EQ((p_zero <<= k_zero).asString(),        "0");
    ASSERT_EQ((p_zero <<= k_not_zero).asString(),    "0");

    ASSERT_EQ((p_not_zero <<= k_zero).asString(),     "3 + 7x^19 + 29x^31");
    ASSERT_EQ((p_not_zero <<= k_not_zero).asString(), "3x^3 + 7x^22 + 29x^34");
}

TEST(POLYNOMIAL, DERIVATIVE) 
{
    using pair = std::pair<const char*, const char*>;
    for (auto [input, expected] :
        {
            pair { "0", "0" },
            pair { "2x + 3", "2" },
            pair { "x^100 + 4x^50 + 7", "200x^49 + 100x^99" },
        })  
    {
        Polynomial polynomial(input);
        ASSERT_EQ(polynomial.derivative().asString(), expected);
    } 
    
    for (auto [input, expected] :
        {
            pair { "0", "0" },
            pair { "2x + 3", "0" },
            pair { "x^5 + 4x^3 + 7", "24x + 20x^3" },
        })  
    {
        Polynomial polynomial(input);
        ASSERT_EQ(polynomial.derivative(2).asString(), expected);
    }
}

TEST(POLYNOMIAL, MUL_T) 
{
    using pair = std::pair<const char*, const char*>;

    Rational zero(0);
    Rational one(1);
    Rational not_zero(2);

    Polynomial p_zero("0");
    Polynomial p_not_zero("42x^1000 + 13x^100 + 7");

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

TEST(POLYNOMIAL, MUL) 
{
    using tuple = std::tuple<const char*, const char*, const char*>;
    using poly = Polynomial;
    for (auto [input1, input2, expected] : {
        tuple { "0", "0", "0" },
        tuple { "1", "1 + 2x", "1 + 2x" },
        tuple { "2 + 2x", "1 + 2x", "2 + 6x + 4x^2" },
    })
    {
        poly p1(input1), p2(input2), result = p1 * p2;
        ASSERT_EQ(result.asString(), expected);

        p1 *= p2;
        ASSERT_EQ(p1.asString(), expected);
    }
}

TEST(POLYNOMIAL, DIV_MOD) 
{
    using tuple = std::tuple<const char*, const char*, const char*, const char*>;
    using poly = Polynomial;
    for (auto [input1, input2, expected_div, expected_mod] : {
        tuple { "9 + 4x + x^2", "2 + x", "2 + x", "5" },
        tuple { "4x", "1 + x", "4", "-4" },
        tuple { "-1 + x", "1 + x + x^2", "0", "-1 + x" }
    })
    {
        poly p1(input1), p2(input2);
        poly div = p1 / p2, mod = p1 % p2;
        ASSERT_EQ(div.asString(), expected_div);
        ASSERT_EQ(mod.asString(), expected_mod);

        p1 /= p2;
        ASSERT_EQ(p1.asString(), expected_div);
        p1 = poly(input1);
        p1 %= p2;
        ASSERT_EQ(p1.asString(), expected_mod);
    }
}

TEST(POLYNOMIAL, ADD) 
{
    using tuple = std::tuple<const char*, const char*, const char*>;
    using poly = Polynomial;
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

        p1 += p2;
        ASSERT_EQ(p1.asString(), expected);
    }

}

TEST(POLYNOMIAL, SUB) 
{
    using tuple = std::tuple<const char*, const char*, const char*>;
    using poly = Polynomial;
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
        
        p1 -= p2;
        ASSERT_EQ(p1.asString(), expected);
    }

}

TEST(POLYNOMIAL, FAC) 
{
    using tuple = std::tuple<const char*, const char*>;
    using poly = Polynomial;
    for (auto [input, expected] : {
        tuple { "0", "0" },
        tuple { "1/12 + 1/6x + 2/3x^2", "1 + 2x + 8x^2" },
        tuple {  "5/36x", "x" },
        tuple { "-5/36x", "x" },
        tuple {  "5/36",  "5/36" },
        tuple { "-5/36",  "-5/36" },
    })
    {
        poly p(input); 
        ASSERT_EQ(p.factorize().asString(), expected);
    }
}

TEST(POLYNOMIAL, GCD) 
{
    using tuple = std::tuple<const char*, const char*, const char*>;
    for (auto [input1, input2, expected] : {
        tuple { "2 - 3x + x^2", "3 - 4x + x^2", "-1 + x" },
        tuple { "3 - 4x + x^2", "2 - 3x+x^2", "-1 + x" },
        tuple { "1 + x", "2 + x", "1"},
        tuple { "1 + x", "1/2", "1/2"}
    })
    {
        Polynomial p1(input1), p2(input2);
        EXPECT_EQ(gcd(p1, p2).asString(), expected);
    }
}

TEST(POLYNOMIAL, NMR) 
{
    using tuple = std::tuple<const char*, const char*>;
    for (auto [input, expected] : {
        tuple { "1 + 2x + x^2", "1 + x"},
        tuple { "-2 + 5x -4x^2 + x^3", "2 - 3x + x^2" },
        tuple { "-46 + 101x - 59x^2 +3x^4 + x^5", "46 - 55x + 4x^2 + 4x^3 + x^4" },
        tuple { "42", "42" },
        tuple { "1 + x", "1 + x" }
    })
    {
        Polynomial p(input);
        EXPECT_EQ(p.nmr().asString(), expected);
    }
}

