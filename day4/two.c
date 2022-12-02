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

    fp = fopen("input2.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    // if (line[0] == '\n' || feof(fp)){
    // }
    int sum = 0;

    int start1;
    int end1;

    int start2;
    int end2;

    const char hyphen[2] = "-";
    const char comma[2] = ",";
    char *token;

    while ((read = getline(&line, &len, fp)) != -1) {
        start1 = atoi(strtok(line, hyphen));
        end1 = atoi(strtok(NULL, comma));
        start2 = atoi(strtok(NULL, hyphen));
        end2 = atoi(strtok(NULL, comma));

        if (!(end1 < start2 || start1 > end2)) {
            sum++;
        }
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