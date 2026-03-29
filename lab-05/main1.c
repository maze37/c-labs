#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "heads.h"

// -h -o = элементы
int main(int argc, char *argv[]) {  // argc - количество аргументов командной строки, argv - массив аргументов.
    Log logs[MAXREC]; // массив структур Log для хранения записей логов
    int log_count = 0; // хранение количества загруженных логов
/*
// треня argc, argv
    for (int i = 1; i < argc; i++) { // 1, т.к пропускаем первый элемент
        if (strcmp(argv[i], "-h") == 0){ // если равны, то вернет 0
            printf("Использование: %s [-i файл_входа] [-o файл_выхода] [-b (бинарный вход)] [-t (бинарный выход)]\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }
*/
    char *input_file = NULL;
    char *output_file = NULL;
    int binary_input = 0, binary_output = 0;
    int opt;
    // все опции обработаны - getopt вернет -1
    while ((opt = getopt(argc, argv, "i:o:bt")) != -1) { // обработки аргументов командной строки
        switch (opt) {
            case 'i': input_file = optarg; break;
            case 'o': output_file = optarg; break;
            case 'b': binary_input = 1; break;
            case 't': binary_output = 1; break;
            default:
                fprintf(stderr, "Help: %s [-i файл_входа] [-o файл_выхода] [-b (бинарный вход)] [-t (бинарный выход)]\n", argv[0]);
                exit(EXIT_FAILURE); // из библиотеки stdlib (завершение с ошибкой)
        }
    }


    if (input_file) {
        if (binary_input) {
            log_count = from_binary(input_file, logs, MAXREC);
        } else {
            log_count = from_text(input_file, logs, MAXREC);
        }
    } else {
        log_count = from_stdin(logs, MAXREC);
    }

    if (output_file) {
        if (binary_output) {
            to_binary(output_file, logs, log_count);
        } else {
            to_text(output_file, logs, log_count);
        }
    } else {
        print_logs(logs, log_count);
    }

    return 0;
}