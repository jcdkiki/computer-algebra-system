/**
 * @file polynomial.hpp
 * @brief Содержит класс Polynomial 
 */

#ifndef CAS_NUMBERS_POLYNOMIAL_HPP_
#define CAS_NUMBERS_POLYNOMIAL_HPP_

#include <list>
#include <string>
#include <istream>
#include <ostream>
#include <sstream>

/**
 * @brief Многочлен.
 *
 * Использует \c std::list для хранения мономов, представленных структурой Monomial.
 * Для этого класса перегружены основные арифметические операторы, что позволяет красиво записывать различные вычисления.
 * Также перегружены операторы ввода и вывода, позволяющие в красивой форме вводить и выводить многочлены.
 * 
 * @tparam T                Тип, используемый для коэффициентов.
 * @tparam zero             Значение коэффициента по умолчанию, тождественен нулю.
 * @tparam one              Значение коэффициента, тождественнен единице, который не будет выводиться при использовании оператора << или метода asString().
 */
template<class T, T zero, T one>
class Polynomial {

    /**
     * @brief Одночлен от одной переменной 'x'.
     *
     * Содержит информацию о коэффициенте и степени одночлена.
     */
    struct Monomial {
        int power;
        T coeff;

        Monomial() {}
        Monomial(int power, T coeff) : power(power), coeff(coeff) {}
    };

    std::list<Monomial> monoms;
 
public:
    /** @brief Создает новый многочлен, равный нулю. */
    Polynomial() : monoms(1, Monomial(0, zero)) {}

    /** @brief Создает новый многочлен из строки.
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

    /** @brief Возвращает степень полинома. */
    int deg() 
    {
        return monoms.back().power;
    }

    /** @brief Возвращает старший коэффициент полинома. */
    T lead() 
    {
        return monoms.back().coeff;
    }

    /** @brief Возвращает строковое представление многочлена. */
    std::string asString()
    {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    /**
     * @brief Выводит многочлен в поток вывода.
     * 
     * @param os                Поток вывода, в который будет выведен многочлен.
     * @param[in] polynomial    Многочлен, который будет выведет в поток вывода.
     */
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& polynomial)
    {
        bool has_x = false;
        bool first = true;


        for (auto& m : polynomial.monoms) {
            if (m.power != 0) {
                has_x = true;
                break;
            }
        }


        if (polynomial.monoms.front().coeff != 0 || !has_x) {
            os << polynomial.monoms.front().coeff;
            first = false;
        }

        auto iter = polynomial.monoms.begin();
        ++iter;
        while (iter != polynomial.monoms.end()) {
            T coeff = iter->coeff;
            
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
            if (iter->power != 1) {
                os << '^' << iter->power;
            }

            ++iter;
        }

        return os;
    }

    /**
     * @brief Вводит многочлен из потока ввода.
     * 
     * Примеры корректного ввода для многочлена с целочисленными коэффициентами аналогичны \c Polynomial(const char *str).
     *
     * @throws std::invalid_argument если используется форма коэффициентов со скобками и не будет найдена закрывающаяся скобка
     *
     * @param is                Поток ввода, из которого будет введен многочлен.
     * @param[out] polynomial   Ссылка на многочлен, в который будет записан результат, предварительно он будет очищен.
     */
    friend std::istream& operator>>(std::istream& is, Polynomial& polynomial)
    {
        polynomial.monoms.resize(1);
        polynomial.monoms.front().power = 0;
        polynomial.monoms.front().coeff = 0;

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
                polynomial.monoms.front().coeff += sign ? -coeff : coeff;
            }
            else {
                is >> c;
                int power = 1;
                if (c == '^') {
                    is >> power;
                }
                else is.unget();

                if (coeff != 0) {
                    Monomial m(power, sign ? -coeff : coeff);
                    if (polynomial.monoms.back().power < m.power)  
                        polynomial.monoms.push_back(m);
                    else {
                        for(auto iter = polynomial.monoms.begin(); iter != polynomial.monoms.end(); iter++) {
                            if (iter->power == m.power) {
                                iter->coeff += m.coeff;
                                break;
                            }
                            else if (iter->power > m.power) {
                                polynomial.monoms.insert(iter, m);
                                break;
                            }
                        }
                    }
                }
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

        return is;
    }
};

#endif
