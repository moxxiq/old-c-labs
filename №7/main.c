///@file
#include <stdio.h>
#include <string.h>
#include <values.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "lab_functions.h"

/*
 * Thank's to https://stackoverflow.com/questions/28331897/singly-linked-list-push-back
 * check returns!
 * NOTE:to function thats push put &head, 'cause SEGFAULT *NULL check
 */
typedef struct AEROFLOT_STRUCT{
    char *destination;///< Місце призначення
    int flight_number;///< Номер рейсу
    int type;///< Тип літака
} Aeroflot;

enum type_of_aeroplane{
    ELSE,///< Тип, що не належить переліченим
    CIVIL,///< Цивільні літаки
    MILITARY///< Військові
};
enum menu_enum{
    INIT = 1,///< Створення нового списку
    PUSH_TOP,///< Додавання в початок
    PUSH_BACK,///< Додавання в кінець
    PUSH_N,///< Додавання після елемента з номером n
    PUSH_KEY,///< Додавання після елемента з заданим ключем
    POP,///< Видалення елемента з початку списку
    REMOVE_BACK,///< Видалення елемента з кінця списку
    REMOVE_N,///< Видалення елемента з заданим номером в списку
    REMOVE_KEY,///< Видалення елемента з заданим ключем
    SHOW,///< Виведення вмісту списку на екран
    SORT,///< Упорядкування елементів
    GET_BY_CITY,///< Виведення рейсів в задане місто
    EXIT///< Вихід
};

char *name_of_type[] = {"ELSE", "CIVIL", "MILITARY"};

typedef struct single_linked_list_aeroflot_struct{
    Aeroflot race;///<Поточний рейс
    struct single_linked_list_aeroflot_struct *next;///<Посилання на наступний рейс
}List_aeroflot;


/**
 * @brief Користувач вказує місце призначення, номер рейсу, тип літака.
 * @details Серед нюансів: звернання до полів структури за допомогою \c ->\n
 * функція для введення тексту message_input()\n
 * функція для введення чисел input_int()\n
 * @return Заповнена користувачем структура \c Aeroflot
 */
Aeroflot aeroflot_user_fill(){
    Aeroflot aeroplane;
    aeroplane.destination = message_input("Місце призначення: ");
    toupper_chrs(aeroplane.destination);
    input_int("Номер рейсу: ", &aeroplane.flight_number, 0, INT_MAX);

    char *type = message_input("Тип літака (military/civil/else): ");
    putchar('\n');
    toupper_chrs(type);
    if (!strcmp(type, "CIVIL")){
        aeroplane.type = CIVIL;
    } else if (!strcmp(type, "MILITARY")){
        aeroplane.type = MILITARY;
    } else{
        aeroplane.type = ELSE;
    }
    return aeroplane;
}
/**
 * @brief Порівняння двох змінних типів \c Aeroflot
 * @details Виконується почергове порівняння полів структури
 * @param first Вказівник на першу структуру
 * @param second Вказівник на другу структуру
 * @return 0 якщо структури однакові \n
 * 1 якщо структури відрізняються місцем призначення\n
 * 2 якщо структури відрізняються номером відправлення\n
 * 3 якщо структури відрізняються типом літака
 */
int aeroflot_cmp(Aeroflot *first, Aeroflot *second){
    if (first->flight_number != second->flight_number)return 2;
    if (first->type != second->type) return 3;
    if (strcmp(first->destination, second->destination)) return 1;
    //else
    return 0;
}
/**
 * \brief Виводим структуру типу Aeroflot в частково відформатованому вигляді
 * \details Форматований вихід здійснюється за допомогою операцій лівостороннього вирівнювання
 * @param aeroplanes Структура для виводу
 */
void print_single_aeroflot(Aeroflot aeroplanes){
    printf("%-25s%-17d%-10s\n",
               aeroplanes.destination,
               aeroplanes.flight_number,
           name_of_type[aeroplanes.type]);
}
/**
 * @brief Вивід рейсів з заданою назвою
 * @details Користувач вводить місто, за яким буде здійснюватись пошук
 * @param head Голова списку в якому здійснюватиметься пошук
 */
