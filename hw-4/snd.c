#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
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
    struct msgbuf sbuf;
    size_t buflen;

    key = 0x1234;

    if ((msqid = msgget(key, IPC_CREAT | 0600)) < 0)
        die("msgget cannot create message queue.");

    //Message Type
    sbuf.mtype = 1;

    while (1)
    {
        printf("Enter a message to add to message queue: ");
        scanf("%[^\n]", sbuf.mtext);
        getchar();

        buflen = strlen(sbuf.mtext) + 1 ;
        sbuf.mtext[buflen] = '\0';

        if (msgsnd(msqid, &sbuf, buflen, 0) < 0)
        {
            printf ("%d, %ld, %s, %d \n", msqid, sbuf.mtype, sbuf.mtext, (int)buflen);
            die("msgsnd failed.");
        }
        else
            printf("Message Sent\n");
    }
    exit(0);
}
