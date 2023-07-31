#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

struct Command
{
    int argc;
    char **signat;
} *commands;

int main()
{
    pid_t pid;
    char str[512];
    char **substr;
    int k = 0;
    int l = 0;
    int commandsCount = 1;
    printf("Введите название программы и ее аргументы\n");
    if (!fgets(str, 510, stdin))
        exit(EXIT_FAILURE);
    while (str[k] != '\0')
    {
        if (str[k] == '|')
            commandsCount++;
        k++;
    }
    k = 0;
    commands = (struct Command *)malloc(commandsCount * sizeof(struct Command));
    substr = (char **)malloc(commandsCount * sizeof(char *));

    for (int i = 0; i < commandsCount; i++)
    {
        l = 0;
        substr[i] = (char *)malloc(128 * sizeof(char));
        while (str[k] != '|' && str[k] != '\0')
        {
            substr[i][l] = str[k];
            if (str[k] == ' ')
                commands[i].argc += 1;
            k++;
            l++;
        }
        if (str[k] != '\0')
            k++;
    }
    k = 0;
    l=0;
    for (int i = 0; i < commandsCount; i++)
    {
        prog[i] = (char *)malloc((50) * sizeof(char));
        l = 0;
        if (i == 0)
        {
            strcpy(prog[i], "/bin/");
            l = 5;
        }
        while (str[k] != ' ' && str[k] != '\0')
        {
            prog[i][l] = str[k];
            k++;
            l++;
        }
        if (prog[i][l - 1] == '\n')
            l -= 1;
        prog[i][l] = '\0';
        k++;
    }
    prog[args + 1] = NULL;

    switch (pid = fork())
    {
    case -1:
        perror("fork");
        exit(EXIT_FAILURE);
        break;
    case 0:
        execvp(prog[0], prog);
        perror("Ошибка EXEC");
        break;
    default:
        wait(0);
        break;
    }
    exit(EXIT_SUCCESS);
}