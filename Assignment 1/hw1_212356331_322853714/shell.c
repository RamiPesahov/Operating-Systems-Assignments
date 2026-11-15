#include "shell.h"



int main() {

    bool should_exit = 0;
    
    char line[MAX_LINE_LEN + 2];

    while(!should_exit) {

        printf("hw1shell$ ");   
        fflush(stdout); // need to flush because there isn't \n

        if(fgets(line, sizeof(line), stdin) == NULL) { // end of input - acts like exit command

            printf("\n");
            reap_all_bg_child_processes(); // we need to reap all the child processes possibly running in the background
            break;
        }
        
        command cmd;
        if(split_to_args(line, &cmd) == false) { // invalid command if the arguments are greather than the MAX_ARG and if the command does'nt exist
            printf("hw1shell: invalid command\n");
        } 

        else if(cmd.argc > 0) { // a regualr command

            should_exit = handle_command(&cmd);
        }
    
        if (!should_exit) {
            reap_finished_bg_jobs(); // reap background jobs
        }
        
    }

    return 0;
}
