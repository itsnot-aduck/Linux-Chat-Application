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

#include "user_config.h"
#include "app_cli.h"
#include "app_socket.h"

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