#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mystring.h"

#define DELIM " \t" // Пробелы
#define PROMPT "> " // ?

int isvowel(char a) {
    const char vowel[] = "aeiouyAEIOUY\0";
    for (int i = 0; vowel[i] != '\0'; i++) {
        if (a == vowel[i]) {
            return 1; // Символ является гласной
        }
    }
    return 0; // Символ не является гласной
}

int main() {
    char *input = myreadline(PROMPT);
    while (input != NULL) {
        printf("%s\n", input);

        clock_t start = clock();
        char *output = process(input);
        clock_t end = clock();

        long double t = (long double)(end - start) / CLOCKS_PER_SEC; // Исправлено
        if (output != NULL) { // Проверка на NULL
            printf("Result - %s\n", output);
            printf("time - %Lf\n", t);
            free(output);
        }
        free(input);
        input = myreadline(PROMPT);
    }
    return 0;
}

char *process(const char *str) {
    char *s = mystrdup(str); // копируем строчку которую ввел пользователь. Зовут его s.
    if (s == NULL){
        return 0;
    }
    int s_len = mystrlen(s); // Длина строки которую ввел пользователь.
    char *res = calloc(s_len + 1, sizeof(char)); // выделили память для строки + символ конца строки.
    if (res == NULL){
        free(s);
        return 0;
    }
    int len = 0;
    char *word = mystrtok(s, DELIM); // strtok - выделяет слова. Delim-пробелы.

    int count = 0; // считать кол-во гласных

    while (word != NULL) { // strtok может быть равен NULL, если больше токенов не найдено.
                count = 0;
        printf("Word: \"%s\"\n", word);

        for (int i = 0; word[i] != '\0'; i++){ // проверка на гласные буквы
                if (isvowel(word[i]) == 1){
                count++;
            }
        }
                if (count % 2 != 0 || mystrlen(word) == 1 || count == 0) {
                        if (len > 0){ // если перед этим словом было слово, то после него мы добавляем пробел
                                res[len] = ' '; // добавляем пробел
                                len++; // из-за пробела у нас увеличился len, поэтому мы его увеличиваем
                        }
                        int w_len = mystrlen(word); // если не было слова, то мы берем след. слово
                        mymemcpy(res + len, word, w_len * sizeof(char)); // копируем слово в результат
                        len += w_len;
        }
        word = mystrtok(NULL, DELIM);
    }
    free(s); // Содержится копия исходной строки
    res[len] = '\0'; // len = 0 изначально, если мы не встретили ни одного слова. Мы напишем ноль байт по индексу len = 0.
    res = realloc(res, (len + 1) * sizeof(char)); // выделяем окончательную память для строки без хвостов
    char *temp = realloc(res, (len+1) * sizeof(char));
    if (temp == NULL){
            free(res);
            return NULL;
    }
    return temp;
}