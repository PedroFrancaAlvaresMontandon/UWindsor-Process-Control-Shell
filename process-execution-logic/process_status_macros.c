#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h> 
#include <sys/types.h>
#include <sys/wait.h>

int main() {  
	int newpid;
	
	printf("before: mypid is %d\n", getpid());  

	if ((newpid = fork()) == -1 ) {
		perror("fork");  
		exit(1); 
	}
	else if (newpid == 0) {
		// child
		printf("I am the child %d, now sleeping for 5 seconds...\n", getpid());  
		sleep(5);
		printf("Child %d is calling abort()...\n", getpid());
		abort();  //terminate
	}
	else {
		//parent
		printf("I am the parent %d, waiting for my child.\n", getpid());  

		int status;
		int child_pid = wait(&status); //wait for child

		printf("My child %d has terminated.\n", child_pid);
		printf("I have received the raw status = %d\n", status);  

		
		if (WIFEXITED(status)) {
			// not true because of abort().
			int exit_status = WEXITSTATUS(status);
			printf("Child exited normally with status = %d\n", exit_status);
		}
		else if (WIFSIGNALED(status)) {
			// true because abort() sends SIGABRT
			
			int signal_num = WTERMSIG(status); //get the signal number
			
			printf("Child was terminated by signal: %d\n", signal_num);
			
			//use strsignal() to get the human-readable signal name
			printf("Signal name: %s\n", strsignal(signal_num));

			//WCOREDUMP checks if a core dump file was created.
			if (WCOREDUMP(status)) {
				printf("A core dump file was generated.\n");
			} else {
				printf("No core dump file was generated.\n");
			}
		}
		
	}

	return 0; 
}