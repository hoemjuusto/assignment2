#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define SERVERS 7  // my desktop has 7 cores and can handle 2 threads/core, so max would be 14

void *server_function(void *arg){

    printf("Server with id: %d launched!\n", *(int *)arg);

    pthread_exit(0);
}

int main() {

    clock_t begin = clock();

    /* here, do your time-consuming job */

    printf("Hello from the master thread!\n");

    int queue_lengths[SERVERS];

    pthread_t *thread_group = malloc(sizeof(pthread_t) * SERVERS);

    for(int i = 0; i < SERVERS; i++){
        int *id = malloc(sizeof(*id));
        if (id == NULL ) {
            fprintf(stderr, "Couldn't allocate memory for thread arg.\n");
            exit(EXIT_FAILURE);
        }
        *id = i;
        pthread_create(&thread_group[i], NULL, server_function, id);
    }
    // wait for all threads to finish
    for(int i = 0; i < SERVERS; i++) {
        pthread_join(thread_group[i], NULL);
    }

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("Runtime: %f", time_spent);

    return 0;
}