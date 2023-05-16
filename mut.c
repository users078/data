#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
int main(){
    int pid,semid,val; // 'pid' is for the process id , 'semid' is the semaphore id 
    struct sembuf sop;
        semid = semget((key_t)6,1,IPC_CREAT | 0666);// Passing in a key and IPC_CREAT to create a semaphore
    
    pid = fork();
    sop.sem_num = 0; // This is the semaphore number
    sop.sem_op = 0; // This is for the operations that will be performed on the semaphore variable
    sop.sem_flg = 0; // This is for the flag of the semaphore variable
    
    if(pid == 0){
        printf("The child will launch a WAIT signal to the parent\n");
        semctl(semid,0,SETVAL,1); // 'semctl' function is used when we perform an operation on semaphore
        // 'semctl' takes 'semid' , -semaphore number- , -set the value- , value set to 1
        sleep(10); // After 10 seconds the commands beneath would run
        printf("The child is awake and doing his JOB\n");
        semctl(semid,0,SETVAL,0); // i.e we took control back
    
    }else{
        sleep(1); // Will sleep for 1 second
        printf("The parent is now ACTIVE and waiting for WAIT signal from the child\n");
       
        //Wait for the signal from child
        semctl(semid,&sop,1);
        printf("The parent is awake and doing his job\n");
        sleep(10);
        printf("Parent Job over\n");
    }
    
    return 0;
}