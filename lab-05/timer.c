#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "heads.h"

void sort_time(void (*sort_func)(Log *, int, int, int), Log *logs, int size, int sort_choice, int dir, const char *sort_name) {
    clock_t start = clock();
    sort_func(logs, size, sort_choice, dir);
    clock_t end = clock();
        double finish = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%s ended for %0.8f sec\n", sort_name, finish);
}