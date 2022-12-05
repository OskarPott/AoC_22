#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
double cpu_time_used;
clock_t start, end;

int print_array(int **array, int nrows, int ncolumns) {
    int i;
    int j;
    for (i = 0; i < nrows; i++) {
        for (j = 0; j < ncolumns; j++){
            printf("%d ", array[i][j]);
        }
        printf("%c", '\n');
    }
}

int move(int **array, int amount, int src, int dest, int nrows, int ncolumns) {
    int i;
    int top_src = 0;
    int top_dest = 0;
    for (i = 0; i < nrows; i++) {
        if (array[i][src-1] != 0 && array[i][src-1] != 32) {
            top_src++;
        }
        if (array[i][dest-1] != 0) {
            top_dest++;
        }
    }
    for (i = 0; i < amount; i++) {
        array[top_dest][dest-1] = array[top_src-1][src-1];
        array[top_src-1][src-1] = 0;
        top_dest = top_dest + 1;
        top_src = top_src - 1;
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

    const char *delimiter_characters = " ";
    char *last_token;

    int nbr_array = 0;
    int i;
    int j;

    int nrows = 100;
    int ncolumns = 9;

    // Allocate 2d array
	int **array;
	array = malloc(nrows * sizeof(int *));
	if(array == NULL)
	{
		fprintf(stderr, "out of memory\n");
		return 1;
    }
	for(i = 0; i < nrows; i++)
    {
        array[i] = malloc(ncolumns * sizeof(int));
        if(array[i] == NULL)
            {
            fprintf(stderr, "out of memory\n");
            return 1;
            }
    }

    int row = 0;
    int input = 1;

    int amount;
    int src;
    int dest;
    int init_height = 8;

    while ((read = getline(&line, &len, fp)) != -1) {
        if (line[1] == '1'){
            input = 0;
        }
        if (input){
            for (i = 0; i < strlen(line)/4; i++) {
                if (line[i*4 +1] == 32) {
                    array[init_height-1-row][i] = 0;    
                } else {
                    array[init_height-1-row][i] = line[i*4 + 1];
                }
            }
        } 
        else {
            if (line[0] == 'm') {
                strtok( line, delimiter_characters );
                amount = atoi(strtok( NULL, delimiter_characters));
                strtok( NULL, delimiter_characters);
                src = atoi(strtok( NULL, delimiter_characters));
                strtok( NULL, delimiter_characters);
                dest = atoi(strtok( NULL, delimiter_characters));
                move(array, amount, src, dest, nrows, ncolumns);
            }
        }
        row++;
    }

    int index = 0;
    int test[ncolumns];

    for (j = 0; j < ncolumns; j++){
        for (i = nrows-1; i >= 0; i--) {
            if (array[i][j] != 0) {
                test[index] = array[i][j];
                index++;
                break;
            }
        }
    }

    for (i = 0; i < ncolumns; i++) {
        printf("%c", test[i]);
    }
    // printf("The answer is: %d", test[3]);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("\nCpu time: %f\n", cpu_time_used);
    
    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
}