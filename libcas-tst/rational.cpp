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
            pair { "-100  /       11", "-100/11" }
        })  
    {
        Rational number(input);
        ASSERT_EQ(number.asString(), expected);
    }

    ASSERT_EQ(Integer("-0").asString(), "0");
}
