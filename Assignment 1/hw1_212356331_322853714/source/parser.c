#include "shell.h"


int split_to_args(char *line, command *cmd) {
    
    // initalize empty command

    cmd->argc = 0;
    cmd->is_bg = 0;
    cmd->raw_command[0] = '\0';
    for(int i = 0; i <= MAX_ARG; i++){
        cmd->args[i] = NULL;
    }

    // cmd -> args[0] is the command type, like: cd, exit ....
    // cmd -> args[argc - 1] says whether its background or no

    int len = strlen(line);
    if(len > 0 && line[len - 1] == '\n') // getting rid of the \n in the end of command
        line[len - 1] = '\0';
    
    // saving the raw command before extracting the information of the command

    strncpy(cmd->raw_command, line, MAX_LINE_LEN);
    cmd->raw_command[MAX_LINE_LEN] = '\0'; 
    
    // getting every word from the command line

    char *word = strtok(line, " \t\r\n"); // removing backspace, tab, and end of sentence including windows 
    while(word != NULL) {

        if(cmd->argc == MAX_ARG) // more than 64 parameters
            return -1;

        cmd -> args[cmd -> argc] = word;
        cmd -> argc = cmd -> argc + 1;
        word = strtok(NULL, " \t\r\n"); 
    }

    // checking whether its a background command and if it is, remove the symbol and keep the command information

    char *last_argument = cmd->args[cmd->argc - 1];
    int last_argument_len = strlen(last_argument);

    if(last_argument[last_argument_len - 1] == '&') { // it means that the last letter is the backgroung signal

        cmd->is_bg = 1; 

        if(last_argument_len == 1) { // it means & is a spereate word

            cmd->args[cmd->argc - 1] = NULL;
            cmd->argc = cmd->argc - 1;
        }
        else { // it means & is the last letter of other argument

            last_argument[last_argument_len - 1] = '\0';
            last_argument_len--;
        }

        if(cmd->argc == 0) // the command is only the argument &, invalid command
            return -1;
    } 
    
    return 0;
}