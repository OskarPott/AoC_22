#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
double cpu_time_used;
clock_t start, end;

static int total_space;
static int answer; //global accessed variable for answer
int answer2; //global accessed variable for answer

typedef struct node{
    int dir;  //dir = 0 for files.
    int size; //size = 0 for directory.
    int children_index; //To keep check of index for node[]
    struct node *up, **node;  //parent and array of children nodes.
}node;


node *createNode(node *parent, int dir, int size){
    node *child = malloc(sizeof(node));
    child->dir = dir;
    child->size = size;
    if (parent != NULL) {
        node **p = realloc(parent->node, 10*sizeof(node**)); //magi??? *1000 va för att den va för liten :)))
        parent->node = p;                                      //varför är detta nödvändigt???
        parent->node[parent->children_index++] = child;
        child->up = parent;
    }
    return child;
}

int calc(node *node) {
    if (node == NULL){
        return 0;
    }
    if (node->size != 0) {
        return node->size;
    }
    int sum = 0;
    for (int i = 0; i < node->children_index; ++i){
        sum += calc(node->node[i]);
    }
    if (sum <= 100000){
        answer += sum;
    }
    if (sum >= total_space - 40000000 && (sum < answer2 || answer2 == 0) && total_space != 0) {
        answer2 = sum;
    }
    return sum;
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

    node *root = NULL;
    node *current = NULL;

    while ((read = getline(&line, &len, fp)) != -1) {
        switch (line[0]) {
        case '$':
            if (line[2] == 'c'){ 
                switch (line[5])
                {
                    case '/': // $ cd /
                        current = root = createNode(NULL,1,0);
                        break;
                    case '.': // $ cd ..
                        current = current->up;
                        break;  
                    default: // $ cd dir_name
                        current = createNode(current, 1, 0);
                        break;  
                }
            }
        case 'd': // listing dir dir_name
            break; 
        default:  // listing size file_name
            createNode(current, 0, strtoul(line, NULL, 10));
            break;
        }
    }

    total_space = calc(root);
    printf("Total filesize: %d", total_space);
    calc(root);
    printf("\nAll directories and files less than 100 000 combined:\n%d", answer2);

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("\nCpu time: %f\n", cpu_time_used);
    
    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
}