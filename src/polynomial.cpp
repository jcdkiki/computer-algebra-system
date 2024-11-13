#include "rznumbers/polynomial.hpp"
#include <sstream>

void Polynomial::resizeAtLeast(size_t size)
{
    if (coeff.size() < size) {
        coeff.resize(size);
    }
}

void Polynomial::strip()
{
    for (size_t i = coeff.size() - 1; i > 0; i--) { // don`t touch free term
        if (coeff[i]) {
            coeff.resize(i + 1);
            return;
        }
    }

    coeff.resize(1);
}

Polynomial::Polynomial() : coeff(1) {}

Polynomial::Polynomial(const char *str)
{
    std::stringstream ss;
    ss << str;
    ss >> *this;
}

Polynomial::Polynomial(const Rational& coeff, int power) : coeff(power + 1)
{
    this->coeff[power] = coeff;
}

/** @brief LED_P_Q - Возвращает старший коэффициент многочлена. */
const Rational& Polynomial::lead() const
{
    return coeff.back();
}

/** @brief DEG_P_N - Возвращает степень многочлена. */
size_t Polynomial::deg() const
{
    return coeff.size() - 1;
}

/** @brief ADD_PP_P - Вычисляет сумму двух многочленов. */
Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs) 
{
    Polynomial res(lhs);
    return res += rhs;
}

/** @brief ADD_PP_P - Вычисляет сумму двух многочленов. */
Polynomial& Polynomial::operator+=(const Polynomial& rhs) 
{
    if (deg() <= rhs.deg()) 
        coeff.resize(rhs.coeff.size());
    
    for (size_t i = 0; i <= rhs.deg(); i++)
        coeff[i] += rhs.coeff[i];

    strip();

    return *this;
}

/** @brief MUL_Pxk_P - Умножает многочлен на x^k. */
Polynomial operator<<(const Polynomial& lhs, size_t rhs) 
{
    Polynomial res(lhs);
    return res <<= rhs;
}

/** @brief MUL_Pxk_P - Умножает многочлен на x^k. */
Polynomial& Polynomial::operator<<=(size_t rhs) 
{        
    if (!(rhs == 0 || deg() == 0 && !coeff.back()))
    {
        ssize_t old_size = coeff.size();
        coeff.resize(coeff.size() + rhs);

        for (ssize_t i = old_size - 1; i >= 0; i--) {
            coeff[i + rhs] = std::move(coeff[i]);
        }

        for (ssize_t i = 0; i < rhs; i++) {
            coeff[i] = Rational();
        }
    }

    return *this;
}

/** @brief DER_P_P - Взятие k-ой производной от многочлена. */
Polynomial Polynomial::derivative(unsigned int k) const 
{
    Polynomial tmp, der(*this);
    
    if (deg() == 0 || deg() < k)
        return tmp; // 0

    for (; k != 0; k--) 
    {
        tmp.coeff.resize(der.coeff.size() - 1);
        for (size_t i = 0; i <= tmp.deg(); i++)
            tmp.coeff[i] = der.coeff[i + 1] * Rational(i + 1);

        der = tmp;
    }

    return der; 
}

/** @brief SUB_PP_P - Вычисляет разность двух многочленов. */
Polynomial operator-(const Polynomial& lhs, const Polynomial& rhs) 
{
    Polynomial res(lhs);
    return res -= rhs; 
}

/** @brief SUB_PP_P - Вычисляет разность двух многочленов. */
Polynomial& Polynomial::operator-=(const Polynomial& rhs) 
{
    if (deg() <= rhs.deg()) 
        coeff.resize(rhs.coeff.size());
    
    for (size_t i = 0; i <= rhs.deg(); i++)
        coeff[i] -= rhs.coeff[i];

    strip();

    return *this;
}

/** @brief MUL_PQ_P - Умножает многочлен на число. */
Polynomial operator*(const Polynomial& lhs, const Rational& rhs) 
{
    if (!rhs)
        return Polynomial();

    Polynomial res(lhs);
    if (rhs != Rational(1))
    {
        for (size_t i = 0; i <= lhs.deg(); i++)
            res.coeff[i] = lhs.coeff[i] * rhs;
    }

    return res;
}

/** @brief MUL_PQ_P - Умножает многочлен на число. */
Polynomial& Polynomial::operator*=(const Rational& rhs) 
{
    if (!rhs) 
    {
        coeff.resize(1);
        coeff[0] = Rational();
    }
    else if (rhs != Rational(1))
    {
        for (auto& c : coeff)
            c *= rhs;
    }

    return *this;

}

/** @brief MUL_PP_P - Вычисляет произведение двух многочленов. */
Polynomial operator*(const Polynomial& lhs, const Polynomial& rhs) 
{
    Polynomial res;
    res.coeff.resize(lhs.coeff.size() + rhs.coeff.size());

    for (size_t i = 0; i <= lhs.deg(); ++i) {
        for (size_t j = 0; j <= rhs.deg(); ++j) {
            res.coeff[i + j] += lhs.coeff[i] * rhs.coeff[j];
        }
    }

    res.strip();
    return res;
}

/** @brief MUL_PP_P - Вычисляет произведение двух многочленов. */
Polynomial& Polynomial::operator*=(const Polynomial& rhs) 
{
    *this = *this * rhs;
    return *this; 
}

