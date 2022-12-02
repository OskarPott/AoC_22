#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
double cpu_time_used;
clock_t start, end;

int main(void)
{
    start = clock();
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("input1.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    int sum = 0;
    int max = 0;

    while ((read = getline(&line, &len, fp)) != -1) {
        sum = sum + atoi(line);
        if (line[0] == '\n' || feof(fp)){
            if (sum > max) {
                max = sum;
            }
            sum = 0;
        }
    }

    printf("%d", max);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("\nCpu time: %f\n", cpu_time_used);

    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
}