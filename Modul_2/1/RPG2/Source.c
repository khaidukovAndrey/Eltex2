//#include "LocationGeneration.h"
#include "Player.h"
#include "CreatePlayer.h"
#include <locale.h>


int main()
{
   setlocale(LC_ALL, "");
   ReadLocations();
   ReadEnemyLevelDistribution();
   ReadWeapons();
   ReadSpells();
   ReadArmor();
   PlayerCreation();
   InitEquipment();
   StartingLocation();
   char exitFlag = 0;
   for (int i = 0; i < 3 && !exitFlag; i++)
   {
      
      GenerateLocation();
      switch (FightControl())
      {
      case 0:
         system("cls");
         printf_s("Вы зачистили локацию от врагов!");
         inventory->gold += 10;
         _getch();

         break;
      case 1:
         system("cls");
         printf_s("Вы позорно бежали");
         _getch();

         break;
      case 2:
         system("cls");
         printf_s("Вы погибли...");
         _getch();
         exitFlag = 1;
         break;
      }
   }
   

   return 0;
}