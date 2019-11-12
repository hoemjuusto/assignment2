//
// Created by juuso on 12.11.2019.
//
#include "queue.h"
#include "bank.h"

#ifndef ASSIGNMENT2_SERVER_H
#define ASSIGNMENT2_SERVER_H
struct Server{
    int id;
    struct Queue *queue;
    struct Bank *bank;
};
int account_exists(struct Bank bank, int id);
#endif //ASSIGNMENT2_SERVER_H
