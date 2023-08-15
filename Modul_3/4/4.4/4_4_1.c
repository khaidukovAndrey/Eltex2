#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>
#include <semaphore.h>

int main() 
{
    int fifo;
    sem_t *sem;
    sem = sem_open("sem", O_CREAT, 0644, 1);
    srand(time(NULL));
    int num;

    if ((fifo = open("/tmp/my_fifo", O_WRONLY)) == -1) 
    {
        perror("Error open");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < 10; i++) 
    {
        num = rand() % 100;
        sem_wait(sem);
        write(fifo, &num, sizeof(num));
        sem_post(sem);
        printf("Сгенерировано число: %d\n", num);
    }

    close(fifo);
    sem_close(sem);

    exit(EXIT_SUCCESS);
}