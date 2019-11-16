//
// Created by juuso on 14.11.2019.
//

#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <unistd.h>

#include <pthread.h>
#include <values.h>
#include <string.h>

#include "queue.h"
#include "miscellanous.h"
#include "server.h"
#include "account.h"


#define NUMOFCLIENTS 1

#define SERVERS 4

// Getting the mutex
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t dataNotProduced =
        PTHREAD_COND_INITIALIZER;
pthread_cond_t dataNotConsumed =
        PTHREAD_COND_INITIALIZER;
// Global variables
int keepRunning = 1;
struct Queue **server_queues;  // array of server queues
struct Bank bank = {.balance = 0, NULL};

void *server_function(void *arg);  // prototype, implementation in the end

int main(){

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


    /*This takes care of the communication between the two programs, the server side program (this) and client program
    * Server side program is launched first*/
    char server_message[256] = "You've reached the bank server!\n\n";
    // create a server socket
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    //define server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);  // same port as with client
    server_address.sin_addr.s_addr = INADDR_ANY;
    // bind the socket to our specified IP and port
    bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));
    // listen to the client
    listen(server_socket, NUMOFCLIENTS);
    // to save the id of the client socket for future data sharing
    int client_socket;
    client_socket = accept(server_socket, NULL, NULL);
    // sending the server_message as a response to connection of client
    send(client_socket, server_message, sizeof(server_message), 0);
    // communication between client and the server
    while(keepRunning) {
        // receive requests from the client as input
        char input[256];
        recv(client_socket, &input, sizeof(input), 0);

        if(strcmp(input,"e") == 0)
        {
            printf("\n\nClient exited the bank!\n\n");
            keepRunning = 0;
        }else{
            int min_length; int min_index;
            min(server_queues, &min_length, &min_index);
            pthread_mutex_lock(&mutex);
            if(enqueue(server_queues[min_index], input) == 0){
                fprintf(stderr, "Error with directing the request %s to server!\n", input);
            }
            pthread_mutex_unlock(&mutex);
        }

    }
    //closing the socket
    close(server_socket);

    // wait for all threads to finish
    for(int i = 0; i < SERVERS; i++) {
        pthread_join(thread_group[i], NULL);
    }

    return 0;
}

void *server_function(void *arg){

    int my_id = *(int*) arg;
    static char empty[1] = "\0";
    struct Queue my_queue = {empty, NULL, 0};  // in my queue implementation first member is empty

    pthread_mutex_lock(&mutex);
    server_queues[my_id] = &my_queue;
    pthread_mutex_unlock(&mutex);

    char request[256];

    while(keepRunning){

        if(!isEmpty(&my_queue)){


            if(dequeue(&my_queue, request) != 1) {
                fprintf(stderr, "Server %d having error handling request %s!\n", *(int *) arg, request);
            }


            // do processing

            process(request, &bank);

        }
    }
    pthread_exit(0);
}
