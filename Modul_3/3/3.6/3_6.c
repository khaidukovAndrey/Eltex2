#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <signal.h>

int IsLocked = 0;
void LockFile(int sig)
{
    IsLocked = 1;
}

void FreeFile(int sig)
{
    IsLocked = 0;
}

int main()
{
    pid_t pid;
    int pipefd[2];
    FILE *f;
    int t;

    f = fopen("f.txt", "w");
    fclose(f);

    if (signal(SIGUSR1, LockFile) == SIG_ERR)
    {
        perror("Signal");
        exit(EXIT_FAILURE);
    }
    if (signal(SIGUSR2, FreeFile) == SIG_ERR)
    {
        perror("Signal");
        exit(EXIT_FAILURE);
    }
    if (pipe(pipefd) == -1)
    {
        perror("Error pipe");
        exit(EXIT_FAILURE);
    }
    switch (pid = fork())
    {
    case -1:
        perror("Error fork");
        exit(EXIT_FAILURE);
        break;
    case 0:
        srand(time(NULL));
        int seek = 0;
        int symT = 0;

        for (int i = 0; i < 10; i++)
        {
            t = rand() % 100;
            write(pipefd[1], &t, sizeof(int));
            while (IsLocked)
            {
            }
            f = fopen("f.txt", "r");
            fseek(f, seek, SEEK_SET);
            if ((symT = fscanf(f, "%d ", &t)) >0)
            {
                fprintf(stdout, "%d\n", t);
                seek += symT;
            }
            fclose(f);
        }
        close(pipefd[1]);

        exit(EXIT_SUCCESS);
        break;
    default:

        for (int i = 0; i < 10; i++)
        {
            read(pipefd[0], &t, sizeof(int));
            while (IsLocked)
            {
            }
            kill(pid, SIGUSR1);
            f = fopen("f.txt", "ab+");
            fprintf(f, "%d ", t);
            fclose(f);
            kill(pid, SIGUSR2);
        }
        close(pipefd[0]);

        exit(EXIT_SUCCESS);
    }
}