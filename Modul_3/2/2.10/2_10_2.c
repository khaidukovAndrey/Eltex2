#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <fcntl.h>


int main()
{
    int fifo;
    srand(time(NULL));
    int num;

    if ((fifo = open("/tmp/my_fifo", O_APPEND | O_WRONLY)) == -1)
    {
        perror("Error open");
        exit(EXIT_FAILURE);
    }
    for (size_t i = 0; i < 10; i++)
    {
        num = rand() % 100;

        write(fifo, &num, sizeof(num));
        printf("Сгенерировано число: %d\n", num);
    }
    close(fifo);

    exit(EXIT_SUCCESS);
}