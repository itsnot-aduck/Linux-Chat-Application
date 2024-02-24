#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <signal.h>
#include <asm-generic/socket.h>
// Clearing the shell using escape sequences
#define clear() printf("\033[H\033[J")
#define MAX_CLI_NUM 8
#define MAX_CONNECTION 10
/* Enable debug option, uncomment to logging*/
#define ENABLE_DEBUG

/* For logging */
#ifdef ENABLE_DEBUG
#define LOG 1
#else
#define LOG 0
#endif

#define log(...)                                                       \
    {                                                                  \
        do                                                             \
        {                                                              \
            if ((LOG))                                                 \
            {                                                          \
                printf("\n[%s:%s:%d] ", __FILE__, __func__, __LINE__); \
                printf(__VA_ARGS__);                                   \
                printf("\n");                                          \
            }                                                          \
        } while (0);                                                   \
    } // Logging

/* Thread handler */
pthread_t accept_thread_id, receive_thread_id;

/* Socket Application variables */
typedef struct
{
    // int id;
    int fileDescription;
    int portNum;
    char myIp[16];
    struct sockaddr_in address;
} SocketInfo_t;

SocketInfo_t CurrentSocket;
SocketInfo_t ConnectedSocket[MAX_CONNECTION] = {0};
int NumOfConnection = 0;
char option[100];

/* Cli handler */
typedef void (*cli_cmd_func_t)(uint8_t argc, char **argv);
typedef struct
{
    cli_cmd_func_t function;
    char *help;
} cli_cmd_info_t;

typedef struct
{
    const char *name;
    const cli_cmd_info_t *cmd_info;
} cli_cmd_entry_t;
/* End of cli_handler */

/* Client Management */
void cliHelp(uint8_t argc, char **argv);
void cliMyIP(uint8_t argc, char **argv);
void cliMyPort(uint8_t argc, char **argv);
void cliConnect(uint8_t argc, char **argv);
void cliList(uint8_t argc, char **argv);
void cliTerminate(uint8_t argc, char **argv);
void cliSend(uint8_t argc, char **argv);
void cliExit(uint8_t argc, char **argv);

static void *receiveMsg(void *param);
void sendMsg(int sockfd, char* msg);
void exit_handler();

const cli_cmd_info_t cli_help =
    {
        cliHelp,
        "help \t \t \t \t Display information about the available user interface options or command manual"};

const cli_cmd_info_t cli_myIp =
    {
        cliMyIP,
        "myip \t \t \t \t Display the IP address of this process."};

const cli_cmd_info_t cli_myPort =
    {
        cliMyPort,
        "myport \t \t \t \t Display the port on which this process is listening for incoming connections."};

const cli_cmd_info_t cli_connect =
    {
        cliConnect,
        "connect <destination> <port no>  establishes a new TCP connection to the specified <destination> at the specified < port no>"};

const cli_cmd_info_t cli_list =
    {
        cliList,
        "list \t \t \t \t Display a numbered list of all the connections this process is part of"};

const cli_cmd_info_t cli_terminate =
    {
        cliTerminate,
        "terminate <connection fd.> \t terminate the connection given with the socket fd"};

const cli_cmd_info_t cli_send =
    {
        cliSend,
        "send <connection id.> <message>  send the message to the host on the connection that is designated by the connection id"};

const cli_cmd_info_t cli_exit =
    {
        cliExit,
        "exit \t \t \t \t Close all connections and terminate this process"};

cli_cmd_entry_t command_entry_table[8] =
    {
        {"help", &cli_help},
        {"myip", &cli_myIp},
        {"myport", &cli_myPort},
        {"connect", &cli_connect},
        {"list", &cli_list},
        {"terminate", &cli_terminate},
        {"send", &cli_send},
        {"exit", &cli_exit}};

void cliHelp(uint8_t argc, char **argv)
{
    for (int i = 1; i < MAX_CLI_NUM; i++)
    {
        printf("%10s \n", command_entry_table[i].cmd_info->help);
    }
}

void cliMyIP(uint8_t argc, char **argv)
{
    FILE *fd = popen("hostname -I", "r");

    if (fd == NULL)
    {
        printf("\nError: can not get IP address");
        return;
    }

    if (fgets(CurrentSocket.myIp, sizeof(CurrentSocket.myIp), fd) == NULL)
    {
        printf("\nError: can not get IP address");
        return;
    }

    printf("\nIP address of this app: %s\n", CurrentSocket.myIp);
}

void cliMyPort(uint8_t argc, char **argv)
{
    printf("Listening port of this app: %d\n", CurrentSocket.portNum);
}

