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

    // 97-122 a-z , 65-90 A-Z
    // 1-26   a-z , 27-52 A-Z

    int sum = 0;
    int curr_line = 0;

    int i;
    int j;
    int set[53];
    int set2[53];
    int set3[53];

    for(i = 0; i < 53; i++) {
        set[i] = 0;
        set2[i] = 0;
        set3[i] = 0;
    }

    while ((read = getline(&line, &len, fp)) != -1) {
        curr_line++;
        int end = strlen(line);
        for (i = 0; i < end-1; i++) {
            int index;
            if (line[i] < 97) {
                index = line[i] - 38;
            } else {
                index = line[i] - 96;
            }

            if (curr_line % 3 == 1) {
                set[index] = 1;
            }
            else if (curr_line % 3 == 2) {
                set2[index] = 1;
            }
            else {
                set3[index] = 1;
            }
        }

        if (curr_line % 3 == 0) {
            for (j = 0; j < 53; j++) {
                if (set[j] == 1 && set2[j] == 1 && set3[j] == 1) {
                    sum = sum + j;
                }
                set[j] = 0;
                set2[j] = 0;
                set3[j] = 0;
            }
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