#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <conio.h>
#include "Trader.h"

#define PLAYER_LEVEL 15
#define MAX_PLAYER_LEVEL 20

struct Enemy
{
   int id;
   float hp;
   float damage;
} *enemyList;



struct CurrentLocation
{
   int id;
   struct Enemy *enemies;
   char enemyAmount;
   char resourceAmount;
   float chestChance;
   float resorceChance;
   unsigned *itemsInChest;
   unsigned *resources;
}*curLoc;

struct Location
{
   int id;
   int enemyID; //kind of enemy
   int resources;
   int chest;
}*locationsList;

struct EnemyDistrib
{
   char levelOfPlayer;
   float chanceWeakEnemy;
   float chanceMediumEnemy;
   float chanceStrongEnemy;
}*enemyDistrib;

char countAllLocations = 0;

void ReadLocations();
void ReadEnemyLevelDistribution();
int GenerateLocation();
void Trader();
void ReadLocations()
{
   FILE *locs;
   fopen_s(&locs, "locations.txt", "r");
   fscanf_s(locs, "%d", &countAllLocations);
   locationsList = malloc(sizeof(struct Location) * countAllLocations);

   for (int i = 0; i < countAllLocations; i++)
   {
      fscanf_s(locs, "%d ", &locationsList[i].id);
      fscanf_s(locs, "%d ", &locationsList[i].enemyID);
      fscanf_s(locs, "%d ", &locationsList[i].resources);
      fscanf_s(locs, "%d", &locationsList[i].chest);
   }
}

void ReadEnemyLevelDistribution()
{
   enemyDistrib = malloc(sizeof(struct EnemyDistrib) * MAX_PLAYER_LEVEL);
   FILE *locs;
   fopen_s(&locs, "enemyLevels.txt", "r");
   for (int i = 0; i < MAX_PLAYER_LEVEL; i++)
   {
      fscanf_s(locs, "%c", &enemyDistrib[i].levelOfPlayer, (int)sizeof(char));
      fscanf_s(locs, "%f", &enemyDistrib[i].chanceWeakEnemy);
      fscanf_s(locs, "%f", &enemyDistrib[i].chanceMediumEnemy);
      fscanf_s(locs, "%f", &enemyDistrib[i].chanceStrongEnemy);
   }
}


int GenerateLocation()
{
   FILE *e = NULL;
   srand(time(NULL));
   free(curLoc); // Тут должна быть очистка если структура была заполнена
   curLoc = malloc(sizeof(struct CurrentLocation));
   curLoc->id = rand() % countAllLocations;
   float enemyKind = (float)(rand() % 100) / 100;
   float countOfEnemy = (float)(rand() % 100) / 100;
   float countOfItems = (float)(rand() % 100) / 100;
   float countOfResources = (float)(rand() % 100) / 100;
   int generatedEnemy = 0;
   int itemListSize = 0;



   switch (locationsList[curLoc->id].enemyID)
   {
   case 0:
      fopen_s(&e, "predators.txt", "r");
      break;
   case 1:
      fopen_s(&e, "robbers.txt", "r");
      break;
   case 2:
      fopen_s(&e, "magicians.txt", "r");
      break;
   case 3:
      fopen_s(&e, "deadman.txt", "r");
      break;
   default:
      break;
   }
   int numOfEnemyKinds = 0;
   fscanf_s(e, "%d", &numOfEnemyKinds);
   enemyList = (struct Enemy *)malloc(sizeof(struct Enemy) * 3);
   for (int i = 0; i < numOfEnemyKinds; i++)
   {
      fscanf_s(e, "%d %f %f", &enemyList[i].id, &enemyList[i].hp, &enemyList[i].damage);
   }
   fclose(e);

   if (enemyKind < enemyDistrib[PLAYER_LEVEL].chanceWeakEnemy && enemyDistrib[PLAYER_LEVEL].chanceWeakEnemy != 0)
      generatedEnemy = 0;
   else if (enemyKind >= enemyDistrib[PLAYER_LEVEL].chanceWeakEnemy && enemyKind < (enemyDistrib[PLAYER_LEVEL].chanceWeakEnemy + enemyDistrib[PLAYER_LEVEL].chanceMediumEnemy))
      generatedEnemy = 1;
   else
      generatedEnemy = 2;


   if (countOfEnemy < enemyDistrib[PLAYER_LEVEL].chanceWeakEnemy && enemyDistrib[PLAYER_LEVEL].chanceWeakEnemy != 0)
      curLoc->enemyAmount = 1;
   else if (countOfEnemy >= enemyDistrib[PLAYER_LEVEL].chanceWeakEnemy && countOfEnemy < (enemyDistrib[PLAYER_LEVEL].chanceWeakEnemy + enemyDistrib[PLAYER_LEVEL].chanceMediumEnemy))
      curLoc->enemyAmount = 2;
   else
      curLoc->enemyAmount = 3;

   curLoc->enemies = (struct Enemy *)malloc(curLoc->enemyAmount * sizeof(struct Enemy));

   for (int i = 0; i < curLoc->enemyAmount; i++)
   {
      curLoc->enemies[i].id = enemyList[generatedEnemy].id;
      curLoc->enemies[i].hp = enemyList[generatedEnemy].hp;
      curLoc->enemies[i].damage = enemyList[generatedEnemy].damage;
   }

   /*FILE *i;
   fopen(i, "r");
   fscanf_s(i, "%d", &itemListSize);
   int *itemList = (int *)malloc(sizeof(int) * itemListSize);
   int *generatedItemList = (int *)malloc(sizeof(int) * itemListSize);
   for (int j = 0; j < itemListSize; j++)
      fscanf_s(i, "%d", &itemList[j]);
   for (int j = 0; j < countOfItems; j++)
      generatedItemList[j] = itemList[rand()% countOfItems];*/
}


