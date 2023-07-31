#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>

int main()
{
    pid_t pid;
    int pipefd[2];
    FILE *f;
    int t;
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
        f = fopen("fx2.txt", "w");
        srand(time(NULL));
        for (int i = 0; i < 10; i++)
        {
            t = rand() % 100;
            write(pipefd[1], &t, sizeof(int));
        }
        close(pipefd[1]);
        fclose(f);
        exit(EXIT_SUCCESS);
        break;
    default:
        f = fopen("f.txt", "w");
        for (int i = 0; i < 10; i++)
        {
            read(pipefd[0], &t, sizeof(int));
            printf("%d\n", t);
            fprintf(f, "%d\n", t);
        }
        close(pipefd[0]);
        fclose(f);
        exit(EXIT_SUCCESS);
    }
}