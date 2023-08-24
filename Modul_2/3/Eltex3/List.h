#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <conio.h>



typedef struct Node
{
   int value;
   struct Node *next;
   struct Node *prev;
}Node;

typedef struct List
{
   struct Node *head;
   struct Node *tail;
   int numOfElems;
}List;

void ListAddToHead(List *list, int value);//
void ListAddToTail(List *list, int value);//
void ListAdd(List *list, int n, int value);//
Node *SearchFromHead(List *list, int n);//
Node *SearchFromTail(List *list, int n);//
int ListPopHead(List *list);//
int ListPopTail(List *list);//
int ListPop(List *list, int n);//
int ListGetValueHead(List *list);//
int ListGetValueTail(List *list);//
int ListGetValue(List *list, int n);//
void ListChangeValueHead(List *list, int newValue);//
void ListChangeValueTail(List *list, int newValue);//
void ListChangeValue(List *list, int n, int newValue);//
void PrintList(List *list);//
void PrintListReverse(List *list);//
void FillList(List *list, int num);//
void DeleteList(List *list);//
List *NewList();//
Node *SearchByValue(List *list, int value);
List *ListConcatenation(List *list1, List *list2);
List *ListIntersection(List *list1, List *list2);
List *ListDifference(List *list1, List *list2);


void ListAddToHead(List *list, int value)
{
   Node *newNode = (Node *)malloc(sizeof(Node));
   newNode->next = NULL;
   newNode->prev = NULL;
   if ((list)->head != NULL)
   {
      newNode->next = (list)->head;
      (list)->head->prev = newNode;
   }
   else
   {
      newNode->next = NULL;
      newNode->prev = NULL;
      (list)->tail = newNode;
   }
   newNode->value = value;
   (list)->head = newNode;
   (list)->numOfElems++;
}

void ListAddToTail(List *list, int value)
{
   Node *newNode = (Node *)malloc(sizeof(Node));
   newNode->next = NULL;
   newNode->prev = NULL;
   if ((list)->tail != NULL)
   {
      newNode->prev = (list)->tail;
      (list)->tail->next = newNode;
   }
   else
   {
      newNode->next = NULL;
      newNode->prev = NULL;
      (list)->head = newNode;
   }
   newNode->value = value;
   (list)->tail = newNode;
   (list)->numOfElems++;
}

void ListAdd(List *list, int n, int value)
{
   if (n > (list)->numOfElems)
      return;
   if (n > 0 && n < (list)->numOfElems)
   {
      Node *tmp = NULL;
      if (n <= (list)->numOfElems / 2)
         tmp = SearchFromHead(list, n-1);
      if (n > (list)->numOfElems / 2)
         tmp = SearchFromTail(list, n-1);
      Node *newNode = (Node *)malloc(sizeof(Node));
      newNode->next = NULL;
      newNode->prev = NULL;
      newNode->value = value;
      tmp->next->prev = newNode;
      newNode->next = tmp->next;
      tmp->next = newNode;
      newNode->prev = tmp;
      (list)->numOfElems++;
   }
   if (n == 0)
      ListAddToHead(list, value);
   if (n == (list)->numOfElems)
      ListAddToTail(list, value);
}

Node *SearchFromHead(List *list, int n)
{
   Node *tmp = NULL;
   tmp = (list)->head;
   int counter = 0;
   while (counter < n)
   {
      tmp = tmp->next;
      counter++;
   }
   return tmp;
}

Node *SearchFromTail(List *list, int n)
{
   Node *tmp = NULL;
   tmp = (list)->tail;
   int counter = (list)->numOfElems;
   while (counter > n+1)
   {
      tmp = tmp->prev;
      counter--;
   }
   return tmp;
}

int ListPopHead(List *list)
{
   Node *tmp = NULL;
   int res = 0;
   res = (list)->head->value;
   tmp = (list)->head->next;
   tmp->prev = NULL;
   free((list)->head);
   (list)->head = tmp;
   (list)->numOfElems--;
   return(res);
}

int ListPopTail(List *list)
{
   Node *tmp = NULL;
   int res = 0;
   res = (list)->tail->value;
   tmp = (list)->tail->prev;
   tmp->next = NULL;
   free((list)->tail);
   (list)->tail = tmp;
   (list)->numOfElems--;
   return(res);
}

int ListPop(List *list, int n)
{
   int res = 0;
   if (n > 0 && n < (list)->numOfElems - 1)
   {
      Node *tmp = NULL;
      if (n <= (list)->numOfElems / 2)
         tmp = SearchFromHead(list, n);
      if (n > (list)->numOfElems / 2)
         tmp = SearchFromTail(list, n);
      res = tmp->value;
      tmp->prev->next = tmp->next;
      tmp->next->prev = tmp->prev;
      free(tmp);
      (list)->numOfElems--;
   }
   if (n == 0)
      res = ListPopHead(list);
   if (n == (list)->numOfElems - 1)
      res = ListPopTail(list);
   return res;
}

int ListGetValueHead(List *list)
{
   return (list)->head->value;
}

int ListGetValueTail(List *list)
{
   return (list)->tail->value;
}

