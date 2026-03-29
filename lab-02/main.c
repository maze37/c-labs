#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define SUCCESS 0
#define INVALID_INPUT 1
#define INVALID_VALUE 2
#define EOF_REACHED 3

float exp1_precision(float x, float precision, int *terms_used){
    float sum = 1.0;
    int k = -1;
    float p = 1.0;
    *terms_used = 1;

    for (int i = 1;; ++i){
        p *= (x * (2 * i - 1) * (2 * i)) / (i * i * 4);
        float term = k * p / (-1 * (2 * i - 1));
        sum += term;

        if (fabs(term) < precision){
            break;
        }

        k *= -1;
        (*terms_used)++;
    }
    return sum;
}

int main(){
    float x;

    float precision;
    int terms_used;

    printf("Enter x : \n");
    if (scanf("%f", &x) == EOF){
        printf("EOF REACHED - 3\n");
        return 3;
    }

    if (getchar() != '\n'){
        printf("INCORRECT INPUT for x - 1\n");
        while (getchar() != '\n');
        return 1;
    }

    if (x < -1 || x > 1){
        printf("INCORRECT VALUE for x - 2\n");
        return 2;
    }

    printf("Enter precision : \n");
    if (scanf("%f", &precision) == EOF){
        printf("EOF REACHED - 3\n");
        return 3;
    }

    if (getchar() != '\n'){
        printf("INCORRECT INPUT for precision - 1\n");
        while (getchar() != '\n');
        return 1;
    }
    if (precision <= 0) {
        printf("INCORRECT VALUE for precision - 2\n");
        return 2;
    }

    float result = exp1_precision(x,precision,&terms_used);

    printf("Result : %f\nTerms Used : %d\n", result, terms_used);

    return 0;
}
