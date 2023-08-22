#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern int my_div(int a, int b);
extern int my_mod(int a, int b);

int main()
{
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
        result = my_div(divisible, divider);
        printf("Ответ: %d", result);
        break;
    case 2:
        result = my_mod(divisible, divider);
        printf("Ответ: %d", result);
        break;
    default:
        printf("Неверный ввод");
    }

    return 0;
}