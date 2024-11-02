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

/**
 * @brief Многочлен.
 *
 * Использует \c std::vector для хранения коэффициентов.
 * Для этого класса перегружены основные арифметические операторы, что позволяет красиво записывать различные вычисления.
 * Также перегружены операторы ввода и вывода, позволяющие в красивой форме вводить и выводить многочлены.
 * 
 * @tparam T                Тип, используемый для коэффициентов
 * @tparam zero             Значение коэффициента по умолчанию. Для чисел должен быть равен нулю
                            (если вы конечно не упоролись чем-нибудь)
 * @tparam one              Значение коэффициента, который не будет выводиться при использовании оператора << или метода asString().
                            Для чисел может быть равен, например, единице.
 */
template<class T, T zero, T one>
class Polynomial {
    std::vector<T> coeff;

    /** @brief При необходимости расширяет вектор коэффициентов до размера \a size */
    void resizeAtLeast(size_t size)
    {
        if (coeff.size() < size) {
            coeff.resize(size, zero);
        }
    }

    /** @brief Удаляет лидирующие нули */
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
    /** @brief Создает новый многочлен, равный нулю */
    Polynomial() : coeff(1, zero) {}

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

            if (coeff != one) {
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
                coeff = one;
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