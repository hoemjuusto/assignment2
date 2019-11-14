//
// Created by juuso on 12.11.2019.
//
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <values.h>
#include <string.h>
#include <unistd.h>
#include "queue.h"
#include "miscellanous.h"
#include <stddef.h>
#include "server.h"
#include "account.h"



static int account_exists(struct Bank *bank, char *id){
    for (int i = 0; bank->accounts[i] != NULL; i++) {
        printf("iterate %d\n", i);
        if (strcmp(bank->accounts[i]->id, id) == 0) {
            return i;
        }
    }
    return -1;
}

int create_account(struct Bank *bank, char *id, float init_balance){
    if(account_exists(bank, id) != -1){
        printf("Account with id %s already exists!\n", id);
        return -1;
    }
    int i = 0;
    for (i = 0; bank->accounts[i] != NULL; i++);

    struct Account new_account;
    strcpy(new_account.id, id);
    new_account.balance=init_balance;
    bank->accounts = realloc(bank->accounts, sizeof(struct Account *)*(i + 1));
    if(bank->accounts == NULL){
        fprintf(stderr, "Failed to reallocate when creating new account!\n");
        return -1;
    }
    bank->accounts[i] = &new_account;
    bank->accounts[i + 1] = NULL;
    printf("New account with id: %s and initial balance: %.2f created!\n", bank->accounts[i]->id, init_balance);
    return 1;
}

static int print_account_balance(struct Bank *bank, char *id) {
    int account_index = account_exists(bank, id);
    printf("Account index %d\n", account_index);
    if(account_index != -1) {
        float account_balance;
        account_balance = bank->accounts[account_index]->balance;
        printf("Account %s balance: %f\n", id, account_balance);
        return 1;
    } else {
        printf("No such account created!\n");
        return 0;
    }
}

int process(char *request, struct Bank *bank){

    char cmd[5];
    char arg[50];
    char ac1[1000];
    char ac2[1000];
    char sum[1000];
    printf("Server got request: %s\n", request);
    sscanf(request, "%s %[^\n]", cmd, arg);
    printf("Command part: %s, argument part: %s\n", cmd, arg);
    if(strcmp(cmd, "l")==0){
        sscanf(arg, "%s", ac1);
        print_account_balance(bank, ac1);
    }
    if(strcmp(cmd, "t")==0){

    }
    if(strcmp(cmd, "w")==0){

    }
    if(strcmp(cmd, "d")==0){

    }
    if(strcmp(cmd, "c")==0){
        sscanf(arg, "%s %s", ac1, sum);
        if(strcmp(sum, "\0")==0){
            create_account(bank, ac1, 0);
        } else{
            create_account(bank, ac1, strtof(sum, NULL));
        }
    }


    return 1;
}