void get_by_city(List_aeroflot **head){
    char *city = message_input("Введіть місто за яким здійснюється пошук рейсу\n");
    toupper_chrs(city);
    bool is = false;
    List_aeroflot *iter = *head;
    printf("Місце призначення        Номер рейсу      Тип літака\n");
    while (iter){
        if (!strcmp(iter->race.destination, city)){
            print_single_aeroflot(iter->race);
            is = true;
        }
        iter = iter->next;
    }
    if (!is){
        printf("Відповідних рейсів не знайдено\n");
    }
}
/**
 * @brief Чи пустий список
 * @details Використовується бібліотека для типу \c bool
 * @warning **head не має бути NULL інакше пошкодження пам'яті
 * @param head Власне список, що буде перевірятись
 * @return 1 якщо пустий, 0 якщо ні
 */
bool is_empty(List_aeroflot **head){
    if (*head == NULL){
        return true;
    }
    return false;
}

/**
 * @brief Додавання в початок
 * @details Для додаткової функціональності створюється та повертається \c new_head\n
 * На початку виконується перевірка на пустоту, а потім додається елемент в однозв'язний список
 * @param old_head Стара голова списку в який буде додаватись
 * @param new_race Сам рейс, який додається
 * @return Новий елемент списку
 */
List_aeroflot *push_top(List_aeroflot **old_head, Aeroflot new_race){
    List_aeroflot *new_head = (List_aeroflot *)malloc(sizeof(List_aeroflot));
    new_head->race = new_race;
    if (*old_head == NULL){
        *old_head = new_head;
        new_head->next = NULL;
    } else{
        List_aeroflot *head = *old_head;
        new_head->next = head;
        *old_head = new_head;
    }
    return new_head;
}
/**
 * @brief Додавання в кінець
 * @details Для додаткової функціональності створюється та повертається \c new_node\n
 * Далі проходимось по списку в кінець і додаєм
 * @param head Голова списку в який буде додаватись
 * @param new_race Сам рейс, який додається
 * @return Новий елемент списку
 */
List_aeroflot *push_back(List_aeroflot **head, Aeroflot new_race){
    List_aeroflot *new_node = (List_aeroflot *)malloc(sizeof(List_aeroflot));
    new_node->race = new_race;
    new_node->next = NULL;
    if (!*head){
        *head = new_node;
        return new_node;
    }
    List_aeroflot *node = *head;
    while (node->next){
        node = node->next;
    }
    node->next = new_node;
    return new_node;
}
/**
 * @brief Додавання рейсу після певного номера у списку
 * @details Вводиться змінна - рахівник, за її допомогою доходим до потрібного елемента.\n
 * Для додаткової функціональності створюється та повертається \c new_head\n
 * @param head Голова списку в який буде додаватись
 * @param new_race Сам рейс, який додається
 * @param N Номер після якого буде доданий рейс
 * @return Новий елемент списку, або голова, якщо не існує такого номера
 */
List_aeroflot *push_after_n(List_aeroflot **head, Aeroflot new_race, int N){
    List_aeroflot *node = *head;
    int i = 0;
    while (node->next != NULL && i != N){
        node = node->next;
        i++;
    }
    if (i == N){
        List_aeroflot *new_node = malloc(sizeof(List_aeroflot));
        new_node->race = new_race;
        new_node->next = node->next;
        node->next = new_node;
        return new_node;
    } else{
        printf("\x1b[6;30;41mПомилка!\x1b[0m  Такого номера немає в списку\n");
    }
    return *head;
}
/**
 * @brief Додавання рейсу після певного ключа у списку
 * @details Проходить по елементах списку і порінює їх aeroflot_cmp(). При відсутності виводить помилку.
 * Для додаткової функціональності створюється та повертається \c new_head\n
 * @param head Голова списку в який буде додаватись
 * @param new_race Сам рейс, який додається
 * @param key_race Рейс, за яким будемо вставляти елемент
 * @return Новий елемент списку, або голова, якщо не існує такого номера
 */
List_aeroflot *push_after_key(List_aeroflot **head, Aeroflot new_race,  Aeroflot key_race){
    List_aeroflot *node = *head;
    while (node->next != NULL && aeroflot_cmp(&node->race,&key_race)){
        node = node->next;
    }
    if (!aeroflot_cmp(&node->race,&key_race)){
        List_aeroflot *new_node = malloc(sizeof(List_aeroflot));
        new_node->race = new_race;
        new_node->next = node->next;
        node->next = new_node;
    } else{
        printf("\x1b[6;30;41mПомилка!\x1b[0m  Такого рейсу немає в списку\n");
    }
    return *head;
}
/**
 * @brief Службова функція видалення
 * @details Видаляє елемент списку по вказівнику
 * @param head Голова списку з якого буде видалятись
 * @param node Елемент, який буде видалятись
 */
