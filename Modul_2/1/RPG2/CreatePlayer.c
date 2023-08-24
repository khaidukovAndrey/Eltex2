#include "CreatePlayer.h"

int PlayerCreation()
{
   character = malloc(sizeof(struct Character));
   skills = (struct Skills *)malloc(sizeof(struct Skills));
   tempskills = (struct Skills *)malloc(sizeof(struct Skills));
   skills->meleeWeapon = 0;
   skills->armor = 0;
   skills->magic = 0;
   skills->stealth = 0;
   skills->crafting = 0;
   tempskills->meleeWeapon = 0;
   tempskills->armor = 0;
   tempskills->magic = 0;
   tempskills->stealth = 0;
   tempskills->crafting = 0;
   RaceSelection();
   skills->meleeWeapon += tempskills->meleeWeapon;
   skills->magic += tempskills->magic;
   skills->armor += tempskills->armor;
   skills->stealth += tempskills->stealth;
   skills->crafting += tempskills->crafting;
   character->skills = skills;
   character->maxhp = 15;
   character->hp = 15;
   InitInventory();
   return 0;
}

int RaceSelection()
{
   int exitFlag = 0;
   int choice = 0;

   while (!exitFlag)
   {
      system("cls");
      printf("ВЫБОР РАСЫ\n");
      printf("1) Человек\n");
      printf("2) Эльф\n");
      printf("3) Орк\n");
      printf("4) Катжит\n\n");
      printf("5) Описание рас\n\n");
      printf("6) Перейти к распределению очков способностей\n");
      printf("7) Перейти к выбору имени персонажа\n");
      printf("8) Завершить создание персонажа\n");
      scanf_s("%d", &choice);
      switch (choice)
      {
      case 1:
         character->race = 0;
         printf("Ваша раса человек\n");
         SetRaceSkills(3, 3, 2, 0, 2);
         _getch();
         break;
      case 2:
         character->race = 1;
         printf("Ваша раса эльф\n");
         SetRaceSkills(1, 5, 0, 1, 3);
         _getch();
         break;
      case 3:
         character->race = 2;
         printf("Ваша раса орк\n");
         SetRaceSkills(4, 0, 5, 0, 1);
         _getch();
         break;
      case 4:
         character->race = 3;
         printf("Ваша раса катжит\n");
         SetRaceSkills(3, 0, 0, 5, 2);
         _getch();
         break;
      case 5:
         _getch();
         break;
      case 6:
         exitFlag = 1;
         DistributionSkillPoints();
         break;
      case 7:
         exitFlag = 1;
         Naming();
         break;
      case 8:
         exitFlag = 1;
         break;
      }

   }
   return 0;
}

int DistributionSkillPoints()
{
   int exitFlag = 0;
   int sp = 0;
   int addsp = 0;
   int choice = 0;

   while (!exitFlag)
   {
      system("cls");
      printf("Распределение очков способностей \n");
      printf("Нераспределено очков: %d\n", unallocatedSkillPoints);
      printf("1) Оружие ближнего боя  : %d\n", skills->meleeWeapon + tempskills->meleeWeapon);
      printf("2) Магия                : %d\n", skills->magic + tempskills->magic);
      printf("3) Защита               : %d\n", skills->armor + tempskills->armor);
      printf("4) Скрытность           : %d\n", skills->stealth + tempskills->stealth);
      printf("5) Крафт                : %d\n\n", skills->crafting + tempskills->crafting);
      printf("6) Перейти к выбору расы\n");
      printf("7) Перейти к выбору имени персонажа\n");
      printf("8) Завершить создание персонажа\n");
      scanf_s("%d", &choice);
      switch (choice)
      {
      case 1:
         scanf_s("%d", &sp);
         addsp = sp - tempskills->meleeWeapon;
         if (addsp > unallocatedSkillPoints || sp < 0)
            break;
         unallocatedSkillPoints -= addsp;
         SetSkillValue(tempskills, 0, sp);
         break;
      case 2:
         scanf_s("%d", &sp);
         addsp = sp - tempskills->magic;
         if (addsp > unallocatedSkillPoints || sp < 0)
            break;
         unallocatedSkillPoints -= addsp;
         SetSkillValue(tempskills, 1, sp);
         break;
      case 3:
         scanf_s("%d", &sp);
         addsp = sp - tempskills->armor;
         if (addsp > unallocatedSkillPoints || sp < 0)
            break;
         unallocatedSkillPoints -= addsp;
         SetSkillValue(tempskills, 2, sp);
         break;
      case 4:
         scanf_s("%d", &sp);
         addsp = sp - tempskills->stealth;
         if (addsp > unallocatedSkillPoints || sp < 0)
            break;
         unallocatedSkillPoints -= addsp;
         SetSkillValue(tempskills, 3, sp);
         break;
      case 5:
         scanf_s("%d", &sp);
         addsp = sp - tempskills->crafting;
         if (addsp > unallocatedSkillPoints || sp < 0)
            break;
         unallocatedSkillPoints -= addsp;
         SetSkillValue(tempskills, 4, sp);
         break;
      case 6:
         exitFlag = 1;
         RaceSelection();
         break;
      case 7:
         exitFlag = 1;
         Naming();
         break;
      case 8:
         exitFlag = 1;
         break;
      }
   }
   return 0;
}

int Naming()
{
   int exitFlag = 0;
   int choice = 0;
   while (!exitFlag)
   {
      system("cls");
      printf("Как вас зовут? \n");
      printf("1) Дать имя персонажу\n");
      printf("2) Перейти к выбору расы\n");
      printf("3) Перейти к распределению очков способностей\n");
      printf("4) Завершить создание персонажа\n");
      scanf_s("%d", &choice);
      switch (choice)
      {
      case 1:
         scanf_s("%s", &character->name, 32);
         break;
      case 2:
         exitFlag = 1;
         RaceSelection();
         break;
      case 3:
         exitFlag = 1;
         DistributionSkillPoints();
         break;
      case 4:
         exitFlag = 1;
         break;
      }
   }
   return 0;
}


void SetRaceSkills(int mw, int ma, int ar, int st, int cr)
{
   skills->meleeWeapon = mw;
   skills->magic = ma;
   skills->armor = ar;
   skills->stealth = st;
   skills->crafting = cr;
}