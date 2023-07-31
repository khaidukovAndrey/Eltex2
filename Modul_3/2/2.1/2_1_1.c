#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define STR_LENGTH 256

int main(int argc, char *argv[])
{
    int fd;
    char str[STR_LENGTH];
    if(read(0, str, STR_LENGTH)==-1)
    {
        printf("Read error.\n");
        exit (EXIT_FAILURE);
    }
    if((fd = open(argv[1], O_WRONLY|O_CREAT|O_APPEND)) == -1)
    {
        printf("Cannot open file.\n");
        exit (EXIT_FAILURE);
    }
    if(write(fd, str, strlen(str))==-1)
    {
        printf("Write error.\n");
        exit (EXIT_FAILURE);
    }
    chmod(argv[1], 00700);
    if (close(fd))
    {
        printf("Close error.\n");
        exit (EXIT_FAILURE);
    }
    exit (EXIT_SUCCESS);
}