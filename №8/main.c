///\file
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <values.h>
#include <stdbool.h>
#include "lab_functions.h"
typedef struct patient_struct{
    char SNF[63];///<ПІБ
    char addres[63];///<Адреса
    int card_numer;///<Номер карти
    _Bool is_removed;///<Статус видаленого файлу
}patient;
// global vars
char TEMP_FILENAME[] = ".temp_cache.txt";///<Ім'я тимчасового файлу-кешу
bool is_opened_text = false;///<Чи є в даний момент часу відкритий текстовий файл
bool is_opened_bin = false;///<Чи є в даний момент часу відкритий бінарний файл
char *current_file_name = NULL;///<Ім'я поточного відкритого файлу
/**
 * \brief Вивід карти пацієнта на екран
 * \details Вивід даних в форматованому вигляді
 * @param card Власне карта пацієнта
 * @param is_not_visible параметр, що потрібен для показу видалених (або ні) файлів
 */
void print_patient(patient card, _Bool is_not_visible){
    if (is_not_visible){
        return;
    }
    printf(" _____________________________________________\n");
    printf("|        ПІБ: %-62s\n",card.SNF);
    printf("|     Адреса: %-62s\n",card.addres);
    printf("|Номер карти: %-62d\n",card.card_numer);
    printf(" ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n");
}
/**
 * \brief Позначення елементів файлу як видалених
 * \details Зчитування поточного файлу, позначення карти як видаленої, запис назад у файл
 * @return 0 в разі успішного виконання
 */
int remove_by_num(){
    FILE *input = fopen(TEMP_FILENAME, "rb");
    int N;
    if (!fread(&N, sizeof(N), 1, input)){
        printf("Помилка читання файлу\n");
        return 0;
    }
    patient *cards = (patient *)malloc(sizeof(patient)*N);
    fread(cards, sizeof(patient), N, input);
    fclose(input);
    int remove_number;
    input_int("Введіть номер карти, яку потрібно видалити\n", &remove_number, 0, INT_MAX);

    FILE *output = fopen(TEMP_FILENAME, "wb");
    if (!output){
        printf("ERROR opening destination file (can be .temp_cache.txt)\n");
        return 0;
    }
    fwrite(&N, sizeof(N),1,output);
    for (int i = 0; i < N; ++i) {
        if (cards[i].card_numer == remove_number){
            cards[i].is_removed = (_Bool)1;
            printf("Карта \"%s\" видалена\n", cards[i].SNF);
        }
    }
    fwrite(cards, sizeof(patient), N, output);
    free(cards);
    fclose(output);
    return 0;
}
/**
 * Створення та заповнення користувачем карти хворого
 * @return Екземпляр карти пацієнта
 */
patient patient_usr_fill(){
    patient card;
    printf("|        ПІБ: ");
    fgets(card.SNF, 62, stdin);
    card.SNF[strlen(card.SNF)-1] = '\0';
    printf("|     Адреса: ");
    fgets(card.addres, 62, stdin);
    card.addres[strlen(card.addres)-1] = '\0';
    card.card_numer = get_int("|Номер карти: ",0, INT_MAX);
    card.is_removed = (_Bool)0;
    return card;
}
/**
 * Відмінювання слова "символ" для різних чисельників
 * @param i Чисельник
 * @return Слово з правильним закінченням
 */
char *symbol_ending(int i){
    char *symb;
    if (i%100>10 && i%100<21){
        symb = "символів";
    } else{
        switch (i%10){
            case 1:
                symb = "символ";
                break;
            case 2:
            case 3:
            case 4:
                symb = "символа";
                break;
            default:
                symb = "символів";

        }
    }
    return symb;
}
/**
 * \brief Кількість символів в останньому слові файла
 * \details Відбувається перевірка існування вже відкритого файла.
 * Суть полягає у відраховуванні певної кількості символів з кінця файлу
 * @return 0 в разі успішного виконання
 */
