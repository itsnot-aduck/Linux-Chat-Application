#include <stdio.h>
#include <string.h>
#include "app_cli.h"
#include "app_socket.h"

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
        {"exit", &cli_exit}
};

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

/* System & thread hander */
void exit_handler()
{
    printf("\n-------->>> Exiting program .....\n");
    exit(0);
}