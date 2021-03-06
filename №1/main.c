#include <stdio.h>
#include <math.h>

/**
 * \file
 */

/**
 * \brief Вибрає номер завдання лабораторної
 * \details \c labNumber - номер лабораторної\n
 * Цикл \c do \c while використовується церез необхідність спочатку
 * ввести дані, а потім перевірити належність відрізку [1;2]\n
 * Для перевірки введення цілого десяткового числа використовується функція inputD()\n
 * Для вибору подальшого завдання лабораторної використовується оператор \c switch
 * за допомогою якого викликається відповідна функція завдання, а саме task1() і task2().\n
 * Реалізовано виконання функції ще раз за бажанням користувача.
 * Прийомом одного символу займається функція get1char().
 * При отриманні символу '1' викликається функція вибору завдання choose_lab().
 */
void choose_lab();
/**
 * \brief Вибрає номер підзавдання завдання номер 1. Структура аналогічна ф-ції choose_lab()
 *
 */
void task1();
/**
 * \brief Виконання першого підзавдання першого завдання
 * \details Спочатку ініціалізуєм потрібні нам змінні.\n
 * Вводимо об'єм та площу (\c do \c while цикли використовуєм для перевірки на невід'ємність).\n
 * Здійснюємо обчислення. Виводим висоту паралелограма
 * \code
 * printf("Висота паралелограма (H = V/S) = ");
 * printf("%.3lf\n", H);
 * \endcode
 * Реалізовано виконання функції ще раз за бажанням користувача.
*/
void task1sub1();
/**
 * \brief Виконання другого підзавдання першого завдання
 * \details Ініціалізуєм змінні, вводим відповідні координати за допомогою inputD()\n
 * Обчислюєм відстань між точками \f$(x_1,y_1)\f$ і \f$(x_2,y_2) = \sqrt{(x_2-x_1)^2+(y_2-y_1)^2}\f$
*/
void task1sub2();
/**
 * \brief Вибрає номер підзавдання завдання номер 2.
 * \details Формат команди завантаження/збереження в обчислювальній системі
 * має вигляд:
 * № розрядів | 15 | 14 | 13 | 12 | 11 | 10 | 9 | 8 | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0
 * --|--|--|--|--|--|--|--|--|--|--|--|--|--|--|--|--
 * значення | 1 | 1 | 1 | 0 | 0 | 0 | 1 | D | R | R | R | R | A | A | A | A
 * Підпрограма 1 task2sub1()
 * Підпрограма2 task2sub2()\n
*/
void task2();
/**
 * \brief Виконання першого підзавдання другого завдання
 * \details Ініціалізація змінних.\n
 * Для зчитування вводу користувача використовується допоміжна змінна \c temp\n
 * На кожному етапі введення змінна є корректною, використовується функція  inputD()\n
 * За допомогою бітових операцій до змінної \c UnitStateWord записуються команди\n
 * Команда виводиться.\n
 * Реалізовано виконання функції ще раз за бажанням користувача.
*/
void task2sub1();
/**
 * \brief Виконання другого підзавдання другого завдання
 * \details
 * Вводиться шістнадцядкове число - код стану та перевіяється на відповідність заданій у варіанті команді.\n
 * Якщо число не є командою, яку ми хочем розібрати - виводим користувачу повідомлення.
 * При введенні вірної команди - вона розбирається на операнди та виводиться користувачу.
 * Реалізовано виконання функції ще раз за бажанням користувача.
*/
void task2sub2();
/**
 * \brief Просить 1 символ від користувача та коректно його повертає з типом char
 * \details Бере з \c stdin один символ, решту відкидає
 */
char get1char();
/**
 * \brief Функція для прийому цілих чисел
 * \param message Повідомлення, що виведеться користувачу перед уведенням
 * \param number Змінна, в яку запишеться вірне значення вводу
 * \details В функцію для валідного вводу передаєм вказівник для оптимізації роботи програми та пам'яті.\n
 * Ініціалізуєм змінну \c isD яка зберігатиме 0 - коли ввід не коректний та 1 -  коли корректний\n
 * На всяк випадок зануляєм змінну \c number.\n
 * В циклі з передумовою вимагаєм в користувача правильні данні для їх введення
 */
void inputD(char message[], int *number);
/**
 * \brief Функція для прийому дійсних чисел (аналогічна inputD() але з заміною цілих чисел на дійсні)
 * \param message Повідомлення, що виведеться користувачу перед уведенням
 * \param number Змінна, в яку запишеться вірне значення вводу
 */
void inputF(char message[],double *number);

int main() {
    printf("ЛАБОРАТОРНА РОБОТА №1\n"
           "БАЗОВІ ТИПИ ДАНИХ, УВЕДЕННЯ-ВИВЕДЕННЯ,\n"
           "БІТОВІ ОПЕРАЦІЇ, ОПЕРАЦІЇ ЗСУВУ\n"
           "Виконав студент групи КМ-82\n"
           "Бубела Дмитро\n"
           "Варіант №4\n");
    choose_lab();
    return 0;
}

void inputD(char message[], int *number)
{
    int isD = 0;
    *number = 0; // Зануляєм
    do
    {
        printf("%s", message); // Виводимо повідомлення користувачу
        isD = scanf("%d", number);// якщо ввід коректний isD = 1
        while (getchar()!='\n') continue; // дуже важлива функція для очищення вхідного потоку
    }
    while (!isD);// поки корисувач не введе значення - повторюєм виконання циклу
}