int char_number(){
    if (is_opened_text){
        FILE *F2;
        if (!(F2 = fopen(TEMP_FILENAME, "r"))){
            printf("Помилка відкриття!\n");
            return 0;
        }
        int i = 0; //chars to the end
        int seek_spaces = 0;
        char tmp_c;
        while (!fseek(F2,-seek_spaces-1, SEEK_END)){
            tmp_c = fgetc(F2);
            if (tmp_c == ' ' || tmp_c == '\n') {
                ++seek_spaces;
            } else{
                break;
            }
        }
        while (!fseek(F2,-i-1-seek_spaces, SEEK_END)){
            tmp_c = fgetc(F2);
            if (tmp_c != ' ' && tmp_c != '\n'){
                ++i;
            } else{
                break;
            }
        }
        //sybm
        printf("Останнє слово містить %i %s\n", i, symbol_ending(i));
        //TODO:check in empty file
    } else{
        printf("Жодного файла не відкрито\n");
    }
    return 0;
}
/**
 * \brief Копіювання тексту з певного рядка
 * \details Відбувається перевірка існування вже відкритого файла.
 * Копіювання з файлу визначеного користувачем
 * @return 0 в разі успішного виконання
 */
int lines_taks(){
    if (is_opened_text){
        FILE *F1, *F2;
        char tmp_c;
        int line = 0,N;// user input N
        while (!(F1 = fopen(message_input("Введіть шлях файлу з якого копіювати\n"), "r"))){
            printf("Помилка відкриття, повторіть введення!\n");
        }
        input_int("Починаючи з якого рядка слід копіювати текст?\n", &N, 1, INT_MAX);
        N--; // start counting from 0
        while ((tmp_c = fgetc(F1)) != EOF && line<N){
            if (tmp_c == '\n'){
                line++;
            }
        }
        if (tmp_c == EOF){
            fclose(F1);
            return 0;
        }
        if (!(F2 = fopen(TEMP_FILENAME, "a"))){
            printf("Помилка запису!\n");
            fclose(F1);
            return 0;
        }
        while (tmp_c != EOF){
            fputc(tmp_c,F2);
            tmp_c = fgetc(F1);
        }
        fclose(F1);
        fclose(F2);
    } else{
        printf("Жодного файла не відкрито\n");
    }
    return 0;
}
/**
 * Копіювання даних з одного текстового файлу в інший
 * @param src Джерело
 * @param dest Призначення
 */
void tranfer_all_text(char *src, char *dest){
    // HAVE NO INPUT CHECKUPS
    FILE *input = fopen(src, "r");
    FILE *output = fopen(dest, "w");
    char c;
    if (!output){
        printf("ERROR opening destination file (can be .temp_cache.txt)\n");
        fclose(input);
        return;
    }
    while ((c = fgetc(input))!= EOF){
        fputc(c, output);
    }
    fclose(input);
    fclose(output);
}
/**
 * Копіювання даних з одного бінарного файлу в інший
 * @param src Джерело
 * @param dest Призначення
 */
void tranfer_all_bin(char *dest, char *src){
    // HAVE NO INPUT CHECKUPS
    FILE *input = fopen(src, "rb");
    FILE *output = fopen(dest, "wb");
    int N;
    if (!output){
        printf("ERROR opening destination file (can be .temp_cache.txt)\n");
        fclose(input);
        return;
    }
    if (!fread(&N, sizeof(N), 1, input)){
        printf("Помилка читання файлу\n");
        return;
    }
    patient *new_cards = (patient *)malloc(sizeof(patient)*N);
    fread(new_cards, sizeof(patient), N, input);
    fclose(input);
    fwrite(&N, sizeof(N),1,output);
    fwrite(new_cards, sizeof(patient), N, output);
    free(new_cards);
    fclose(output);
}
/**
 * Закриття текстового файлу
 * @return 0 в разі успішного виконання
 */
int close_text(){
    is_opened_text = false;
    return 0;
}
/**
 * Закриття бінарного файлу
 * @return 0 в разі успішного виконання
 */
int close_bin(){
    is_opened_bin = false;
    return 0;
}
/**
 * \brief Стискання бінарного файлу
 * \details Зчитується файл, кількість видимих карток,
 * записуються видимі картки в динамічний масив
 */
