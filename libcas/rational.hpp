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
     * @brief рекурсивно вычислляет НОД (вспомогательная функция)
     * @param[in] numerator,denominator Ссылки класса натурального и целого цисла
     * @returns Возвращает вычисленую НОД в виде одного из классов
     */
    Integer gcd_recursive(const Integer& numerator, const Integer& denominator);

    /**
     * @brief Вычислляет НОД и преобразовывает её
     * @param[in] numerator,denominator Ссылки класса натурального и целого цисла
     * @returns Возвращает НОД в виде строки
     */
    const char* greatest_common_divisor(const Integer& numerator, const Natural& denominator);

    /**
     * @brief RED_Q_Q - Сокращение дроби
    */
    void reduce();

    /**
     * @brief Вспомогательная функция для конвертирования натурального в целое
    */
    Integer convert_denominator_to_integer(const Rational& other) const { return Integer(other.denominator); }

    /**
     * @brief ADD_QQ_Q - Сложение двух дробей
     * @param[in] other - Правый операнд в сложении
     * @returns Возвращает текущий объект
     */
    Rational& operator+(const Rational& other);

    /**
     * @brief SUB_QQ_Q - Вычитание двух дробей
     * @param[in] other - Правый операнд в вычитании
     * @returns Возвращает текущий объект
     */
    Rational& operator-(const Rational& other);

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
