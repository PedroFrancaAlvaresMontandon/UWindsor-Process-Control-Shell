#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

void childFunction(char *line);

// write() for console output
void write_string(const char *str) {
    write(STDOUT_FILENO, str, strlen(str));
}

int main() {
    char input_buffer[256];
    pid_t pid;
    int status;


    write_string("This program makes simple arithmetic calculations.\n");

    //gets in an infinite loop
    for (;;) {
        
        write_string("Enter an arithmetic statement, e.g., 34 + 132 > ");

        memset(input_buffer, 0, sizeof(input_buffer));

        //reads the whole input line 
        ssize_t bytes_read = read(STDIN_FILENO, input_buffer, sizeof(input_buffer) - 1);
        if (bytes_read <= 0) {
            write_string("\nGoodbye.\n");
            break;
        }
        input_buffer[bytes_read] = '\0';

        
        pid = fork();

        if (pid == -1) {
            perror("fork");
            exit(1);
        } else if (pid == 0) {
            //child
            childFunction(input_buffer);
        } else {
            // parent 
            write_string("Created a child to make your operation, waiting ...\n");

            // wait for child.
            wait(&status);

            //parent checks returned status 
            if (WIFEXITED(status)) {
                int exit_code = WEXITSTATUS(status);
                
                
                if (exit_code == 50) {
                    write_string("Wrong statement\n");
                } else if (exit_code == 100) {
                    write_string("Division by zero\n");
                } else if (exit_code == 200) {
                    write_string("Wrong operator\n");
                }
            }
        }
    } 

    return 0;
}

//child through childFunction(char *line):
void childFunction(char *line) {
    int n1, n2, result;
    char op;
    char output_buffer[256];

    
    write_string("I am a child working for my parent.\n");

    //sscanf() to convert the input line
    int items_scanned = sscanf(line, "%d %c %d", &n1, &op, &n2);

    //case of a wrong statement
    if (items_scanned != 3) {
        exit(50);
    }

    switch (op) {
        case '+':
            result = n1 + n2;
            break;
        case '-':
            result = n1 - n2;
            break;
        case '*':
            result = n1 * n2;
            break;
        case '/':
            if (n2 == 0) {
                exit(100);
            }
            result = n1 / n2;
            break;
        default:
            exit(200);
    }

    //create an output buffer
    sprintf(output_buffer, "%d %c %d = %d\n", n1, op, n2, result);

    write_string(output_buffer);
    
    exit(0);
}