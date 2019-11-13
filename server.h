// Server-side functions
// Created by juuso on 12.11.2019.
//
#include "queue.h"
#include "bank.h"

#ifndef ASSIGNMENT2_SERVER_H
#define ASSIGNMENT2_SERVER_H
int create_account(struct Bank *bank, int id, float init_balance);
int process(char request[MAX_INPUT], struct Bank bank);
#endif //ASSIGNMENT2_SERVER_H
