/**
 * @file polynomial.hpp
 * @brief Содержит класс Polynomial 
 */

#ifndef CAS_NUMBERS_POLYNOMIAL_HPP_
#define CAS_NUMBERS_POLYNOMIAL_HPP_

#include <vector>
#include <string>
#include <istream>
#include <ostream>
#include <sstream>

#include "rznumbers/rational.hpp"

/**
 * @brief Многочлен с рациональными коэффициетнами.
 *
 * Использует \c std::vector для хранения коэффициентов.
 * Для этого класса перегружены основные арифметические операторы, что позволяет красиво записывать различные вычисления.
 * Также перегружены операторы ввода и вывода, позволяющие в красивой форме вводить и выводить многочлены. 
 */
class Polynomial {
    std::vector<Rational> coeff;

    /** @brief При необходимости расширяет вектор коэффициентов до размера \a size */
    void resizeAtLeast(size_t size)
    {
        if (coeff.size() < size) {
            coeff.resize(size);
        }
    }

    /** @brief Удаляет лидирующие нули */
    void strip()
    {
        for (size_t i = coeff.size() - 1; i > 0; i--) { // don`t touch free term
            if (coeff[i]) {
                coeff.resize(i + 1);
                return;
            }
        }

        coeff.resize(1);
    }

public:
    /** @brief Создает новый многочлен, равный нулю */
    Polynomial() : coeff(1) {}

    /** @brief Создает новый многочлен из строки
     * 
     * Примеры корректного ввода для многочлена с целочисленными коэффициентами:
     *  - \c "100"
     *  - \c "0"
     *  - \c "100x"
     *  - \c "0x^2"
     *  - \c "13x^1000"
     *  - \c "x^3 + 3x + 100x^40 + 5x^30"
     *  - \c "(5)x^5 + 7x^6 + (8)x^10"
     *  - \c "-10x - 3x^2"
     *  - \c "5 + 2 + 3x + 5x"
     *  - \c "5 - 2 + 3x - 5x"
     */
    Polynomial(const char *str)
    {
        std::stringstream ss;
        ss << str;
        ss >> *this;
    }

    /**
     * @brief Создает моном.
     * 
     * @param[in] coeff Коэффициент монома. 
     * @param[in] power Степень монома.
     */
    Polynomial(const Rational& coeff, int power) : coeff(power + 1)
    {
        this->coeff[power] = coeff;
    }

    /** @brief LED_P_Q - Возвращает старший коэффициент многочлена. */
    const Rational& lead() const
    {
        return coeff.back();
    }
    
    /** @brief DEG_P_N - Возвращает степень многочлена. */
    size_t deg() const
    {
        return coeff.size() - 1;
    }

    /** @brief ADD_PP_P - Вычисляет сумму двух многочленов. */
    friend Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs) 
    {
        Polynomial res(lhs);
        return res += rhs;
    }

    /** @brief ADD_PP_P - Вычисляет сумму двух многочленов. */
    Polynomial& operator+=(const Polynomial& rhs) 
    {
        if (deg() <= rhs.deg()) 
            coeff.resize(rhs.coeff.size());
        
        for (size_t i = 0; i <= rhs.deg(); i++)
            coeff[i] += rhs.coeff[i];

        strip();

        return *this;
    }
    
    /** @brief MUL_Pxk_P - Умножает многочлен на x^k. */
    friend Polynomial operator<<(const Polynomial& lhs, size_t rhs) 
    {
        Polynomial res(lhs);
        return res <<= rhs;
    }

    /** @brief MUL_Pxk_P - Умножает многочлен на x^k. */
    Polynomial& operator<<=(size_t rhs) 
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
    Polynomial derivative(unsigned int k = 1) const 
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
    friend Polynomial operator-(const Polynomial& lhs, const Polynomial& rhs) 
    {
        Polynomial res(lhs);
        return res -= rhs; 
    }

    /** @brief SUB_PP_P - Вычисляет разность двух многочленов. */
    Polynomial& operator-=(const Polynomial& rhs) 
    {
        if (deg() <= rhs.deg()) 
            coeff.resize(rhs.coeff.size());
        
        for (size_t i = 0; i <= rhs.deg(); i++)
            coeff[i] -= rhs.coeff[i];

        strip();

        return *this;
    }

    /** @brief MUL_PQ_P - Умножает многочлен на число. */
    friend Polynomial operator*(const Polynomial& lhs, const Rational& rhs) 
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
    Polynomial& operator*=(const Rational& rhs) 
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
    friend Polynomial operator*(const Polynomial& lhs, const Polynomial& rhs) 
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
    Polynomial& operator*=(const Polynomial& rhs) 
    {
        *this = *this * rhs;
        return *this; 
    }

    /** @brief DIV_PP_P - Вычисляет частное от деления многочлена на многочлен при делении с остатком. */
    friend Polynomial operator/(const Polynomial& lhs, const Polynomial& rhs) 
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
    Polynomial& operator/=(const Polynomial& rhs) 
    {
        *this = *this / rhs;
        return *this;
    }

    /** @brief MOD_PP_P - Вычисляет остаток от деления многочлена на многочлен при делении с остатком. */
    friend Polynomial operator%(const Polynomial& lhs, const Polynomial& rhs) 
    {
        Polynomial res(lhs);
        return res %= rhs;
    }

    /** @brief MOD_PP_P - Вычисляет остаток от деления многочлена на многочлен при делении с остатком. */
    Polynomial& operator%=(const Polynomial& rhs) 
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

    /** @brief Возвращает строковое представление многочлена */
    std::string asString()
    {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    /**
     * @brief Выводит многочлен в поток вывода
     * 
     * @param os                Поток вывода, в который будет выведен многочлен
     * @param[in] polynomial    Многочлен, который будет выведет в поток вывода
     */
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& polynomial)
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
                if (is_negative) coeff = -coeff;
            }
            else {
                first = false;
                if (is_negative) {
                    coeff = -coeff;
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

    /**
     * @brief Вводит многочлен из потока ввода
     * 
     * Примеры корректного ввода для многочлена с целочисленными коэффициентами аналогичны \c Polynomial(const char *str)
     *
     * @param is                Поток ввода, из которого будет введен многочлен
     * @param[out] polynomial   Ссылка на многочлен, в который будет записан результат
     */
    friend std::istream& operator>>(std::istream& is, Polynomial& polynomial)
    {
        polynomial.coeff.resize(1);
        polynomial.coeff[0] = 0;

        char c;
        bool sign = false;

        is >> c;
        if (c == '-')
            sign = true;
        else
            is.unget();

        while (true) {
            int tmp;
            is >> tmp;
            Rational coeff(tmp);

            if (is.fail()) {
                coeff = Rational(1);
                is.clear();
            }

            is >> c;
            if (c != 'x') {
                is.unget();
                if (sign) polynomial.coeff[0] -= coeff;
                else      polynomial.coeff[0] += coeff;
            }
            else {
                is >> c;
                size_t power = 1;
                if (c == '^') {
                    is >> power;
                }
                else is.unget();

                polynomial.resizeAtLeast(power + 1);
                if (sign) polynomial.coeff[power] -= coeff;
                else      polynomial.coeff[power] += coeff;
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
