#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>
#include <string.h>
#include <signal.h>

typedef struct Node
{
    int value;
    struct Node *next;
    struct Node *prev;
} Node;

typedef struct List
{
    struct Node *head;
    struct Node *tail;
    int numOfElems;
} List;
void ListAddToTail(List *list, int value);
int ListPop(List *list, int n);
void DeleteList(List *list);
List *NewList();
Node *SearchFromHead(List *list, int n);
struct MsgBuf
{
    long mtype;
    char mtext[81];
} buf;
int exitFlag = 0;
int main(int argc, char *argv[])
{
    int number = 0;
    int msqid;
    key_t key;
    int i, len;
    char strMsg[256];
    int maxlen = 81;
    List *clients = NewList();
    Node *tmp;
    if ((key = ftok("./client.out", 0)) < 0)
    {
        printf("Can\'t generate key\n");
        exit(-1);
    }
    fprintf(stdout, "1");

    if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0)
    {
        printf("Can\'t get msqid\n");
        exit(-1);
    }
    fprintf(stdout, "2");

    while (1)
    {

        if (len = msgrcv(msqid, (struct msgbuf *)&buf, maxlen, 0, 0) < 0)
        {
            printf("Can\'t receive message from queue\n");
            msgctl(msqid, IPC_RMID, NULL);
            exit(EXIT_FAILURE);
        }
        fprintf(stdout, "Длинна: %d\n", len);
        if (buf.mtype == 255)
        {
            fprintf(stdout, "%s", buf.mtext);

            ListAddToTail(clients, atol(buf.mtext));
            fprintf(stdout, "%ld", atol(buf.mtext));
        }
        else
        {

            number = buf.mtype;
            int v = 0;
            while (number > 9)
            {
                strMsg[v] = (number % 10) + '0';
                number = number / 10;
                v++;
            }
            strMsg[v] = number + '0';
            v++;
            strMsg[v] = '\0';
            char t;
            for (int i = 0; i < v / 2; i++)
            {
                t = strMsg[i];
                strMsg[i] = strMsg[v - 1 - i];
                strMsg[v - 1 - i] = t;
            }
            strcat(strMsg, buf.mtext);
            strcpy(buf.mtext, strMsg);
            for (int i = 0; i < clients->numOfElems; i++)
            {
                tmp = SearchFromHead(clients, 0);
                buf.mtype = tmp->value + 100;
                fprintf(stdout, "%s\n", buf.mtext);
                fprintf(stdout, "%ld", buf.mtype);
                len = strlen(buf.mtext) + 1;
                if (msgsnd(msqid, (struct msgbuf *)&buf, len, 0) < 0)
                {
                    printf("Can\'t send message to queue\n");
                    msgctl(msqid, IPC_RMID, NULL);
                    exit(EXIT_FAILURE);
                }
            }
        }
    }
    msgctl(msqid, IPC_RMID, NULL);

    exit(EXIT_SUCCESS);
}

void ListAddToTail(List *list, int value)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->next = NULL;
    newNode->prev = NULL;
    if ((list)->tail != NULL)
    {
        newNode->prev = (list)->tail;
        (list)->tail->next = newNode;
    }
    else
    {
        newNode->next = NULL;
        newNode->prev = NULL;
        (list)->head = newNode;
    }
    newNode->value = value;
    (list)->tail = newNode;
    (list)->numOfElems++;
}
int ListPop(List *list, int n)
{
    // int res = 0;
    // if (n > 0 && n < (list)->numOfElems - 1)
    // {
    //     Node *tmp = NULL;
    //     if (n <= (list)->numOfElems / 2)
    //         tmp = SearchFromHead(list, n);
    //     if (n > (list)->numOfElems / 2)
    //         tmp = SearchFromTail(list, n);
    //     res = tmp->value;
    //     tmp->prev->next = tmp->next;
    //     tmp->next->prev = tmp->prev;
    //     free(tmp);
    //     (list)->numOfElems--;
    // }
    // if (n == 0)
    //     res = ListPopHead(list);
    // if (n == (list)->numOfElems - 1)
    //     res = ListPopTail(list);
    // return res;
}
void DeleteList(List *list)
{
    Node *tmp = NULL;
    while ((list)->head->next)
    {
        tmp = (list)->head;
        (list)->head = (list)->head->next;
        free(tmp);
    }
    free((list)->head);
    free((list));
}

List *NewList()
{
    List *list = (List *)malloc(sizeof(List));
    list->head = NULL;
    list->tail = NULL;
    list->numOfElems = 0;
    return list;
}

Node *SearchFromHead(List *list, int n)
{
    Node *tmp = NULL;
    tmp = (list)->head;
    int counter = 0;
    while (counter < n)
    {
        tmp = tmp->next;
        counter++;
    }
    return tmp;
}