#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>
#include <string.h>
#include <signal.h>

struct MsgBuf
{
    long mtype;
    char mtext[81];
} buf;
int exitFlag = 0;
void sigusrHandler(int sig)
{
    exitFlag = 1;
}
int main(int argc, char *argv[])
{
    int clientId = atoi(argv[1]);
    pid_t pid = 0;
    int number = 0;
    int msqid;
    key_t key;
    int i, len;

    int maxlen = 81;
    printf("%s", argv[0]);
    if ((key = ftok(argv[0], 0)) < 0)
    {
        printf("Can\'t generate key\n");
        exit(-1);
    }
    if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0)
    {
        printf("Can\'t get msqid\n");
        exit(-1);
    }
    buf.mtype = 255;
    strcpy(buf.mtext, argv[1]);
    printf("Клиент:%s\n",buf.mtext);

    if (msgsnd(msqid, (struct msgbuf *)&buf, len, 0) < 0)
    {
        printf("Can\'t send message to queue\n");
        msgctl(msqid, IPC_RMID, NULL);
        exit(EXIT_FAILURE);
    }
    buf.mtype = clientId;

    switch (pid = fork())
    {
    case -1:
        perror("Error fork");
        exit(EXIT_FAILURE);
        break;
    case 0:
        if (signal(SIGUSR1, sigusrHandler) == SIG_ERR)
        {
            perror("Signal");
            exit(EXIT_FAILURE);
        }
        while (!exitFlag)
        {
            if (len = msgrcv(msqid, (struct msgbuf *)&buf, maxlen, clientId + 100, 0) < 0)
            {
                msgctl(msqid, IPC_RMID, NULL);
                exit(EXIT_FAILURE);
            }

            fprintf(stdout, "%s\n", buf.mtext);
        }
        break;
    default:
        while (!exitFlag)
        {
            scanf("%s", buf.mtext);
            if (strcmp(buf.mtext, "exit") == 0)
            {
                kill(pid, SIGUSR1);
                break;
            }
            len = strlen(buf.mtext) + 1;
            if (msgsnd(msqid, (struct msgbuf *)&buf, len, 0) < 0)
            {
                printf("Can\'t send message to queue\n");
                msgctl(msqid, IPC_RMID, NULL);
                exit(EXIT_FAILURE);
            }
        }
        break;
    }
    msgctl(msqid, IPC_RMID, NULL);

    exit(EXIT_SUCCESS);
}