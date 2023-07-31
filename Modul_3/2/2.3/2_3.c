#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


int main(int argc, char *argv[])
{
    DIR *dir;
    if(argc!=2)
    {
        perror("Invalid number of arguments");
        exit(EXIT_FAILURE);
    }
    if((dir = opendir(argv[1]))==NULL)
    {
        perror("Error opendir");
        exit(EXIT_FAILURE);
    }
    struct dirent *dr;
    while((dr = readdir(dir))!=NULL)
    {
        printf("%s\n", dr->d_name);
    }
    if(closedir(dir)==-1);
    {
        perror("Error closedir");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}