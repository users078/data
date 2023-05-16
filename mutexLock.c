#include <sys/sem.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int shared = 1;
pthread_mutex_t L;
void *fun1(){
    int x;
    printf("Thread 1 trying to acquire Lock\n");
    pthread_mutex_lock(&L);
    x = shared;
    printf("Thread 1 acquired the lock and reads the value of shared variable as %d\n",x);
    x++;
    printf("Local updation done to x now value of x is %d\n",x);
    sleep(1);
    shared = x;
    printf("Value of shared assigned by x is %d\n",shared);
    pthread_mutex_unlock(&L);
}
void *fun2(){
    int y;
    printf("Thread 2 trying to acquire Lock\n");
    pthread_mutex_lock(&L);
    y = shared;
    printf("Thread 2 reads the value of the shared variable as %d\n",y);
    y--;
    printf("Local updation done to y now value of y is %d\n",y);
    sleep(1);
    shared = y;
    printf("Value of shared assigned by y is %d\n",shared);
    pthread_mutex_unlock(&L);
}

int main(){
    pthread_mutex_init(&L,NULL);
    pthread_t thread1,thread2;
    pthread_create(&thread1,NULL,fun1,NULL);
    pthread_create(&thread2,NULL,fun2,NULL);
    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);
    printf("Final value of the shared variable is %d",shared);
    return 0;
}