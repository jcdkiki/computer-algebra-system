/**
 * @file rational.hpp
 * @brief Содержит класс Rational 
 */

#ifndef CAS_NUMBERS_RATIONAL_HPP_
#define CAS_NUMBERS_RATIONAL_HPP_

#include "natural.hpp"
#include "integer.hpp"
#include <cstring>

/**
 * @brief Длинное Рациональное число.
 *
 * Числитель имеет тип Integer, знаменатель имеет тип Natural.
 * Для этого класса перегружены основные арифметические операторы, что позволяет красиво записывать различные вычисления.
 * Также для этого класса перегружены операторы ввода/вывода.
 */
class Rational {
    Integer numerator;
    Natural denominator;
public:

    /** @brief Создает новое рациональное число, равное нулю */
    Rational();

    /**
     * @brief Создает новое рациональное число из строки
     * 
     * Примеры корректного ввода:
     *  - \c "5/9"
     *  - \c "-100/11"
     *  - \c "5/1"
     *  - \c "123"
     */
    explicit Rational(const char *str);

    /** @brief Возвращает строковое представление числа */
    std::string asString();

    /** @brief Возвращает числитель числа */
    Integer get_numerator() { return numerator; }

    /** @brief Возвращает делитель числа */
    Natural get_denominator() { return denominator; }

    /**
     * @brief Вычислляет НОД
     * @param[in] numerator,denominator Ссылки класса натурального и целого цисла
     * @returns Возвращает НОД в виде строки
     */
    Natural greatest_common_divisor(const Integer& numerator, const Natural& denominator);

    /**
     * @brief RED_Q_Q - Сокращение дроби
    */
    void reduce();
    
    /**
     * @brief ADD_QQ_Q - Сложение двух дробей
     * @param[in] lhs,rhs - Левый и правый операнд
     * @returns Cумму двух чисел
     */
    friend Rational operator+(const Rational& lhs, const Rational& rhs);

    /**
     * @brief SUB_QQ_Q - Вычитание двух дробей
     * @param[in] lhs,rhs - Левый и правый операнд
     * @returns Разность двух чисел
     */
    friend Rational operator-(const Rational& lhs, const Rational& rhs);

    /**
     * @brief MUL_QQ_Q - Умножение двух дробей
     * @param[in] lhs,rhs - Левый и правый операнд
     * @returns Возвращает текущий объект
     */
    friend Rational operator*(const Rational& lhs, const Rational& rhs);

    /**
     * @brief ADD_QQ_Q - Прибавляет рационального числа
     * @param[in] rhs - Число, которое нужно прибавить
     * @returns Результат прибавления
     */
    Rational& operator+=(const Rational& rhs);

    /**
     * @brief SUB_QQ_Q - Вычитание рационального числа
     * @param[in] rhs - Число, которое нужно отнять
     * @returns Разность двух чисел
     */
    Rational& operator-=(const Rational& rhs);

    /**
     * @brief SUB_QQ_Q - Умножение двух дробей
     * @param[in] rhs - Число, на уоторе нужно умножить
     * @returns Произведение двух чисел
     */
    Rational& operator*=(const Rational& rhs);


    friend std::ostream& operator<<(std::ostream& os, const Rational& number);
    friend std::istream& operator>>(std::istream& is, Rational& number);
};

/**
 * @brief Выводит рациональное число в поток вывода
 * 
 * @param os            Поток вывода, в который будет выведено число
 * @param[in] number    Число, которое будет выведено
 */
std::ostream& operator<<(std::ostream& os, const Rational& number);

/**
 * @brief Вводит рациональное число из потока ввода
 * 
 * @param is            Поток ввода, из которого будет введено число
 * @param[out] number   Ссылка на число, в которое будет записан результат
 */
std::istream& operator>>(std::istream& is, Rational& number);

#endif