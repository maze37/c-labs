#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "heads.h"

int main(int argc, char *argv[]) {
    srand(time(NULL));

    Log *logs = malloc(MAXREC * sizeof(Log));
    if (!logs) {
        perror("Failed to allocate!!!!!");
        return EXIT_FAILURE;
    }
    int log_count = 0;
    char *input_file = NULL;
    char *output_file = NULL;
    int binary_input = 0, binary_output = 0;
    int sort_choice = 0, dir = 1;
    int opt;
    while ((opt = getopt(argc, argv, "i:o:btf:d")) != -1) {
        switch (opt) {
            case 'i': input_file = optarg; break;
            case 'o': output_file = optarg; break;
            case 'b': binary_input = 1; break;
            case 't': binary_output = 1; break;
            case 'f': sort_choice = atoi(optarg); break;
            case 'd': dir = 0; break;
            default:
                fprintf(stderr, "Help: %s [-i файл_входа] [-o файл_выхода] [-b (бин. вход)] [-t (бин. выход)] "
                        " [-f (0-id, 1-priority)] [-d (0-убыв, 1-возр)]\n", argv[0]);
                free(logs);
                exit(EXIT_FAILURE);
        }
    }


    if (input_file) {
        if (binary_input) {
            log_count = from_binary(input_file, logs, MAXREC);
        }
        else {
            log_count = from_text(input_file, logs, MAXREC);
        }
    }
    else {
        log_count = from_stdin(logs, MAXREC);
    }

    printf("\n");
    sort_time(qsort_sort, logs, log_count, sort_choice, dir, "qsort");
    sort_time(shaker_sort, logs, log_count, sort_choice, dir, "shaker sort");
    sort_time(double_selection_sort, logs, log_count, sort_choice, dir, "double selection sort");

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

    free(logs);
    return 0;
}