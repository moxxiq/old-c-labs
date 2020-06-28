//
// Created by mox on 22.03.19.
//
///\file

#ifndef INC_LAB_FUNCTIONS_H
#define INC_LAB_FUNCTIONS_H

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
 */
void to_repeat(void (*func)(), char message[]);
/**
 * \brief Реалізація корректного введення цілих десяткових чисел користувачем
 * @param message Повідомлення до користувача
 * @param number Змінна в яку буде записуватися правильний ввід
 * @param lwr_border Нижня межа
 * @param hir_border Верхня межа
 */
void input_int(char message[], int *number,int lwr_border, int hir_border);
/**
 * \brief Фікс input_int для забезпечення "чистої" функції
 * @param message Повідомлення до користувача
 * @param lwr_border Нижня межа
 * @param hir_border Верхня межа
 * @return правильний ввід користувача
 */
int get_int(char message[], int lwr_border, int hir_border);
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
/**
 * \brief Функція для створення меню
 * \details Друкує меню та виконує певний пункт меню, поки той не 0
 * @param n Кількість пунктів меню
 * @param ... Почерговий перелік тексту пункту та функції, що їх виконують.
 * \warning Функції, що виконують відповідні пункти меню потинні повертати \c int , так як будуть виконуватись допоки їх результат буде ненульовий
 * @return Вибраний пункт меню
 */
int menu(int n, ...);
#endif //INC_LAB_FUNCTIONS_H
