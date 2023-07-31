#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

char pathFile[256];
DIR *dir;
struct dirent *dr;

char *InParent()
{
    char *temp = &pathFile[strlen(pathFile)-1];
    while (*temp != '/')
        {
            *temp = '\0';
            temp--;
        }
    if (strcmp(pathFile, "/") != 0)
    {
        *temp='\0';
    }
    return pathFile;
}

char *InChild(char *fileName)
{
    if (strcmp(pathFile, "/") != 0)
        strcat(pathFile, "/");
    strcat(pathFile, fileName);
    return pathFile;
}

void PrintContent()
{
    struct stat st;
    char pathContent[256];
    while ((dr = readdir(dir)) != NULL)
    {

        strcpy(pathContent, pathFile);
        strcat(pathContent, "/");
        strcat(pathContent, dr->d_name);
        strcat(pathContent, "\0");
        if (stat(pathContent, &st) == -1)
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

int main()
{
    char exitFlag = 1;
    char fileName[32];
    char *child;
    char *parent;

    // strcpy(pathFile,"/");
    if ((dir = opendir("/")) == NULL)
    {
        perror("Error opendir");
        exit(EXIT_FAILURE);
    }
    PrintContent();
    if (closedir(dir) == -1)
    {
        perror("Error closedir");
        exit(EXIT_FAILURE);
    }
    while (exitFlag)
    {
        scanf("%s", fileName);
        if (strcmp(fileName, "exit") == 0)
        {
            exitFlag = 0;
        }
        else if (strcmp(fileName, "..") == 0 && strcmp(pathFile, "/") != 0)
        {
            parent = InParent();
            if ((dir = opendir(parent)) == NULL)
            {
                perror("Error opendir");
                exit(EXIT_FAILURE);
            }
            PrintContent();
            if (closedir(dir) == -1)
            {
                perror("Error closedir");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            child = InChild(fileName);
            struct stat st;
            if (stat(child, &st) == -1)
            {
                perror("Error stat");
                exit(EXIT_FAILURE);
            }
            if (S_ISDIR(st.st_mode))
            {
                if ((dir = opendir(child)) == NULL)
                {
                    perror("Error opendir");
                    exit(EXIT_FAILURE);
                }
                PrintContent();
                if (closedir(dir) == -1)
                {
                    perror("Error closedir");
                    exit(EXIT_FAILURE);
                }
            }
            else
                printf("Данный файл не является дирректорией\n");
        }
    }
    exit(EXIT_SUCCESS);
}