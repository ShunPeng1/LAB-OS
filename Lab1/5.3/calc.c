#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logic.h"


int main() {
    char input[100];
    char hist[100][100];
    float ans = 0;
    int len = 0;

    FILE *fp;
    fp = fopen("calc_data.txt", "w+");
    fprintf(fp, "%f\n", ans);
    fclose(fp);

    while (1) {
        printf(">> ");
        fgets(input, 100, stdin);

        if (strcmp(input, "EXIT\n") == 0) {
            return 0;
        }

        if (strcmp(input, "HIST\n") == 0) {
            history(hist, len);
            continue;
        }

        char *token;
        char *args[3];
        int i = 0;

        token = strtok(input, " \n");
        while (token != NULL) {
            args[i++] = token;
            token = strtok(NULL, " \n");
        }

        if (i != 3) {
            printf("SYNTAX ERROR\n");
            continue;
        }

        float first;
        if (strcmp(args[0], "ANS") == 0) {
            FILE *fp = fopen("calc_data.txt", "r");
            fscanf(fp, "%f", &first);
            fclose(fp);
        } else {
            first = atof(args[0]);
        }

        char operator = args[1][0];

        float second;
        if (strcmp(args[2], "ANS") == 0) {
            FILE *fp = fopen("calc_data.txt", "r");
            fscanf(fp, "%f", &second);
            fclose(fp);
        } else {
            second = atof(args[2]);
        }

        calculate(first, operator, second, &ans);

        fp = fopen("calc_data.txt", "w+");
        fprintf(fp, "%f\n", ans);
        fclose(fp);

        sprintf(hist[len++], "%s %c %s = %f", args[0], operator, args[2], ans);
    }

    return 0;
}
