#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#define MAXSIZE 128

int msqid;

void sigint_handler(int sig)
{
    msgctl(msqid, IPC_RMID, 0);
}

void die(char *s)
{
    perror(s);
    exit(1);
}

struct msgbuf
{
    long mtype;
    char mtext[MAXSIZE];
};

int main()
{
    signal(SIGINT, sigint_handler);

    key_t key;
    struct msgbuf rcvbuffer;

    key = 0x1234;

    if ((msqid = msgget(key, IPC_CREAT | 0600)) < 0)
        die("msgget create or get msg failed!");

    printf("Ready to receive msgs...\n");

    while (1)
    {
         //Receive an answer of message type 1.
        if (msgrcv(msqid, &rcvbuffer, MAXSIZE, 1, 0) < 0)
            die("msgrcv");

        printf("%s\n", rcvbuffer.mtext);
    }

    exit(0);
}
