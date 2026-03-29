#include <stdlib.h>
#include <unistd.h>
#include "heads.h"

// sort_choice — определяет поле сортировки: 0 — по id, 1 — по priority.
// dir — направление сортировки: 1 — по возрастанию, 0 — по убыванию.
// sort_method = 0-шейкер, 1-двухс.

int main(int argc, char *argv[]) { // argc - количество аргументов командной строки, argv - массив
    Log logs[MAXREC]; // массив структур Log для хранения записей логов
    int log_count = 0; // хранение количества загруженных логов

    char *input_file = NULL;
    char *output_file = NULL;
    int binary_input = 0, binary_output = 0;
    int sort_method = 0, sort_choice = 0, dir = 1; // direction - направление
    int opt;

    while ((opt = getopt(argc, argv, "i:o:btm:f:d")) != -1) { // обработки аргументов командной строки
        switch (opt) {
            case 'i': input_file = optarg; break;
            case 'o': output_file = optarg; break;
            case 'b': binary_input = 1; break;
            case 't': binary_output = 1; break;
            case 'm': sort_method = atoi(optarg); break;
            case 'f': sort_choice = atoi(optarg); break;
            case 'd': dir = 0; break;
            default:
                fprintf(stderr, "Help: %s [-i файл_входа] [-o файл_выхода] [-b (бин. вход)] [-t (бин. выход)] "
                        " [-f (0-id, 1-priority)] [-d (0-убыв, 1-возр)]\n", argv[0]);
                exit(EXIT_FAILURE); // из библиотеки stdlib (завершение с ошибкой)
        }
    }

    if (input_file) {
        if (binary_input) {
            log_count = from_binary(input_file, logs, MAXREC);
        }
        else {
            log_count = from_text(input_file, logs, MAXREC);
        }
    } else {
        log_count = from_stdin(logs, MAXREC);
    }

    // всё с сортировкой
    if (sort_method == 0) {
        shaker_sort(logs, log_count, sort_choice, dir);
    }
    else if (sort_method == 1) {
        double_selection_sort(logs, log_count, sort_choice, dir);
    }

    if (output_file) {
        if (binary_output) {
            to_binary(output_file, logs, log_count);
        }
        else {
            to_text(output_file, logs, log_count);
        }
    }
    else {
        print_logs(logs, log_count);
    }

    return 0;
}