void zip_bin(){
    FILE *input = fopen(TEMP_FILENAME, "rb");
    int N, M=0;
    if (!fread(&N, sizeof(N), 1, input)){
        printf("Помилка читання файлу\n");
        return;
    }
    patient *cards = (patient *)malloc(sizeof(patient)*N);
    fread(cards, sizeof(patient), N, input);
    fclose(input);
    for (int i = 0; i < N; ++i) {
        if (!cards[i].is_removed){
            ++M;
        }
    }
    patient *new_cards = (patient *)malloc(sizeof(patient)*M);
    for (int i = 0, j = 0; i < N; ++i) {
        if (!cards[i].is_removed){
            new_cards[j++] = cards[i];
        }
    }
    FILE *output = fopen(TEMP_FILENAME, "wb");
    if (!output){
        printf("ERROR opening destination file (can be .temp_cache.txt)\n");
        fclose(input);
        return;
    }
    fwrite(&M, sizeof(int),1,output);
    fwrite(new_cards, sizeof(patient), M, output);
    free(cards);
    free(new_cards);
    fclose(output);
}
/**
 * \brief Зберегти як... текстовий файл
 * \details Відбувається перевірка існування вже відкритого файла.
 * Запис у файл з потрібною навою
 * @return 0 в разі успішного виконання
 */
int saveas_text(){
    if (is_opened_text){
        current_file_name = message_input("Введіть назву/шлях файла\n");
        tranfer_all_text(TEMP_FILENAME, current_file_name);
    } else{
        printf("Жодного файла не відкрито\n");
    }
    return 0;
}
/**
 * \brief Зберегти як... бінарний файл
 * \details Відбувається перевірка існування вже відкритого файла.
 * Запис у файл з потрібною навою
 * @return 0 в разі успішного виконання
 */
int saveas_bin(){
    int is_zip;
    if (is_opened_bin){
        current_file_name = message_input("Введіть назву/шлях файла\n");
        input_int("Зберегти з ущільненням? (0/1)\n", &is_zip, 0, 1);
        if (is_zip){
            zip_bin();
        }
        tranfer_all_bin(current_file_name, TEMP_FILENAME);
    } else{
        printf("Жодного файла не відкрито\n");
    }
    return 0;
}
/**
 * \brief Зберегти текстовий файл
 * \details Відбувається перевірка існування вже відкритого файла.
 * Запис у файл з потрібною навою або у поточний відкритий файл
 * @return 0 в разі успішного виконання
 */
int save_text(){
    if (is_opened_text){
        if (!(current_file_name)){
            current_file_name = message_input("Введіть назву/шлях файла\n");
        }
        tranfer_all_text(TEMP_FILENAME, current_file_name);
    } else{
        printf("Жодного файла не відкрито\n");
    }
    return 0;
}
/**
 * \brief Зберегти бінарний файл
 * \details Відбувається перевірка існування вже відкритого файла.
 * Запис у файл з потрібною навою або у поточний відкритий файл
 * @return 0 в разі успішного виконання
 */
int save_bin(){
    int is_zip;
    if (is_opened_bin){
        if (!(current_file_name)){
            current_file_name = message_input("Введіть назву/шлях файла\n");
        }
        input_int("Зберегти з ущільненням? (0/1)\n", &is_zip, 0, 1);
        if (is_zip){
            zip_bin();
        }
        tranfer_all_bin(current_file_name, TEMP_FILENAME);
    } else{
        printf("Жодного файла не відкрито\n");
    }
    return 0;
}
/**
 * \brief Очистити текстовий файл
 * @return 0 в разі успішного виконання
 */
int clear_text(){
    FILE *ofstream = fopen(TEMP_FILENAME, "w");
    fclose(ofstream);
    return 0;
}
/**
 * \brief Очистити бінарний файл
 * @return 0 в разі успішного виконання
 */
int clear_bin(){
    FILE *ofstream = fopen(TEMP_FILENAME, "wb");
    fclose(ofstream);
    return 0;
}
/**
 * \brief Редагувати текстовий файл з попереднім очищенням вмісту
 * \details Запис користувацького рядка в файл
 * @return 0 в разі успішного виконання
 */
int clear_edit_text(){
    FILE *ofstream = fopen(TEMP_FILENAME, "w");
    char bufer[255];
    fgets(bufer, 254, stdin);
    fputs(bufer, ofstream);
    fclose(ofstream);
    return 0;
}
/**
 * \brief Редагувати бінарний файл з попереднім очищенням вмісту
 * \details Запис користувацького масиву карт пацієнтів в файл
 * @return 0 в разі успішного виконання
 */
