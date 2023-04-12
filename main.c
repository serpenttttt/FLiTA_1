#include <stdio.h>
#include <locale.h>
#include <stdbool.h>
#include <stdlib.h>

// структура узла
typedef struct node {
    int value;  // значение, которое содержит узел
    struct node *next;
} node; // создаем тип данных node на основе узлов

// функция добавления узла в множество
void add_node(int value, node **set_i) {
    node *tmp = (node *) malloc(sizeof (node));
    tmp->value = value;
    tmp->next = *set_i;
    *set_i = tmp;
}

// удаление узлов множества
void destroy_nodes(node *set_i) {
    if (set_i == NULL) return;
    if (set_i->next != NULL) {
        set_i = set_i->next;
        destroy_nodes(set_i->next);
    }
    free(set_i);
}

// тест на число в двоичной системе счисления
bool binary_number_test(int test_value) {
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
void to_decimal(node *set_double, node **set_decimal) {
    int summ, number, length;
    number = set_double->value;
    if (set_double != NULL) {
        set_double = set_double->next;
        if (set_double != NULL) to_decimal(set_double, set_decimal);
        summ = 0;
        for (length = 0; number >= 1; ++length) {
            summ += (number % 10) * (1 << length); // второй множитель - альтернатива pow(2, length) - возведение в степень length
            number /= 10;
        }
        add_node(summ, set_decimal);
    }
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
    node *set_double = NULL;
    int input;
    puts("Введите элемент множества чисел в двоичной системе. \nЧтобы закончить ввод, введите любую букву.");
    while (scanf("%d", &input)) {    // проверка на ввод именно числа, а не других символов
        if (input >= 0 && !binary_number_test(input) && !compare_with_set_i(input, set_double)) {
            add_node(input, &set_double);
        } else {
            printf("Ошибка. ");
        }
        puts("Введите элемент множества чисел в двоичной системе.");
    }

    if (set_double != NULL) {

        // вывод множества 1
        puts("\nМножество чисел в двоичной системе.");
        print_set(set_double);

        // перевод множества 1 в множество 2, вывод множества 2
        puts("\nМножество чисел в десятичной системе.");
        node *set_decimal = NULL;
        to_decimal(set_double, &set_decimal);
        print_set(set_decimal);

        // освобождаем память
        destroy_nodes(set_double);
        destroy_nodes(set_decimal);
        puts("\nПамять очищена!");

    }
    return 0;
}
