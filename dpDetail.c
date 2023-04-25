#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t chopstick[5]; // as we have 5 chopsticks
void * philos(void *);
void eat(int);

int main()
{
    int i, n[5];
    pthread_t T[5]; // as we have 5 philosophers
    for(i=0;i<5;i++)
    {
        sem_init(&chopstick[i],0,1);    // semaphore variable , sharing among threads , set value semaphore variable
    }
    for(i=0;i<5;i++)
    {
       n[i] = i;
       pthread_create(&T[i], NULL, philos, (void *)&n[i]);  // Creating the 5 threads , parameters -> philosopher , fourth param is input n[i] to the philos function for the philosophers 
    }
    for(i=0;i<5;i++)
    {
        pthread_join(T[i], NULL);   // Joining each of the 5 threads
    }

}
void * philos(void * n)
{
    int ph = *(int *)n; // Here we pass in the philisophers 
    printf("Philosopher %d wants to eat\n",ph);
    printf("Philosopher %d tries to pick left chopstick\n",ph);
    sem_wait(&chopstick[ph]);   // if it is able to execute this i.e the value of 'chopstick[ph]' is 1 then it will decrement the value of 'chopstick[ph]' and enter in the critical region moving furthur in the code
    printf("Philosopher %d picks the left chopstick\n",ph); // if the above function is executed without getting stuck in the while loop forever
    
    printf("Philosopher %d tries to pick right chopstick\n",ph);
    sem_wait(&chopstick[(ph+1)%5]); 
    printf("Philosopher %d picks the right chopstick\n",ph);// if the above function to pick up right chopstick is successfull without getting stuck in the while loop forever
    
    eat(ph);    // Eat function is called if the current Philosopher is able to pick up both the chopsticks
    sleep(2);   // Current theread will sleep and another thread will get a chance to execute
    printf("Philosopher %d has finished eating\n",ph);
    
    sem_post(&chopstick[(ph+1)%5]); //sets the value of right chopstick semaphore variable back to '1'
    printf("Philosopher %d leaves the right chopstick\n",ph);
    sem_post(&chopstick[ph]);   // sets the value of left chopstick semaphore variable back to '1'
     printf("Philosopher %d leaves the left chopstick\n",ph);
    
}

void eat(int ph)
{
    printf("Philosopher %d begins to eat\n",ph);
}
