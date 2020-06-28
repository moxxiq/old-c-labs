//
// Created by mox on 22.03.19.
//
///\file

#ifndef INC_5_LAB_FUNCTIONS_H
#define INC_5_LAB_FUNCTIONS_H

#define clear() printf("\033[H\033[J")

/**
 * \brief Отримує від користувача ввід, перед яким виводить повідомлення
 * @param message Повідомлення, яке буде показане користувачу
 * @return Ввід користувача в форматі \c char[]
 */
char *message_input(char message[]);
/**
 * \brief Перевірка чи кожне введене число є десятковим (від'ємним також)
 * @param str число у вигляді увеного масиву char
 * @return 1, якщо число десяткове, 0 якщо ні
 */
int is_every_digit(char *str);
/**
 * \brief Перевірка чи кожне введене число є дробовим (від'ємним також)
 * @param str число у вигляді увеного масиву char
 * @return 1, якщо число дробове, 0 якщо ні
 */
int is_every_digit_double(char *str);
/**
 * \brief Функція, що повторює задану їй функцію за бажанням користувача.
 * @param func Функція, яка буде повторюватись
 * @param message Повідомлення до користувача
 * @param pow_10_to
 */
void to_repeat(void (*func)(void), char message[]);
/**
 * \brief Реалізація корректного введення цілих десяткових чисел користувачем
 * @param message Повідомлення до користувача
 * @param number Змінна в яку буде записуватися правильний ввід
 * @param lwr_border Нижня межа
 * @param hir_border Верхня межа
 */
void input_int(char message[], int *number,int lwr_border, int hir_border);
/**
 * \brief Реалізація корректного введення десяткових дійсних чисел користувачем
 * @param message Повідомлення до користувача
 * @param number Змінна в яку буде записуватися правильний ввід
 * @param lwr_border Нижня межа
 * @param hir_border Верхня межа
 */
void input_long_double(char message[], long double *number,long double lwr_border, long double hir_border);
/**
 * \brief Обмін двох аргументів
 * @param first Адреса першого аргументу
 * @param second Адреса другого аргумент
 */
void swap_int(int *first, int *second);
/**
 * \brief toupper to every char in \c str
 * \details code goes here
 * @param str input string
 */
void toupper_chrs(char str[]);

#endif //INC_5_LAB_FUNCTIONS_H
