/**
 * @file rational.hpp
 * @brief Содержит класс Rational 
 */

#ifndef CAS_NUMBERS_RATIONAL_HPP_
#define CAS_NUMBERS_RATIONAL_HPP_

#include "natural.hpp"
#include "integer.hpp"

/**
 * @brief Длинное Рациональное число.
 *
 * Числитель имеет тип Integer, знаменатель имеет тип Natural.
 * Для этого класса перегружены основные арифметические операторы, что позволяет красиво записывать различные вычисления.
 * Также для этого класса перегружены операторы ввода/вывода.
 *
 * @author Кашечкин Олег (гр. 3384)
 */
class Rational {
    Integer numerator;
    Natural denominator;
public:

    /** @brief Создает новое рациональное число, равное нулю */
    Rational();


    /**
     * @brief TRANS_Z_Q - преобразование целого в дробное
     * @param[in] number - целое число
     */
    explicit Rational(Integer number) : numerator(number), denominator("1") { }

    /**
     * @brief Создает новое рациональное число
     * @param[in] numerator - числитель
     * @param[in] denominator - знаменатель
     */
    explicit Rational(const Integer &numerator, const Natural &denominator);

    /**
     * @brief Создает новое рациональное число
     * @param[in] numerator - числитель
     * @param[in] denominator - знаменатель
     */
    explicit Rational(int numerator, unsigned int denominator = 1);

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
    Integer get_numerator() const { return numerator; }

    /** @brief Возвращает знаменатель числа */
    Natural get_denominator() const { return denominator; }

    /**
     * @brief RED_Q_Q - Сокращение дроби
    */
    void reduce();

    /** @brief TRANS_Q_Z Создает новое целое число из рационального (если знаменатель равен 1)
     *  @returns возвращает копию числа
    */
    operator Integer();
    
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
     * @brief DIV_QQ_Q - Деление двух дробей
     * @param[in] lhs,rhs - Левый и правый операнд
     * @returns Возвращает текущий объект
     */
    friend Rational operator/(const Rational& lhs, const Rational& rhs);

    /**
     * @brief ADD_QQ_Q - Прибавляет рационального числа
     * @param[in] rhs - Число, которое нужно прибавить
     * @returns Результат прибавления
     */
    Rational& operator+=(const Rational& rhs);

    /**
     * @brief SUB_QQ_Q - Вычитание рационального числа
     * @param[in] rhs - Число, которое нужно отнять
     * @returns Результат вычитания
     */
    Rational& operator-=(const Rational& rhs);

    /**
     * @brief SUB_QQ_Q - Умножение двух дробей
     * @param[in] rhs - Число, на которое нужно умножить
     * @returns Произведение двух чисел
     */
    Rational& operator*=(const Rational& rhs);

    /**
     * @brief DIV_QQ_Q - Деление двух дробей
     * @param[in] rhs - Правый операнд в деления
     * @returns Возвращает текущий объект
     */
    Rational& operator/=(const Rational& rhs);

    /**
     * @brief INT_Q_B - Проверка сокращенного дробного на целое
     * @returns Возвращает значения буливое значение
     */
    bool isInteger();

    /**
     * @brief Проверяет, равно ли число нулю.
     * 
     * @return true, если число не равно нулю.
     * @return false, если число равно нулю.
     */
    explicit operator bool() const;

    /** @name Операторы сравнения
     * @param[in] this,rhs Сравниваемые числа
     * @returns true, если условие верно
     * @returns в противном случае false
     */
    ///@{

    /** @brief Два числа равны */
    friend bool operator==(const Rational &lhs, const Rational &rhs);

    /** @brief Два числа не равны */
    friend bool operator!=(const Rational &lhs, const Rational &rhs);
    
    ///@}

    /**
     * @brief Проверяет положительность числа.
     * 
     * @param number    число.
     * @returns 1, если число больше нуля
     * @returns 0, елси число равно нулю
     * @returns -1, если число меньше нуля
     */
    friend int sign(const Rational &number);

    /** @brief Создает рациональное число с противоположным знаком. */
    Rational operator-();

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
