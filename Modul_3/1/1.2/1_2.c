#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void ExitFunc()
{
    printf("Программа завершилась\n");
    return 0;
}

int main(int argc, char **argv[])
{
    pid_t pid;
    char str[80];
    switch(pid = fork())
    {
        case -1:
            perror("fork");
            exit(EXIT_FAILURE);
            break;
        case 0:
            strcpy(str, "Аргумент дочернего процесса: ");
            for(int i=1; i<argc;i++)
                printf("%s %s\n", str, argv[i]);
            break;
        default:
            strcpy(str, "Аргумент родительского процесса: ");
            for(int i=1; i<argc;i++)
                printf("%s %s\n", str, argv[i]);
            wait(0);
            break;
    } 
    atexit(ExitFunc);
}
