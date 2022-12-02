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

    int score = 0;

    // A, X = ROCK
    // B, Y = Paper
    // C, Z = Scissor 

    // The score for a single round is the score for the shape you selected 
    // (1 for Rock, 2 for Paper, and 3 for Scissors) plus the score for the outcome 
    // of the round (0 if you lost, 3 if the round was a draw, and 6 if you won).

    while ((read = getline(&line, &len, fp)) != -1) {
        if (line[0] == 'A') { 
            if(line[2] == 'X') {
                score = score + 1 + 3;
            }
            else if(line[2] == 'Y') {
                score = score + 2 + 6;
            } 
            else {
                score = score + 3 + 0;
            } 
        }
        else if (line[0] == 'B') {
            if(line[2] == 'X') {
                score = score + 1 + 0;
            }
            else if(line[2] == 'Y') {
                score = score + 2 + 3;
            } 
            else {
                score = score + 3 + 6;
            } 
        } 
        else {
            if(line[2] == 'X') {
                score = score + 1 + 6;
            }
            else if(line[2] == 'Y') {
                score = score + 2 + 0;
            } 
            else {
                score = score + 3 + 3;
            } 
        }
    }

    printf("%d", score);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("\nCpu time: %f\n", cpu_time_used);

    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
}