int ListGetValue(List *list, int n)
{
   int res = 0;
   if (n > (list)->numOfElems - 1)
      return;
   if (n > 0 && n < (list)->numOfElems-1)
   {
      Node *tmp = NULL;
      if (n <= (list)->numOfElems / 2)
         tmp = SearchFromHead(list, n);
      if (n > (list)->numOfElems / 2)
         tmp = SearchFromTail(list, n);
      res = tmp->value;
   }
   if (n == 0)
      res = ListGetValueHead(list);
   if (n == (list)->numOfElems-1)
      res = ListGetValueTail(list);
   return res;
}

void ListChangeValueHead(List *list, int newValue)
{
   (list)->head->value = newValue;
}

void ListChangeValueTail(List *list, int newValue)
{
   (list)->tail->value = newValue;
}

void ListChangeValue(List *list, int n, int newValue)
{
   if (n > 0 && n < (list)->numOfElems-1)
   {
      Node *tmp = NULL;
      if (n <= (list)->numOfElems / 2)
         tmp = SearchFromHead(list, n);
      if (n > (list)->numOfElems / 2)
         tmp = SearchFromTail(list, n);
      tmp->value = newValue;
   }
   if (n == 0)
      ListChangeValueHead(list, newValue);
   if (n == (list)->numOfElems-1)
      ListChangeValueTail(list, newValue);
}

void PrintList(List *list)
{
   int counter = 0;
   Node *tmp = NULL;
   tmp = (list)->head;
   while (counter < (list)->numOfElems && tmp != NULL)
   {
      printf_s("%d\n", tmp->value);
      if (tmp->next != NULL)
         tmp = tmp->next;
      counter++;
   }
}

void PrintListReverse(List *list)
{
   int counter = 0;
   Node *tmp = NULL;
   tmp = (list)->tail;
   while (counter < (list)->numOfElems && tmp != NULL)
   {
      printf_s("%d\n", tmp->value);
      if (tmp->prev != NULL)
         tmp = tmp->prev;
      counter++;
   }
}

void FillList(List *list, int num)
{
   Node *tmp = NULL;
   srand(time(NULL));
   int counter = 0;
   int randVal = 0;
   if (list->head == NULL)
      ListAddToTail(list, randVal);
   tmp = list->head;
   randVal = rand() % 101;
   tmp->value = randVal;
   counter = 1;
   while (counter < num)
   {
      randVal = rand() % 101;
      if (tmp->next != NULL)
      {
         tmp = tmp->next;
         tmp->value = randVal;
      }
      else
      {
         ListAddToTail(list, randVal);
         tmp = tmp->next;
      }
      counter++;
   }
}

void DeleteList(List *list)
{
   Node *tmp = NULL;
   while ((list)->head->next)
   {
      tmp = (list)->head;
      (list)->head = (list)->head->next;
      free(tmp);
   }
   //free((list)->head);
   free((list));
}

List *NewList()
{
   List *list = (List *)malloc(sizeof(List));
   list->head = NULL;
   list->tail = NULL;
   list->numOfElems = 0;
   return list;
}

Node *SearchByValue(List *list, int value)
{
   Node *tmp1 = NULL;
   Node *tmp2 = NULL;
   tmp1 = list->head;
   tmp2 = list->tail;
   if (tmp1 == NULL && tmp2 == NULL)
      return NULL;
   while (tmp1 != tmp2 && tmp1->next != tmp2)
   {
      if (tmp1->value == value)
         return tmp1;
      if (tmp2->value == value)
         return tmp2;
      tmp1 = tmp1->next;
      tmp2 = tmp2->prev;
   }
   if (tmp1->value == value)
      return tmp1;
   if (tmp2->value == value)
      return tmp2;
   return NULL;
}

List *ListConcatenation(List *list1, List *list2)
{
   if (list2->numOfElems > list1->numOfElems)
   {
      List *tmpList = list1;
      list1 = list2;
      list2 = tmpList;
      free(tmpList);
   }
   List *result = NewList();
   int value = 0;
   Node *tmp = NULL;
   tmp = list1->head;
   while (tmp != NULL)
   {
      if (SearchByValue(result, tmp->value) == NULL)
         ListAddToTail(result, tmp->value);
      tmp = tmp->next;
   }
   tmp = list2->head;
   while (tmp != NULL)
   {
      if (SearchByValue(result, tmp->value) == NULL)
         ListAddToTail(result, tmp->value);
      tmp = tmp->next;
   }
   return result;
}

List *ListIntersection(List *list1, List *list2)
{
   if (list2->numOfElems > list1->numOfElems)
   {
      List *tmpList = list1;
      list1 = list2;
      list2 = tmpList;
   }
   List *result = NewList();
   int value = 0;
   Node *tmp = NULL;
   tmp = list1->head;
   while (tmp != NULL)
   {
      if (SearchByValue(result, tmp->value) == NULL && SearchByValue(list2, tmp->value) != NULL)
         ListAddToTail(result, tmp->value);
      tmp = tmp->next;
   }
   return result;
}

List *ListDifference(List *list1, List *list2)
{
   List *result = NewList();
   int value = 0;
   Node *tmp = NULL;
   tmp = list1->head;
   while (tmp != NULL)
   {
      if (SearchByValue(list2, tmp->value) == NULL)
         ListAddToTail(result, tmp->value);
      tmp = tmp->next;
   }
   return result;
}