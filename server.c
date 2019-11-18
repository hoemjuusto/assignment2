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
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_lock(&mutex);
    for (int i = 0; bank->accounts[i] != NULL; i++) {
        if (strcmp(bank->accounts[i]->id, id) == 0) {
            pthread_mutex_unlock(&mutex);
            return i;
        }
    }
    pthread_mutex_unlock(&mutex);
    return -1;
}

int create_account(struct Bank *bank, char *id, float init_balance){
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_lock(&mutex);
    if(account_exists(bank, id) != -1){
        printf("Account with id %s already exists!\n", id);
        pthread_mutex_unlock(&mutex);
        return -1;
    }
    int i = 0;
    for (i = 0; bank->accounts[i] != NULL; i++);
    struct Account *new_account = malloc(sizeof(struct Account));
    strcpy(new_account->id, id);
    new_account->balance=init_balance;
    bank->accounts = realloc(bank->accounts, sizeof(struct Account *)*(i + 1) + sizeof(NULL));
    if(bank->accounts == NULL){
        fprintf(stderr, "Failed to reallocate when creating new account!\n");
        pthread_mutex_unlock(&mutex);
        return -1;
    }
    bank->accounts[i] = new_account;
    bank->accounts[i + 1] = NULL;
    printf("New account with id: %s and initial balance: %.2f created!\n", bank->accounts[i]->id, init_balance);
    for (int ind = 0; bank->accounts[ind] != NULL; ind++){
        printf("Account id %s, balance %f\n", bank->accounts[ind]->id, bank->accounts[ind]->balance);
    }
    pthread_mutex_unlock(&mutex);
    return 1;
}

static int print_account_balance(struct Bank *bank, char *id, char *response_buffer) {

    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_lock(&mutex);
    int account_index = account_exists(bank, id);
    if(account_index == -1) {
        printf("No such account created!\n");
        snprintf(response_buffer, 100, "No account with id %s created!\n", id);
        pthread_mutex_unlock(&mutex);
        return 0;
    }
    printf("Account id: %s, balance: %f\n", bank->accounts[account_index]->id, bank->accounts[account_index]->balance);
    snprintf(response_buffer, 100, "Account id: %s, balance: %f\n", bank->accounts[account_index]->id, bank->accounts[account_index]->balance);
    pthread_mutex_unlock(&mutex);
    return 1;


}

int process(char *request, struct Bank *bank, char *response, pthread_barrier_t *our_barrier){



    // initializing everything as empty
    char cmd[5] = "\0";
    char arg[50] = "\0";
    char ac1[1000] = "\0";
    char ac2[1000] = "\0";
    char sum[1000] = "\0";
    strcpy(response, "\0");

    printf("Server got request: %s\n", request);
    sscanf(request, "%s %[^\n]", cmd, arg);
    printf("Command part: %s, argument part: %s\n", cmd, arg);
    if(strcmp(cmd, "l")==0){
        sscanf(arg, "%s", ac1);
        print_account_balance(bank, ac1, response);
    }
    if(strcmp(cmd, "t")==0){
        if(sscanf(arg, "%s %s %s", ac1, ac2, sum) == 3){
            int ac1_index = account_exists(bank, ac1);
            int ac2_index = account_exists(bank, ac2);
            if(ac1_index == -1 || ac2_index == -1){
                snprintf(response, 100, "Account id's are incorrect or don't exist.\n");
                return 0;
            }
            deposit(bank->accounts[ac2_index], withdraw(bank->accounts[ac1_index], strtof(sum, NULL)));
        }
    }
    if(strcmp(cmd, "w")==0){
        if(sscanf(arg, "%s %s", ac1, sum) == 2) {
            int ac1_index = account_exists(bank, ac1);
            if(ac1_index == -1) {snprintf(response, 100, "Account id is incorrect or doesn't exist.\n"); return 0;}
            snprintf(response, 100, "Managed to withdraw %f from account %s", withdraw(bank->accounts[ac1_index], strtof(sum, NULL)), ac1);
        } else{
            snprintf(response, 100, "Wrong number of arguments\n");
        }
    }
    if(strcmp(cmd, "d")==0){
        if(sscanf(arg, "%s %s", ac1, sum) == 2) {
            int ac1_index = account_exists(bank, ac1);
            if(ac1_index == -1) {snprintf(response, 100, "Account id is incorrect or doesn't exist.\n"); return 0;}
            deposit(bank->accounts[ac1_index], strtof(sum, NULL));
        } else{
            snprintf(response, 100, "Wrong number of arguments\n");
        }
    }
    if(strcmp(cmd, "c")==0){
        if(sscanf(arg, "%s %s", ac1, sum)==2){
            create_account(bank, ac1, strtof(sum, NULL));
        } else{
            create_account(bank, ac1, 0);
        }
    }
    if(strcmp(cmd, "b")==0){
        pthread_barrier_wait(&our_barrier);
        snprintf(response, 100, "Bank balance: %f", bank->balance);
    }
    char buffer[] = "\nRequest was successful\n";
    strcat(response, buffer);

    return 1;
}
