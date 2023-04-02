#include <stdio.h>
#include <locale.h>
#include <stdbool.h>
#include <stdlib.h>

// ��������� ����
typedef struct node {
    int value;  // ��������, ������� �������� ����
    struct node *next;
} node; // ������� ��� ������ node �� ������ �����

// ������� ������������� ���������
node *init_set(int value) {
    node *first = (node *) malloc(sizeof(node));
    first->value = value;
    return first;
}

// ������� ���������� ���� � ���������
void add_node(int value, node *set_i) {
    while (set_i->next != NULL) {        // ������������ � ������ ������
        set_i = set_i->next;
    }
   set_i->next = (node *) malloc(sizeof(node));
   set_i->next->next = NULL;
   set_i->next->value = value;
}

// �������� ���� ���������
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

// ���� �� ����� � �������� ������� ���������
bool test_double(int test_value) {
    for (int i = 0; test_value >= 1; ++i) {
        if ((test_value % 10 != 1) && (test_value % 10 != 0)) {
            return true;
        }
        test_value /= 10;
    }
    return false;
}

// ���� �� ���������� �������, ������� ��� ���� � ���������
bool compare_with_set_i(int same_value, node *set_i) {
    while (set_i != NULL) {
        if (same_value == set_i->value) {
            return true;
        }
        set_i = set_i->next;
    }
    return false;
}

// ������� ��� �������� ��������� � �������� ������� �������� � ��������� � ���������� ������� ���������
node *to_decimal(node *set_double) {
    node *set_decimal = NULL; // ����������� ��������� NULL
    int summ, number, length;
    while (set_double != NULL) {
        number = set_double->value;
        summ = 0;
        for (length = 0; number >= 1; ++length) {
            summ += (number % 10) *
                    (1 << length); // ������ ��������� - ������������ pow(2, length) - ���������� � ������� length
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

// ������� ������ ���������
void print_set(node *set_i) {
    while (set_i != NULL) {
        printf("%d ", set_i->value);
        set_i = set_i->next;
    }
}

int main() {
    setlocale(LC_ALL, ".1251"); // ������������� ��������� ��� �������� �����
    node *set_double = NULL; // ����������� ��������� NULL
    int input;
    puts("������� ������� ��������� ����� � �������� �������. \n����� ��������� ����, ������� ����� �����.");
    while (scanf("%d", &input)) {    // �������� �� ���� ������ �����, � �� ������ ��������
        if (set_double == NULL) {
            if (input >= 0 && !test_double(input)) {
                set_double = init_set(input);
            } else {
                puts("������.");
            }
        }
        else {
            if (input >= 0 && !test_double(input) && !compare_with_set_i(input, set_double)) {
                add_node(input, set_double);
            } else {
                puts("������.");
            }
        }
        puts("������� ������� ��������� ����� � �������� �������.");
    }

    if (set_double != NULL) {
        // ����� ��������� 1
        puts("\n��������� ����� � �������� �������.");
        print_set(set_double);

        // ������� ��������� 1 � ��������� 2, ����� ��������� 2
        puts("\n��������� ����� � ���������� �������.");
        node *set_decimal = to_decimal(set_double);
        print_set(set_decimal);

        // ����������� ������
        while(set_double != NULL){
            set_double = destroy_node(set_double);
            set_decimal = destroy_node(set_decimal);
        }
    }
    return 0;
}
