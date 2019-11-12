//
// Created by juuso on 9.11.2019.
//

#include "account.h"


int deposit(struct Account *a, float amount){
    a->balance += amount;
    return 1;
}

double withdraw(struct Account *a, float amount){
    if(a->balance>=amount){
        a->balance-=amount;
        return amount;
    } else{
        double ret = a->balance;
        a->balance = 0;
        return ret;
    }
}