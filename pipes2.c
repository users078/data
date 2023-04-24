#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main()
{
    int pipe_fd[2];
    pid_t pid;
    if (pipe(pipe_fd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid == 0)
    {
        close(pipe_fd[0]);
        dup2(pipe_fd[1], STDOUT_FILENO);
        execlp("ls", "ls", "-l", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }
    else
    {
        close(pipe_fd[1]);
        char buffer[1024];
        ssize_t nread;
        while ((nread = read(pipe_fd[0], buffer, sizeof(buffer))) != 0)
        {
            write(STDOUT_FILENO, buffer, nread);
        }
        wait(NULL);
    }
    return 0;
}