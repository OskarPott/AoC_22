#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
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
        if (line[0] == 10 || feof(fp)){
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

    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
}