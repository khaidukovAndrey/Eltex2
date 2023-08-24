#include "Fight.h"

int FightControl()
{
   srand(time(NULL));
   char exitFlag = 0;
   char inExitFlag = 0;
   int choice = 0;
   int inChoice = 0;
   int enemyChoice = 0;
   int chanceToDamage = 0;
   int weaponKind = 0;
   int tryToDamage = 0;
   int countDefeated = 0;
   int numAttacking = 0;
   while (!exitFlag)
   {
      inExitFlag = 0;
      while (!inExitFlag)
      {
         system("cls");
         printf("БОЙ\n");
         printf("%s [%.0f/%.0f]\n", character->name, character->hp, character->maxhp);
         printf("Враги: \n");
         PrintEnemies();
         printf("1) Атаковать\n");
         printf("2) Применить зелье\n");
         printf("3) Экипировать\n");
         printf("4) Сбежать\n");
         scanf_s("%d", &choice);
         switch (choice)
         {
         case 1:
            if (equipment->weapon != NULL)
               weaponKind = 0;
            else
               weaponKind = 1;
            system("cls");
            printf("БОЙ\n");
            printf("%s [%.0f/%.0f]", character->name, character->hp, character->maxhp);
            printf("Враги: \n");
            PrintEnemies();
            printf("Выберите врага\n");

            while (scanf_s("%d", &enemyChoice) == 0 || curLoc->enemies[enemyChoice - 1].hp <= 0);
            chanceToDamage = CalcChanceToDamage();
            tryToDamage = rand() % 100;
            if (tryToDamage < chanceToDamage)
            {
               if (weaponKind == 0)
                  curLoc->enemies[enemyChoice - 1].hp -= equipment->weapon->damage;
               if (weaponKind == 1)
                  curLoc->enemies[enemyChoice - 1].hp -= equipment->spell->damage;
            }
            if (curLoc->enemies[enemyChoice - 1].hp <= 0)
               countDefeated++;
            if (countDefeated == curLoc->enemyAmount)
            {
               exitFlag = 1;
            }
            inExitFlag = 1;
            break;
         case 2:


            break;
         case 3:
            Equip();
            break;
         case 4:
            return 1;
            break;
         default:
            break;
         }
      }
      if (!exitFlag)
      {
         system("cls");
         printf("БОЙ\n");
         printf("%s [%.0f/%.0f]", character->name, character->hp, character->maxhp);
         printf("Враги: \n");
         PrintEnemies();
         for (int i = 0; i < curLoc->enemyAmount; i++)
         {
            if (curLoc->enemies[i].hp > 0)
            {
               chanceToDamage = CalcEnemyChanceToDamage();
               tryToDamage = rand() % 100;
               if (tryToDamage < chanceToDamage)
               {
                  character->hp -= curLoc->enemies[i].damage;
               }

            }

         }
      }
      if (character->hp < 0)
      {
         return 2;
      }
   }
   return 0;
}

