#include "shell.h"

int main() {

    int exit = 0;
    
    char line[MAX_LINE_LEN + 2];

    while(1) {

        printf("hw1shell$ ");   
        fflush(stdout); // need to flush because there isn't \n

        if(fgets(line, sizeof(line), stdin) == NULL) {

            printf("hw1shell: %s failed, errno is %d", line, errno);
            fflush(stdout);
            break;
        }
        
        command *cmd;
        if(split_to_args(line, cmd) == -1) { // invalid command if the arguments are greather than the MAX_ARG and if the command does'nt exist/ 
            
            printf("hw1shell: invalid command");
            fflush(stdout);
            continue;
        } 

        if(cmd->argc == 0) // an empty command, we need to continue
            continue;


        
    }

    return 0;
}
