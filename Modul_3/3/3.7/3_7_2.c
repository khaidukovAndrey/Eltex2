#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>

#define LAST_MESSAGE 255

struct MsgBuf
{
    long mtype;
    char mtext[81];
} buf;

int main(int argc, char *argv[])
{
    int msqid;
    key_t key;
    int len, maxlen;

    if ((key = ftok(argv[1], 0)) < 0)
    {
        printf("Can\'t generate key\n");
        exit(EXIT_FAILURE);
    }

    if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0)
    {
        printf("Can\'t get msqid\n");
        exit(EXIT_FAILURE);
    }
    while (1)
    {

        maxlen = 81;
        if (len = msgrcv(msqid, (struct msgbuf *)&buf, maxlen, 0, 0) < 0)
        {
            printf("Can\'t receive message from queue\n");
            msgctl(msqid, IPC_RMID, NULL);
            exit(EXIT_FAILURE);
        }

        if (buf.mtype == LAST_MESSAGE)
        {
            msgctl(msqid, IPC_RMID, NULL);
            break;
        }
        printf("message type = %ld, info = %s\n", buf.mtype, buf.mtext);
    }
    exit(EXIT_SUCCESS);
}