void remove_aeroflot_ptr(List_aeroflot **head, List_aeroflot *node){
    List_aeroflot *cur_node = *head;
    if (cur_node == node){
        *head = cur_node->next;
        free(cur_node);
        return;
    }
    List_aeroflot *node_to_delete;
    while (cur_node->next != node) {
        cur_node = cur_node->next;
    }
    node_to_delete = cur_node->next;
    cur_node->next = node_to_delete->next;
    free(node_to_delete);
}
/**
 * @brief Видалення першого елемента списку
 * @details Функція, що видаляє голову списку, використовується допоміжна службова функція remove_aeroflot_ptr()
 * @param head Голова списку з якого буде видалятись
 * @return Видалений елемент
 */
List_aeroflot *pop(List_aeroflot **head){
    if (is_empty(head)){
        printf("Список порожній\n");
        return *head;
    }
    List_aeroflot *head_to_return = malloc(sizeof(List_aeroflot*));
    *head_to_return = **head;
    remove_aeroflot_ptr(head,*head);
    return head_to_return;
}
/**
 * @brief Видалення певного елемента списку (за номером)
 * @details Видаляє Нтий елемент за допомогою remove_aeroflot_ptr()
 * @param head Голова списку з якого буде видалятись
 * @param N Номер, який буде видалятись
 * @return Видалений елемент
 */
List_aeroflot *remove_aeroflot_n(List_aeroflot **head, int N) {
    List_aeroflot *node = *head;
    List_aeroflot *node_to_return = malloc(sizeof(List_aeroflot *));
    int i = 0;
    if (is_empty(head)) {
        printf("Список порожній!\n");
        return NULL;
    }
    while (node->next != NULL && i != N){
        node = node->next;
        i++;
    }
    if (i==N){
        *node_to_return = *node;
        remove_aeroflot_ptr(head, node);
        return node_to_return;
    }
    printf("\x1b[6;30;41mПомилка!\x1b[0m  Такого рейсу немає в списку\n");
    return NULL;
}
/**
 * @brief Видалення певного елемента списку (за ключем)
 * @details Видаляє елемент з заданим ключем
 * @param head Голова списку з якого буде видалятись
 * @param key Ключ, за яким видалиться елемент списку
 */
void remove_aeroflot_key(List_aeroflot **head, Aeroflot key){
    List_aeroflot *node = *head;
    if (is_empty(head)){
        printf("Список порожній\n");
        return;
    }
    while (node->next && aeroflot_cmp(&node->race, &key)){
        node = node->next;
    }
    if (!aeroflot_cmp(&node->race, &key)){
        remove_aeroflot_ptr(head, node);
    } else{
        printf("\x1b[6;30;41mПомилка!\x1b[0m  Такого рейсу немає в списку\n");
    }
}
/**
 * @brief Видалення останнього елементу зі списку
 * @details Проходим в кінець списку і видаляєм елемент
 * @param head Голова списку з якого буде видалятись
 * @return Видалений елемент
 */
List_aeroflot *remove_back(List_aeroflot **head){
    if (is_empty(head)){
        printf("Список порожній\n");
        return *head;
    }
    List_aeroflot *cur_node = *head;
    while (cur_node->next){
        cur_node = cur_node->next;
    }
    List_aeroflot *node_to_return = malloc(sizeof(List_aeroflot *));
    *node_to_return = *cur_node;
    remove_aeroflot_ptr(head, cur_node);
    return node_to_return;
}

/**
 * @brief Видалення всього списку
 * @details Видаляється голова допоки список не порожній
 * @param head Голова списку з якого буде видалятись
 */
void remove_list(List_aeroflot **head){
    while (*head){
        pop(head);
    }
}
/**
 * @brief Вивід усього списку на екран
 * @details Виводиться "шапка" а потім почергово кожен елемент списку за допопмогою print_single_aeroflot()
 * @param head Голова списку, який буде виводитись
 */
void print_aeroflot_list(List_aeroflot **head){

    if (head == NULL || *head == NULL){
        printf("Список порожній\n");
    } else{
        printf("Місце призначення        Номер рейсу      Тип літака\n");
        List_aeroflot *node = *head;
        while (node->next != NULL){
            print_single_aeroflot(node->race);
            node = node->next;
        }
        print_single_aeroflot(node->race);
    }
}
/**
 * @brief Службова функція для підрахунку довжини списку
 * @details Використовується в інший функціях
 * @param head Голова списку, довжина якого буде обчислюватись
 * @return Число - довжина списку
 */
