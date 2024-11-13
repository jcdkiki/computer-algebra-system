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
    void resizeAtLeast(size_t size);

    /** @brief Удаляет лидирующие нули */
    void strip();

public:
    /** @brief Создает новый многочлен, равный нулю */
    Polynomial();

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
    Polynomial(const char *str);

    /**
     * @brief Создает моном.
     * 
     * @param[in] coeff Коэффициент монома. 
     * @param[in] power Степень монома.
     */
    Polynomial(const Rational& coeff, int power);

    /** @brief LED_P_Q - Возвращает старший коэффициент многочлена. */
    const Rational& lead() const;
    
    /** @brief DEG_P_N - Возвращает степень многочлена. */
    size_t deg() const;

    /** @brief ADD_PP_P - Вычисляет сумму двух многочленов. */
    friend Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs);

    /** @brief ADD_PP_P - Вычисляет сумму двух многочленов. */
    Polynomial& operator+=(const Polynomial& rhs);
    
    /** @brief MUL_Pxk_P - Умножает многочлен на x^k. */
    friend Polynomial operator<<(const Polynomial& lhs, size_t rhs);

    /** @brief MUL_Pxk_P - Умножает многочлен на x^k. */
    Polynomial& operator<<=(size_t rhs);
    
    /** @brief DER_P_P - Взятие k-ой производной от многочлена. */
    Polynomial derivative(unsigned int k = 1) const;

    /** @brief SUB_PP_P - Вычисляет разность двух многочленов. */
    friend Polynomial operator-(const Polynomial& lhs, const Polynomial& rhs);

    /** @brief SUB_PP_P - Вычисляет разность двух многочленов. */
    Polynomial& operator-=(const Polynomial& rhs);

    /** @brief MUL_PQ_P - Умножает многочлен на число. */
    friend Polynomial operator*(const Polynomial& lhs, const Rational& rhs);

    /** @brief MUL_PQ_P - Умножает многочлен на число. */
    Polynomial& operator*=(const Rational& rhs);

    /** @brief MUL_PP_P - Вычисляет произведение двух многочленов. */
    friend Polynomial operator*(const Polynomial& lhs, const Polynomial& rhs);

    /** @brief MUL_PP_P - Вычисляет произведение двух многочленов. */
    Polynomial& operator*=(const Polynomial& rhs);

    /** @brief DIV_PP_P - Вычисляет частное от деления многочлена на многочлен при делении с остатком. */
    friend Polynomial operator/(const Polynomial& lhs, const Polynomial& rhs);

    /** @brief DIV_PP_P - Вычисляет частное от деления многочлена на многочлен при делении с остатком. */
    Polynomial& operator/=(const Polynomial& rhs);

    /** @brief MOD_PP_P - Вычисляет остаток от деления многочлена на многочлен при делении с остатком. */
    friend Polynomial operator%(const Polynomial& lhs, const Polynomial& rhs);

    /** @brief MOD_PP_P - Вычисляет остаток от деления многочлена на многочлен при делении с остатком. */
    Polynomial& operator%=(const Polynomial& rhs);

    /** @brief Возвращает строковое представление многочлена */
    std::string asString();

    /**
     * @brief Выводит многочлен в поток вывода
     * 
     * @param os                Поток вывода, в который будет выведен многочлен
     * @param[in] polynomial    Многочлен, который будет выведет в поток вывода
     */
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& polynomial);

    /**
     * @brief Вводит многочлен из потока ввода
     * 
     * Примеры корректного ввода для многочлена с целочисленными коэффициентами аналогичны \c Polynomial(const char *str)
     *
     * @param is                Поток ввода, из которого будет введен многочлен
     * @param[out] polynomial   Ссылка на многочлен, в который будет записан результат
     */
    friend std::istream& operator>>(std::istream& is, Polynomial& polynomial);

    /** @brief FAC_P_Q - Выносит рациональную часть из многочлена, делая коэффициенты целыми, старший член положительным. */
    Polynomial factorize();

    /** @brief GCF_PP_P - Вычисляет НОД двух многочленов. */
    friend Polynomial gcd(const Polynomial &lhs, const Polynomial &rhs);

    /** @brief NMR_P_P - Возвращает многочлен буз кратных корней. */
    Polynomial nmr();
};

#endif
