#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <values.h>
#include <string.h>
#include <unistd.h>
#include "queue.h"
#include "miscellanous.h"
#include "server.h"
#include "account.h"

#define SERVERS 4

// Getting the mutex
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t dataNotProduced =
        PTHREAD_COND_INITIALIZER;
pthread_cond_t dataNotConsumed =
        PTHREAD_COND_INITIALIZER;

int keepRunning = 1;
struct Queue **server_queues;  // array of server queues
struct Bank bank = {.balance = 0, NULL};

void *server_function(void *arg);  // prototype, implementation in the end
void *entry_function(void *arg);  // prototype, implementation in the end

int main() {

    clock_t begin = clock();
    /* here, do your time-consuming job */
    // initializing server threads and queues
    pthread_t *thread_group = malloc(sizeof(pthread_t) * SERVERS);
    server_queues = malloc(sizeof(struct Queue)*SERVERS);
    bank.accounts = malloc(sizeof(NULL));
    *(bank.accounts)= NULL;

    for(int i = 0; i < SERVERS; i++){
        int *id = malloc(sizeof(*id));
        if (id == NULL ) {
            fprintf(stderr, "Couldn't allocate memory for thread arg.\n");
            exit(EXIT_FAILURE);
        }
        *id = i;
        pthread_create(&thread_group[i], NULL, server_function, id);
    }

    pthread_t *master_thread = malloc(sizeof(pthread_t));
    int *mid = malloc(sizeof(*mid));
    *mid = 100;
    pthread_create(master_thread, NULL, entry_function, mid);

    pthread_join(*master_thread, NULL);
    // wait for all threads to finish
    for(int i = 0; i < SERVERS; i++) {
        pthread_join(thread_group[i], NULL);
    }

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("Runtime: %f", time_spent);

    return 0;
}


void *server_function(void *arg){

    int my_id = *(int*) arg;
    static char empty[1] = "\0";
    struct Queue my_queue = {empty, NULL, 0};  // in my queue implementation first member is empty

    pthread_mutex_lock(&mutex);
    server_queues[my_id] = &my_queue;
    pthread_mutex_unlock(&mutex);

    char request[100];

    while(keepRunning){

        if(!isEmpty(&my_queue)){
            if(dequeue(&my_queue, request) != 1) {
                fprintf(stderr, "Server %d having error handling request!\n", *(int *) arg);
            }
            // do processing
            process(request, &bank);
        }
    }
    pthread_exit(0);
}



void *entry_function(void *arg){

    printf("Master thread launched!\n\n");

    char input[MAX_INPUT];

    while(keepRunning){
        printf("Give serve-request (submit with enter, e to exit):\n");
        fgets(input, MAX_INPUT, stdin);
        char delim[] = "\n";
        strcpy(input, strtok(input, delim));
        printf("You gave request: %s\n", input);

        if(strcmp(input,"e") == 0)
        {
            printf("\n\nExiting the bank!\n\n");
            keepRunning = 0;
        }else{
            int min_length; int min_index;
            min(server_queues, &min_length, &min_index);
            pthread_mutex_lock(&mutex);
            if(enqueue(server_queues[min_index], input) == 0){
                fprintf(stderr, "Error with directing the request %s to server!\n", input);
            }
            /*for(int i=0; i<SERVERS; i++){
                printf("Server %d queue length: %d\n", i, server_queues[i]->size);
            }*/
            pthread_mutex_unlock(&mutex);
        }
    }

    pthread_exit(0);
}