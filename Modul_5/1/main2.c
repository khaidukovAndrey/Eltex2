#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dlfcn.h>

void *library_handler;

int main()
{
    library_handler = dlopen("./libdiv_dyn.so", RTLD_LAZY);
    if (!library_handler)
    {
        fprintf(stderr, "dlopen() error: %s\n", dlerror());
        exit(EXIT_FAILURE);
    };
    int (*func)(int a, int b);
    int choice = 0;
    int divider = 0;
    int divisible = 0;
    int result = 0;
    
    printf("1)Целочисленное деление\n");
    printf("2)Деление по модулю\n");
    printf("Введите операцию и числа:\n");
    scanf("%d", &choice);
    scanf("%d", &divisible);
    scanf("%d", &divider);
    if (divider == 0)
        exit(EXIT_FAILURE);
    switch (choice)
    {
    case 1:
        func = dlsym(library_handler, "my_div");
        result = (*func)(divisible, divider);
        printf("Ответ: %d", result);
        break;
    case 2:
        func = dlsym(library_handler, "my_mod");
        result = (*func)(divisible, divider);
        printf("Ответ: %d", result);
        break;
    default:
        printf("Неверный ввод");
    }
    dlclose(library_handler);
    return 0;
}