void Equip()
{
   int exitFlag = 0;
   int choice = 0;
   int numEqItem = 0;
   int inExitFlag = 0;
   int inChoice = 0;
   while (!exitFlag)
   {
      system("cls");
      printf("Что экипировать?\n");
      printf("1) Клинок\n");
      printf("2) Заклинание\n");
      printf("3) Одежду\n\n");
      printf("4) Назад\n");
      scanf_s("%d", &choice);
      switch (choice)
      {
      case 1:
         system("cls");
         inExitFlag = 0;
         inChoice = 0;
         while (!inExitFlag)
         {
            system("cls");
            printf("ИНВЕНТАРЬ клинки\n");
            printf("Содержимое:\n");
            for (int i = 0; i < 5; i++)
            {
               if (inventory->weapon[i]->id != 0)
                  printf_s("%d. %s %f\n", i, inventory->weapon[i]->name, inventory->weapon[i]->damage);
               else
                  printf_s("%d. -------------------\n", i);

            }
            printf("\n1)Экипировать\n");
            printf("2)Назад\n");
            scanf_s("%d", &inChoice);
            switch (inChoice)
            {
            case 1:
               scanf_s("%d", &numEqItem);
               if (inventory->weapon[numEqItem]->id != 0)
               {
                  equipment->weapon = inventory->weapon[numEqItem];
                  equipment->spell = NULL;
               }
               break;
            case 2:
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
            printf("ИНВЕНТАРЬ заклинания\n");
            printf("Содержимое:\n");
            for (int i = 0; i < 5; i++)
            {
               if (inventory->spells[i]->id != 0)
                  printf_s("%d. %s %f\n", i, inventory->spells[i]->name, inventory->spells[i]->damage);
               else
                  printf_s("%d. -------------------\n", i);

            }
            printf("\n1)Экипировать\n");
            printf("2)Назад\n");
            scanf_s("%d", &inChoice);
            switch (inChoice)
            {
            case 1:
               scanf_s("%d", &numEqItem);
               if (inventory->spells[numEqItem]->id != 0)
               {
                  equipment->spell = inventory->spells[numEqItem];
                  equipment->weapon = NULL;
               }
               break;
            case 2:
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
            printf("ИНВЕНТАРЬ одежда\n");
            printf("Содержимое:\n");
            for (int i = 0; i < 5; i++)
            {
               if (inventory->armor[i]->id != 0)
                  printf_s("%d. %s %f\n", i, inventory->armor[i]->name, inventory->armor[i]->protection);
               else
                  printf_s("%d. -------------------\n", i);

            }
            printf("\n1)Экипировать\n");
            printf("2)Назад\n");
            scanf_s("%d", &inChoice);
            switch (inChoice)
            {
            case 1:
               scanf_s("%d", &numEqItem);
               if (inventory->armor[numEqItem]->id != 0)
               {
                  equipment->armor = inventory->armor[numEqItem];
               }
               break;
            case 2:
               inExitFlag = 1;
               break;
            }
         }
         break;
      case 4:
         exitFlag = 1;
         break;
      }

   }
}

void PrintEnemies()
{
   char enemyName[32];
   switch (locationsList[curLoc->id].enemyID)
   {
   case 0:
      switch (curLoc->enemies[0].id)
      {
      case 0:
         strcpy_s(enemyName, sizeof(enemyName), "Волк");
         break;
      case 1:
         strcpy_s(enemyName, sizeof(enemyName), "Тигр");
         break;
      case 2:
         strcpy_s(enemyName, sizeof(enemyName), "Медведь");
         break;
      default:
         break;
      }
      break;
   case 1:
      switch (curLoc->enemies[0].id)
      {
      case 0:
         strcpy_s(enemyName, sizeof(enemyName), "Бандит");
         break;
      case 1:
         strcpy_s(enemyName, sizeof(enemyName), "Разбойник");
         break;
      case 2:
         strcpy_s(enemyName, sizeof(enemyName), "Головорез");
         break;
      default:
         break;
      }
      break;
   case 2:
      switch (curLoc->enemies[0].id)
      {
      case 0:
         strcpy_s(enemyName, sizeof(enemyName), "Ученик некроманта");
         break;
      case 1:
         strcpy_s(enemyName, sizeof(enemyName), "Адепт некромантии");
         break;
      case 2:
         strcpy_s(enemyName, sizeof(enemyName), "Мастер некромантии");
         break;
      default:
         break;
      }
      break;
   case 3:
      switch (curLoc->enemies[0].id)
      {
      case 0:
         strcpy_s(enemyName, sizeof(enemyName), "Драугр");
         break;
      case 1:
         strcpy_s(enemyName, sizeof(enemyName), "Беспокойный драугр");
         break;
      case 2:
         strcpy_s(enemyName, sizeof(enemyName), "Призрачный драугр");
         break;
      default:
         break;
      }
      break;
   default:
      break;
   }
   for (int i = 0; i < curLoc->enemyAmount; i++)
   {
      printf("%s  [%.0f hp]\n", enemyName, curLoc->enemies[i].hp);
   }
}

int CalcChanceToDamage()
{
   int chanceToDamage = 0;
   if (curLoc->enemies[0].id == 0)
   {
      chanceToDamage = 70;
   }
   if (curLoc->enemies[0].id == 1)
   {
      chanceToDamage = 50;
   }
   if (curLoc->enemies[0].id == 2)
   {
      chanceToDamage = 30;
   }

   if (equipment->weapon != NULL)
   {
      chanceToDamage += character->skills->meleeWeapon * 4;
   }
   else
   {
      chanceToDamage += character->skills->magic * 4;
   }
   return chanceToDamage;
}

int CalcEnemyChanceToDamage()
{
   int chanceToDamage = 0;
   if (curLoc->enemies[0].id == 0)
   {
      chanceToDamage = 30;
   }
   if (curLoc->enemies[0].id == 1)
   {
      chanceToDamage = 50;
   }
   if (curLoc->enemies[0].id == 2)
   {
      chanceToDamage = 70;
   }

   chanceToDamage -= character->skills->stealth * 2;
   return chanceToDamage;
}