void inputF(char message[],double *number)
{
    int isF = 0;
    *number = 0.0;
    do
    {
        printf("%s", message);
        isF = scanf("%lf", number);
        while (getchar()!='\n') continue;
    }
    while (!isF);
}

char get1char()
{
    char i = getchar();
    while (getchar()!='\n') continue;
    return i;
}

void choose_lab()
{
    int labNumber;
    do
    {
        inputD("Виберіть завдання з лабораторної роботи 1, 2:\n", &labNumber);
    }
    while (labNumber < 1 || labNumber > 2);
    //Вимагаєм у користувача цифру 1 або 2
    switch (labNumber)
    {
        //Виконуєм завдання лабораторнної
        case 1: task1(); break;
        case 2: task2(); break;
    }
    printf("Хочете продовжити виконання лабораторної роботи? (0 / 1)\n");
    if (get1char() == '1')
    {
        choose_lab();
    }
}

void task1()
{
    int subTask = 0;
    do
    {
        inputD("Введіть номер підзавдання: 1, 2\n", &subTask);
    }
    while (subTask != 1 && subTask != 2);
    switch (subTask)
    {
        case 1: task1sub1(); break;
        case 2: task1sub2(); break;
    }
    printf("Бажаєте повторити вибір першого завдання? (0/1)\n");
    if (get1char() == '1')
    {
        task1();
    }
}

void task1sub1()
{
    double V,S,H;//Відповідні дані, що необхідні для здійснення обчислень
    printf("Я програма для обчислення висоти паралелепіпеда за формулою H = V/S\n");
    do
    {
        inputF("Введіть об'єм паралелограма:", &V);
    }
    while (V<0);
    do
    {
        inputF("Введіть площу основи паралелограма:", &S);
    }
    while (S<0);
    H = V/S;
    printf("Висота паралелограма (H = V/S) = ");
    printf("%.3lf\n", H);
    printf("Бажаєте повторити це завдання? (0/1)\n");
    if (get1char() == '1')
    {
        task1sub1();
    }
}

void task1sub2()
{
    double distance;
    int x1,x2,y1,y2;
    printf("Я програма для обчислення відстаней між точками.\n");
    printf("Введіть координати 2х точок (x1;y1),(x1;y2)\n");
    inputD("x1 = ",&x1);
    inputD("y1 = ",&y1);
    inputD("x2 = ",&x2);
    inputD("y2 = ",&y2);
    distance = sqrt((x2 - x1)*(x2 - x1)+(y2 - y1)*(y2 - y1));
    printf("Відстань між точками = %.3lf\n", distance);
    printf("Бажаєте повторити це завдання? (0/1)\n");
    if (get1char() == '1')
    {
        task1sub2();
    }
}

void task2()
{
    int subTask = 0;
    do
    {
        inputD("Введіть номер підзавдання (завантаження/збереження): 1, 2\n", &subTask);
    }
    while (subTask != 1 && subTask != 2);
    switch (subTask)
    {
        case 1: task2sub1(); break;
        case 2: task2sub2(); break;
    }
    printf("Бажаєте повторити вибір першого завдання? (0/1)\n");
    if (get1char() == '1')
    {
        task2();
    }
}

void task2sub1()
{
    char D,R,A; // напрям у регістр/пам'ять // перший операнд (регістр) // регістр адреси другого операнда
    unsigned int UnitStateWord; //слово стану
    int temp;
    printf("Я програма, що формує команду завантаження/збереження в обчислювальній системі\n");
    do
    {
        inputD("Уведіть напрям запису у регістр/пам'ять (1/0)\n", &temp);
    }
    while (temp != 1 && temp != 0);
    D = temp;
    do
    {
        inputD("Уведіть перший операнд (регістр) (0-15)\n", &temp);
    }
    while (temp < 0 || temp > 15);
    R = temp;
    do
    {
        inputD("Уведіть регістр адреси другого операнда (0-15)\n", &temp);
    }
    while (temp < 0 || temp > 15);
    A = temp;
    UnitStateWord = 0x71<<9;
    UnitStateWord |= (D & 1)<<8;
    UnitStateWord |= (R & 0xF)<<4;
    UnitStateWord |= (A & 0xF);
    printf("Слово стану пристрою %04x\n",UnitStateWord);
    printf("Бажаєте повторити це завдання? (0/1)\n");
    if (get1char() == '1')
    {
        task2sub1();
    }
}

void task2sub2()
{
    unsigned int UnitStateWord; //слово стану
    int isX;
    printf("Я програма, що розбирає команду завантаження/збереження в обчислювальній системі\n");
    do
    {
        printf("Уведіть cлово стану пристрою\n"
               "(16-кове число від 0 до e3ff):\n");
        isX = scanf("%x", &UnitStateWord);
        while (getchar()!='\n') continue;
    }
    while (!isX || UnitStateWord>0xFFFF);
    if (UnitStateWord>>8 != 0xe3 && UnitStateWord>>8 != 0xe2)
    {
        printf("Це не команда збереження/завантаження!!!\n");
    }
    else
    {
        printf("Напрямок передачі = %d\n", (UnitStateWord>>8) & 1);
        printf("Перший операнд (регістр) = %d\n", (UnitStateWord>>4) & 0xF);
        printf("Регістр адреси другого операнда = %d\n", UnitStateWord & 0xF);
    }
    printf("Бажаєте повторити це завдання? (0/1)\n");
    if (get1char() == '1')
    {
        task2sub2();
    }
}