int get_list_length(List_aeroflot *head){
    int i = 0;
    List_aeroflot *node = head;
    if (node) {
        i++;
        while (node = node->next)i++;
    }
    return i;
}
/**
 * @brief Порівняння елементів по номеру рейсу
 * @details В якості аргументів взято вказівники
 * @param first Перший елемент списку
 * @param second Другий елемент списку
 * @return \c true якщо <= інакше - false
 */
bool less_eq_flight_number(Aeroflot *first, Aeroflot *second){
    return (bool)(first->flight_number <= second->flight_number);
}
/**
 * @brief Порівняння елементів по типу літака
 * @details В якості аргументів взято вказівники
 * @param first Перший елемент списку
 * @param second Другий елемент списку
 * @return \c true якщо <= інакше - false
 */
bool less_eq_type(Aeroflot *first, Aeroflot *second){
    return (bool)(first->type <= second->type);
}
/**
 * @brief Порівняння елементів по місцю призначення
 * @details Порівняння відбувається в алфавітному порядку
 * @param first Перший елемент списку
 * @param second Другий елемент списку
 * @return \c true якщо <= інакше - false
 */
bool less_eq_race_destination(Aeroflot *first, Aeroflot *second){
    int min = strlen(first->destination);
    if (strlen(first->destination) > strlen(second->destination)) min  = strlen(second->destination);
    for (int i = 0; i < min; ++i) {
        if (tolower(first->destination[i]) == tolower(second->destination[i])) continue;
        if (tolower(first->destination[i]) < tolower(second->destination[i])) return true;
        return false;
    }
    if (strlen(first->destination) < strlen(second->destination)) return true;
    return false;
}
/**
 * Порівняння елементів відносно переданої функції порівняння
 * @param first Перший елемент списку
 * @param second Другий елемент списку
 * @param less_equal Функція порівняння
 * @return \c true якщо <= інакше - false
 */
bool less_eq_list(List_aeroflot *first, List_aeroflot *second, bool (*less_equal)()){
    if (!first) return false;
    if (!second) return true;
    return (*less_equal)(&first->race, &second->race);
}
/**
 * @brief Злиття
 * @details Пояснення алгоритму сортування не входить в лабораторну роботу
 */
List_aeroflot *merge_list(List_aeroflot *first, List_aeroflot *second, bool (*less_equal)()) {
    List_aeroflot *head_to_return, *iter_list;
    if (!first){
        return second;
    }
    if (!second){
        return first;
    }
    if (less_eq_list(first, second, less_equal)){
        head_to_return = first;
        first = first->next;
    } else{
        head_to_return = second;
        second = second->next;
    }
    iter_list = head_to_return;
    while (first || second){
        if (less_eq_list(first, second, less_equal)){
            iter_list->next = first;
            first = first->next;
        } else{
            iter_list->next = second;
                second = second->next;
        }
        iter_list = iter_list->next;
    }
    iter_list->next = NULL;
    return head_to_return;
}
/**
 * @brief Алгоритм сортування злиттям
 * @details Пояснення алгоритму сортування не входить в лабораторну роботу
 */
List_aeroflot *sort_aeroflot_list (List_aeroflot *head, int length, bool (*less_equal)()){
    if (length < 2){
        return head;
    }
    List_aeroflot *half_head, *node = head;
    int i = 0;
    while (i<length/2-1){
        node = node->next;
        i++;
    }
    half_head = node->next;
    node->next = NULL;
    return merge_list(sort_aeroflot_list(head, i+1, less_equal), sort_aeroflot_list(half_head,length-i-1, less_equal), less_equal);
}
/**
 * @brief Створення нового списку (затирання старого)
 * @details По факту старий список просто очищається (при створенні нового виникали б втрати пам'яті)
 * @param old_head Голова старого списку
 * @return Голову нового списку
 */
List_aeroflot re_init_list(List_aeroflot **old_head){
    remove_list(old_head);
    push_back(old_head, aeroflot_user_fill());
    return **old_head;
}
/**
 * @brief Сортування списку за вибором користувача
 * @details Виконується сортування за зчитуваним варіантом користувача
 * @param head Голова списку, який сортується
 */
void sort_list(List_aeroflot **head){
    printf("За чим сортувати список?\n"
           "1.  Місцем призначення\n"
           "2.  Номером рейсу\n"
           "3.  Типом літака\n"
    );
    bool (*l_eq)();
    switch (get_int("",1,3)){
        case 1:
            l_eq = less_eq_race_destination;
            break;
        case 2:
            l_eq =  less_eq_flight_number;
            break;
        case 3:
            l_eq = less_eq_type;
            break;
    }
    *head = sort_aeroflot_list(*head, get_list_length(*head), l_eq);

}
/**
 * @brief Меню
 * @details Реалізація вибору виконання функції за допомогою оператора \c switch\n
 * Нижче наведений код, для додаткової інформації натисніть по назві функції.
 * @param head Голова списку над яким виконуватимуться маніпуляції
 * @return Чи продовжувати виконання функції
 */
