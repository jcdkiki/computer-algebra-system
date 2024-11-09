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

TEST(RATIONAL, SUBTRACTION) 
{
    using tuple = std::tuple<const char*, const char*, const char*>;
    for (auto [input1, input2, expected] : {
        tuple { "10/6", "14/6",  "-2/3" },
        tuple { "20/3", "7/6",  "11/2" },
        tuple { "0/3", "0/6",  "0" },
        tuple { "0/3", "1/6",  "-1/6" },
        tuple { "-7/3", "2/4",  "-17/6" },
        tuple { "-21/4", "-112/41",  "-413/164" },
        tuple { "9533231681522876397130480885115596404053/759627102205017252677234476961037249241", "7581790521830612961910312739549210457473/3302704898240121201452666149958905115293",  "25726117406999856898645750768097413750515156738326550490877363631806655045454536/2508824151288459653029081886851848768462741810768984852147194618661308681742613" },
    })
    {
        Rational n1(input1), n2(input2);
        Rational result = n1 - n2;
        EXPECT_EQ(result.asString(), expected);
    }
}

TEST(RATIONAL, MULTIPLICATION) 
{
    using tuple = std::tuple<const char*, const char*, const char*>;
    for (auto [input1, input2, expected] : {
        tuple { "6/5", "7/6",  "7/5" },
        tuple { "5/5", "10/10",  "1" },
        tuple { "-12/17", "41/17",  "-492/289" },
        tuple { "-10/175", "-10/30",  "2/105" },
        tuple { "0/175", "10/30",  "0" },
        tuple { "6693275894100451472543720934941029648074/0036722054891261307866672864157889296645", "6647110722548418390910218342050589834651/2579664835732039155993130984532211077982",  "823906406752777094887903307823763546161638823930743701173513214659995414455781/1754270253681639384605503913702911159624243790984114912598786331430652332785" },
    })
    {
        Rational n1(input1), n2(input2);
        Rational result = n1 * n2;
        EXPECT_EQ(result.asString(), expected);
    }
}


TEST(RATIONAL, DIVISION) 
{
    using tuple = std::tuple<const char*, const char*, const char*>;
    for (auto [input1, input2, expected] : {
        tuple { "8/5", "4/11",  "22/5" },
        tuple { "20/20", "5/5",  "1" },
        tuple { "-21/9", "15/4",  "-28/45" },
        tuple { "-20/8", "-41/3",  "15/82" },
        tuple { "15/6", "-5/19",  "-19/2" },
        tuple { "0/45334", "45345/34554",  "0" },
        tuple { "5378596443143663694935507150060928794608/670063715127709450856900878092767183434", "8931749619201839516395476287219493412960/7581790521830612961910312739549210457473",  "2548711970836154797877105958111625280443553363846896951081737629651371133481599/374052583277055547515584794089664264497517875017624847219058037133788439556540" },
    })
    {
        Rational n1(input1), n2(input2);
        Rational result = n1 / n2;
        EXPECT_EQ(result.asString(), expected);
    }
}


TEST(RATIONAL, CONVERT_INTEGER_TO_RATIONAL) 
{
    using pair = std::pair<const char*, const char*>;
    for (auto [input, expected] : {
        pair { "5", "5/1"},
        pair { "-54754676567", "-54754676567/1"}
    })
    {   
        Integer integer(input);
        Rational n1(integer);
        EXPECT_EQ(n1.asStringWithOneInDenominator(), expected);
    }
}