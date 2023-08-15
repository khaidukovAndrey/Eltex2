#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <time.h>

int shmid;
int *shm;
int count = 0;

void sigint_handler(int sig)
{
    printf("Количество обработанных наборов данных: %d\n", count);
    shmdt(shm);
    shmctl(shmid, IPC_RMID, NULL);
    exit(EXIT_SUCCESS);
}

int main()
{
    signal(SIGINT, sigint_handler);

    key_t key = ftok("shmfile", 65);
    shmid = shmget(key, 1024, IPC_CREAT | 0666);
    shm = (int *)shmat(shmid, NULL, 0);

    srand(time(NULL));

    while (1)
    {
        int n = rand() % 10 + 1;
        shm[0] = n;
        for (int i = 1; i <= n; i++)
            shm[i] = rand() % 1000;

        switch (fork())
        {
        case -1:
            perror("Error fork");
            exit(EXIT_FAILURE);
        case 0:
            int min = shm[1];
            int max = shm[1];
            for (int i = 2; i <= n; i++)
            {
                if (shm[i] < min)
                    min = shm[i];
                if (shm[i] > max)
                    max = shm[i];
            }
            shm[n + 1] = min;
            shm[n + 2] = max;
            exit(EXIT_SUCCESS);
        default:
            wait(NULL);
            printf("Min: %d\n", shm[n + 1]);
            printf("Max: %d\n\n", shm[n + 2]);
            count++;
        }
    }
}