bool menu(List_aeroflot **head){
    int choice;
    printf(" _________________________________________________\n"
           "|                     Меню                        |\n");
    printf("%-50s|\n","|1.  Створення списку                             ");
    printf("%-50s|\n","|2.  Додавання в початок                          ");
    printf("%-50s|\n","|3.  Додавання в кінець                           ");
    printf("%-50s|\n","|4.  Додавання після елемента з номером n         ");
    printf("%-50s|\n","|5.  Додавання після елемента з заданим ключем    ");
    printf("%-50s|\n","|6.  Видалення елемента з початку списку          ");
    printf("%-50s|\n","|7.  Видалення елемента з кінця списку            ");
    printf("%-50s|\n","|8.  Видалення елемента з заданим номером в списку");
    printf("%-50s|\n","|9.  Видалення елемента з заданим ключем          ");
    printf("%-50s|\n","|10. Виведення вмісту списку на екран             ");
    printf("%-50s|\n","|11. Упорядкування елементів                      ");
    printf("%-50s|\n","|12. Виведення рейсів в задане місто              ");
    printf("%-50s|\n","|13. Вихід                                        ");
    printf(" ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n");
    input_int("Виберіть пункт меню\n", &choice, 0, 13);
    switch (choice) {
        case 0: return false;
        case INIT:
            re_init_list(head);
            break;
        case PUSH_TOP:
            push_top(head, aeroflot_user_fill());
            break;
        case PUSH_BACK:
            push_back(head, aeroflot_user_fill());
            break;
        case PUSH_N:
            push_after_n(head, aeroflot_user_fill(), get_int("Після якого номера додати число?\n", 0, INT_MAX));
            break;
        case PUSH_KEY:
            printf("Введіть новий ключ та ключ пошуку\n");
            push_after_key(head, aeroflot_user_fill(), aeroflot_user_fill());
            break;
        case POP:
            pop(head);
            break;
        case REMOVE_BACK:
            remove_back(head);
            break;
        case REMOVE_N:
            remove_aeroflot_n(head, get_int("Який номер видалити?\n", 0, INT_MAX));
            break;
        case REMOVE_KEY:
            printf("Введіть ключ пошуку\n");
            remove_aeroflot_key(head, aeroflot_user_fill());
            break;
        case SHOW:
            print_aeroflot_list(head);
            break;
        case SORT:
            sort_list(head);
            break;
        case GET_BY_CITY:
            get_by_city(head);
            break;
        case EXIT:
            return false;
        default:
            printf("Something went wrong");
    }
    return true;
}
/**
 * @brief Завдання Лабораторної роботи номер 5
 * @details Адаптація під роботу з лінійними списками.
 * Додавання здійснюється в кінець списку за допомогою push_back().
 * Для введення структури типу Aeroflot використовується aeroflot_user_fill().\n
 * Виводиться щойно уведений список print_aeroflot_list().
 * Сортується за номером рейсу sort_aeroflot_list() less_eq_flight_number().
 * Виводиться список
 * @param task1_list_head Голова списку над яким виконуватимуться маніпуляції
 * @return Голова списку
 */
List_aeroflot **task_1(List_aeroflot **task1_list_head) {
    printf("Виконується завдання з Лабораторної роботи номер 5\n");
    for (int i = 0; i < 5; ++i) {
        push_back(task1_list_head, aeroflot_user_fill());
    }
    print_aeroflot_list(task1_list_head);
    printf("Виконується сортування за номером рейсу\n");
    *task1_list_head = sort_aeroflot_list(*task1_list_head, get_list_length(*task1_list_head), less_eq_flight_number);
    print_aeroflot_list(task1_list_head);
    return task1_list_head;
}
/**
 * Функція для виклику меню
 * @param list Голова списку над яким виконуватимуться маніпуляції
 */
void calling_menu(List_aeroflot **list){
    bool to_continue;
    do{
        to_continue = menu(list);
    }while (to_continue);
}

int main() {
    List_aeroflot *task1_list_head = NULL;
    clear();
    task_1(&task1_list_head);
    calling_menu(&task1_list_head);
    return 0;
}
