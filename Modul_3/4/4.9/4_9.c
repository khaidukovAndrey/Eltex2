#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <time.h>


int *shm;
int count = 0;

void sigint_handler(int sig)
{
    printf("Количество обработанных наборов данных: %d\n", count);
    munmap(shm, 1024);
    shm_unlink("shm");
    exit(EXIT_SUCCESS);
}

int main()
{
    signal(SIGINT, sigint_handler);

    int shm_fd = shm_open("shm", O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, 1024);
    shm = (int *)mmap(NULL, 1024, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    srand(time(NULL));

    while (1)
    {
        int n = rand() % 100 + 1;
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
            wait(NULL);
            wait(NULL);
            printf("Min: %d\n", shm[n + 1]);
            printf("Max: %d\n\n", shm[n + 2]);
            count++;
        }
    }
}