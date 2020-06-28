#include <stdio.h>
#include <string.h>
#include <values.h>
#include <ctype.h>
#include "lab_functions.h"
///\file
typedef struct AEROFLOT_STRUCT{
    char *destination;///< Місце призначення
    int flight_number;///< Номер рейсу
    int type;///< Тип літака
} AEROFLOT;

enum type_of_aeroplane{
        ELSE,///< Тип, що не належить переліченим
        CIVIL,///< Цивільні літаки
        MILITARY///< Військові
};
/**
 * \brief Заміна структур \c AEROFLOT між собою
 * \details Заміна здійснюється за вказівниками
 * @param first
 * @param second
 */
void swap_aeroflot(AEROFLOT *first, AEROFLOT *second){
    AEROFLOT temp = *first;
    *first = *second;
    *second = temp;
}
/**
 * \brief Сортування обміном масива
 * @param arr Власне масив
 * @param N Розмірність масива
 * \details Сортування обміном. Послідовно порівнюється \c flight_number елемента a_0 із кожним
 * наступним a_i . Якщо a_i<a_0 , то ці два елементи міняють місцями.
 * Таким чином елемент з найменшим \c flight_number виявляється на своєму місці на початку масиву.
 * Потім цей метод застосовують до елемента a_1 і т.д.
 */
void swaping_sort_struct(AEROFLOT *arr, int N){
    for (int i = 0; i < N-1; ++i) {
        for (int j = 1; j+i < N; ++j) {
            if (arr[i].flight_number>arr[j+i].flight_number){
                swap_aeroflot(&arr[i],&arr[j+i]);
            }
        }
    }
}
/**
 * \brief Вказуєм місце призначення, номер рейсу, тип літака.
 * \details Серед нюансів звернання до полів структури за допомогою \c ->
 * @param aeroplane Структура рейсу
 */
void aeroflot_user_fill(AEROFLOT *aeroplane){
    aeroplane->destination = message_input("Місце призначення: ");
    toupper_chrs(aeroplane->destination);
    input_int("Номер рейсу: ", &aeroplane->flight_number, 0, INT_MAX);

    char *type = message_input("Тип літака: ");
    toupper_chrs(type);
    if (!strcmp(type, "CIVIL")){
        aeroplane->type = CIVIL;
    } else if (!strcmp(type, "MILITARY")){
        aeroplane->type = MILITARY;
    } else{
        aeroplane->type = ELSE;
    }
}
/**
 * \brief Виводим масив структур типу AEROFLOT в частково відформатованому вигляді
 * \details Форматований вихід здійснюється за допомогою пробілів та \\t
 * @param aeroplanes
 * @param N
 */
void print_aeroflot(AEROFLOT aeroplanes[], int N){
    printf("Місце призначення \tНомер рейсу \tНомер типу\n");
    for (int i = 0; i < N; ++i) {
        printf("\t%s \t  \t  \t%d \t  \t  \t  \t%d\n",
               aeroplanes[i].destination,
               aeroplanes[i].flight_number,
               aeroplanes[i].type);
    }
}
/**
 * \brief Виводить рейси що співпадають з \c filter_destination
 * \details Перед порівнянням переводим все в верхній регістр
 * @param aeroplanes Масив структур з рейсами
 * @param N Кількість рейсів
 * @param filter_destination Місце призначення
 */
void print_aeroflot_filter_destination(AEROFLOT aeroplanes[], int N, char filter_destination[]){
    toupper_chrs(filter_destination);
    int is_match  = 0;
    printf("Місце призначення \tНомер рейсу \tНомер типу\n");
    for (int i = 0; i < N; ++i) {
        if (!strcmp(filter_destination,aeroplanes[i].destination)){
            printf("\t%s \t  \t  \t%d \t  \t  \t  \t%d\n",
                   aeroplanes[i].destination,
                   aeroplanes[i].flight_number,
                   aeroplanes[i].type);
            is_match = 1;
        }
    }
    if (!is_match){
        printf("Рейсів по цьому напрямку немає!\n");
    }
}

/**
 * \brief Завдання лабораторної рботи
 * \details Створюємо \c N об'єктів типу \c AEROFLOT , користувач заповнює дані кожного
 * рейсу aeroflot_user_fill() .\n
 * Упорядкуєм рейси за зростанням номером рейсу модифікованою функцією сортування з попередньої лабораторної
 * swaping_sort_struct()\n Виводимо відсортований список.\n
 * Виконується пошук рейсів за місцем призначення заданим користувачем print_aeroflot_filter_destination()
 */
void task_1(){
    const int N = 5;
    char destination[254];
    AEROFLOT kpi_aeroplanes[N];
    for (int i = 0; i < N; ++i) {
        printf("Рейс №%d\n", i+1);
        aeroflot_user_fill(&kpi_aeroplanes[i]);
    }
    printf("Упорядкуєм рейси за зростанням номером рейсу\n");
    swaping_sort_struct(kpi_aeroplanes, N);
    print_aeroflot(kpi_aeroplanes, N);
    printf("Пошук рейсів за місцем призначення\n");
    strcpy(destination,message_input("Місце призначення: "));
    print_aeroflot_filter_destination(kpi_aeroplanes, N, destination);
}

int main() {
    clear();
    to_repeat(task_1, "Бажаєте повторити виконання завдання?\n");
    return 0;
}