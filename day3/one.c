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

    // if (line[0] == '\n' || feof(fp)){
    // }

    // 97-122 a-z , 65-90 A-Z
    // 1-26   a-z , 27-52 A-Z

    int sum = 0;

    while ((read = getline(&line, &len, fp)) != -1) {
        int mid = strlen(line)/2;
        int end = strlen(line);
        int i;
        int j;
        for (i = 0; i < mid; i++) {
            for (j = mid; j < end; j++) {
                if (line[i] == line[j]){ 
                    if (line[i] < 97) {
                        sum = sum + line[i] - 38;
                    } else {
                        sum = sum + line[i] - 96;
                    }
                    goto stop;
                }
            }
        }
        stop:;
    }

    printf("%d", sum);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("\nCpu time: %f\n", cpu_time_used);
    
    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
}