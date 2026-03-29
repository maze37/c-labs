#ifndef HEADS_H
#define HEADS_H
#include <stdio.h>

#define MAXREC 100000
#define MAXCHAR 256

typedef struct {
    int id;
    int priority;
    char message[MAXCHAR];
} Log;

const char* priority_to_string(int priority);
int from_stdin(Log *logs, int max_size);
int from_text(const char *filename, Log *logs, int max_size);
int from_binary(const char *filename, Log *logs, int max_size);
void print_logs(const Log *logs, int count);
void to_text(const char *filename, const Log *logs, int count);
void to_binary(const char *filename, const Log *logs, int count);
void shaker_sort(Log *logs, int size, int sort_choice, int dir);
void double_selection_sort(Log *logs, int size, int sort_choice, int dir);
void qsort_sort(Log *logs, int size, int sort_choice, int dir);
void sort_time(void (*sort_func)(Log *, int, int, int), Log *logs, int size, int sort_choice, int dir, const char *sort_name);

#endif // HEADS_H