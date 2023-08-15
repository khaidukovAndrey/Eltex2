#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <semaphore.h>


int main() 
{
    int fifo, buf;
    sem_t *sem;
    sem = sem_open("sem", 0);
    if ((fifo = open("/tmp/my_fifo", O_RDONLY)) == -1) 
    {
        perror("Error open");
        exit(EXIT_FAILURE);
    }

    while (read(fifo, &buf, sizeof(buf)) > 0) 
    {
        sem_wait(sem);
        printf("Прочитано число: %d\n", buf);
        sem_post(sem);
    }

    close(fifo);
    sem_close(sem);
    unlink("/tmp/my_fifo");

    exit(EXIT_SUCCESS);
}