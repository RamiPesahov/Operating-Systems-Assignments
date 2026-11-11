#include "shell.h"


int split_to_args(char *line, command *cmd) {
    
    cmd->argc = 0;
    cmd->is_bg = 0;
    cmd->raw_command[0] = '\0';
    for(int i = 0; i <= MAX_ARG; i++){
        cmd->args[i] = NULL;
    }

    int len = strlen(line);
    if(len > 0 && line[len - 1] == '\n') // getting rid of the \n in the end of command
        line[len - 1] = '\0';
    
    strncpy(cmd->raw_command, line, MAX_LINE_LEN);
    cmd->raw_command[MAX_LINE_LEN] = '\0';
    
    
    strtok(cmd.args[cmd.argc], " \t\r\n");
}