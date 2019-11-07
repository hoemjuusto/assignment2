#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <values.h>
#include <string.h>
#include "queue.h"
#include "miscellanous.h"

#define SERVERS 7  // my desktop has 4 cores and can handle 2 threads/core, so max would be 8 (7 servers + 1 master thread)

// Getting the mutex
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t dataNotProduced =
        PTHREAD_COND_INITIALIZER;
pthread_cond_t dataNotConsumed =
        PTHREAD_COND_INITIALIZER;

int queue_lengths[SERVERS];  // global variable that just holds the queue lengths of individual servers (threads)
// when creating queue, in my implementation the first member of queue has to be empty
struct Queue **server_queues;  // array of server queues
int server_queue_lengths[SERVERS];
void *server_function(void *arg);  // prototype, implementation in the end
void *entry_function(void *arg);  // prototype, implementation in the end

int main() {

    clock_t begin = clock();
    /* here, do your time-consuming job */
    // initializing server threads and queues
    pthread_t *thread_group = malloc(sizeof(pthread_t) * SERVERS);
    server_queues = malloc(sizeof(struct Queue)*SERVERS);

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
    struct Queue my_queue = {empty, NULL, 0};
    server_queues[my_id] = &my_queue;
    server_queue_lengths[my_id] = my_queue.size;
    char buffer[100];
    int keepRunning = 1;

    while(keepRunning){

        if(!isEmpty(&my_queue)){
            if(dequeue(&my_queue, buffer) == 1){
                printf("Server with id %d handled request %s successfully!\n", my_id, buffer);
            } else{
                fprintf(stderr, "Error handling request!\n");
            }

        }
    }




    pthread_exit(0);
}


void *entry_function(void *arg){

    printf("Master thread launched!\n\n");

    static int keepRunning = 1;

    char input[MAX_INPUT];
    char buffer[100];

    while(keepRunning){
        printf("Give serve-request (submit with enter, c to close the bank):\n\n");
        fgets(input, MAX_INPUT, stdin);
        if(strcmp(input,"c\n") == 0)
        {
            printf("Closing the bank!\n\n");
            keepRunning = 0;
        }else{
            int min_length; int min_index;
            min(server_queue_lengths, &min_length, &min_index);
            if(enqueue(server_queues[min_index], input) == 0){
                fprintf(stderr, "Error with directing the server request!\n");
            }
        }
    }

    pthread_exit(0);
}