#include "shell.h"

void system_call_error(char *system_call_name, int error) {

    printf("hw1shell: %s failed, errno is %d\n", system_call_name, error);
}

bool handle_command(command *cmd) {

    char *command_type = cmd->args[0]; 
    
    if(strcmp(command_type, "cd") == 0) {

        if(cmd->argc != 2) { // only cd <directoryname> is valid

            printf("hw1shell: invalid command\n");
            return false;         
        }

        char *path = cmd->args[1];
        int cd_result = chdir(path);        
        
        if(cd_result == -1) { // if the cd command was unsucessful because of a variant command, like cd to a non-existing directory
            
            system_call_error("chdir", errno); // handle failed system call attempt and use the errno
            printf("hw1shell: invalid command\n");
        }
        
    }
    else if(strcmp(command_type, "jobs") == 0) {



    }
    else if(strcmp(command_type, "exit") == 0) {

        // reap_all_bg_child_process()
        return true; // we want to exit so should_exit = true
    }
    else {
        // not finished
        pid_t pid = fork();
        if(pid > 0) {

            // father
        }
        else if(pid == 0) {

            // chyid
        }
        else {

            system_call_error("fork", errno);
        }
        if(execvp(command_type, cmd->args) == -1) {

            system_call_error(command_type, errno);
        }
    }
    return false; 
}


