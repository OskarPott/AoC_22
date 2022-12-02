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

    int sum = 0;

    int one = 0;
    int two = 0;
    int three = 0;
    
    int max = 0;

    while ((read = getline(&line, &len, fp)) != -1) {
        sum = sum + atoi(line);
        if (line[0] == '\n' || feof(fp)){
            // If sum is bigger than the smallest of one, two, three. Change sum to the smallest.
            if(one < two && one < three)
            {
                if (sum > one) {
                    one = sum;
                }
            }
            else if(two < three)
            {
                if (sum > two) {
                    two = sum;
                }
            }
            else
            {
                if (sum > three) {
                    three = sum;
                }
            }
            sum = 0;
        }
    }

    int total = one + two + three;

    printf("%d", total);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("\nCpu time: %f\n", cpu_time_used);
    
    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
}