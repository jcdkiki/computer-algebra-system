#ifndef CAS_NUMBERS_POLYNOMIAL_HPP_
#define CAS_NUMBERS_POLYNOMIAL_HPP_

#include <vector>
#include <string>
#include <istream>
#include <ostream>
#include <sstream>

template<class T, T default_coeff>
class Polynomial {
    std::vector<T> coeff;

    void resizeAtLeast(size_t size)
    {
        if (coeff.size() < size) {
            coeff.resize(size);
        }
    }

    void strip()
    {
        for (size_t i = coeff.size() - 1; i > 0; i--) { // don`t touch free term
            if (coeff[i] != 0) {
                coeff.resize(i + 1);
                return;
            }
        }

        coeff.resize(1);
    }

public:
    Polynomial() : coeff(1, 0) {}

    Polynomial(const char *str)
    {
        std::stringstream ss;
        ss << str;
        ss >> *this;
    }

    std::string asString()
    {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    friend std::ostream& operator<<(std::ostream& os, const Polynomial& polynomial)
    {
        bool has_x = false;
        bool first = true;
        for (size_t i = 1; i < polynomial.coeff.size(); i++) {
            if (polynomial.coeff[i] != 0) {
                has_x = true;
                break;
            }
        }

        if ((bool)polynomial.coeff[0] || !has_x) {
            os << polynomial.coeff[0];
            first = false;
        }

        for (size_t i = 1; i < polynomial.coeff.size(); i++) {
            T coeff = polynomial.coeff[i];
            if (!coeff) {
                continue;
            }

            bool sign = (coeff < 0);

            if (!first) {
                os << (sign ? " - " : " + ");
                if (sign) coeff = -coeff;
            }
            else {
                first = false;
                if (sign) {
                    coeff = -coeff;
                    os << "-";
                }
            }

            if (coeff != default_coeff) {
                os << coeff;
            }

            os << "x";
            if (i != 1) {
                os << '^' << i;
            }
        }
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Polynomial& polynomial)
    {
        polynomial.coeff.resize(1);
        polynomial.coeff[0] = 0;

        char c;
        bool should_close = false;
        bool sign = false;

        is >> c;
        if (c == '-')
            sign = true;
        else
            is.unget();

        while (true) {
            should_close = false;

            is >> c;        
            if (c == '(')
                should_close = true;
            else
                is.unget();

            T coeff;
            is >> coeff;

            if (is.fail()) {
                coeff = default_coeff;
                is.clear();
            }

            is >> c;
            if (should_close) {
                if (c != ')') {
                    throw std::invalid_argument("bad polynomial input");
                }
                is >> c;
            }

            if (c != 'x') {
                is.unget();
                polynomial.coeff[0] += sign ? -coeff : coeff;
            }
            else {
                is >> c;
                size_t power = 1;
                if (c == '^') {
                    is >> power;
                }
                else is.unget();

                polynomial.resizeAtLeast(power + 1);
                polynomial.coeff[power] += sign ? -coeff : coeff;
            }

            is >> c;
            if (c == '-') {
                sign = true;
            }
            else if (c == '+') {
                sign = false;
            }
            else {
                is.unget();
                break;
            }
        }

        polynomial.strip();
        return is;
    }
};

#endif
