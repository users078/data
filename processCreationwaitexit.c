#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include<stdlib.h>
int main() {
    pid_t pid;
    int status;

    printf("Parent process ID: %d\n", getpid());

    pid = fork();

    if (pid == -1) {
        perror("fork() failed");
        return 1;
    } else if (pid == 0) {
        printf("Child process ID: %d\n", getpid());
        printf("Child's parent process ID: %d\n", getppid());
        exit(0);
    } else {
        printf("Parent waiting for child...\n");
        wait(&status);
        printf("Child process finished with status %d\n", status);
    }

    return 0;
}