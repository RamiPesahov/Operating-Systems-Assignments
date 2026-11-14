#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define MAX_LINE_LEN 1024
#define MAX_ARG 64 
#define MAX_BG_JOBS 4

typedef struct {

    int argc; // defines the numebr of arguments in the command line
    char *args[MAX_ARG + 1];  // Values of each argument(string) of the command line terminates with NULL - basically array of strings
    char raw_command[MAX_LINE_LEN + 1];  // saving the command the user put for jobs command
    int is_bg; // 1 if it's backgroung and 0 it is frontend 
} command;

int split_to_args(char *line, command *cmd); // takes a command from user, analyzing and extracting its arguments
 


#endif