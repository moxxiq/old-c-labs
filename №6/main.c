#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lab_functions.h"
///\file
/**
 * \brief Завдання лабораторної роботи
 * \details
 * Користувач вводить розмірність майбутнього двумірного масива.
 * Він створюється та заразом масив сум стовбчиків, після чого зануляється.
 * Виконується заповнення випадковими числами та підрахунок сум стовбців.\n
 * Визначається колонка з максимальною сумою елементів.\n
 * Виконується вивід масиву з виділенням стовбця з максимальною сумою.\n
 * Виконується вивід масиву сум, вивід стовбця з найбільшою сумою елементів\n
 * Виконується вивільнення пам'яті.\n
 */
void task_1(){
    int cols, rows, max_col = 0;
    input_int("Введіть кількість рядків масива (1-18665)\n", &rows, 1, 18665);
    input_int("Введіть кількість стовбців масива (1-18665)\n", &cols, 1, 18665);
    // Основний масив
    int **arr = (int **) malloc(rows*sizeof(int *));
    // Суми стовбців
    int *sum_of_cols = (int *) malloc(cols*sizeof(int));
    for (int i = 0; i < rows; ++i) {
        arr[i] = (int *)malloc(cols* sizeof(int));
    }
    // Занулення масиву сумм колонок
    for (int i = 0; i < cols; ++i) {
        sum_of_cols[i] = 0;
    }
    // Заповнення випадковими числами, підрахунок суми колонок
    srand(time(NULL));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            arr[i][j] = rand()%201-100;
            sum_of_cols[j]+=arr[i][j];
        }
    }
    // Знаходження максимальної суми елементів
    for (int i = 1; i < cols; ++i) {
        if (sum_of_cols[max_col]<sum_of_cols[i]){
            max_col = i;
        }
    }
    // Вивід масиву з виділеною колонкою з максимальною сумою
    printf("Масив має вигляд\n");
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            printf("  \t");
            if (j == max_col){
                printf("\x1b[6;30;41m");
                printf("%d",arr[i][j]);
                printf("\x1b[0m ");
            }else{
                printf("%d ",arr[i][j]);
            }
        }
        putchar('\n');
    }
    // Вивід масиву сум
    printf("Суми колонок\n");
    for (int i = 0; i < cols; ++i) {
        printf("  \t");
        if (i == max_col){
            printf("\x1b[6;30;41m");
            printf("%d",sum_of_cols[i]);
            printf("\x1b[0m ");
        }else{
            printf("%d", sum_of_cols[i]);
        }
    }
    putchar('\n');
    // Вивід стовбця з найбільшою сумою елементів
    printf("№%d - стовбець з найбільшою сумою елементів\n", max_col+1);
    //Вивільнення пам'яті
    for (int i = 0; i < rows; ++i) {
        free(arr[i]);
    }
    free(arr);
    free(sum_of_cols);
}

int main() {
    to_repeat(task_1, "Бажаєте повторити виконання завдання?\n");
    return 0;
}