void cliConnect(uint8_t argc, char **argv)
{
    /* argv[1]: ip 
    *  argv[2]: port    
    */
   log("try to connect to ip %s with port %s", argv[1], argv[2]);
   SocketInfo_t newInstance;
   newInstance.fileDescription = socket(AF_INET, SOCK_STREAM, 0);
    if (newInstance.fileDescription == -1){
        printf("\nError: can not create socket for this app");
        return;
    }
    // /* Init information for app */
    newInstance.address.sin_family = AF_INET;
    newInstance.address.sin_addr.s_addr = inet_addr(argv[1]);
    newInstance.portNum = atoi(argv[2]);
    newInstance.address.sin_port = htons(newInstance.portNum);
    strcpy(newInstance.myIp, argv[1]);
    if(connect(newInstance.fileDescription, (struct sockaddr*)(&newInstance.address), sizeof(newInstance.address)) == 0 ){
        printf("Connected to a new connection from address: %s\n", newInstance.myIp);
        ConnectedSocket[NumOfConnection] = newInstance;
        /* Create thread to get message from new app */
        if (pthread_create(&receive_thread_id, NULL, &receiveMsg, &ConnectedSocket[NumOfConnection]))
        {
            printf("Error: can not create thread to receive message\n");
        }
        else
        {
            pthread_detach(receive_thread_id);
            NumOfConnection++;
        }
    }
}
   
void cliList(uint8_t argc, char **argv)
{
    if(NumOfConnection == 0){
        printf("No connection found\n");
        return;
    }
    printf("ID \t IP \t \t Port\n");
    for (int i = 0; i < NumOfConnection; i++){
        printf("%d \t %s \t \t %d\n", ConnectedSocket[i].fileDescription, ConnectedSocket[i].myIp, ConnectedSocket[i].portNum);
    }
}

void cliTerminate(uint8_t argc, char **argv)
{
    char str[100];
    int sockfd = atoi(argv[1]);
    for (int i = 0; i < NumOfConnection; i++){
        if (sockfd == ConnectedSocket[i].fileDescription){
            sprintf(str, "The peer at port %d has disconnected\n", ConnectedSocket[i].portNum);
            sendMsg(sockfd, str);
            ConnectedSocket[i].fileDescription = -1;
            return;
        }
    }
    printf("Error: target not found \n");   
}

void sendMsg(int sockfd, char* msg){
    if(write(sockfd, msg, (strlen(msg))) == -1)
        printf("Error: can not send message\n");
}

void cliSend(uint8_t argc, char **argv)
{
    /* argv[1] is the sockfd, argv[2] is the message*/
    int sockfd = atoi(argv[1]);
    char* msg = argv[2];
    log("Send to sockfd %d with message %s\n", sockfd, msg);
    /* Find for the available id */
    for (int i = 0; i < NumOfConnection; i++){
        if (sockfd == ConnectedSocket[i].fileDescription){
            sendMsg(sockfd, msg);
            return;
        }
    }
    printf("Error: target not found\n");
}

void cliExit(uint8_t argc, char **argv)
{
    for(int i = 0; i < NumOfConnection; i++){
        if(ConnectedSocket[i].fileDescription > 0){
            close(ConnectedSocket[i].fileDescription);
        }
    }
    close(CurrentSocket.fileDescription);
    exit_handler();
}

void cli_handler(char *input)
{
    char *cur;
    char *argv[5];
    int count = 0, i = 0;
    log("command: %s", input);
    cur = strtok(input, " ");
    while (cur != NULL) {
        argv[count] = cur;
        log("Token: %s\n", argv[count]); // Debug print
        cur = strtok(NULL, " ");
        count++;
    }
    log("Cmd arg count: %d\n", count);
    for (i = 0; i < MAX_CLI_NUM; i++)
    {
        if (strstr(argv[0], command_entry_table[i].name))
        {
            command_entry_table[i].cmd_info->function(count, argv);
            break;
        }
    }
    if (i == MAX_CLI_NUM)
    {
        printf("Command not found, type \"help\" for view \n");
    }
}

/* System & thread hander */
void exit_handler()
{
    printf("\n-------->>> Exiting program .....\n");
    exit(0);
}

static void *receiveMsg(void *param)
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

int main(int argc, char *argv[])
{
    char buffer[30];

    if (signal(SIGINT, exit_handler) == SIG_ERR)
    {
        printf("\nCan not handler SIGINT");
    }
    if (argc < 2)
    {
        printf("\nNo port provided\ncommand: ./server <port number>\n");
        exit(EXIT_FAILURE);
    }
    log("Init application with port %d", atoi(argv[1]));
    initSocket(atoi(argv[1]));

    while (1)
    {
        printf("> ");
        fflush(stdin);
        fgets(buffer, sizeof(buffer), stdin);
        cli_handler(buffer);
    }
    return 0;
}