int clear_edit_bin(){
    int M;
    FILE *output = fopen(TEMP_FILENAME, "wb");
    if (!output){
        printf("ERROR opening destination file (can be .temp_cache.txt)\n");
        return 0;
    }
    input_int("Скільки структур буде введено?\n", &M, 0, 255);
    fwrite(&M, sizeof(M),1,output);
    patient *new_cards = (patient *)malloc(sizeof(patient)*M);
    printf("Вводьте структури\n");
    for (int i = 0; i < M; ++i) {
        new_cards[i] = patient_usr_fill();
        putchar('\n');
    }
    fwrite(new_cards, sizeof(patient), M, output);
    free(new_cards);
    fclose(output);
    return 0;
}
/**
 * \brief Додати картки в початок файлу
 * \details Запис користувацького масиву карт пацієнтів в файл перед попередніми
 * @return 0 в разі успішного виконання
 */
int add_front_bin(){
    FILE *input = fopen(TEMP_FILENAME, "rb");
    int N,M, temp_n;
    if (!fread(&N, sizeof(N), 1, input)){
        printf("Помилка читання файлу\n");
        fclose(input);
        return 0;
    }
    patient *cards = (patient *)malloc(sizeof(patient)*N);
    fread(cards, sizeof(patient), N, input);
    fclose(input);
    FILE *output = fopen(TEMP_FILENAME, "wb");
    if (!output){
        printf("ERROR opening destination file (can be .temp_cache.txt)\n");
        return 0;
    }
    input_int("Скільки структур буде введено?\n", &M, 0, 255);
    temp_n = N + M;
    fwrite(&temp_n, sizeof(temp_n),1,output);
    patient *new_cards = (patient *)malloc(sizeof(patient)*M);
    printf("Вводьте структури\n");
    for (int i = 0; i < M; ++i) {
        new_cards[i] = patient_usr_fill();
        putchar('\n');
    }
    fwrite(new_cards, sizeof(patient), M, output);
    fwrite(cards, sizeof(patient), N, output);
    free(cards);
    free(new_cards);
    fclose(output);
    return 0;
}
/**
 * \brief Додати рядки в кінець файлу
 * \details Запис користувацького рядка в кінець файлу
 * @return 0 в разі успішного виконання
 */
int append_text(){
    FILE *astream = fopen(TEMP_FILENAME, "a+");
    fseek(astream, 0, SEEK_SET);
    char c, bufer[255];
    while ((c = fgetc(astream)) != EOF){
        putchar(c);
    }
    fgets(bufer, 254, stdin);
    fputs(bufer, astream);
    fclose(astream);
    return 0;
}
/**
 * \brief Додати картки в кінець файлу
 * \details Запис користувацького масиву карт пацієнтів в файл після попередніх
 * @return 0 в разі успішного виконання
 */
int append_bin(){
    FILE *input = fopen(TEMP_FILENAME, "rb");
    int N,M, temp_n;
    if(!fread(&N, sizeof(N), 1, input)){
        printf("Помилка читання файлу\n");
        fclose(input);
        return 0;
    }
    patient *cards = (patient *)malloc(sizeof(patient)*N);
    fread(cards, sizeof(patient), N, input);
    fclose(input);
    FILE *output = fopen(TEMP_FILENAME, "wb");
    if (!output){
        printf("ERROR opening destination file (can be .temp_cache.txt)\n");
        free(cards);
        return 0;
    }
    input_int("Скільки структур буде введено?\n", &M, 0, 255);
    temp_n = N + M;
    fwrite(&temp_n, sizeof(temp_n),1,output);
    patient *new_cards = (patient *)malloc(sizeof(patient)*M);
    printf("Вводьте структури\n");
    for (int i = 0; i < M; ++i) {
        new_cards[i] = patient_usr_fill();
        putchar('\n');
    }
    fwrite(cards, sizeof(patient), N, output);
    fwrite(new_cards, sizeof(patient), M, output);
    free(cards);
    free(new_cards);
    fclose(output);
    return 0;
}
/**
 * \brief Меню редагування текстового файлу
 * \details Відбувається перевірка існування вже відкритого файла.
 * Поки користувач не вибере вихід - не вийде з підменю
 * @return 0 в разі успішного виконання
 */
