#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <values.h>
//
//
// Created by mox on 22.03.19.
// edit 23.03.19.
//     Added fix for input_int "" is now equals wrong
//     fix last symbol \\n in message input
//
char *message_input(char message[]){
    char *usr_input = (char*) malloc(sizeof(char)*254);
    printf("%s", message); // Виводимо повідомлення користувачу
    fgets(usr_input, 254, stdin);
    usr_input[strlen(usr_input)-1] = '\0';
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
    for (i; i < len; ++i) {
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
    for (i; i < len; ++i) {
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
    while (!is_suits || !is_every_digit(usr_input) || !strlen(usr_input) || *number < lwr_border || *number > hir_border){
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
void swap_int(int *first, int *second){
    /**
     * \details Заміна здійснюється за вказівниками
     */
    int temp = *first;
    *first = *second;
    *second = temp;
}
void toupper_chrs(char str[]){
    for (int i = 0; i < strlen(str); ++i) {
        str[i] = (char)toupper(str[i]);
    }
}
