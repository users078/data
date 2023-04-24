#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define MAX 50  // Max Bytes of data that can be written in the message queue
  
// structure for message queue
struct mesg_buffer {
    long mesg_type;
    char mesg_text[100];
} message;
  
int main()
{
    key_t key;
    int msgid;
  
    // ftok to generate unique key
    key = ftok("progfile", 65);
  
    // msgget creates a message queue
    // and returns queue identifier
    msgid = msgget(key, 0666 | IPC_CREAT);  // Key , Permission i.e Read And Write , instruct to create the message queue
    message.mesg_type = 1;
  
    printf("Write Data : ");
    fgets(message.mesg_text,MAX,stdin);
  
    // msgsnd to send message
    msgsnd(msgid, &message, sizeof(message), 0);    // Zero in the last parameter means that when the queue is full it will suspend the send message process and wait for space to be available
  
    // display the message
    printf("Data send is : %s \n", message.mesg_text);
  
    return 0;
}
