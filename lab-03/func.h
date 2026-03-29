#ifndef FUNC_H_INCLUDED
#define FUNC_H_INCLUDED

void array_print(const int *arr, int len);
int array_create(int **arr, int *len);
int array_insert(int **arr, int *len, int idx, int value);
int array_delete(int **arr, int *len, int idx);
int array_delete_same(int **arr, int *len);
int getlenth(int a);
int same(int a);

#endif // FUNC_H_INCLUDED