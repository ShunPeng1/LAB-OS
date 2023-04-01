#include <stdio.h>
#include "logic.h"

void calculate(float first, char operator, float second, float *ans) {
    switch (operator) {
        case '+':
            *ans = first + second;
            break;
        case '-':
            *ans = first - second;
            break;
        case 'x':
            *ans = first * second;
            break;
        case '/':
            if (second == 0) {
                printf("MATH ERROR\n");
                return;
            }
            *ans = first / second;
            break;
        case '%':
            *ans = (int) first % (int) second;
            break;
        default:
            printf("SYNTAX ERROR\n");
            return;
    }
    printf("%f\n", *ans);
}

void history(char hist[100][100], int len) {
    int i;
    int low = (len - 5) > 0 ? (len - 5) : 0;
    for (i = low; i < len; i++) {
        printf("%s\n", hist[i]);
    }
}
