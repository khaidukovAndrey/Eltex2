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
    if((fd = fopen(argv[1], "r")) == NULL)
    {
        printf("Cannot open file.\n");
        exit (EXIT_FAILURE);
    }
    if(fread(str, sizeof(char), STR_LENGTH,fd)==-1)
    {
        printf("Read error.\n");
        exit (EXIT_FAILURE);
    }
    if(fwrite(str, sizeof(char), strlen(str), stdout)==-1)
    {
        printf("Write error.\n");
        exit (EXIT_FAILURE);
    }
    if (fclose(fd)==EOF)
    {
        printf("Close error.\n");
        exit (EXIT_FAILURE);
    }
    exit (EXIT_SUCCESS);
}