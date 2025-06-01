#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>


int main()
{
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    char *args[100];
    pid_t pid;
    int status;
    while (1) {
        printf("mini_shell> ");
        fflush(stdout);

        read = getline(&line, &len, stdin);
        if (read == -1) {
            perror("getline");
            free(line);
            exit(EXIT_FAILURE);
        }

        // Remove newline character
        if (line[read - 1] == '\n') {
            line[read - 1] = '\0';
        }

        // Tokenize the input
        int i = 0;
        args[i] = strtok(line, " ");
        while (args[i] != NULL) {
            i++;
            args[i] = strtok(NULL, " ");
        }

        // Check for empty command
        if (i == 0) {
            continue;
        }

        if (strcmp(args[0], "exit") == 0) {
         break;
        }

        // Fork a child process
        pid = fork();
        if (pid < 0) {
            perror("fork");
            free(line);
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            execvp(args[0], args);
            perror("execvp");
            exit(EXIT_FAILURE);
        } else {
            // Parent process
            do {
                waitpid(pid, &status, 0);
            } while (!WIFEXITED(status));
        }
    }

    free(line);
    return 0;

}
