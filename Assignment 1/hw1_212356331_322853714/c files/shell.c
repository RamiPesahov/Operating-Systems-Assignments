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
        
        split_to_args(line);
        
    }

    return 0;
}
