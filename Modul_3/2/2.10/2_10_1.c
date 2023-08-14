#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <fcntl.h>


int main() {
    int fifo, buf;

    if ((fifo = open("/tmp/my_fifo", O_RDONLY)) == -1) 
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    while (read(fifo, &buf, sizeof(buf)) > 0) 
    {
        printf("Прочитано число: %d\n", buf);
    }

    close(fifo);

    exit(EXIT_SUCCESS);
}