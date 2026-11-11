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

    int argc; // defines the numebr of arguments in the line
    char *args[MAX_ARG + 1];  // defines the values of each argument(string) terminates with NULL - basically array of strings
    char raw_command[MAX_LINE_LEN + 1];  // saving the command the user put for jobs command
    int is_bg; // 1 if it's backgroung and 0 it is frontend 
} command;




#endif