//
// Created by juuso on 12.11.2019.
//

#include <stddef.h>
#include "server.h"

int create_account(struct Bank *bank){
    size_t id = sizeof(bank.accounts)/sizeof(struct Account *) + 1;
    struct Account new_account = {id, 0};
    bank->accounts[id] = &new_account;
}

int account_exists(struct Bank bank, int id){
    size_t size = sizeof(bank.accounts)/sizeof(struct Account *);
    for(int i = 0; i < size; i++){
        if(bank.accounts[i].id==id){
            return 1;
        }
    }
    return 0;
}