int edit_text(){
    if (is_opened_text){
        while (menu(3,
                "Дозапис в кінець файлу", append_text,
                "Виправлення (дані стираються)", clear_edit_text,
                "Очистити файл", clear_text))
            continue;
    } else{
        printf("Немає відкритих файлів\n");
    }
    return 0;
}
/**
 * \brief Меню редагування бінарного файлу
 * \details Відбувається перевірка існування вже відкритого файла.
 * Поки користувач не вибере вихід - не вийде з підменю
 * @return 0 в разі успішного виконання
 */
int edit_bin(){
    if (is_opened_bin){
        while (menu(4,
                    "Дозапис в кінець файлу", append_bin,
                    "Дозапис в початок файлу", add_front_bin,
                    "Виправлення (дані стираються)", clear_edit_bin,
                    "Очистити файл", clear_bin))
            continue;
    } else{
        printf("Немає відкритих файлів\n");
    }
    return 0;
}
/**
 * \brief Перегляд файлу
 * \details Відбувається перевірка існування вже відкритого файла.
 * Вивід вмісту файла на екран
 * @return 0 в разі успішного виконання
 */
int lookup_text(){
    char c;
    if (is_opened_text){
        FILE *temp_file = fopen(TEMP_FILENAME, "r");
        while ((c = fgetc(temp_file)) != EOF){
            putchar(c);
        }
        putchar('\n');
        fclose(temp_file);
    } else{
        printf("Немає відкритих файлів\n");
    }
    return 0;
}
/**
 * \brief Перегляд файлу
 * \details Відбувається перевірка існування вже відкритого файла.
 * Вивід вмісту файла на екран
 * @return 0 в разі успішного виконання
 */
int lookup_bin(){
    if (is_opened_bin){
        FILE *input = fopen(TEMP_FILENAME, "rb");
        int N;
        if (!(fread(&N, sizeof(N), 1, input))){
            printf("Помилка читання файлу\n");
            return 0;
        }
        patient *new_cards = (patient *)malloc(sizeof(patient)*N);
        fread(new_cards, sizeof(patient), N, input);
        fclose(input);
        for (int j = 0; j < N; ++j) {
            print_patient(new_cards[j], new_cards[j].is_removed);
        }
        free(new_cards);
    } else{
        printf("Немає відкритих файлів\n");
    }
    return 0;
}
/**
 * \brief Перегляд файлу
 * \details Відбувається перевірка існування вже відкритого файла.
 * Вивід видалених карт на екран
 * @return 0 в разі успішного виконання
 */
int lookup_deleted_bin(){
    if (is_opened_bin){
        FILE *input = fopen(TEMP_FILENAME, "rb");
        int N;
        if(!fread(&N, sizeof(N), 1, input)){
            printf("Помилка читання файлу\n");
            fclose(input);
            return 0;
        }
        patient *new_cards = (patient *)malloc(sizeof(patient)*N);
        fread(new_cards, sizeof(patient), N, input);
        fclose(input);
        for (int j = 0; j < N; ++j) {
            print_patient(new_cards[j], !new_cards[j].is_removed);
        }
        free(new_cards);
    } else{
        printf("Немає відкритих файлів\n");
    }
    return 0;
}
/**
 * \brief Створення нового бінарного файлу
 * \details Відбувається перевірка існування вже відкритого файла.
 * Запит користувача на ввід шляху файла, якщо такого не існує - пропозиція на створення.
 * Оновлюється статус відкритого активного файлу.
 * @return 0 в разі успішного виконання
 */
int open_text(){
    if (is_opened_text){
        printf("Файл уже відкрито, закрийте попередній!\n");
    } else {
        is_opened_text = true;
        FILE *existing_check;
        current_file_name = message_input("Введіть ім'я/шлях файлу\n");
        if (!(existing_check = fopen(current_file_name, "r"))){
            printf("Файлу не існує!\n");
            int create;
            input_int("Створити новий з такою назвою? (1/0)\n",&create,0,1);
            if (create){
                save_text();
            } else{
                current_file_name = NULL;
                is_opened_text = false;
            }
        }else{
            tranfer_all_text(current_file_name, TEMP_FILENAME);
            fclose(existing_check);
        }
    }
    return 0;
}
/**
 * \brief Створення нового текстового файлу
 * \details Відбувається перевірка існування вже відкритого файла.
 * Запит користувача на ввід шляху файла, якщо такого не існує - пропозиція на створення.
 * Оновлюється статус відкритого активного файлу.
 * @return 0 в разі успішного виконання
 */
