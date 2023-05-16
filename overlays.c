#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <semaphore.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <pthread.h>
#include <unistd.h>

int main(){
    printf("Transfer control to execlp function");
    //execlp("head","head","-2","sample.txt",NULL); // No path required
    //execl("/usr/bin/head","head","-2","sample.txt",NULL); // Path required and can be found using 'which head'
    char *args[4] = {"head","-2","sample.txt",NULL}; // For charecter array declaration use '*-arrayName-'
//    execv("/usr/bin/head",args); // Path is required and a vector with arguments is to be provided
//    execvp("head",args); // Path is not required but arguments vector is required
    // We can use 'execvpe' and 'execle' which accepts enviroment variable input array as its parameters 
    return 0;
}