#ifndef __APP_SOCKET_H__
#define __APP_SOCKET_H__

#include <pthread.h>

#include "user_config.h"
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h>

typedef struct
{
    // int id;
    int fileDescription;
    int portNum;
    char myIp[16];
    struct sockaddr_in address;
} SocketInfo_t;

extern int NumOfConnection;
extern char option[100];
extern SocketInfo_t CurrentSocket;
extern SocketInfo_t ConnectedSocket[MAX_CONNECTION];
extern pthread_t accept_thread_id, receive_thread_id;

/* Thread handler */
void *receiveMsg(void *param);
void sendMsg(int sockfd, char* msg);

void initSocket(int port);

#endif /* __APP_SOCKET_H__ */