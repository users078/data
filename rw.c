#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int count = 0, rcount=0; 
sem_t rw_mutex, mutex;

void* writer(void *p)
{
    int *i = (int *)p;
    sem_wait(&rw_mutex);
    printf("\nWriter %d writes page number %d", *i, ++count);
    sem_post(&rw_mutex);
}

void* reader(void* p)
{
    int* i = (int*)p;
    sem_wait(&mutex);
    rcount++;
    if(rcount == 1)
    sem_wait(&rw_mutex);
    sem_post(&mutex);
    
    printf("\nReader %d reads page number %d ",*i,count);
    
    sem_wait(&mutex);
    rcount--;
    if(rcount == 0)
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