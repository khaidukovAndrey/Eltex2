#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>


int sigintCounter =0;

void sigintHandler(int sig)
{
    printf("Получен сигнал SIGINT\n");
    sigintCounter++;
    if(sigintCounter==3)
        exit(EXIT_SUCCESS);
}

int main()
{
    signal(SIGINT, sigintHandler);
    FILE *fd = NULL;
    int counter = 0;

    while (1)
    {
        if ((fd = fopen("counter.txt", "ab+")) == NULL)
        {
            perror("fopen");
            exit(EXIT_FAILURE);
        }
        if (fprintf(fd, "%d\n", counter) < 0)
        {
            perror("fprintf");
            exit(EXIT_FAILURE);
        }
        counter++;
        sleep(1);
        if (fclose(fd) == EOF)
        {
            perror("fclose");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}