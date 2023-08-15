#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <sys/sem.h>




int main() 
{
    int fifo;
    struct sembuf sem;
    sem.sem_flg = 0;
    sem.sem_num = 0;
    srand(time(NULL));
    int num;
    key_t key;
    key = ftok("/etc/fstab",0);
    int sem_id = semget(key, 1, IPC_CREAT | 0644);
    if (sem_id == -1) 
    {
        perror("Error semget");
        exit(EXIT_FAILURE);
    }

    sem.sem_op = 1;
    semop(sem_id, &sem, 1);

    if ((fifo = open("/tmp/my_fifo", O_WRONLY)) == -1) 
    {
        perror("open");
        exit(EXIT_FAILURE);
    }


    for (size_t i = 0; i < 10; i++) 
    {
        num = rand() % 100;

        sem.sem_op = -1;
        semop(sem_id, &sem, 1);
        write(fifo, &num, sizeof(num));
        sem.sem_op = 1;
        semop(sem_id, &sem, 1);

        printf("Сгенерировано число: %d\n", num);
    }

    close(fifo);

    exit(EXIT_SUCCESS);
}