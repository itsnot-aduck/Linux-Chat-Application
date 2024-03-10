#include <stdio.h>
#include <string.h>
#include "app_socket.h"
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <signal.h>
#include <asm-generic/socket.h>
/* Thread handler */
int NumOfConnection = 0;
char option[100];
SocketInfo_t CurrentSocket;
SocketInfo_t ConnectedSocket[MAX_CONNECTION] = {0};
pthread_t accept_thread_id, receive_thread_id;


void *receiveMsg(void *param)
{
    char send_buffer[200];
    SocketInfo_t* DestSocket = (SocketInfo_t*) param;
    int connfd = DestSocket->fileDescription;
    while(1){
        int read_numb = read(connfd, send_buffer, (sizeof(send_buffer)));
        if(read_numb){
            log("read_numb: %d", read_numb);
            printf("Recv Mesage from %s\n", DestSocket->myIp);
            printf("Sender's port: %d\n", DestSocket->portNum);
            printf("Message: %s with length %ld\n", send_buffer, strlen(send_buffer));   
        }
    }
}

static void *accept_app(void *param)
{
    int clientFileDescription, ret;
    struct sockaddr_in client_addr;
    socklen_t len = sizeof(client_addr);
    while (1)
    {
        clientFileDescription = accept(CurrentSocket.fileDescription, (struct sockaddr *)&client_addr, &len);
        if (clientFileDescription == -1)
        {
            printf("\nError: can not accept new app");
            return NULL;
        }
        /* Save info of new instance */
        /* Add node - (for ver2. using linked - list)*/
        ConnectedSocket[NumOfConnection].fileDescription = clientFileDescription;
        ConnectedSocket[NumOfConnection].address = client_addr;
        ConnectedSocket[NumOfConnection].portNum = ntohs(client_addr.sin_port);

        /* Convert binary ip of client to char */
        inet_ntop(AF_INET, &client_addr.sin_addr, ConnectedSocket[NumOfConnection].myIp, sizeof(ConnectedSocket[NumOfConnection].myIp));

        printf("Accept a new connection from address: %s, setup at port: %d\n", ConnectedSocket[NumOfConnection].myIp, ConnectedSocket[NumOfConnection].portNum);

        /* Create thread to get message from new app */
        if (pthread_create(&receive_thread_id, NULL, &receiveMsg, &ConnectedSocket[NumOfConnection]))
        {
            printf("\nError: can not create thread to receive message\n");
        }
        else
        {
            pthread_detach(receive_thread_id);
            NumOfConnection++;
        }
    }
}

void initSocket(int port)
{
    CurrentSocket.fileDescription = socket(AF_INET, SOCK_STREAM, 0);
    /* Prevent err: “address already in use” */
    setsockopt(CurrentSocket.fileDescription, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &option, sizeof(option));
    if (CurrentSocket.fileDescription == -1)
    {
        printf("\nError: can not create socket for this app");
        exit(-1);
    }
    /* Init information for current app's socket */
    CurrentSocket.portNum = port;
    CurrentSocket.address.sin_family = AF_INET;
    CurrentSocket.address.sin_port = htons(CurrentSocket.portNum);
    CurrentSocket.address.sin_addr.s_addr = INADDR_ANY;

    if (bind(CurrentSocket.fileDescription, (struct sockaddr *)&CurrentSocket.address, sizeof(CurrentSocket.address)) == -1)
    {
        printf("\nError: can not make bind for this socket");
        exit(-1);
    }

    if (listen(CurrentSocket.fileDescription, MAX_CONNECTION) == -1)
    {
        printf("\nError: can not listen for this device");
        exit(-1);
    }

    printf("\nApplication is listening on port : %d\n", CurrentSocket.portNum);

    if (pthread_create(&accept_thread_id, NULL, &accept_app, NULL))
    {
        printf("\nError: can not create thread for accept new app");
        exit(-1);
    }
}