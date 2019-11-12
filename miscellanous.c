//
// Created by juuso on 7.11.2019.
//
#include <string.h>
#include <stdlib.h>
#include "miscellanous.h"
#include "queue.h"
#include "stdio.h"

#define SERVERS 4

void min(struct Queue **sqs, int *min_value, int *min_index){
    int minimum;
    int index;
    minimum = sqs[0]->size;
    index = 0;
    /*size_t size = sizeof(sqs)/sizeof(*sqs);  //todo: get this to work
    printf("%zu", size);*/
    for (int c = 1; c < SERVERS; c++)
    {
        if (sqs[c]->size < minimum)
        {
            minimum = sqs[c]->size;
            index = c;
        }
    }
    *min_value = minimum;
    *min_index = index;
}

int process(struct Queue *q){

    char cmd[5];
    char arg[50];
    int ac1;
    int ac2;
    float sum;
    fprintf(stdin, "%s", q->request);
    fscanf(stdin, "%s %s", cmd, arg);
    if(strcmp(cmd, "l")==0){
        fprintf(stdin, "%s", arg);
        fscanf(stdin, "%d", ac1);

    }
    if(strcmp(cmd, "t")==0){
        fprintf(stdin, "%s", arg);
        fscanf(stdin, "%s %s %f", ac1, ac2, sum);
    }
    if(strcmp(cmd, "w")==0){

    }
    if(strcmp(cmd, "d")==0){

    }


    return 1;
}