/** @brief DIV_PP_P - Вычисляет частное от деления многочлена на многочлен при делении с остатком. */
Polynomial operator/(const Polynomial& lhs, const Polynomial& rhs) 
{
    if (!rhs.lead())
        throw std::runtime_error("cannot div from a null");

    Polynomial K;

    if (lhs.deg() >= rhs.deg())
    {
        Polynomial P(lhs);
        K.coeff.resize(P.deg() - rhs.deg() + 1);

        for (ssize_t p = P.deg() - rhs.deg(); p >= 0; p--) 
        {
            Rational c = P.lead() / rhs.lead();
            K.coeff[p] = c;

            P -= (rhs << p) * c;
            P.strip();
        }
    }

    return K;
}

/** @brief DIV_PP_P - Вычисляет частное от деления многочлена на многочлен при делении с остатком. */
Polynomial& Polynomial::operator/=(const Polynomial& rhs) 
{
    *this = *this / rhs;
    return *this;
}

/** @brief MOD_PP_P - Вычисляет остаток от деления многочлена на многочлен при делении с остатком. */
Polynomial operator%(const Polynomial& lhs, const Polynomial& rhs) 
{
    Polynomial res(lhs);
    return res %= rhs;
}

/** @brief MOD_PP_P - Вычисляет остаток от деления многочлена на многочлен при делении с остатком. */
Polynomial& Polynomial::operator%=(const Polynomial& rhs) 
{
    if (!rhs.lead())
        throw std::runtime_error("cannot divide by zero");

    for (ssize_t p = deg() - rhs.deg(); p >= 0; p--)
    {
        Rational c = lead() / rhs.lead();
        
        *this -= (rhs << p) * c;
        strip();
    }

    return *this;
}

std::string Polynomial::asString()
{
    std::stringstream ss;
    ss << *this;
    return ss.str();
}

std::ostream& operator<<(std::ostream& os, const Polynomial& polynomial)
{
    bool has_x = false;
    bool first = true;
    for (size_t i = 1; i < polynomial.coeff.size(); i++) {
        if ((bool)polynomial.coeff[i]) {
            has_x = true;
            break;
        }
    }

    if ((bool)polynomial.coeff[0] || !has_x) {
        os << polynomial.coeff[0];
        first = false;
    }

    for (size_t i = 1; i < polynomial.coeff.size(); i++) {
        Rational coeff = polynomial.coeff[i];
        if (!coeff) {
            continue;
        }

        bool is_negative = (sign(coeff) == -1);

        if (!first) {
            os << (is_negative ? " - " : " + ");
            if (is_negative) coeff *= Rational(-1);
        }
        else {
            first = false;
            if (is_negative) {
                coeff *= Rational(-1);
                os << "-";
            }
        }

        if (coeff != Rational(1)) {
            os << coeff;
        }

        os << "x";
        if (i != 1) {
            os << '^' << i;
        }
    }
    return os;
}

std::istream& operator>>(std::istream& is, Polynomial& polynomial)
{
    polynomial.coeff.resize(1);
    polynomial.coeff[0] = Rational();

    char c;
    bool sign = false;

    is >> c;
    if (c == '-')
        sign = true;
    else
        is.unget();

    while (true) {
        int power = 0;
        Rational coeff;

        try {
            is >> coeff;
        }
        catch (std::runtime_error &e) {
            coeff = Rational(1);
        }

        is >> c;
        if (c == 'x') {
            power = 1;
            is >> c;
            if (c == '^') {
                is >> power;
            }
            else is.unget();
        }
        else is.unget();

        polynomial.resizeAtLeast(power + 1);
        if (sign) polynomial.coeff[power] -= coeff;
        else      polynomial.coeff[power] += coeff;
        
        c = '\0';
        is >> c;
        if (c == '-') sign = true;
        else if (c == '+') sign = false;
        else {
            is.unget();
            break;
        }
    }

    polynomial.strip();
    return is;
}

Polynomial Polynomial::factorize() 
{
    Polynomial polynomial(*this);

    if (deg())
    {
        Natural general_lcm = polynomial.lead().get_denominator(); 
        for (auto& c : polynomial.coeff) 
        {
            general_lcm = leastCommMul(general_lcm, c.get_denominator()); 
        }
    
        Natural general_gcd = abs(polynomial.lead().get_numerator());
        for (auto& c : polynomial.coeff) 
        {
            c *= Rational(general_lcm);
            general_gcd = greatCommDiv(general_gcd, abs(c.get_numerator()));
        }

        for (auto& c : polynomial.coeff)
            c /= Rational(general_gcd);

        if (polynomial.lead().get_numerator() < Integer(0))
            polynomial *= Rational(-1);
    }

    return polynomial;
}

Polynomial gcd(const Polynomial &lhs, const Polynomial &rhs)
{
    Polynomial left(lhs), right(rhs);

    while (left.lead() && right.lead())
    {
        if (left.deg() > right.deg())
            left %= right;
        else 
            right %= left;
    } 
  
    Polynomial res = (left + right).factorize();
    return res;
}

Polynomial Polynomial::nmr() {
    if (deg() > 1)
        return *this / gcd(*this, this->derivative());
    
    return Polynomial(*this);
}

