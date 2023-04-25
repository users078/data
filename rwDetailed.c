#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int count = 0, rcount=0; 
sem_t rw_mutex, mutex;

void* writer(void *p)
{
    int *i = (int *)p;
    sem_wait(&rw_mutex);    // Locks the write operation and goes into critical section via decrementing the semaphore 'rw_mutex' value
    printf("\nWriter %d writes page number %d", *i, ++count);   // Shared variable 'count' is updated
    sem_post(&rw_mutex); // Lock is released
}

void* reader(void* p)
{
    int* i = (int*)p;
    sem_wait(&mutex);   
    rcount++;
    if(rcount == 1) // Checks if the current reader is the first reader
    sem_wait(&rw_mutex);    // if yes then it locks the write operation
    sem_post(&mutex);   // Releases 'rcount' so the other readers can come in and read
    
    printf("\nReader %d reads page number %d ",*i,count);
    
    sem_wait(&mutex); //Reader is done with reading so it will lock the other readers
    rcount--;   // Decrement the 'rcount'
    if(rcount == 0) // If it is the last reader then it releases the write operation
    sem_post(&rw_mutex);
    sem_post(&mutex);
}

int main() {
    sem_init(&mutex,0,1);
    sem_init(&rw_mutex,0,1);
    
    int a[6]={1,2,3,1,2,3};
    pthread_t T[6];
    for(int i=0;i<3;i++) pthread_create(&T[i],NULL,writer,&a[i]);
    for(int i=3;i<6;i++) pthread_create(&T[i],NULL,reader,&a[i]);
    for(int i=0;i<6;i++) pthread_join(T[i],NULL);
  
    return 0;
}