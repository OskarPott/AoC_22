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
            printf("%c ", array[i][j]);
        }
        printf("%c", '\n');
    }
}

int vis(int **array, int nrows, int ncolumns) {
    int i;
    int j;
    int row;
    int col;
    int total_visible = 0;
    int visible[4] = {1};
    int temp = 0;

    for (row = 1; row < nrows-1; row++) {
        for (col = 1; col < ncolumns-1; col++){
            visible[0] = 1;
            visible[1] = 1;
            visible[2] = 1;
            visible[3] = 1;
            for (i = 0; i < col; i++) { //Before row
                if (array[row][i] >= array[row][col]){
                    visible[0] = 0;
                }
            }
            for (i = col+1; i < ncolumns; i++) { //After row
                if (array[row][i] >= array[row][col]){
                    visible[1] = 0;
                }
            }
            for (i = 0; i < row; i++) { //Before col
                if (array[i][col] >= array[row][col]){
                    visible[2] = 0;
                }
            }
            for (i = row+1; i < nrows; i++) { //After col
                if (array[i][col] >= array[row][col]){
                    visible[3] = 0;
                }
            }
            if (visible[0] == 1 || visible[1] == 1 || visible[2] == 1 || visible[3] == 1){
                total_visible++;
            }
        }
    }
    printf("%d", total_visible);
    return total_visible;
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

    int nrows = 99;
    int ncolumns = 99;
    int i;

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
    while ((read = getline(&line, &len, fp)) != -1) {
        int length = strlen(line); 
        for (i = 0; i < length; i++) {
            array[row][i] = line[i];
        }
        row++;
        
    }
    print_array(array, nrows ,ncolumns);

    int visible = nrows+nrows+ncolumns-2+ncolumns-2 + vis(array, nrows, ncolumns);

    printf("\n%d", visible);

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("\nCpu time: %f\n", cpu_time_used);
    
    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
}