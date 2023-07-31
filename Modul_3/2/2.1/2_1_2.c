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
    if((fd = open(argv[1], O_RDONLY)) == -1)
    {
        printf("Cannot open file.\n");
        exit (EXIT_FAILURE);
    }
    if(read(fd, str, STR_LENGTH)==-1)
    {
        printf("Read error.\n");
        exit (EXIT_FAILURE);
    }
    if(write(1, str, strlen(str))==-1)
    {
        printf("Write error.\n");
        exit (EXIT_FAILURE);
    }
    if (close(fd))
    {
        printf("Close error.\n");
        exit (EXIT_FAILURE);
    }
    exit (EXIT_SUCCESS);
}