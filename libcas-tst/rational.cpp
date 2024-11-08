#include "rational.hpp"
#include <gtest/gtest.h>

TEST(RATIONAL, IO)
{
    using pair = std::pair<const char*, const char*>;
    for (auto [input, expected] :
        {
            pair { "5/9", "5/9" },
            pair {
                "99999999999999999999999999999/99999",
                "99999999999999999999999999999/99999"
            },
            pair { "-100  /       11", "-100/11" },
            pair { "5/1", "5" },
            pair { "123", "123" }
        })  
    {
        Rational number(input);
        ASSERT_EQ(number.asString(), expected);
    }

    EXPECT_THROW(Rational("100/0"), std::runtime_error);
    ASSERT_EQ(Integer("-0").asString(), "0");
}

TEST(RATIONAL, GCD)
{
    using pair = std::pair<const char*, const char*>;
    for (auto [input, expected] : {
        pair { "48/18", "6" },
        pair { "54/24", "6" },
        pair { "100/10", "10" },
        pair { "17/34", "17" },
        pair { "-231/140", "7" },
        pair { "0/100", "100" },
        pair { "345654633/867876", "3" },
        pair { "10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000/10", "10" },
        pair { "345654633546456756756765756/867876567765886797890456546", "2" },
        pair { "8931749619201839516395476287219493412960/2794927242316834532807463226089536046445", "5" },

    })  
    {
        Rational number(input);
        const char* gcd_result = number.greatest_common_divisor(number.get_numerator(), number.get_denominator());
        std::string temp = expected;
        ASSERT_EQ(gcd_result, temp);
    }
}

TEST(RATIONAL, REDUCE)
{
    using pair = std::pair<const char*, const char*>;
    for (auto [input, expected] : {
        pair { "20/5", "4" },
        pair { "100000000000000000000000000/1000000000000000000000000", "100" },
        pair { "4344/3", "1448" },
        pair { "5647464577645/567476465", "1129492915529/113495293" },
        pair { "25000000000000000000000000000000000000/2500000000000000000000000000000000000", "10" },
        pair { "345654633546456756756765756/867876567765886797890456546", "172827316773228378378382878/433938283882943398945228273" },
        pair { "0/150", "0" },
        pair { "-20/140", "-1/7" },
        pair { "-7000/1000", "-7" },

    })  
    {
        Rational number(input);
        number.reduce();

        std::string temp = expected;
        EXPECT_EQ(number.asString(), expected);
    }
}

TEST(RATIONAL, ADDITION) 
{
    using tuple = std::tuple<const char*, const char*, const char*>;
    for (auto [input1, input2, expected] : {
        tuple { "10/6", "14/6",  "4" },
        tuple { "256/16", "1830/72",  "497/12" },
        tuple { "20/5", "14/6",  "19/3" },
        tuple { "65754845764567/56486784674676", "867458675445687748/47687547864788675",  "52135638768819802558435516948373/2693716247901623133595364094300" },
        tuple { "-20/5", "-105/8",  "-137/8" },
        tuple { "-20/5", "105/8",  "73/8" },
        tuple { "0", "50/8",  "25/4" },
    })
    {
        Rational n1(input1), n2(input2);
        n1 += n2;
        EXPECT_EQ(n1.asString(), expected);
    }
}
