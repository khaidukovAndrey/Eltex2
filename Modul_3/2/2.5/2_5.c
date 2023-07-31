#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    char pathFile[256];

    DIR *dir;
    if (argc != 2)
    {
        perror("Invalid number of arguments");
        exit(EXIT_FAILURE);
    }
    if ((dir = opendir(argv[1])) == NULL)
    {
        perror("Error opendir");
        exit(EXIT_FAILURE);
    }
    struct dirent *dr;
    struct stat st;

    while ((dr = readdir(dir)) != NULL)
    {
        while ((dr = readdir(dir)) != NULL)
        {
            strcpy(pathFile, argv[1]);
            strcat(pathFile, "/");
            strcat(pathFile, dr->d_name);
            strcat(pathFile, "\0");
            if (stat(pathFile, &st) == -1)
            {
                perror("Error stat");
                exit(EXIT_FAILURE);
            }
            if (S_ISLNK(st.st_mode))
                printf("Cим. ссылка ");
            if (S_ISREG(st.st_mode))
                printf("Файл        ");
            if (S_ISDIR(st.st_mode))
                printf("Каталог     ");
            if (S_ISCHR(st.st_mode))
                printf("Cим. устр.  ");
            if (S_ISBLK(st.st_mode))
                printf("Блочн. устр ");
            if (S_ISFIFO(st.st_mode))
                printf("Канал FIFO  ");
            if (S_ISSOCK(st.st_mode))
                printf("Cокет       ");
            printf("%s\n", dr->d_name);
        }
    }
    if (closedir(dir) == -1)
    {
        perror("Error closedir");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}