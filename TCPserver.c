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
#include <netinet/in.h>
#include <arpa/inet.h>

#include "queue.h"
#include "miscellanous.h"
#include "server.h"
#include "account.h"


#define NUMOFCLIENTS 1

#define SERVERS 4

struct arg_struct {
    int id;
    int csock;
};

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

    //in_addr struct has a single member s_addr
    struct in_addr addr;

    //Convert the IP dotted quad into struct in_addr
    inet_aton("88.195.222.155", &(addr));

    server_address.sin_addr.s_addr = addr.s_addr;
    // bind the socket to our specified IP and port
    bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));
    // listen to the client
    listen(server_socket, NUMOFCLIENTS);
    // to save the id of the client socket for future data sharing
    int client_socket;
    client_socket = accept(server_socket, NULL, NULL);
    // creating threads
    for(int i = 0; i < SERVERS; i++){
        struct arg_struct args;
        args.id = i;
        args.csock = client_socket;
        pthread_create(&thread_group[i], NULL, server_function, (void *)&args);
    }
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

    struct arg_struct *args = arg;
    int my_id = args->id;
    int client_socket = args->csock;
    pthread_mutex_unlock(&mutex);
    printf("My id: %d, client sock: %d\n", my_id, client_socket);

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
            char response[100];
            process(request, &bank, response);
            send(client_socket, response, sizeof(response), 0);

        }
    }
    pthread_exit(0);
}
