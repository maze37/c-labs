#include <stdlib.h>
#include "heads.h"

// меняет местами два элемента массива
void swap(Log *a, Log *b) {
    Log temp = *a;
    *a = *b;
    *b = temp;
}

// шейкерная сортировка
void shaker_sort(Log *logs, int size, int sort_choice, int dir) {
    int left = 0;
    int right = size - 1;
    int swapped = 1;

    while (left < right && swapped) {
        swapped = 0;
        // проход слева направо
        for (int i = left; i < right; i++) {
            int a, b;
            if (sort_choice == 0) {
                a = logs[i].id;
                b = logs[i + 1].id;
            } else {
                a = logs[i].priority;
                b = logs[i + 1].priority;
            }

            if ((dir == 1 && a > b) || (dir == 0 && a < b)) {
                swap(&logs[i], &logs[i + 1]);
                swapped = 1;
            }
        }
        right--;

        // проход справа налево
        for (int i = right; i > left; i--) {
            int a, b;
            if (sort_choice == 0) {
                a = logs[i].id;
                b = logs[i - 1].id;
            } else {
                a = logs[i].priority;
                b = logs[i - 1].priority;
            }

            if ((dir == 1 && a < b) || (dir == 0 && a > b)) {
                swap(&logs[i], &logs[i - 1]);
                swapped = 1;
            }
        }
        left++;
    }
}

// двухсторонняя сортировка выбором
void double_selection_sort(Log *logs, int size, int sort_choice, int dir) {
    for (int i = 0; i < size / 2; i++) {
        int min_idx = i;
        int max_idx = i;

        // минимальный и максимальный элементы в оставшейся части
        for (int j = i + 1; j < size - i; j++) {
            int current;
            int minv;
            int maxv;

            if (sort_choice == 0) {  // по id
                current = logs[j].id;
                minv = logs[min_idx].id;
                maxv = logs[max_idx].id;
            } else {  // по priority
                current = logs[j].priority;
                minv = logs[min_idx].priority;
                maxv = logs[max_idx].priority;
            }
            // новый минимум
            if (dir == 1) {  // по возрастанию
                if (current < minv) {
                    min_idx = j;
                }
            } else {  // по убыванию
                if (current > minv) {
                    min_idx = j;
                }
            }

            // новый максимум
            if (dir == 1) {  // по возрастанию
                if (current > maxv) {
                    max_idx = j;
                }
            } else {  // по убыванию
                if (current < maxv) {
                    max_idx = j;
                }
            }
        }
        // меняем минимальный элемент с первым неотсортированным
        swap(&logs[i], &logs[min_idx]);
        // если максимальный элемент был на месте i, то теперь он находится на min_idx
        if (max_idx == i) {
            max_idx = min_idx;
        }
        // меняем максимальный элемент с последним неотсортированным
        swap(&logs[size - i - 1], &logs[max_idx]);
    }
}

// сравнитель для qsort (он не умеет сравнивать, поэтому нужны фнуциуии-помощники)
int srav_qsort_id_voz(const void *a, const void *b) { // id по воз
    const Log *logA = (const Log *)a;
    const Log *logB = (const Log *)b;
    return logA->id - logB->id;
}

int srav_qsort_id_ub(const void *a, const void *b) { // id по уб
    const Log *logA = (const Log *)a;
    const Log *logB = (const Log *)b;
    return logB->id - logA->id;
}

int srav_qsort_priority_voz(const void *a, const void *b) { // priority по воз
    const Log *logA = (const Log *)a;
    const Log *logB = (const Log *)b;
    return logA->priority - logB->priority;
}

int srav_qsort_priority_ub(const void *a, const void *b) { // priority по уб
    const Log *logA = (const Log *)a;
    const Log *logB = (const Log *)b;
    return logB->priority - logA->priority;
}