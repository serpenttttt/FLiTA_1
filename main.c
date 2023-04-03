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
node *init_set() {
    node *first = (node *) malloc(sizeof(node));
    first->next = NULL;
    return first;
}

// ������� ���������� ���� � ���������
void add_node(int value, node *set_i) {
    while (set_i->next != NULL) {        // ������������ � ������ ������
        set_i = set_i->next;
    }
    set_i->value = value;
    set_i->next = (node *) malloc(sizeof(node));
    set_i->next->next = NULL;
}

// �������� ���� ���������
void destroy_nodes(node *set_i) {
    if (set_i == NULL) return;
    if (set_i->next != NULL) {
        set_i = set_i->next;
        destroy_nodes(set_i->next);
    }
    free(set_i);
}

// ���� �� ����� � �������� ������� ���������
bool binary_number_test(int test_value) {
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
    while (set_i->next != NULL) {
        if (same_value == set_i->value) {
            return true;
        }
        set_i = set_i->next;
    }
    return false;
}

// ������� ��� �������� ��������� � �������� ������� �������� � ��������� � ���������� ������� ���������
node *to_decimal(node *set_double) {
    node *set_decimal = init_set();
    int summ, number, length;
    while (set_double->next != NULL) {
        number = set_double->value;
        summ = 0;
        for (length = 0; number >= 1; ++length) {
            summ += (number % 10) *
                    (1 << length); // ������ ��������� - ������������ pow(2, length) - ���������� � ������� length
            number /= 10;
        }
        add_node(summ, set_decimal);
        set_double = set_double->next;
    }
    return set_decimal;
}

// ������� ������ ���������
void print_set(node *set_i) {
    while (set_i->next != NULL) {
        printf("%d ", set_i->value);
        set_i = set_i->next;
    }
}

int main() {
    setlocale(LC_ALL, ".1251"); // ������������� ��������� ��� �������� �����
    node *set_double = init_set();
    int input;
    puts("������� ������� ��������� ����� � �������� �������. \n����� ��������� ����, ������� ����� �����.");
    while (scanf("%d", &input)) {    // �������� �� ���� ������ �����, � �� ������ ��������
        if (input >= 0 && !binary_number_test(input) && !compare_with_set_i(input, set_double)) {
            add_node(input, set_double);
        } else {
            printf("������. ");
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
        destroy_nodes(set_double);
        destroy_nodes(set_decimal);
        puts("\n������ �������!");

    }
    return 0;
}
