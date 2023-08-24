#include "Player.h"


void ReadWeapons()
{
   int count;
   FILE *locs;
   fopen_s(&locs, "weapons.txt", "r");
   fscanf_s(locs, "%d", &count);
   weaponList = (struct Weapon*)malloc(sizeof(struct Weapon) * count);

   for (int i = 0; i < count; i++)
   {
      fscanf_s(locs, "%d ", &weaponList[i].id);
      fscanf_s(locs, "%f ", &weaponList[i].damage);
      fscanf_s(locs, "%d ", &weaponList[i].cost);
      fscanf_s(locs, "%s", weaponList[i].name, 32);
   }
}

void ReadSpells()
{
   int count;
   FILE *locs;
   fopen_s(&locs, "spells.txt", "r");
   fscanf_s(locs, "%d", &count);
   spellList = (struct Spell *)malloc(sizeof(struct Spell) * count);

   for (int i = 0; i < count; i++)
   {
      fscanf_s(locs, "%d ", &spellList[i].id);
      fscanf_s(locs, "%d ", &spellList[i].type);
      fscanf_s(locs, "%f ", &spellList[i].damage);
      fscanf_s(locs, "%d ", &spellList[i].cost);
      fscanf_s(locs, "%s", spellList[i].name, 32);
   }
}

void ReadArmor()
{
   int count;
   FILE *locs;
   fopen_s(&locs, "armor.txt", "r");
   fscanf_s(locs, "%d", &count);
   armorList = (struct Spell *)malloc(sizeof(struct Spell) * count);

   for (int i = 0; i < count; i++)
   {
      fscanf_s(locs, "%d ", &armorList[i].id);
      fscanf_s(locs, "%f ", &armorList[i].protection);
      fscanf_s(locs, "%d ", &armorList[i].cost);
      fscanf_s(locs, "%s", armorList[i].name, 32);
   }
}

void InitInventory()
{
   inventory= (struct Inventory*)malloc(sizeof(struct Inventory));
   inventory->gold = 50;
   inventory->weapon= malloc(sizeof(struct Weapon)*5);
   inventory->spells= malloc(sizeof(struct Spell)*5);
   inventory->armor= malloc(sizeof(struct Armor)*5);
   for (int i = 0; i < 5; i++)
   {
      inventory->weapon[i] = malloc(sizeof(struct Weapon));
      inventory->weapon[i]->id=0;
      inventory->spells[i] = malloc(sizeof(struct Spell));
      inventory->spells[i]->id = 0;
      inventory->armor[i] = malloc(sizeof(struct Armor));
      inventory->armor[i]->id=0;
   }
   /*for (int i = 0; i < 10; i++)
   {
      inventory->potion[i] = malloc(sizeof(struct Potion));
      inventory->potion[i]->id=0;
      inventory->materials[i] = malloc(sizeof(struct Materials));
      inventory->materials[i]->id=0;
   }*/
}

void InventoryController()
{
   int exitFlag = 0;
   int choice = 0;
   int numEqItem = 0;
   int inExitFlag = 0;
   int inChoice = 0;
   while (!exitFlag)
   {
      system("cls");
      printf("ИНВЕНТАРЬ\n");
      printf("1) Посмотреть клинки\n");
      printf("2) Посмотреть заклинания\n");
      printf("3) Посмотреть одежду\n");
      printf("4) Посмотреть зелья\n\n");
      printf("5) Посмотреть материалы\n\n");
      printf("6) Выйти\n");
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
            printf("2)Выкинуть\n");
            printf("3)Назад\n");
            scanf_s("%d", &inChoice);
            switch (inChoice)
            {
            case 1:
               scanf_s("%d", &numEqItem);
               if(inventory->weapon[numEqItem]->id!=0)
               {
                  equipment->weapon = inventory->weapon[numEqItem];
                  equipment->spell = NULL;
               }
               break;
            case 2:
               scanf_s("%d", &numEqItem);
               inventory->weapon[numEqItem]->id=0;
               break;
            case 3:
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
            printf("2)Выкинуть\n");
            printf("3)Назад\n");
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
               scanf_s("%d", &numEqItem);
               inventory->spells[numEqItem]->id = 0;
               break;
            case 3:
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
            printf("2)Выкинуть\n");
            printf("3)Назад\n");
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
               scanf_s("%d", &numEqItem);
               inventory->armor[numEqItem]->id = 0;
               break;
            case 3:
               inExitFlag = 1;
               break;
            }
         }
         break;
      case 4:
         

         break;
      case 5:
         
      case 6:
         exitFlag = 1;
         break;
      }

   }
}

void InitEquipment()
{
   equipment = malloc(sizeof(struct Equipment));
   equipment->weapon = NULL;
   equipment->spell = NULL;
   equipment->armor = NULL;
}

void SetSkillValue(struct Skills *sl, int skillID, int val)
{
   switch (skillID)
   {
   case 0:
      sl->meleeWeapon = val;
      break;
   case 1:
      sl->magic = val;
      break;
   case 2:
      sl->armor = val;
      break;
   case 3:
      sl->stealth = val;
      break;
   case 4:
      sl->crafting = val;
      break;
   }
}