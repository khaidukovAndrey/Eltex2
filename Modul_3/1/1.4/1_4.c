#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>


int main(int argc, char **argv[])
{
    pid_t pid;
    char str[256];
    int k = 0;
    int l = 0;
    int args = 0;
    char **prog;
    printf("Введите название программы и ее аргументы\n");
    if(!fgets(str, 254, stdin))
        exit(EXIT_FAILURE);
    while(str[k] != '\0')
    {
        if(str[k] == ' ')
            args+=1;
        k++;
    }
    k = 0;
    prog = (char**)malloc((args+2)*sizeof(char*));
    for(int i =0;i<args+1;i++)
    {
        prog[i] = (char*)malloc((50)*sizeof(char));
        l=0;
        while(str[k] != ' ' && str[k] != '\0')
        {
            prog[i][l] = str[k];
            k++;
            l++;
        }
        prog[i][l] = '\0';
        k++;
    }
    prog[args+1] =NULL;

    switch(pid = fork())
    {
        case -1:
            perror("fork");
            exit(EXIT_FAILURE);
            break;
        case 0:
            execv(prog[0],prog);
            perror("Ошибка EXEC");
            break;
        default:
            wait(0);
            break;
    }
    exit(EXIT_SUCCESS);
}