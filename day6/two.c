#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
double cpu_time_used;
clock_t start, end;

int check(char *line, int index){
    int array[256] = {0};
    int i;
    for (i = index-14; i < index; i++){
        if (array[line[i]] == 1) {
            return 1;
        }
        array[line[i]] = 1;
    }
    return 0;
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
    int index = 14;
    while ((read = getline(&line, &len, fp)) != -1) {
        while (check(line, index-1)) {
            index++;
        }
    }

    printf("%d", index-1);

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("\nCpu time: %f\n", cpu_time_used);
    
    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
}