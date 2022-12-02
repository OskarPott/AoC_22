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
    char * line2 = NULL;
    int end2;
    char * line3 = NULL;
    int end3;

    int i;
    int j;
    int k;

    while ((read = getline(&line, &len, fp)) != -1) {
        int end = strlen(line);
        if (curr_line == 0) {
            line2 = strdup(line);
            end2 = strlen(line2);
        }
        else if (curr_line == 1) {
            line3 = strdup(line);
            end3 = strlen(line3);
        }
        else {
            for (i = 0; i < end; i++){
                for (j = 0; j < end2; j++){
                    for (k = 0; k < end3; k++){
                        if (line[i] == line2[j] && line[i] == line3[k]) {
                            if (line[i] < 97) {
                                sum = sum + line[i] - 38;
                            } else {
                                sum = sum + line[i] - 96;
                            }
                            goto stop;
                        }
                    }
                }
            }
            stop:;
            curr_line = -1;
        }
        curr_line++;
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