#include "List.h"
#include<windows.h>
#include<locale.h>


void PrintMenu();

int main()
{
   setlocale(LC_ALL, "");
   List *list1 = NewList();
   List *list2 = NewList();
   List *res=NULL;
   int choice = 0;
   int n = 0;
   int num = 0;
   char exitFlag = 0;
   while (!exitFlag)
   {
      PrintMenu();
      scanf_s("%d", &choice);
      printf_s("\n\n\n");

      switch (choice)
      {
      case 1:
         list1 = NewList();
         break;
      case 2:
         list2 = NewList();
         break;
      case 3:
         printf_s("Введите количество чисел:");
         scanf_s("%d", &n);
         FillList(list1, n);
         break;
      case 4:
         printf_s("Введите количество чисел:");
         scanf_s("%d", &n);
         FillList(list2, n);
         break;
      case 5:
         printf_s("Список List_1:\n");
         PrintList(list1);
         _getch();
         break;
      case 6:
         printf_s("Список List_2:\n");
         PrintList(list2);
         _getch();
         break;
      case 7:
         printf_s("Список List_1 в обратном порядке:\n");
         PrintListReverse(list1);
         _getch();
         break;
      case 8:
         printf_s("Введите число:");
         scanf_s("%d", &num);
         ListAddToHead(list1, num);
         break;
      case 9:
         printf_s("Введите число:");
         scanf_s("%d", &num);
         ListAddToTail(list1, num);
         break;
      case 10:
         printf_s("Введите позицию и число:");
         scanf_s("%d %d", &n, &num);
         ListAdd(list1, n, num);
         break;
      case 11:
         num = ListPopHead(list1);
         printf_s("Получено число: %d", num);
         _getch();
          break;
      case 12:
         num = ListPopTail(list1);
         printf_s("Получено число: %d", num);
         _getch();
         break;
      case 13:
         printf_s("Введите позицию:");
         scanf_s("%d", &n);
         num = ListPop(list1, n);
         printf_s("Получено число: %d", num);
         _getch();
         break;
      case 14:
         num = ListGetValueHead(list1);
         printf_s("Получено число: %d", num);
         _getch();
         break;
      case 15:
         num = ListGetValueTail(list1);
         printf_s("Получено число: %d", num);
         _getch();
         break;
      case 16:
         printf_s("Введите позицию:");
         scanf_s("%d", &n);
         num = ListGetValue(list1, n);
         printf_s("Получено число: %d", num);
         _getch();
         break;
      case 17:
         printf_s("Введите число:");
         scanf_s("%d", &num);
         ListChangeValueHead(list1, num);
         break;
      case 18:
         printf_s("Введите число:");
         scanf_s("%d", &num);
         ListChangeValueTail(list1, num);
         break;
      case 19:
         printf_s("Введите позицию и число:");
         scanf_s("%d %d", &n, &num);
         ListChangeValue(list1, n, num);
         break;
      case 20:
         res = ListConcatenation(list1, list2);
         printf_s("Результат объединения:\n");
         PrintList(res);
         _getch();
         break;
      case 21:
         res = ListIntersection(list1, list2);
         printf_s("Результат пересечения:\n");
         PrintList(res);
         _getch();
         break;
      case 22:
         res = ListDifference(list1, list2);
         printf_s("Результат разности:\n");
         PrintList(res);
         _getch();
         break;
      case 23:
         DeleteList(list1);
         break;
      case 24:
         DeleteList(list2);
         break;
      case 25:
         exitFlag = 1;
         break;
      }
   }
   DeleteList(res);
   return 0;
}

void PrintMenu()
{
   system("cls");
   printf_s("1. Создать List_1\n");
   printf_s("2. Создать List_2\n");
   printf_s("3. Заполнить случайными числами List_1\n");
   printf_s("4. Заполнить случайными числами List_2\n");
   printf_s("5. Вывести List_1\n");
   printf_s("6. Вывести List_2\n");
   printf_s("7. Вывести List_1 в обратном порядке\n");
   printf_s("8. Добавить к голове List_1\n");
   printf_s("9. Добавить к хвосту List_1\n");
   printf_s("10. Добавить число в List_1\n");
   printf_s("11. Pop из головы List_1\n");
   printf_s("12. Pop из хвоста List_1\n");
   printf_s("13. Pop число из List_1\n");
   printf_s("14. Получить из головы List_1\n");
   printf_s("15. Получить из хвоста List_1\n");
   printf_s("16. Получить число из List_1\n");
   printf_s("17. Изменить значение головы List_1\n");
   printf_s("18. Изменить значение хвоста List_1\n");
   printf_s("19. Изменить число в List_1\n");
   printf_s("20. Объединение List_1 и List_2\n");
   printf_s("21. Пересечение List_1 и List_2\n");
   printf_s("22. Разность List_1 и List_2\n");
   printf_s("23. Удалить List_1\n");
   printf_s("24. Удалить List_2\n");
   printf_s("25. Выход\n");
}