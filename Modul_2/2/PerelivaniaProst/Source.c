#include <stdlib.h>
#include <stdio.h>
#include <locale.h>

struct Buckets
{
   unsigned firstCap, secondCap, thirdCap;
   unsigned first, second, third;
};
typedef struct CombList
{
   struct CombList *next;
   unsigned first, second, third;
}CombList;

CombList *ptr;


void PrintCombination(struct Buckets *b);
char CheckGoal(struct Buckets *b, unsigned goal);
void PourWater(char in, char out, struct Buckets *b);
void InitBuckets(struct Buckets *b);
void SortBuckets(struct Buckets *b);
void AddNode(struct CombList *c, unsigned f, unsigned s, unsigned t);
void CheckLoop(unsigned f, unsigned s, unsigned t);



int main()
{
   setlocale(LC_ALL, "");
   struct Buckets b;
   CombList *comblist = malloc(sizeof(CombList));
   unsigned goal;
   char ExitFlag = 1;
   char FinishFlag = 1;
   int count = 0;
   printf_s("Введите ёмкости вёдер: ");
   InitBuckets(&b);
   
   comblist->first = b.first;
   comblist->second = b.second;
   comblist->third = b.third;
   comblist->next = NULL;
   ptr = comblist;
   printf_s("Введите цель: ");
   if (!scanf_s("%u", &goal))
      exit(EXIT_FAILURE);
   if (CheckGoal(&b, goal))
      exit(EXIT_SUCCESS);
   PrintCombination(&b);
   while (FinishFlag)
   {
      ExitFlag = 1;
      PourWater(2, 1, &b);
      count++;
      CheckLoop(b.first, b.second, b.third);
      AddNode(comblist, b.first, b.second, b.third);
      PrintCombination(&b);
      if (CheckGoal(&b, goal))
         FinishFlag = 0;
      while (ExitFlag && FinishFlag)
      {
         PourWater(3, 2, &b);
         count++;
         CheckLoop(b.first, b.second, b.third);
         AddNode(comblist, b.first, b.second, b.third);
         PrintCombination(&b);
         if (b.second == 0)
            break;
         if (CheckGoal(&b, goal))
         {
            FinishFlag = 0;
            break;
         }
         PourWater(1, 3, &b);
         count++;
         CheckLoop(b.first, b.second, b.third);
         AddNode(comblist, b.first, b.second, b.third);
         PrintCombination(&b);
         if (CheckGoal(&b, goal))
         {
            FinishFlag = 0;
            break;
         }
      }
      
   }
   printf("\n%d\n", count);
   return 0;
}

void AddNode(struct CombList *c, unsigned f, unsigned s, unsigned t)
{
   CombList *temp = c;
   while (temp->next != NULL)
   {
      temp = temp->next;
   }
   temp->next = malloc(sizeof(CombList));
   temp = temp->next;
   temp->first = f;
   temp->second = s;
   temp->third = t;
   temp->next = NULL;
}

void CheckLoop(unsigned f, unsigned s, unsigned t)
{
   CombList *temp = ptr;
   while (temp->next != NULL)
   {
      if (temp->first == f && temp->second == s && temp->third == t)
      {
         printf_s("Обнаружено зацикливание. Решение не найдено.");
         exit(EXIT_FAILURE);
      }
      temp = temp->next;
   }
   if (temp->first == f && temp->second == s && temp->third == t)
   {
      printf_s("Обнаружено зацикливание. Решение не найдено.");
      exit(EXIT_FAILURE);
   }
   
}

char CheckGoal(struct Buckets *b, unsigned goal)
{
   if ((*b).first == goal || (*b).second == goal || (*b).third == goal)
   {
      printf("Результат: ");
      printf_s("%u %u %u\n", (*b).first, (*b).second, (*b).third);
      return 1;
   }
   return 0;
}

void PourWater(char in, char out, struct Buckets *b)
{
   unsigned tIn = 0;
   unsigned tOut = 0;
   unsigned tInCap = 0;
   unsigned tOutCap = 0;
   switch (in) {
   case 1:
      tIn = b->first;
      tInCap = b->firstCap;
      break;
   case 2:
      tIn = b->second;
      tInCap = b->secondCap;
      break;
   case 3:
      tIn = b->third;
      tInCap = b->thirdCap;
      break;
   }
   switch (out) {
   case 1:
      tOut = b->first;
      tOutCap = b->firstCap;
      break;
   case 2:
      tOut = b->second;
      tOutCap = b->secondCap;
      break;
   case 3:
      tOut = b->third;
      tOutCap = b->thirdCap;
      break;
   }

   if (tOut >= tInCap - tIn)
   {
      tOut -= tInCap - tIn;
      tIn = tInCap;
   }
   else
   {
      tIn += tOut;
      tOut = 0;
   }

   switch (in) {
   case 1:
      b->first = tIn;
      break;
   case 2:
      b->second = tIn;
      break;
   case 3:
      b->third = tIn;
      break;
   }
   switch (out) {
   case 1:
      b->first = tOut;
      break;
   case 2:
      b->second = tOut;
      break;
   case 3:
      b->third = tOut;
      break;
   }

}

void PrintCombination(struct Buckets *b)
{
   printf_s("%u %u %u\n", (*b).first, (*b).second, (*b).third);
}

void InitBuckets(struct Buckets *b)
{
   if (!scanf_s("%u %u %u", &(*b).firstCap, &(*b).secondCap, &(*b).thirdCap))
      exit(EXIT_FAILURE);
   SortBuckets(&(*b));
   (*b).first = (*b).firstCap;
   (*b).second = 0;
   (*b).third = 0;
}

void SortBuckets(struct Buckets *b)
{
   unsigned temp;
   if ((*b).firstCap < (*b).secondCap)
   {
      temp = (*b).firstCap;
      (*b).firstCap = (*b).secondCap;
      (*b).secondCap = temp;
   }
   if ((*b).secondCap < (*b).thirdCap)
   {
      temp = (*b).secondCap;
      (*b).secondCap = (*b).thirdCap;
      (*b).thirdCap = temp;
   }
   if ((*b).firstCap < (*b).secondCap)
   {
      temp = (*b).firstCap;
      (*b).firstCap = (*b).secondCap;
      (*b).secondCap = temp;
   }
}