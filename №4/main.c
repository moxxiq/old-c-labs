#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <values.h>
#include <ctype.h>

/**
 * Очищення екрану на UNIX системах
 */
#define clear() printf("\033[H\033[J")
///\file
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
 * \brief Повертає 10 в заданому степені \details Код наведений нижче
 * @param power Степінь десятки
 * @return 10^power
 */
long pow_10_to(int *power);
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
 * \brief Заокруглює число за математичними правилами з заданою точністю
 * @param num Число, яке необхідно заокруглити
 * @param precision Точність
 * @return Заокруглене число
 */
long double round_number (long double *num, int *precision);
/**
 * \brief Виводить усі множники числа
 * @param entered_number Число, з якого берем множники
 */
void print_dividers(int *entered_number);
/**
 * \brief Рекурсивно рахує довжину рядка
 * @param phrase Власне рядок
 * @param i Лічильник
 * @return Довжину рядка
 */
int count_length(char phrase[],int i);
/**
 * Обгортка для count_length()
 */
int get_length(char phrase[]);
/**
 * \brief Вибір підзавдання №1 \details Код функції нижче
 */
void task_1();
/**
 * \brief Виконання завдання №1 підзавдання №1
 */
void task_1_1();
/**
 * \brief Виконання завдання №1 підзавдання №2
 */
void task_1_2();
/**
 * \brief Виконання завдання №2
 */
void task_2();
int main() {
    clear();

    int choice;
    do {
        clear();
        input_int("Виберіть номер завдання (1, 2):\n",
                  &choice,
                  1,
                  2);
        switch (choice) {
            case 1:
                task_1();
                break;
            case 2:
                to_repeat(task_2, "Бажаєте продовжити виконання завдання 2?");
                break;
        }
        input_int("Бажаєте повторно виконати лабораторну?:\n", &choice, 0, 1);
    }while (choice);
    return 0;
}
void input_long_double(char message[], long double *number,long double lwr_border, long double hir_border){
    /**
     * \details Перевіряєм на належність типу та межам
     */
    if (lwr_border == hir_border){
        lwr_border = LDBL_MIN;
        hir_border = LDBL_MAX;
    }
    char *usr_input = message_input(message);
    int is_suits = sscanf(usr_input,"%Lf",number);
    while (!is_suits || (!is_every_digit_double(usr_input) && !is_every_digit(usr_input)) || *number < lwr_border || *number > hir_border){
        printf("ERROR INPUT\n");
        usr_input = message_input(message);
        is_suits = sscanf(usr_input,"%Lf",number);
    }
}
void task_1(){
    int choice;
    do {
        clear();
        input_int("Виберіть номер підзавдання (1, 2):\n",
                  &choice,
                  1,
                  2);
        switch (choice) {
            case 1:
                to_repeat(task_1_1,"Бажаєте продовжити виконання підзавдання 1?");
                break;
            case 2:
                to_repeat(task_1_2, "Бажаєте продовжити виконання підзавдання 2?");
                break;
        }
        input_int("Бажаєте повторно виконати вибір підзавдання завдання 1?:\n", &choice, 0, 1);
    }while (choice);
}
void task_1_1(){
    /**
     * \details
     * Уводим вхідні дані за допомогою функцій, що підтримують валідацію input_long_double() input_int() .\n
     * Викликаєм власну функцію заокруглення round_number() .
     * Виводим число з заданою точністю
     */
    printf("Завдання 1.1\n");
    long double entered_number;
    int precision;
    input_long_double("Введіть дійсне число\n", &entered_number, 0.0, 0.0);
    input_int("Введіть бажану точність\n", &precision, 0, INT_MAX);
    long double num = round_number(&entered_number, &precision);
    printf("%.*Lf\n", precision, num);
}
void task_1_2(){
    /**
     * \details
     * Уводим вхідні дані за допомогою функцій, що підтримують валідацію input_int() .\n
     * Виводимо дільники за допомогою print_dividers() .
     */
    printf("Завдання 1.2\n");
    int entered_number;
    input_int("Уведіть ціле додатнє число\n",&entered_number,1,INT_MAX);
    print_dividers(&entered_number);
}

void task_2(){
    /**
     * Вводимо фразу латиницею. Обчислюємо довжину рядка за допомогою get_length() та віднімаєм символ переходу на новий рядок.
     * Виводим довжину.
     */
    printf("Завдання 2\n");
    char phrase[254];
    printf("Введіть фразу (тільки латиниця (ASCII), інакше - невірний результат)\n");
    fgets(phrase, 253, stdin);
    printf("Її довжина = %d\n", get_length(phrase)-1);
}

