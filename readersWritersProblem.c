#include <stdio.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <fcntl.h>
#include <sys/sem.h>
#include <pthread.h>
#include <semaphore.h>


sem_t wrt;
pthread_mutex_t L;
int cnt=1;
int numreader=1;

void *writer(void *wno){
    sem_wait(&wrt); // Decrements the semaphore value from 1 to 0 to obtain all the resources and block the other calling operations
        cnt = cnt*2;// Increments the value of 'cnt' to 'cnt*2'
    printf("Writer %d modified cnt to %d\n",*((int *)wno),cnt);
    sem_post(&wrt); // performing the 'signal()' operation to release or increment the semaphore variable so other processes can then acquire the 'wait()' signal
}

void *reader(void *rno){
    pthread_mutex_lock(&L); // Creating a mutex lock for the readers to read 
    numreader++; // Since a reader just camein so we increase the numreader by 1
    if(numreader == 1){ // If this is the first reader then we will lock or obtain all the resources of the writer operation and just perform the reader operation
        sem_wait(&wrt); 
    }
    pthread_mutex_unlock(&L); // Unlocking the mutex lock so the other readers can also access or perform the read operation

    printf("Reader %d read cnt as %d\n",*((int *)rno),cnt);
           
    // Reader operation acquires the lock before modifying the numreader
    pthread_mutex_lock(&L);
    numreader--; // Reader decrements the numreader variable value as it is now finished with the reading operation
    if(numreader == 1){ // if the reader is the last reader
        sem_post(&wrt); // Decrementing the semapgore variable value from 1 to 0
    }
    pthread_mutex_unlock(&L); // Release the lock so the other read processes can make their entry
}

int main(){
    pthread_t read[10],write[5];
    pthread_mutex_init(&L,NULL); //Initializing the pthread mutex variable
    sem_init(&wrt,0,1); // Initializing the semaphore variable with the semaphore variable and we do this via a binary semaphore variable and since we want to share this semaphore variable between threads we put '0' as the middle parameter
    int a[10] = {1,2,3,4,5,6,7,8,9,10};
    int i;
        for(i=0;i<10;i++){ // Creating the 'read' array of threads
        pthread_create(&read[i],NULL,(void *)reader,(void *)&a[i]);
    }
    for(i=0;i<5;i++){ // Creating the 'write' array of threads
        pthread_create(&write[i],NULL,(void *)writer,(void *)&a[i]);
    }
    //Joining the 'read' and 'write' threads together
    for(i=0;i<10;i++){
        pthread_join(&read[i],NULL);
    }
    for(i=0;i<5;i++){
        pthread_join(&write[i],NULL);
    }
    pthread_mutex_destroy(&L);
    return 0;
}