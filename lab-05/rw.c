#include <stdlib.h>
#include <string.h>
#include "heads.h"

// уровнень важности в строчку
const char* priority_to_string(int priority) {
    switch (priority) {
        case 0: return "debug";
        case 1: return "info";
        case 2: return "warn";
        case 3: return "error";
        case 4: return "fatal";
        default: return "invalid"; // просто ошибка - слово добавил от себя
    }
}

// ввод с клавы
int from_stdin(Log *logs, int max_size) { // MAXREC
    int count; // сколько записей хочешь ?
    printf("Enter count of logs: ");
    if (scanf("%d", &count) != 1 || count <= 0 || count > max_size) {
        fprintf(stderr, "Error: invalid count of logs!\n");
        return 0;
    }
    getchar(); // очистка буфера

        // ввод каждой записи
    for (int i = 0; i < count; i++) {
        printf("Enter id, priority (0-4) и messege: ");
        if (scanf("%d %d", &logs[i].id, &logs[i].priority) != 2) { // проверяем что считано два значения
            fprintf(stderr, "Error: invalid input!\n"); // fprintf - запись формат. данных в файл
            return i; // кол-во введенных значений
        }
        getchar();
        fgets(logs[i].message, MAXCHAR, stdin); // сообщение лога
        logs[i].message[strcspn(logs[i].message, "\n")] = '\0'; // удаляем символ новой строки из конца строки, если он есть
    }
    // strscpn- возвращает индекс \n. по сути, заканчиваем так
    return count;
}

// данные из текстового файла
int from_text(const char *filename, Log *logs, int max_size) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error: can't open file");
        return 0;
    }
    int count = 0;
    while (count < max_size && fscanf(file, "%d %d", &logs[count].id, &logs[count].priority) == 2) { // fscanf - считывание данных из файла
        fgetc(file); // считываниие одного символа
        fgets(logs[count].message, MAXCHAR, file); // считывание строки
        logs[count].message[strcspn(logs[count].message, "\n")] = '\0';
        count++;
    }
    fclose(file);
    return count;
}

// данные из бинарного файла
int from_binary(const char *filename, Log *logs, int max_size) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Error: can't open file");
        return 0;
    }
    int count = fread(logs, sizeof(Log), max_size, file);
    fclose(file);
    return count;
}

// вывод данных
void print_logs(const Log *logs, int count) {
    printf("\nLogs:\n");
    for (int i = 0; i < count; i++) {
        printf("%d [%s] %s\n", logs[i].id, priority_to_string(logs[i].priority), logs[i].message);
    }
}

// сохранение в текстовый файл
void to_text(const char *filename, const Log *logs, int count) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Error: can't open file");
        return;
    }
    char buffer[512]; // буфер для строки

    for (int i = 0; i < count; i++) {
        snprintf(buffer, sizeof(buffer), "%d %d %s\n", logs[i].id, logs[i].priority, logs[i].message); // буфер в файл
        fputs(buffer, file); // запись строки в файл
    }

    fclose(file);
}

void to_binary(const char *filename, const Log *logs, int count) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        fprintf(stderr, "Error '%s'.\n", filename);
        return;
    }

    fwrite(&count, sizeof(int), 1, file); // запись количества элементов в файл (count)

    for (int i = 0; i < count; i++) { // запись каждого элемента logs
        fwrite(&logs[i].id, sizeof(int), 1, file); // запись id
        fwrite(&logs[i].priority, sizeof(int), 1, file); // запись priority
        int message_len = strlen(logs[i].message) + 1; // длина сообщения. (+1 для завершающего)
        fwrite(&message_len, sizeof(int), 1, file); // запись длины
        fwrite(logs[i].message, sizeof(char), message_len, file); // запись текста
    }

    fclose(file);
}