char *message_input(char message[]){
    char *usr_input = (char*) malloc(sizeof(char)*254);
    printf("%s", message); // Виводимо повідомлення користувачу
    fgets(usr_input, 254, stdin);
    return usr_input;
}

int is_every_digit(char *str){
    /**
     * \details
     * Преревіряєм кожен символ на те, чи є він числом. Дозволяються від'ємні числа.
     */
    int len = strlen(str);
    int i = 0;
    if (atoi(str)<0) i++;// якщо менше нуля - мінус пропускаєм
    for (i; i < len-1; ++i) {
        if (!isdigit(str[i])){
            return 0;//будь-який знак - не цифра
        }
    }
    return 1;
}

int is_every_digit_double(char *str){
    /**
     * \details
     * Зчитуєм число та перевіряєм чи є воно дійсним та чи не є у нього нічого окрім цифр, знака мінус, однієї крапки
     */
    int len = strlen(str);
    long double number;
    sscanf(str,"%Lf",&number);
    int i = 0, dot_counter = 0;
    if (number<0.0) i++;// якщо менше нуля - мінус пропускаєм
    for (i; i < len-1; ++i) {
        if (!isdigit(str[i])){
            if (str[i]=='.') {
                dot_counter++;
            }else{
                return 0;//будь-який знак - не цифра або крапка (максимум 1)
            }
        }
    }
    if (dot_counter-1) return 0;
    return 1;
}

void input_int(char message[], int *number,int lwr_border, int hir_border){
    /**
     * \details Перевіряєм на належність типу та межам
     */
    if (lwr_border == hir_border){
        lwr_border = INT_MIN;
        hir_border = INT_MAX;
    }
    char *usr_input = message_input(message);
    int is_suits = sscanf(usr_input,"%d",number);
    while (!is_suits || !is_every_digit(usr_input) || *number < lwr_border || *number > hir_border){
        printf("ERROR INPUT\n");
        usr_input = message_input(message);
        is_suits = sscanf(usr_input,"%d",number);
    }
}
void to_repeat(void (*func)(void), char message[]){
    /**
     * \details
     * Викорисковуються вказівники на функцію, щоб забезпечити її повторне виконання.
     */
    int choice;
    do{
        (*func)();
        input_int(message,&choice,0,1);
    }while (choice);
}
int get_length(char phrase[]){
    /**
     * \details
     * get_length() - обгортка для count_length() без задання лишньої константи.
     * Виконуєм рекурсивну функцію підрахунку дожвжини рядка count_length() починаючи з 0.
     */
    return count_length(phrase,0);
}

long pow_10_to(int *power){

    long ten = 1;
    for (int i = 0; i < *power; ++i) {
        ten *= 10;
    }
    return ten;
}
int count_length(char phrase[],int i){
    /**
     * Сумуєм цей символ з символами решти рядка до кінця.
     */
    if (!phrase[i]){
        return 0;
    }
    int sum = 1 + count_length(phrase,i+1);
    return sum;
}

void print_dividers(int *entered_number){
    /**
     * \details
     * Просто ідемо від одиниці до заданого числа і якщо це дільник - виводим. Також виводим тривіальні дільники.
     */
    printf("Дільники числа:\n1\n");
    for (int i = 2; i < *entered_number/2; ++i) {
        if (!(*entered_number%i)){
            printf("%d\n", i);
        }
    }
    if (*entered_number>1) printf("%d\n",*entered_number);
}

long double round_number (long double *num, int *precision){
    /**
     * Створюєм значення точності перетворене в десятки \c accuracy.
     * \c math_round_addition використовуєтся заокруглення за математичними правилами (= [x+0.5]).
     * Відкидається решта знаків після заданої точності.
     * \c answer перетворюється за заданою точністю в long double
     */
    // створено додаткові змінні для пояснення суті та полегшення відладки
    long accuracy = pow_10_to(precision); // значення точності перетворене в десятки
    long double math_round_addition = 0.5*(1/(long double)accuracy);// використовуєтся заокруглення за математичними правилами (= [x+0.5])
    long double answer = (long)(((*num)+math_round_addition)*accuracy);// відкидаються решта "нулів"
    answer /= (long double)accuracy ;// власне поділ на цілу і дробову частини
    return answer;
}
