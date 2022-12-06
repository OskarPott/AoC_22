#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
double cpu_time_used;
clock_t start, end;

int check(char *line, int index){
    int buffer[4];
    int i;
    if (line[index-3] != line[index-2] && line[index-3] != line[index-1] && line[index-3] != line[index] && line[index-2] != line[index-1] && line[index-2] != line[index] && line[index-1] != line[index]){
        return 0;
    }
    return 1;
}


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
    int index = 4;

    while ((read = getline(&line, &len, fp)) != -1) {
        while (check(line, index-1)) {
            index++;
        }
    }
    int j;

    printf("%d", index);

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("\nCpu time: %f\n", cpu_time_used);
    
    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
}