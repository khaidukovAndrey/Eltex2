#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv[])
{
    pid_t pid;
    switch(pid = fork())
    {
        case -1:
            perror("fork");
            exit(EXIT_FAILURE);
            break;
        case 0:
            if((argc-1)/2 ==0)
                exit(EXIT_SUCCESS);
            for(int i=(int)((argc-1)/2); i<argc;i++)
                printf("%d\n", atoi(argv[i])*atoi(argv[i]));
            break;
        default:
            for(int i=1; i<(int)((argc-1)/2);i++)
                printf("%d\n", atoi(argv[i])*atoi(argv[i]));
            wait(0);
            break;
    } 
    exit(EXIT_SUCCESS);
}