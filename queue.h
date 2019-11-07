//
// Created by juuso on 7.11.2019.
//

#ifndef ASSIGNMENT2_QUEUE_H
#define ASSIGNMENT2_QUEUE_H

struct Queue {
    char *request;  // Name of queue member (dynamically allocated)
    struct Queue *next;  // (pointer to next queue member)
    int size;
};

void list_requests(struct Queue *q);

int isEmpty(struct Queue *q);

int enqueue(struct Queue *q, const char *request);

int dequeue(struct Queue *q, char *buffer);
#endif //ASSIGNMENT2_QUEUE_H
