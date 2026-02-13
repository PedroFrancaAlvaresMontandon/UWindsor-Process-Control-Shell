#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <cmd1> [arg1] <cmd2> [arg2] ...\n", argv[0]);
        exit(1);
    }

    int i = 1;
    while (i < argc) {
        

        pid_t pid = fork();

        if (pid < 0) {
            perror("fork");
            exit(1);
        } 
        else if (pid == 0) {
            //child 
            printf("Child PID %d: Executing command '%s'\n", getpid(), argv[i]);
    
            if (i == argc - 1) {
                execlp(argv[i], argv[i], (char *)NULL);
            } 
            else {
              
                execlp(argv[i], argv[i], argv[i+1], (char *)NULL);
            }

            perror("execlp failed");
            exit(1);
        } 
        else {
            //parent 
            
            //parent must advance the index 'i' to the next command.
            if (i == argc - 1) {
                //last command 0 args: increment by 1
                i++;
            } else {
                //command with 1 arg: increment by 2 
                i += 2;
            }
        }
    }

    // parent should wait for all children
    printf("Parent PID %d: Waiting for all children to finish...\n", getpid());
    
    //loop wait() until it returns -1
    while (wait(NULL) > 0);

    printf("Parent PID %d: All children have terminated.\n", getpid());
    printf("Observation: The outputs from child processes are intermingled,\n");
    printf("because they all run in parallel and share the same terminal.\n");

    return 0;
}