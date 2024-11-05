/**
 * @file natural.hpp
 * @brief Содержит класс Natural 
 */

#ifndef CAS_NUMBERS_NATURAL_HPP_
#define CAS_NUMBERS_NATURAL_HPP_

#include <vector>
#include <ostream>
#include <istream>
#include <string>

/**
 * @brief Длинное натуральное число.
 *
 * Использует \c std::vector для хранения цифр. Используется десятичная система счисления.
 * Для этого класса перегружены основные арифметические операторы, что позволяет красиво записывать различные вычисления.
 * 
 * @authors Берлет Максим (гр. 3384)
 */

/** @brief оператор преобразования должен знать о классе, чтобы в него преобразовывать*/
class Natural {
public:
    using Digit = char;         /**< Тип цифры */
private:
    std::vector<Digit> digits;  /**< Вектор цифр */

    /** @brief Убирает незначащие нули */
    void strip();

public:
    /** @brief Основание системы счисления */
    constexpr static int BASE = 10;

    /** @brief Создает новое натуральное число, равное нулю. */
    Natural();

    /** @brief Создает новое натуральное число из строки */
    explicit Natural(const char *str);
    
    /** @brief Преобразует натуральное число в его строковое представление */
    std::string asString();

    friend std::ostream& operator<<(std::ostream& os, const Natural& number);
    friend std::istream& operator>>(std::istream& is, Natural& number);
    friend Natural operator+(const Natural &lhs, const Natural &rhs);
    friend Natural operator-(const Natural &lhs, const Natural &rhs);
    friend Natural getDivDigitInPower(const Natural &lhs, const Natural &rhs);

    /**
     * @brief SUB_NN_N - Вычисляет разность двух натуральных чисел
     * @param[in] number Вычитаемое число
     * @returns Разность, которая сохраняется в текущем левом числе
     */
    Natural& operator-=(const Natural &number);

    /** @brief Префиксный декремент */
    Natural& operator--();

    /** @brief Постфиксный декремент */
    Natural operator--(int); 

    /**
     * @brief ADD_NN_N - Прибавляет натуральное число
     * @param[in] n Число, которое нужно прибавить
     * @returns Результат прибавления \a n
     */
    Natural& operator+=(const Natural &n);
    
    /**
     * @brief ADD_1N_N - Увеличивает натуральное число на единицу
     * @returns Себя \b после увеличения
     */
    Natural& operator++();

    /**
     * @brief ADD_1N_N - Увеличивает натуральное число на единицу
     * @returns Себя \b перед увеличением
     */
    Natural operator++(int);

    /**
     * @brief COM_NN_D - Сравнивает два натуральных числа
     * @param[in] n1,n2 Сравниваемые числа
     * @returns 0, если n1 == n2
     * @returns 1, если n1 < n2
     * @returns 2, если n1 > n2
     */
    static int cmp(const Natural &n1, const Natural &n2);

    /**
     * @brief MUL_ND_N - Умножение натурального числа на цифру.
     * @param[in] digit - Цифра, на которую умножаем.
     * @returns Возвращает натуральное число умноженное на цифру. Создается копия.
     */
    Natural operator*(const Natural::Digit& digit) const;

    /**
     * @brief Возвращает натуральное число умноженное на цифру. Не создается копия.
     */
    Natural &operator*=(const Natural::Digit& digit);

    /**
     * @brief MUL_Nk_N - Умножает натуральное число на 10^k. Не создает копию.
     * @param[in] k - Натуральное число, степень 10.
     * @returns Возвращает натуральное число, умноженное на 10^k.
     */
    Natural &mul_by_10_in_k(size_t k);

    /**
     * @brief Аналог битового сдвига для натуральных чисел с основанием 10. Создает копию.
     */
    Natural operator<<(size_t k) const;

    /**
     * @brief Аналог битового сдвига для натуральных чисел с основанием 10. Не создает копию.
     */
    Natural &operator<<=(size_t k);

    friend Natural operator*(const Natural &lhs, const Natural &rhs);
    /**
     * @brief MUL_NN_N - Вычисляет произведение двух натуральных чисел
     * @param[in] number Число, на которое мы умножаем наше текущее
     * @returns Произведение, которое сохраняется в текущую переменную
     */
    Natural operator*=(const Natural &number);
    
    /**
     * @brief NZER_N_B - Выполняет проверку на ноль
     * @returns true, если число не равно нулю.
     * @returns false, если число равно нулю. 
     */
    operator bool() const;

    /** @name Операторы сравнения (обёртка над методом cmp)
     * @param[in] this,rhs Сравниваемые числа
     * @returns true, если условие верно
     * @returns в противном случае false
     */
    ///@{
    /** @brief Два числа равны */
    bool operator==(const Natural &rhs) const;
    
    /** @brief Два числа не равны */
    bool operator!=(const Natural &rhs) const;
    
    /** @brief Первое число больше второго */
    bool operator>(const Natural &rhs) const;
    
    /** @brief Первое число меньше второго */
    bool operator<(const Natural &rhs) const;
    
    /** @brief Первое число больше либо равно второго */
    bool operator>=(const Natural &rhs) const;
    
    /** @brief Первое число меньше либо равно второго */
    bool operator<=(const Natural &rhs) const;
    ///@}
};

/**
 * @brief Выводит натуральное число в поток вывода
 * 
 * @param os            Поток вывода, в который будет выведено число
 * @param[in] number    Число, которое будет выведено
 */
std::ostream& operator<<(std::ostream& os, const Natural& number);

/**
 * @brief Вводит натуральное число из потока ввода
 * 
 * @param is            Поток ввода, из которого будет введено число
 * @param[out] number   Ссылка на число, в которое будет записан результат
 */
std::istream& operator>>(std::istream& is, Natural& number);

/**
 * @brief ADD_NN_N - Вычисляет сумму двух натуральных чисел
 * @param[in] lhs,rhs Складываемые числа
 * @returns Cумму двух чисел
 */
Natural operator+(const Natural &lhs, const Natural &rhs);

/**
 * @brief MUL_NN_N - Вычисляет произведение двух натуральных чисел
 * @param[in] lhs,rhs Умножаемые числа
 * @returns Произведение двух чисел
 */
Natural operator*(const Natural &lhs, const Natural &rhs);

/**
 * @brief SUB_NN_N - Вычисляет разность двух натуральных чисел
 * @param[in] lhs,rhs Вычитаемые числа
 * @returns Разность двух чисел
 */
Natural operator-(const Natural &lhs, const Natural &rhs);

/**
 * @brief DIV_NN_Dk - Вычисляет первую цифру деления большего натурального на меньшее, домноженное на 10^k
 * @param[in] lhs,rhs Делимое и делитель
 * @returns Первая цифра деления, домноженная на 10^k
 */
Natural getDivDigitInPower(const Natural &lhs, const Natural &rhs);

#endif
