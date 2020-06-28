#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
///\file

#define clear() printf("\033[H\033[J")
#define INT_MIN -2147483648
#define INT_MAX 2147483647

/**
 * \brief Отримує від користувача ввід, перед яким виводить повідомлення
 * @param message Повідомлення, яке буде показане користувачу
 * @return Ввід користувача в форматі \c char
 */
char *message_input(char message[]);
/**
 * Перевірка чи кожне введене число є десятковим (від'ємним також)
 * @param str число у вигляді увеного масиву char
 * @return 1, якщо число десяткове, 0 якщо ні
 */
int is_every_digit(char *str);
/**
 * \brief Перевіряє на входження \c srt в \c pattern
 * @param pattern Символи, один з яких може дорівнювати \c str
 * @param str Символ, який порівнюється з кожним з \c pattren
 * @return 1 або 0
 */
int match_char(char *pattern, char str);
/**
 * Перевіряє чи є одракові однобайтні символи в тексті \c word
 * @param word Текст, звідки береться слово
 * @param begin Порядок першого символа слова в тексті
 * @param end Порядок останнього символа слова в тексті
 * @return 1 або 0
 */
int is_chars_repeat(char *word, int begin, int end);
/**
 * Посимвольний вивід уривка з тексту \c phrase
 * @param phrase Текст, уривок якого буде виведений
 * @param i Номер першого символу уривка
 * @param j Номер останнього символу уривка
 */
void print_part(char *phrase, int i, int j);
/**
 * \brief Функція, що повторює задану їй функцію за бажанням користувача.
 * @param func Функція, яка буде повторюватись
 */
void to_repeat(void (*func)(void));
/**
 * \brief Реалізація корректного введення
 * @param message Повідомлення до користувача
 * @param number Змінна в яку буде записуватися правильний ввід
 * @param lwr_border Нижня межа
 * @param hir_border Верхня межа
 */
void input_int(char message[], int *number,int lwr_border, int hir_border);

/**
 * \brief Завдання №1
 * \details Спочатку програма зчитує ввід користувача та вираховує його довжину.
 * Далі шукає слова по розділювачам, що є в \c PATTERN, запам'ятовуючи позиції початку і кінця.
 * Перевіряє функцію is_chars_repeat() чи є повтори символів у слові
 * і відповідні слова виділяє, виводить функцією print_part().
 */
void task_1();

int main() {
    to_repeat(task_1);
    return 0;
}

void task_1(){
    char PATTERN[]=",. "; // типи розділювачів
    char phrase[254];// фраза, яку ми зчитали
    int j = 0;
    int length_of_phrase;// довжина фрази
    clear();
    printf("Введіть речення, "
           "я виділю слова з буквами, що не повторюються\n");
    fgets(phrase, 253, stdin);
    length_of_phrase = strlen(phrase) - 1;
    for (int i = 0; i < length_of_phrase; ++i) {
        for (j = i; !match_char(PATTERN, phrase[j]) && j < length_of_phrase; ++j);
        if (is_chars_repeat(phrase, i, j)) {
            print_part(phrase, i, j);
        } else {
            printf("\x1b[6;30;43m");
            print_part(phrase, i, j);
            printf("\x1b[0m");
        }
        printf("%c", phrase[j]);
        i = j;
    }
}

char *message_input(char message[]){
    char *usr_input = (char*) malloc(sizeof(char)*254);
    printf("%s", message); // Виводимо повідомлення користувачу
    fgets(usr_input, 254, stdin);
    return usr_input;
}

int match_char(char *pattern, char str){
    /**
     * \details
     * Порівнює посимвольно з кожним з \c pattern
     */
    int len = strlen(pattern);
    for (int i = 0; i < len; ++i) {
        if (pattern[i]==str){
            return 1;
        }
    }
    return 0;
}

int is_chars_repeat(char *word, int begin, int end){
    /**
     * \details
     * Преревірка букв на повтори здійснюється шляхом почергового порівняння кожного символу з рештою у слові, що йдуть за ним.
     * Також, якщо це двухбайтний \c char укр. алфавіту, то перший його байт буде = або -47 або -48
     */
    for (begin; begin < end; ++begin) {
        if (word[begin] != -47 && word[begin] != -48){// + укр алфавіт
            for (int i = begin+1; i < end; ++i) {
                if (tolower(word[begin])==tolower(word[i])){
                    return 1;
                }

            }
        }
    }
    return 0;
}

void print_part(char *phrase, int i, int j){
    for (int k = i; k < j; ++k) {
        printf("%c", phrase[k]);
    }
}

void to_repeat(void (*func)(void)){
    /**
     * \details
     * Викорисковуються вказівники на функцію, щоб забезпечити її повторне виконання.
     */
    int choice;
    do{
        (*func)();
        input_int("Бажаєте продовжити виконання цього завдання?:\n",&choice,0,1);
    }while (choice);
}

void input_int(char message[], int *number,int lwr_border, int hir_border){
    /**
     * Якщо межі однакові, то вони стають мінімальними/максимальними.\n
     * Виконується введеня користувачем, умова циклу while превіряє
     * чи кожне введене число є десятковим за допомогою is_every_digit().\n
     * Також виконується перевірка чи належить число відрізку lwr_border hir_border\n
     * Наприкінці у змінну *number записується правильне число.
     */
    if (lwr_border == hir_border){
        lwr_border = INT_MIN;
        hir_border = INT_MAX;
    }
    char *usr_input = message_input(message);
    while (!is_every_digit(usr_input) || atoi(usr_input) < lwr_border || atoi(usr_input) > hir_border){
        printf("ERROR INPUT\n");
        usr_input = message_input(message);
    }
    *number = atoi(usr_input);
}

int is_every_digit(char *str){//uhh some potentially buggy function
    /**
     * Знаходить довжину числа, враховуючи знак переходу\n
     * З урахуванням '-' обмежує максимальну довжину числа згідно лімітів int.
     * В коментарях можна побачити нюанси. Наприкінці перевіряєм чи всі символи є десятковими.
     */
    int len = strlen(str);
    if (len>2 && (str[0] != '-') && ((!isdigit(str[0]))||len>11)){
        return 0;//додатнє число більше 11 знаків або не з знаком - на початку
    }
    if ((str[0] == '-') && (len>12)){
        return 0;//від'ємне число більше 11 знаків
    }
    if (len == 2 && !isdigit(str[0])){
        return 0;//не одна цифра
    }
    if (len==1){
        return 0;// читаєм \n
    }
    for (int i = 1; i < len-1; ++i) {
        if (!isdigit(str[i])){
            return 0;//будь-який знак - не цифра
        }
    }
    return 1;
}
