#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

#define STR_LENGTH 256
#define FILE_NAME_L 32


int main(int argc, char *argv[])
{
    DIR *dir;
    int fd;
    char str[STR_LENGTH];
    char newFName[FILE_NAME_L];
    int chng =0;
    if((dir = opendir("."))==NULL)
    {
        perror("Error opendir");
        exit(EXIT_FAILURE);
    }
    struct dirent *dr;
    while((dr = readdir(dir))!=NULL)
        if(strcmp(dr->d_name, argv[1])==0)
            break;
    if(dr == NULL)
    {
        printf("Файла не существует в текущем каталоге. Создать файл с этим именем?(1/0)\n");
        scanf("%d", &chng);
        switch(chng)
        {
            case 0:
                printf("Завершение программы");
                exit(EXIT_SUCCESS);
                break;
            case 1:
                if((fd = open(argv[1], O_CREAT|O_WRONLY|O_APPEND)) == -1)
                {
                    printf("Cannot open file.\n");
                    exit (EXIT_FAILURE);
                }
                printf("Файл создан\n");
                break;
            default:
                printf("Неверное значение");
                exit(EXIT_FAILURE);
        }
    }
    else
    {
        if((fd = open(argv[1], O_WRONLY|O_APPEND)) == -1)
        {
            printf("Cannot open file.\n");
            exit (EXIT_FAILURE);
        }
    }
    if(read(0, str, STR_LENGTH)==-1)
    {
        printf("Read error.\n");
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