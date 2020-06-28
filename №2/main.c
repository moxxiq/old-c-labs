#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
/**
 * \file
 */
#define clear() printf("\033[H\033[J")
#define INT_MIN -2147483648
#define INT_MAX 2147483647

struct Pair_arr{
    int first;
    int second;
};

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
 * \brief Виконання завдання №1 \details Дивіться нижче
 */
void task1();
/**
 * \brief Виконання завдання №2 \details Дивіться нижче
 */
void task2();
/**
 * \brief Обмін двох аргументів
 * @param first Адреса першого аргументу
 * @param second Адреса другого аргумент
 */
void swap(int *first, int *second);
/**
 * \brief Заповнює одновимірний масив довільними числами
 * @param arr Вказівник на масив, який буде заповнювати функція
 * @param N Розмір масива
 */
void rand_fill_1d(int *arr,int N);
/**
 * Заповнюється двовимірний масив довільними числами
 * @param arr Сам масив
 * @param N Одна з його розмірностей
 */
void rand_fill_2d(int **arr,int N);
/**
 * \brief Виводить одновимірний масив
 * @param arr Масив, який буде виводитись
 * @param N Розмір масива
 */
void print_arr_1d(int *arr, int N);
/**
 * \brief Виводить двовимірний масив з виділенням кольором нулів
 * @param arr Масив, який буде виводитись
 * @param N Одна з його розмірностей
 */
void print_arr_2d_redzero(int **arr, int N);
/**
 * \brief Виводить одновимірний масив виділяючи кольорами його min max елементи.\n
 * Виводить їх добуток.
 * @param arr Власне масив
 * @param N Розмірність масива
 * @param minmax мінімальний та максимальний елементи
 */
void print_arr_minmax(int *arr, int N, struct Pair_arr *minmax);
/**
 * Сортування обміном масива
 * @param arr Власне масив
 * @param N РОзмірність масива
 */
void swaping_sort(int *arr, int N);
/**
 * \brief Заповнення масива вводом користувача
 * @param arr Власне масив
 * @param N Розмірність масива
 */
void usr_fill_1d(int *arr, int N);
/**
 * Заповнення 2d масива вводом користувача
 * @param arr Власне масив
 * @param N Одна з його розмірностей
 */
void usr_fill_2d(int **arr, int N);
/**
 * \brief Реалізація корректного введення
 * @param message Повідомлення до користувача
 * @param number Змінна в яку буде записуватися правильний ввід
 * @param lwr_border Нижня межа
 * @param hir_border Верхня межа
 */
void input_int(char message[], int *number,int lwr_border, int hir_border);
/**
 * \brief Функція, що повторює задану їй функцію за бажанням користувача.
 * @param func Функція, яка буде повторюватись
 */
void to_repeat(void (*func)(void));
/**
 * Здійснює прохід масиву паралельно головній діагоналі, починаючи з верхнього правого кута.
 * @param arr Масив, по якому функція буде іти
 * @param N Розмірність масива
 * @param pos Позиція за нашим проходом
 * @return Значення певної комірки масиву за її номером при лічбі паралельно головній діагоналі, починаючи з верхнього правого кута.
 */
int *go_zigzag(int **arr, int N, int pos);
/**
 * \brief Переміщує всі нулі за правилом функції to_repeat().
 * @param arr Масив, у якому здійснюватиметься заміна.
 * @param N Розмір масиву.
 */
void zeros_to_begin_2d(int **arr, int N);

int main() {
    int choice;
    do {
        clear();
        input_int("Виберіть номер завдання (1, 2):\n",
                  &choice,
                  1,
                  2);
        switch (choice) {
            case 1:
                to_repeat(task1);
                break;
            case 2:
                to_repeat(task2);
                break;
        }
        input_int("Бажаєте повторно виконати завдання?:\n", &choice, 0, 1);
    }while (choice);

    return 0;
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

char *message_input(char message[]){
    char *usr_input = (char*) malloc(sizeof(char)*254);
    printf("%s", message); // Виводимо повідомлення користувачу
    fgets(usr_input, 254, stdin);
    return usr_input;
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

void to_repeat(void (*func)(void)){
    int choice;
    do{
        (*func)();
        input_int("Бажаєте продовжити виконання цього завдання?:\n",&choice,0,1);
    }while (choice);
}

void print_arr_1d(int *arr, int N){
    for (int i = 0; i < N; ++i) {
        printf("%d ",arr[i]);
    }
    putchar('\n');
}

void print_arr_2d_redzero(int **arr, int N){
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            printf("\t \t");
            if (arr[i][j]>=0) {
                printf(" ");
            }
            if (arr[i][j]==0){
                printf("\x1b[6;30;41m");
                printf("%d",arr[i][j]);
                printf("\x1b[0m ");
            } else{
                printf("%d",arr[i][j]);
            }
        }
        putchar('\n');
    }
}

void rand_fill_1d(int *arr,int N){
    /**
     * \details Для виведення різних результатів при повторних запусках програми використовується функція srand(time(NULL))\n
     * Діапазон визначається цим виразом \c %20001-10000
     */
    srand(time(NULL));
    for (int i = 0; i < N; ++i){
        arr[i] = rand()%20001-10000;
    }
}

void rand_fill_2d(int **arr,int N){
    /**
     * Для виведення різних результатів при повторних запусках програми використовується функція srand(time(NULL))\n
     * Діапазон визначається цим виразом \c %21-10
     */
    srand(time(NULL));
    for (int i = 0; i < N; ++i){
        for (int j = 0; j < N; ++j) {
            arr[i][j] = rand()%21-10;
        }
    }
}

void usr_fill_1d(int *arr, int N){
    /**
     * \details Виконується перевірка при введенні за допомогою функції input_int()
     */
    for (int i = 0; i < N; ++i) {
        printf("%i",i);
        input_int(": ", &arr[i], 0, 0);
    }
}

