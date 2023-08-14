#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#define LAST_MESSAGE 255

struct MsgBuf
{
    long mtype;
    char mtext[81];
} buf;

int main(int argc, char *argv[])
{
    int number = 0;
    int msqid;
    key_t key;
    int i, len;
    char msg[10];
    if ((key = ftok(argv[1], 0)) < 0)
    {
        printf("Can\'t generate key\n");
        exit(-1);
    }
    if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0)
    {
        printf("Can\'t get msqid\n");
        exit(-1);
    }
    buf.mtype = 1;

    for (i = 0; i < 10; i++)
    {
        number = rand() % 10;
        int v = 0;
        while (number > 9)
        {
            msg[v] = (number % 10) + '0';
            number = number / 10;
            v++;
        }
        msg[v] = number + '0';
        v++;
        msg[v] = '\0';
        char t;
        for (int i = 0; i < v / 2; i++)
        {
            t = msg[i];
            msg[i] = msg[v - 1 - i];
            msg[v - 1 - i] = t;
        }
        strcpy(buf.mtext, msg);
        printf("%s\n", buf.mtext);

        len = strlen(buf.mtext) + 1;
        if (msgsnd(msqid, (struct msgbuf *)&buf, len, 0) < 0)
        {
            printf("Can\'t send message to queue\n");
            msgctl(msqid, IPC_RMID, NULL);
            exit(EXIT_FAILURE);
        }
    }
    buf.mtype = LAST_MESSAGE;
    len = 0;
    if (msgsnd(msqid, (struct msgbuf *)&buf, len, 0) < 0)
    {
        printf("Can\'t send message to queue\n");
        msgctl(msqid, IPC_RMID, NULL);
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}