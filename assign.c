// 1. The child process send two numbers to the parent process via message queue. 
// The parent process calculate the sum and return via same message queue.
// The child process print the result and exit. 
// The parent process wait for completion of the child and then exit.

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/msg.h>

#define MQ_KEY 0x00001234


typedef struct msg {
    long type;
    int num1;
    int num2;
} msg_t;

int main() {
    int ret, s, mqid;
    // create message queue
    mqid = msgget(MQ_KEY, IPC_CREAT|0600);
    if(mqid < 0) {
        perror("msgget() failed");
        _exit(1);
    }
    ret = fork();
    if(ret == 0) {
        // child process -- receiver
        
        msg_t m1;
        m1.type = 99;

        printf("child: enter a num1: ");
        scanf("%d", &m1.num1);
        
        
        printf("child: enter a num2: ");
        scanf("%d", &m1.num2);

        msgsnd(mqid, &m1, sizeof(msg_t), 0);
        msgsnd(mqid, &m1, sizeof(m1.num2), 0);

        
        msgrcv(mqid, &m1, sizeof(msg_t) - sizeof(long), 33, 0);
        printf("child: received sum from parent - %d\n", m1.num1);


        
    }
    else {
        // parent process -- sender
        msg_t m2;

        msgrcv(mqid, &m2, sizeof(msg_t), 99, 0);
        printf("parent: received - %d %d\n", m2.num1,m2.num2);
        
        int sum = m2.num1 + m2.num2;

        m2.type = 33; 
        m2.num1 = sum;
        msgsnd(mqid, &m2, sizeof(msg_t) - sizeof(long), 0);

        waitpid(-1, &s, 0);
        msgctl(mqid, IPC_RMID, NULL);
    }
    return 0;
}