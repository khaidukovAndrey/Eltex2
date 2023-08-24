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
         printf_s("������� ���������� �����:");
         scanf_s("%d", &n);
         FillList(list1, n);
         break;
      case 4:
         printf_s("������� ���������� �����:");
         scanf_s("%d", &n);
         FillList(list2, n);
         break;
      case 5:
         printf_s("������ List_1:\n");
         PrintList(list1);
         _getch();
         break;
      case 6:
         printf_s("������ List_2:\n");
         PrintList(list2);
         _getch();
         break;
      case 7:
         printf_s("������ List_1 � �������� �������:\n");
         PrintListReverse(list1);
         _getch();
         break;
      case 8:
         printf_s("������� �����:");
         scanf_s("%d", &num);
         ListAddToHead(list1, num);
         break;
      case 9:
         printf_s("������� �����:");
         scanf_s("%d", &num);
         ListAddToTail(list1, num);
         break;
      case 10:
         printf_s("������� ������� � �����:");
         scanf_s("%d %d", &n, &num);
         ListAdd(list1, n, num);
         break;
      case 11:
         num = ListPopHead(list1);
         printf_s("�������� �����: %d", num);
         _getch();
          break;
      case 12:
         num = ListPopTail(list1);
         printf_s("�������� �����: %d", num);
         _getch();
         break;
      case 13:
         printf_s("������� �������:");
         scanf_s("%d", &n);
         num = ListPop(list1, n);
         printf_s("�������� �����: %d", num);
         _getch();
         break;
      case 14:
         num = ListGetValueHead(list1);
         printf_s("�������� �����: %d", num);
         _getch();
         break;
      case 15:
         num = ListGetValueTail(list1);
         printf_s("�������� �����: %d", num);
         _getch();
         break;
      case 16:
         printf_s("������� �������:");
         scanf_s("%d", &n);
         num = ListGetValue(list1, n);
         printf_s("�������� �����: %d", num);
         _getch();
         break;
      case 17:
         printf_s("������� �����:");
         scanf_s("%d", &num);
         ListChangeValueHead(list1, num);
         break;
      case 18:
         printf_s("������� �����:");
         scanf_s("%d", &num);
         ListChangeValueTail(list1, num);
         break;
      case 19:
         printf_s("������� ������� � �����:");
         scanf_s("%d %d", &n, &num);
         ListChangeValue(list1, n, num);
         break;
      case 20:
         res = ListConcatenation(list1, list2);
         printf_s("��������� �����������:\n");
         PrintList(res);
         _getch();
         break;
      case 21:
         res = ListIntersection(list1, list2);
         printf_s("��������� �����������:\n");
         PrintList(res);
         _getch();
         break;
      case 22:
         res = ListDifference(list1, list2);
         printf_s("��������� ��������:\n");
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
   printf_s("1. ������� List_1\n");
   printf_s("2. ������� List_2\n");
   printf_s("3. ��������� ���������� ������� List_1\n");
   printf_s("4. ��������� ���������� ������� List_2\n");
   printf_s("5. ������� List_1\n");
   printf_s("6. ������� List_2\n");
   printf_s("7. ������� List_1 � �������� �������\n");
   printf_s("8. �������� � ������ List_1\n");
   printf_s("9. �������� � ������ List_1\n");
   printf_s("10. �������� ����� � List_1\n");
   printf_s("11. Pop �� ������ List_1\n");
   printf_s("12. Pop �� ������ List_1\n");
   printf_s("13. Pop ����� �� List_1\n");
   printf_s("14. �������� �� ������ List_1\n");
   printf_s("15. �������� �� ������ List_1\n");
   printf_s("16. �������� ����� �� List_1\n");
   printf_s("17. �������� �������� ������ List_1\n");
   printf_s("18. �������� �������� ������ List_1\n");
   printf_s("19. �������� ����� � List_1\n");
   printf_s("20. ����������� List_1 � List_2\n");
   printf_s("21. ����������� List_1 � List_2\n");
   printf_s("22. �������� List_1 � List_2\n");
   printf_s("23. ������� List_1\n");
   printf_s("24. ������� List_2\n");
   printf_s("25. �����\n");
}