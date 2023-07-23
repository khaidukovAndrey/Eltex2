#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    if(argc != 3)
        {
            printf("Неверное кол-во аргументов");
            exit(EXIT_FAILURE);
        }
    printf("%d\n", atoi(argv[1])+atoi(argv[2]));
    exit(EXIT_SUCCESS);
}