void usr_fill_2d(int **arr, int N){
    /**
     * \details Виконується перевірка при введенні за допомогою функції input_int()
     */
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            printf("[%i,%i]",i,j);
            input_int(": ", &arr[i][j], 0, 0);
        }
    }
}

struct Pair_arr *find_minmax(int *arr, int N){
    struct Pair_arr *minmax = (struct Pair_arr*)malloc(2*sizeof(int)*2);
    minmax->first = INT_MAX;
    minmax->second = INT_MIN;
    for (int i = 0; i < N; ++i) {
        if (arr[i] > minmax->second) {
            minmax->second = arr[i];
        }
        if (arr[i] < minmax->first){
            minmax->first = arr[i];
        }
    }
    return minmax;
}

void print_arr_minmax(int *arr, int N, struct Pair_arr *minmax){
    /**
     * \details Виконується перебір комірок масива. Виводиться сам елемент, якщо він не мінімальний і не максимальний.\n
     * Виділяється кольором мінімальний та максимальні елементи, для перевірки використовується struct Pair_arr у якій зберігаються
     * мінімальні та максимальні елементи.
     */
    for (int i = 0; i < N; ++i) {
        if (arr[i]==minmax->first){
            printf("\x1b[6;30;41m");
            printf("%d",arr[i]);
            printf("\x1b[0m ");
        } else if (arr[i]==minmax->second){
            printf("\x1b[6;30;42m");
            printf("%d",arr[i]);
            printf("\x1b[0m ");
        } else {
            printf("%d ",arr[i]);
        }
    }
    putchar('\n');
    printf("Мінімальний елемент %d\n"
           "Максимальний елемент %d\n",
           minmax->first,
           minmax->second);
    printf("Їх добуток = %d\n", minmax->first*minmax->second);
}

void swap(int *first, int *second){
    /**
     * \details Заміна здійснюється за вказівниками
     */
    int temp = *first;
    *first = *second;
    *second = temp;
}

void swaping_sort(int *arr, int N){
    /**
     * Сортування обміном. Послідовно порівнюється елемент a_0 із кожним
     * наступним a_i . Якщо a_i<a_0 , то ці два елементи міняють місцями.
     * Таким чином найменший елемент виявляється на своєму місці на початку масиву.
     * Потім цей метод застосовують до елемента a 1 і т.д.
     */
    for (int i = 0; i < N-1; ++i) {
        for (int j = 1; j+i < N; ++j) {
            if (arr[i]<arr[j+i]){
                swap(&arr[i],&arr[j+i]);
            }
        }
    }
}

int *go_zigzag(int **arr, int N, int pos){
    // pos [0;N^2]
    int i,j,inner_i,inner_j,k = 0;
    i = 0;
    while (i < 2*N-1){
        if (i-N < 0){//зміна індексу і відносно головної діагоналі
            inner_i = 0;
        } else{
            inner_i = i-(N-1);
        }
        j = (N-1)-i+inner_i;
        inner_j = 0;
        while (j<N-inner_i){
            if (k == pos){
                return &arr[inner_i+inner_j][j];
            }
            inner_j++;
            j++;
            k++;
        }
        i++;
    }
}

void zeros_to_begin_2d(int **arr, int N){
    /**
     * \details Виконується прохід за допомогою функції go_zigzag() та заміна функцією swap()
     */
    int pos_0;
    for (int i = 0; i < N*N; ++i) {
        if (*go_zigzag(arr,N,i) != 0){
            pos_0 = i+1;
            while (pos_0<N*N && *go_zigzag(arr,N,pos_0)!=0){
                pos_0++;
            }
            if (pos_0==N*N){
                return;
            }
            swap(go_zigzag(arr,N,pos_0),go_zigzag(arr,N,i));
        }
    }
}

void task1(){
    int N; // array size
    int choice;
    clear();
    input_int("Введіть розмір масива (1-348389376)\n", &N, 1, 348389376);
    int *arr = (int*)malloc(N* sizeof(int));
    input_int("Виберіть спосіб заповнення масиву:\n"
              "1 - автоматично випадковими числами\n"
              "2 - власноруч\n",
              &choice,
              1,
              2);
    switch (choice){
        case 1: rand_fill_1d(arr,N);
            break;
        case 2: usr_fill_1d(arr,N);
            break;
    }
    print_arr_minmax(arr,N,find_minmax(arr,N));
    printf("\nВиконується сортування...\n");
    swaping_sort(arr,N);
    printf("Відсортований масив має вигляд:\n");
    print_arr_1d(arr,N);
    free(arr);
}

void task2(){
    int N;// array dimensions
    int choice;
    clear();
    input_int("Введіть розмірність масива NxN (1-18665)\n", &N, 1, 18665);
    int **arr = (int**)malloc(N*sizeof(int *));
    for (int i = 0; i < N; ++i) {
        arr[i] = (int *)malloc(N * sizeof(int));
    }
    input_int("Виберіть спосіб заповнення масиву:\n"
              "1 - автоматично випадковими числами\n"
              "2 - власноруч\n",
              &choice,
              1,
              2);
    switch (choice){
        case 1: rand_fill_2d(arr,N);
            break;
        case 2: usr_fill_2d(arr,N);
            break;
    }
    printf("Масив має вигляд:\n");
    print_arr_2d_redzero(arr,N);
    printf("Переміщуємо нулі паралельно головній діагоналі...\n");
    zeros_to_begin_2d(arr, N);
    printf("Масив тепер має вигляд:\n");
    print_arr_2d_redzero(arr,N);
    //free memory
    for (int i = 0; i < N; ++i) {
        free(arr[i]);
    }
    free(arr);
    //
}