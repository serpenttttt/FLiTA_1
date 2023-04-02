#include <stdio.h>
#include <locale.h>
#include <stdbool.h>
#include <stdlib.h>

// структура узла
typedef struct node {
    int value;  // значение, которое содержит узел
    struct node *next;
} node; // создаем тип данных node на основе узлов

// функция инициализации множества
node *init_set(int value) {
    node *first = (node *) malloc(sizeof(node));
    first->value = value;
    return first;
}

// функция добавления узла в множество
void add_node(int value, node *set_i) {
    while (set_i->next != NULL) {        // перемещаемся в начало списка
        set_i = set_i->next;
    }
   set_i->next = (node *) malloc(sizeof(node));
   set_i->next->next = NULL;
   set_i->next->value = value;
}

// удаление узла множества
node *destroy_node(node *set_i) {
    node *temp = set_i;
    if (set_i == NULL)
        return NULL;
    if (set_i->next == NULL) {
        printf("\nDeleted! %d\n", set_i->value);
        free(set_i);
        return NULL;
    }
    else {
        while (set_i->next->next != NULL) {
            set_i = set_i->next;
        }
        printf("\nDeleted! %d\n", set_i->next->value);
        free(set_i->next);
        set_i->next = NULL;
    }
    return temp;
}

// тест на число в двоичной системе счисления
bool test_double(int test_value) {
    for (int i = 0; test_value >= 1; ++i) {
        if ((test_value % 10 != 1) && (test_value % 10 != 0)) {
            return true;
        }
        test_value /= 10;
    }
    return false;
}

// тест на одинаковый элемент, который уже есть в множестве
bool compare_with_set_i(int same_value, node *set_i) {
    while (set_i != NULL) {
        if (same_value == set_i->value) {
            return true;
        }
        set_i = set_i->next;
    }
    return false;
}

// функция для перевода множества в двоичной системе счиления в множество в десятичной системе счисления
node *to_decimal(node *set_double) {
    node *set_decimal = NULL; // присваиваем указателю NULL
    int summ, number, length;
    while (set_double != NULL) {
        number = set_double->value;
        summ = 0;
        for (length = 0; number >= 1; ++length) {
            summ += (number % 10) *
                    (1 << length); // второй множитель - альтернатива pow(2, length) - возведение в степень length
            number /= 10;
        }
        if (set_decimal == NULL) {
            set_decimal = init_set(summ);
            set_double = set_double->next;
        } else {
            add_node(summ, set_decimal);
            set_double = set_double->next;
        }
    }
    return set_decimal;
}

// функция вывода множества
void print_set(node *set_i) {
    while (set_i != NULL) {
        printf("%d ", set_i->value);
        set_i = set_i->next;
    }
}

int main() {
    setlocale(LC_ALL, ".1251"); // устанавливает параметры для русского языка
    node *set_double = NULL; // присваиваем указателю NULL
    int input;
    puts("Введите элемент множества чисел в двоичной системе. \nЧтобы закончить ввод, введите любую букву.");
    while (scanf("%d", &input)) {    // проверка на ввод именно числа, а не других символов
        if (set_double == NULL) {
            if (input >= 0 && !test_double(input)) {
                set_double = init_set(input);
            } else {
                puts("Ошибка.");
            }
        }
        else {
            if (input >= 0 && !test_double(input) && !compare_with_set_i(input, set_double)) {
                add_node(input, set_double);
            } else {
                puts("Ошибка.");
            }
        }
        puts("Введите элемент множества чисел в двоичной системе.");
    }

    if (set_double != NULL) {
        // вывод множества 1
        puts("\nМножество чисел в двоичной системе.");
        print_set(set_double);

        // перевод множества 1 в множество 2, вывод множества 2
        puts("\nМножество чисел в десятичной системе.");
        node *set_decimal = to_decimal(set_double);
        print_set(set_decimal);

        // освобождаем память
        while(set_double != NULL){
            set_double = destroy_node(set_double);
            set_decimal = destroy_node(set_decimal);
        }
    }
    return 0;
}
