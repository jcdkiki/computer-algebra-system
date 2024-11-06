#include <iostream>
#include "natural.hpp"
#include "integer.hpp"

int main()
{
    Natural number1, number2;
    Integer number3, number4;
    while (true) {
        std::cout << "Type two integer numbers: " << std::endl;
        std::cin >> number3 >> number4;
        std::cout << "You typed: " << number3 << " and " << number4 << std::endl;
        std::cout << "mod: " << (number3%number4) << std::endl;
    }
}
