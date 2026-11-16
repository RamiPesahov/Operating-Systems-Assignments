#include "shell.h"

static bg_job bg_jobs[MAX_BG_JOBS];

void system_call_error(char *system_call_name, int error) {
    printf("hw1shell: %s failed, errno is %d\n", system_call_name, error);
}

static int count_active_bg_jobs(void) {
    int count = 0;
    for(int i = 0; i < MAX_BG_JOBS; i++) {
        if(bg_jobs[i].active) {
            count++;
        }
    }
    return count;
}

static void add_bg_job(pid_t pid, const char *raw_cmd) {
    //adding background job to the first possible empty job slot
    for(int i = 0; i < MAX_BG_JOBS; i++) {
        if(!bg_jobs[i].active) {
            bg_jobs[i].pid = pid;
            strncpy(bg_jobs[i].raw_command, raw_cmd, MAX_LINE_LEN);
            bg_jobs[i].raw_command[MAX_LINE_LEN] = '\0';
            bg_jobs[i].active = true;
            break;
        }
    }
}

void reap_finished_bg_jobs(void) {
    for(int i = 0; i < MAX_BG_JOBS; i++) {
        if(bg_jobs[i].active) {
            pid_t res = waitpid(bg_jobs[i].pid, NULL, WNOHANG);
            if(res > 0) {
                printf("hw1shell: pid %d finished\n", bg_jobs[i].pid);
                bg_jobs[i].active = false; //empty the slot
            }
            else if(res == -1) {
                system_call_error("waitpid", errno);
                bg_jobs[i].active = false; // free the slot so it does'nt stay stuck
            }
        }
    }
}

void reap_all_bg_child_processes(void) {
    for(int i = 0; i < MAX_BG_JOBS; i++) {
        if(bg_jobs[i].active) {
            if(waitpid(bg_jobs[i].pid, NULL, 0) == -1) {
                system_call_error("waitpid", errno);
            }
            bg_jobs[i].active = false;
        }
    }
}

bool handle_command(command *cmd) {

    char *command_type = cmd->args[0]; 
    
    if(strcmp(command_type, "cd") == 0) {

        if(cmd->is_bg || cmd->argc != 2) { // reject 'cd ... &' and wrong argument counts
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
        
        // Design decision: reject "jobs" with extra arguments or '&' as invalid command
        if(cmd->is_bg || cmd->argc != 1) {
            printf("hw1shell: invalid command\n");
            return false;
        }

        for(int i = 0; i < MAX_BG_JOBS; i++) {
            if(bg_jobs[i].active) {
                printf("%d\t%s\n", bg_jobs[i].pid, bg_jobs[i].raw_command);
            }
        }
    }
    else if(strcmp(command_type, "exit") == 0) {

        // Design decision: reject 'exit' with extra arguments or '&' as invalid command
        if(cmd->is_bg || cmd->argc != 1) {
            printf("hw1shell: invalid command\n");
            return false;
        }

        reap_all_bg_child_processes();
        return true; // we want to exit so should_exit = true
    }
    else {
        if(cmd->is_bg && count_active_bg_jobs() >= MAX_BG_JOBS) {
            printf("hw1shell: too many background commands running\n");
            return false;
        }        
        
        pid_t pid = fork();
        if(pid > 0) {
            // father
            if(cmd->is_bg) {
                printf("hw1shell: pid %d started\n", pid);
                add_bg_job(pid, cmd->raw_command);
            }
            else {
                if(waitpid(pid, NULL, 0) == -1) {
                    system_call_error("waitpid", errno);
                }
            }
        }
        else if(pid == 0) {
            execvp(command_type, cmd->args);  //replace the child with the apropriate program
            system_call_error("execvp", errno);
            printf("hw1shell: invalid command\n"); // execvp returns only on error
            exit(1); //exit the chuld process with error
        }
        else {
            system_call_error("fork", errno);
        }

    }
    return false; 
}