void StartingLocation()
{
   int exitFlag = 0;
   int choice = 0;
   system("cls");
   printf("Вы проснулись в трюме корабля после ночного шторма.\n");
   printf("Вас с трудом разбудил тёмный эльф. \n");
   printf("Вы узник на этом корабле, но совершенно не помните как здесь оказались. \n");
   printf("Вы причаливаете к берегу. \n");
   printf("В трюм спускается стражник и сообщает, что указом императора вы освобождаетесь. \n");
   printf("Выйдя на палубу, вы видите рыбацкий городок Сейда-Нин. \n");
   printf("Вдали, за причудливым грибным лесом, возвышается вулкан. Вулкан огромен, возможно самая высокая гора во всем Нирне. И он пробудился.\n");
   printf("Вас охватывает неясное видение. Но не получается разобрать ничего, кроме всепоглощающего пламени.\n");
   printf("Видение прерывает женский голос, исходящий словно со всех сторон, но слышишь его только ты.\n");
   printf("\"Я значала, что ты вернешься. Я укажу тебе путь. \"\n");
   printf("Голос стихает\n");
   _getch();
   InitTrader();
   Trader();
   system("cls");
   printf("Твое приключение начинается\n");
   system("cls");
}

void Trader()
{
   int exitFlag = 0;
   int inExitFlag = 0;
   int sellExitFlag = 0;
   int choice = 0;
   int inChoice = 0;
   int numSoldItem = 0;
   int k = 0;
   while (!exitFlag)
   {
      system("cls");
      printf("ТОРГОВЕЦ\n");
      printf("1) Продать\n");
      printf("2) Купить\n");
      printf("3) Инвентарь\n");
      printf("4) Покинуть торговца\n");
      scanf_s("%d", &choice);
      switch (choice)
      {
      case 1:
         while (!sellExitFlag)
         {
            printf("ТОРГОВЕЦ\n");
            printf("Что продать?\n");
            printf("1) Клинки\n");
            printf("2) Заклинания\n");
            printf("3) Одежду\n\n");
            printf("4) Назад\n");
            scanf_s("%s", &choice, 32);
            switch (choice)
            {
            case 1:
               system("cls");
               inExitFlag = 0;
               inChoice = 0;
               while (!inExitFlag)
               {
                  system("cls");
                  printf("ТОРГОВЕЦ\n");
                  printf("Что продать?\n");
                  printf("Содержимое инвентаря:\n");
                  for (int i = 0; i < 5; i++)
                  {
                     if (inventory->weapon[i]->id != 0)
                        printf_s("%d. %s %f %d\n", i, inventory->weapon[i]->name, inventory->weapon[i]->damage, inventory->weapon[i]->cost);
                     else
                        printf_s("%d. -------------------\n", i);

                  }
                  printf("1)Продать\n");
                  printf("2)Назад\n");
                  scanf_s("%d", &inChoice);
                  switch (inChoice)
                  {
                  case 1:
                     scanf_s("%d", &numSoldItem);
                     if (inventory->weapon[numSoldItem]->id != 0)
                     {
                        inventory->gold += inventory->weapon[numSoldItem]->cost;
                        inventory->weapon[numSoldItem]->id = 0;
                     }
                     break;
                  case 2:
                     sellExitFlag = 1;
                     inExitFlag = 1;
                     break;
                  }
               }
               break;
            case 2:
               system("cls");
               inExitFlag = 0;
               inChoice = 0;
               while (!inExitFlag)
               {
                  system("cls");
                  printf("ТОРГОВЕЦ\n");
                  printf("Что продать?\n");
                  printf("Содержимое инвентаря:\n");
                  for (int i = 0; i < 5; i++)
                  {
                     if (inventory->spells[i]->id != 0)
                        printf_s("%d. %s %f %d\n", i, inventory->spells[i]->name, inventory->spells[i]->damage, inventory->spells[i]->cost);
                     else
                        printf_s("%d. -------------------\n", i);

                  }
                  printf("\n1)Продать\n");
                  printf("2)Назад\n");
                  scanf_s("%d", &inChoice);
                  switch (inChoice)
                  {
                  case 1:
                     scanf_s("%d", &numSoldItem);
                     if (inventory->spells[numSoldItem]->id != 0)
                     {
                        inventory->gold += inventory->spells[numSoldItem]->cost;
                        inventory->spells[numSoldItem]->id = 0;
                     }
                     break;
                  case 2:
                     sellExitFlag = 1;
                     inExitFlag = 1;
                     break;
                  }
               }
               break;
            case 3:
               system("cls");
               inExitFlag = 0;
               inChoice = 0;
               while (!inExitFlag)
               {
                  system("cls");
                  printf("ТОРГОВЕЦ\n");
                  printf("Что продать?\n");
                  printf("Содержимое инвентаря:\n");
                  printf("№  name       protection     cost\n");
                  for (int i = 0; i < 5; i++)
                  {
                     if (inventory->armor[i]->id != 0)
                        printf_s("%d. %s %f %d\n", i, inventory->armor[i]->name, inventory->armor[i]->protection, inventory->armor[i]->cost);
                     else
                        printf_s("%d. -------------------\n", i);

                  }
                  printf("\n1)Продать\n");
                  printf("2)Назад\n");
                  scanf_s("%d", &inChoice);
                  switch (inChoice)
                  {
                  case 1:
                     scanf_s("%d", &numSoldItem);
                     if (inventory->armor[numSoldItem]->id != 0)
                     {
                        inventory->gold += inventory->armor[numSoldItem]->cost;
                        inventory->armor[numSoldItem]->id = 0;
                     }
                     break;
                  case 2:
                     sellExitFlag = 1;
                     inExitFlag = 1;
                     break;
                  }
               }
               break;
            case 4:
               exitFlag = 1;
               inExitFlag = 1;
               break;
            }
         }

      case 2:
         inExitFlag = 0;
         exitFlag = 0;
         while (!inExitFlag)
         {
            k = 0;
            system("cls");
            printf("ТОРГОВЕЦ\n");
            printf("Что купить?\n");
            printf("Торговец предлагает:\n");
            printf("№  name       power     cost\n");
            printf("1. %s %f %d\n", trader->weapon->name, trader->weapon->damage, trader->weapon->cost);
            printf("2. %s %f %d\n", trader->spell->name, trader->spell->damage, trader->spell->cost);
            printf("3. %s %f %d\n\n", trader->armor->name, trader->armor->protection, trader->armor->cost);
            printf("4) Назад\n");
            scanf_s("%d", &choice, 32);
            switch (choice)
            {
            case 1:
               if (inventory->gold >= trader->weapon->cost)
               {
                  while (inventory->weapon[k]->id != 0)
                     k++;
                  if (k <= 5)
                  {
                     trader->gold += trader->weapon->cost;
                     inventory->gold -= trader->weapon->cost;
                     inventory->weapon[k]->id = trader->weapon->id;
                     inventory->weapon[k]->damage = trader->weapon->damage;
                     inventory->weapon[k]->cost = trader->weapon->cost;
                     strcpy_s(inventory->weapon[k]->name, 32, trader->weapon->name);
                  }
               }
               break;
            case 2:
               if (inventory->gold >= trader->spell->cost)
               {
                  while (inventory->spells[k]->id != 0)
                     k++;
                  if (k <= 5)
                  {
                     trader->gold += trader->spell->cost;
                     inventory->gold -= trader->spell->cost;
                     inventory->spells[k]->id = trader->spell->id;
                     inventory->spells[k]->damage = trader->spell->damage;
                     inventory->spells[k]->cost = trader->spell->cost;
                     strcpy_s(inventory->spells[k]->name, 32, trader->spell->name);
                  }
               }
               break;
            case 3:
               if (inventory->gold >= trader->armor->cost)
               {
                  while (inventory->armor[k]->id != 0)
                     k++;
                  if (k <= 5)
                  {
                     trader->gold += trader->armor->cost;
                     inventory->gold -= trader->armor->cost;
                     inventory->armor[k]->id = trader->armor->id;
                     inventory->armor[k]->protection = trader->armor->protection;
                     inventory->armor[k]->cost = trader->armor->cost;
                     strcpy_s(inventory->armor[k]->name, 32, trader->armor->name);
                  }
               }
               break;
            case 4:
               exitFlag = 1;
               inExitFlag = 1;
               break;
            }
         }
         break;
      case 3:
         InventoryController();
         break;
      case 4:
         exitFlag = 1;
         break;
      }
   }
}
