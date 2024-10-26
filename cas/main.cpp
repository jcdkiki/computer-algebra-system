#include <iostream>
#include "natural.hpp"

int main()
{
    Natural number1, number2;
    while (true) {
        std::cout << "Type two natural numbers: " << std::endl;
        std::cin >> number1 >> number2;
        std::cout << "You typed: " << number1 << " and " << number2 << std::endl;
    }
}
