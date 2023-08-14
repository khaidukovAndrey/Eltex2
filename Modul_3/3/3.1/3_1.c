#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    FILE *fd = NULL;
    int counter = 0;
    if ((fd = fopen("counter.txt", "ab+")) == NULL)
    {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    while (1)
    {
        if (fprintf(fd, "%d\n", counter) < 0)
        {
            perror("fprintf");
            exit(EXIT_FAILURE);
        }
        counter++;
        sleep(1);
    }
    if (fclose(fd) == EOF)
    {
        perror("fclose");
        exit(EXIT_FAILURE);
    }
    return 0;
}