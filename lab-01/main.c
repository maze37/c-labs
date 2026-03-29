#include <stdio.h>

int GetLenth(int number){
    int result = 0;
    while (number != 0){
        result++;
        number /= 10;
    }
    return result;
}

int GetPow(int x, int y){
    int result = 1;
    for (int idx = 0; idx < y; idx++){
        result *= x;
    }
    return result;
}

int IsArmstrong(int number){
    int len = GetLenth(number);
    int sum = 0;
    int res = number;

    while (number != 0){
        sum += GetPow(number % 10, len);
        number /= 10;
    }
    return sum == res;
}

int main(){
    int start_range; int end_range;

    printf("Please enter start range: \n");
    scanf("%d", &start_range);
    printf("Please enter end range: \n");
    scanf("%d", &end_range);

    for (int number = start_range; number < end_range; number++){
        if (IsArmstrong(number)){
            printf( "Number %d is Armstrong\n", number);
        }
    }
}
