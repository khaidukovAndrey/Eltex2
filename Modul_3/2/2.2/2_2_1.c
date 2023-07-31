#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define STR_LENGTH 32

int main(int argc, char *argv[])
{
    FILE *fd;
    char str[STR_LENGTH];
    if(fread(str, sizeof(char), STR_LENGTH, stdin)==-1)
    {
        printf("Read error.\n");
        exit (EXIT_FAILURE);
    }
    if((fd = fopen(argv[1], "wa")) == NULL)
    {
        printf("Cannot open file.\n");
        exit (EXIT_FAILURE);
    }
    if(fwrite(str, sizeof(char), strlen(str), fd)==-1)
    {
        printf("Write error.\n");
        exit (EXIT_FAILURE);
    }
    chmod(argv[1], 00700);
    if (fclose(fd)==EOF)
    {
        printf("Close error.\n");
        exit (EXIT_FAILURE);
    }
    exit (EXIT_SUCCESS);
}