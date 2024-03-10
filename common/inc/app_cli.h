#ifndef __APP_CLI_H__
#define __APP_CLI_H__

#include "user_config.h"
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <asm-generic/socket.h>
/* Socket Application variables */


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

void cli_handler(char *input);
void exit_handler();
/* Client Management */
void cliHelp(uint8_t argc, char **argv);
void cliMyIP(uint8_t argc, char **argv);
void cliMyPort(uint8_t argc, char **argv);
void cliConnect(uint8_t argc, char **argv);
void cliList(uint8_t argc, char **argv);
void cliTerminate(uint8_t argc, char **argv);
void cliSend(uint8_t argc, char **argv);
void cliExit(uint8_t argc, char **argv);

#endif /* __APP_CLI_H__ */