#include <stdio.h>
#include <stdlib.h>
#include "func.h"

int main() {
    int *data = NULL;
    int len = 0;
    char option = 0;
    int idx = 0;
    int value = 0;
    int del = 0;
    while (option != '0'){
        printf("\n");
        printf("***** MENU *****\n");
        printf("1. Create an array\n");
        printf("2. Insert element\n");
        printf("3. Delete element\n");
        printf("4. Delete elements with same values\n");
        printf("5. Print array\n");
        printf("0. Exit\n");
        printf("\n");
        int r = scanf(" %c", &option);
        if (r == EOF) {
            free(data);
            return 0;
        }
        switch (option){
        case '1':
            if (len > 0){
                len = 0;
                free(data);
            }
            if (array_create(&data,&len)){
                printf("Success!\n");
            }
            else{
                printf("Failed to allocate!\n");
            }
            array_print(data, len);
            break;
        case '2':
            printf("Enter index : \n");
            if (scanf("%d", &idx) < 0){
                printf("Bad index!\nTry again with correct index!\n");
                break;
            }
            printf("Enter value : \n");
            scanf("%d", &value);
            if (array_insert(&data,&len,idx,value)){
                printf("Success!\n");
            }
            else {
                printf("Failed to allocate!\n");
            }
            array_print(data, len);
            break;
        case '3':
            printf("Enter index : \n");
            if (scanf("%d", &del) < 0){
                printf("Bad index!\nTry again with correct index!\n");
                break;
            }
            if (array_delete(&data, &len, del)){
                printf("Success!\n");
            }
            else {
                printf("Failed to allocate!\n");
            }
            array_print(data, len);
            break;
        case '4':
            printf("Delete elements with same numbers!\n");
            array_delete_same(&data, &len);
            array_print(data, len);
            break;
        case '5':
            array_print(data, len);
            break;
        case '0':
            printf("Exit\n");
            free(data);
            return 0;
        default:
            printf("Wrong input!\n");
            break;
        }
    }
    free(data);
    return 0;
}