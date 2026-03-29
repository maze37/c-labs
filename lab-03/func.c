#include <stdio.h>
#include <stdlib.h>

#include "func.h"

void array_print(const int *arr, int len) {
    if (arr == NULL || len == 0) {
        printf("Array is empty\n");
        return;
    }
    for (int i = 0; i < len; ++i) {
        printf("array[%d] = %d\n", i, arr[i]);
    }
}

int array_create(int** arr, int* len){
    int *m_arr = malloc((*len) * sizeof(int));

    if (m_arr == NULL){
        (*len) = 0;
        return 0;
    }

    (*arr) = m_arr;
    return 1;
}

int array_insert(int **arr, int *len, int idx, int value){
    int (*re_arr) = realloc((*arr), ((*len)+1) * sizeof(int));
    if (re_arr == NULL){
        return 0;
    }
    (*arr) = re_arr;

    if (idx > (*len)){
        idx = *len;
    }

    for (int i = *len; i > idx; i--) {
        (*arr)[i] = (*arr)[i-1];
    }

    (*len)++;
    (*arr)[idx] = value;
    return 1;
}

int array_delete(int **arr, int *len, int idx){
    for (int i = idx; i < (*len) - 1; i++) {
        (*arr)[i] = (*arr)[i + 1];
    }

    (*len)--;
    if ((*len) == 0){
        return 1;
    }

    int *ken_arr = realloc(*arr, (*len) * sizeof(int));
    if (ken_arr == NULL){
        return 0;
    }

    (*arr) = ken_arr;
    return 1;
}

int getlenth(int a){
    int res = 0;

    while (a){
        res++;
        a /= 10;
    }
    if (res < 2){
        return 1; // Число меньше 10.
    }
    else {
        return 0;
    }
}

int same(int a){
    int b = a % 10;
    if (getlenth(a)){
        return 0; // Если getlenth = 1, то число меньше 10.
    }
    while (a) {
        if (a % 10 != b) {
            return 0;
        }
        a /= 10;
    }
    return 1;
}

int array_delete_same(int **arr, int *len){
    for (int i = 0; i < (*len); ){
        if (same((*arr)[i])){
            array_delete(arr,len,i);
        }
        else{
            i++;
        }
    }
    return 1;
}