int open_bin(){
    if (is_opened_bin){
        printf("Файл уже відкрито, закрийте попередній!\n");
    } else {
        is_opened_bin = true;
        FILE *existing_check;
        current_file_name = message_input("Введіть ім'я/шлях файлу\n");
        if (!(existing_check = fopen(current_file_name, "r"))){
            printf("Помилка відкриття, файлу не існує!\n");
            int create;
            input_int("Створити новий з такою назвою? (1/0)\n",&create,0,1);
            if (create){
                save_bin();
            } else{
                current_file_name = NULL;
                is_opened_bin = false;
            }
        }else{
            tranfer_all_bin(TEMP_FILENAME, current_file_name);
            fclose(existing_check);
        }
    }
    return 0;
}
/**
 * \brief Створення нового текстового файлу
 * \details Відбувається перевірка існування вже відкритого файла.
 * Через особливість роботи програми - тимчасовий робочий файл - зануляється.
 * Стан активного файла встановлюється відкритим.
 * @return 0 в разі успішного виконання
 */
int create_text(){
    if (is_opened_text){
        printf("Файл уже відкрито, закрийте попередній!\n");
    } else{
        FILE *text_fstream = fopen(TEMP_FILENAME, "w");
        fclose(text_fstream);
        is_opened_text = true;
    }
    return 0;
}
/**
 * \brief Створення нового бінарного файлу
 * \details Відбувається перевірка існування вже відкритого файла.
 * Через особливість роботи програми - тимчасовий робочий файл - зануляється,
 * туди записується кількість активних структур, тобто 0. Стан активного файла встановлюється відкритим.
 * @return 0 в разі успішного виконання
 */
int create_bin(){
    if (is_opened_bin){
        printf("Файл уже відкрито, закрийте попередній!\n");
    } else{
        FILE *bin_fstream = fopen(TEMP_FILENAME, "wb");
        int N = 0;
        fwrite(&N, sizeof(int), 1, bin_fstream);
        fclose(bin_fstream);
        is_opened_bin = true;
    }
    return 0;
}
/**
 * \brief Меню для роботи з файлом у текстовому форматі
 * \details Викликає меню для вибору роботи з файлом.
 * На кожен пункт окрема визначена функція, що також  може бути і підменю
 * @return Номер вибраного пункту
 */
int menu_text(){
    return menu(9, "Створити новий файл", create_text,
            "Відкрити файл", open_text,
            "Перегляд файлу", lookup_text,
            "Редагувати файл", edit_text,
            "Зберегти файл", save_text,
            "Зберегти файл як ...", saveas_text,
            "Закрити файл", close_text,
            "Скопіювати рядки з файла, починаючи з n-го", lines_taks,
            "Підрахувати кількість символів в останньому слові файлу", char_number);
}
/**
 * \brief Меню для роботи з файлом у бінарному форматі
 * \details Викликає меню для вибору роботи з файлом.
 * На кожен пункт окрема визначена функція, що також  може бути і підменю
 * @return Номер вибраного пункту
 */
int menu_bin(){
    return menu(9, "Створити новий файл", create_bin,
                "Відкрити файл", open_bin,
                "Перегляд файлу", lookup_bin,
                "Перегляд видалених карток", lookup_deleted_bin,
                "Редагувати файл", edit_bin,
                "Видалити за номером карти", remove_by_num,
                "Зберегти файл", save_bin,
                "Зберегти файл як ...", saveas_bin,
                "Закрити файл", close_bin);
}
/**
 * \brief Меню для вибору режиму роботи з файлом
 * \details Викликається меню 2 двома пунктами.
 * Зануляється поточне ім'я файлу
 * @return
 */
int menu_begin(){
    while (menu(2, "Робота з текстом", menu_text, "Робота з бінарним файлом", menu_bin)){
        current_file_name = NULL;
        continue;
    }
    return 0;
}
/**
 * Виклик головного меню
 */
int main() {
    clear();
    menu_begin();
    return 0;
}