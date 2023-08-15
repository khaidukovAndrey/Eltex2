#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/ipc.h>


int main() 
{
    int fifo, buf;
    int sem_id;
    struct sembuf sem_op;
    key_t key;
    key = ftok("/etc/fstab",0);
    sem_id = semget(key, 1, 0);
    if (sem_id == -1) 
    {
        perror("Error semget");
        exit(EXIT_FAILURE);
    }

    if ((fifo = open("/tmp/my_fifo", O_RDONLY)) == -1) 
    {
        perror("Error open");
        exit(EXIT_FAILURE);
    }

    while (read(fifo, &buf, sizeof(buf)) > 0) 
    {
        sem_op.sem_num = 0;
        sem_op.sem_op = -1;
        sem_op.sem_flg = 0;
        semop(sem_id, &sem_op, 1);

        printf("Прочитано число: %d\n", buf);

        sem_op.sem_num = 0;
        sem_op.sem_op = 1;
        sem_op.sem_flg = 0;
        semop(sem_id, &sem_op, 1);
    }

    close(fifo);
    unlink("/tmp/my_fifo");

    exit(EXIT_SUCCESS);
}