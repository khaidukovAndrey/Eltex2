#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void sigintHandler(int sig)
{
    if (sig == 2)
        printf("Получен сигнал SIGINT\n");
    if (sig == 3)
        printf("Получен сигнал SIGQUIT\n");
}

int main()
{
    signal(SIGINT, sigintHandler);
    signal(SIGQUIT, sigintHandler);

    FILE *fd = NULL;
    int counter = 0;

    while (1)
    {
        if ((fd = fopen("counter.txt", "ab+")) == NULL)
        {
            perror("fopen");
            exit(EXIT_FAILURE);
        }
        signal(SIGINT, SIG_IGN);
        signal(SIGQUIT, SIG_IGN);
        if (fprintf(fd, "%d\n", counter) < 0)
        {
            perror("fprintf");
            exit(EXIT_FAILURE);
        }
        counter++;
        sleep(1);
        signal(SIGINT, sigintHandler);
        signal(SIGQUIT, sigintHandler);
        if (fclose(fd) == EOF)
        {
            perror("fclose");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}