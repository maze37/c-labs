#include <stdio.h>
#include <stdlib.h>

// Инд зад - удалить все символы в списке до первой точки и после последней точки с запятой

typedef struct Node {
    char ch;
    struct Node *next; // указатель на следующее значение
} Node;

void push(Node **head, char ch) {
    Node *new_node = (Node*)malloc(sizeof(Node)); // выделяем память для нового узла
    new_node->ch = ch; // значение ноды
    new_node->next = NULL; // указывает на пустоту, тк он последний элемент

    if (*head == NULL) { // ну если список пуст, то создаю новую ноду
        *head = new_node;
    }
    else { // пройдусь до конца списка, чтоб добавить в конец самый
        Node *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

void printlist(const Node *head) { // печатаю
    while (head) {
        printf("%c", head->ch);
        head = head->next;
    }
    printf("\n");
}

// я тут просто ищу точку и точку с запятой. если нашел, то перехожу к обработке.
// я не удаляю никакие узлы, я просто очищаю и оставляю только то, что мне нужно по условию
void process(Node **head) {
    Node *current = *head;
    Node *firstdot = NULL;
    Node *lastsemicolon = NULL;

    // файндим первую точку и точку с запятой
    while (current != NULL) {
        if (current->ch == '.' && firstdot == NULL) {
            firstdot = current; // Запоминаем первую точку
        }
        if (current->ch == ';') {
            lastsemicolon = current; // Запоминаем последнюю точку с запятой
        }
        current = current->next;
    }

    if (firstdot != NULL) {
        // чистим до первой точки
        current = *head;
        while (current != firstdot) {
            Node *next_node = current->next;
            free(current);
            current = next_node;
        }
        *head = firstdot; // тк точка теперь первый символ, то хед должен указывать на него

        // чистим после точки с запятой
        if (lastsemicolon != NULL) {
            current = lastsemicolon->next;
            lastsemicolon->next = NULL; // Отсечем список после точки с запятой
            while (current != NULL) {
                Node *next_node = current->next;
                free(current);
                current = next_node;
            }
        }
    }
        // если точки нет, то нужно очистить абсолютно все
    else {
        current = *head;
        while (current != NULL) {
            Node *next_node = current->next;
            free(current);
            current = next_node;
        }
        *head = NULL;
    }
}

int main() {
    Node *head = NULL;
    char ch;

    // Читаем символы до EOF
    while ((ch = getchar()) != EOF) {
        push(&head, ch);
    }

    printf("\n");
    printf("Исходная строка: \n");
    printlist(head);

    process(&head);

    printf("Модифицированная строка: \n");
    printlist(head);
    printf("\n");

    // Освобождаем память для списка
    while (head != NULL) {
        Node *next_node = head->next;
        free(head);
        head = next_node;
    }

    return 0;
}