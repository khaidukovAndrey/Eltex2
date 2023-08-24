#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

struct Inventory;
struct Weapon;
struct Armor;
struct Potion;
struct Materials;

struct Weapon
{
   int id;
   char name[32];
   float damage;
   int cost;
}*weaponList, *availableWeapons;

struct Spell
{
   int id;
   int type;
   char name[32];
   float damage;
   int cost;
}*spellList, *availableSpells;

struct Potion
{
   int id;
   int type;
   char name[32];
   int stack;
   int cost;
};

struct Materials
{
   int id;
   int type;
   char name[32];
   int stack;
   int cost;
};

struct Armor
{
   int id;
   int type;
   char name[32];
   float protection;
   int cost;
}*armorList, *availableArmor;

struct Inventory
{
   int gold;
   struct Armor **armor;
   struct Potion **potion;
   struct Weapon **weapon;
   struct Weapon **spells;
   struct Materials **materials;
}*inventory;

struct Equipment
{
   struct Weapon *weapon;
   struct Armor *armor;
   struct Spell *spell;
}*equipment;

struct Character
{
   char name[32];
   int race;
   struct Skills *skills;
   float damage;
   float maxhp;
   float hp;
}*character;

struct Skills
{
   int meleeWeapon; //1
   int magic; //2
   int armor;      //3
   int stealth;      //4
   int crafting;       //5
   //int two_handedWeapon; //1
   //int one_handedWeapon; //2
   //int lightWeapon;      //3
   //int destruction;      //4
   //int witchcraft;       //5
   //int recovery;         //6
   //int heavyArmor;       //7
   //int mediumArmor;      //8
   //int lightArmor;       //9
   //int stealth;          //10
   //int breakingLocks;    //11
   //int theft;            //12
   //int alchemy;          //13
   //int blacksmithing;    //14
   //int enchantment;      //15
}*skills, *tempskills;


void ReadWeapons();
void ReadSpells();
void ReadArmor();
void InitEquipment();
void InitInventory();
void InventoryController();

void SetSkillValue(struct Skills *sl, int skillID, int val);

//void AddSkillValue(int skillID, int val)
//{
//   switch (skillID)
//   {
//   case 0:
//      skills->meleeWeapon += val;
//      break;
//   case 1:
//      skills->magic += val;
//      break;
//   case 2:
//      skills->armor += val;
//      break;
//   case 3:
//      skills->stealth += val;
//      break;
//   case 4:
//      skills->crafting += val;
//      break;
//}

//void IncSkillValue(int skillID)
//{
//   switch (skillID)
//   {
//   case 1:
//      skills->meleeWeapon++;
//      break;
//   case 2:
//      skills->one_handedWeapon++;
//      break;
//   case 3:
//      skills->lightWeapon++;
//      break;
//   case 4:
//      skills->destruction++;
//      break;
//   case 5:
//      skills->witchcraft++;
//      break;
//   case 6:
//      skills->recovery++;
//      break;
//   case 7:
//      skills->heavyArmor++;
//      break;
//   case 8:
//      skills->mediumArmor++;
//      break;
//   case 9:
//      skills->lightArmor++;
//      break;
//   case 10:
//      skills->stealth++;
//      break;
//   case 11:
//      skills->breakingLocks++;
//      break;
//   case 12:
//      skills->theft++;
//      break;
//   case 13:
//      skills->alchemy++;
//      break;
//   case 14:
//      skills->blacksmithing++;
//      break;
//   case 15:
//      skills->enchantment++;
//      break;
//   }
//   /*switch (skillID)
//   {
//   case 1:
//      skills->two_handedWeapon++;
//      break;
//   case 2:
//      skills->one_handedWeapon++;
//      break;
//   case 3:
//      skills->lightWeapon++;
//      break;
//   case 4:
//      skills->destruction++;
//      break;
//   case 5:
//      skills->witchcraft++;
//      break;
//   case 6:
//      skills->recovery++;
//      break;
//   case 7:
//      skills->heavyArmor++;
//      break;
//   case 8:
//      skills->mediumArmor++;
//      break;
//   case 9:
//      skills->lightArmor++;
//      break;
//   case 10:
//      skills->stealth++;
//      break;
//   case 11:
//      skills->breakingLocks++;
//      break;
//   case 12:
//      skills->theft++;
//      break;
//   case 13:
//      skills->alchemy++;
//      break;
//   case 14:
//      skills->blacksmithing++;
//      break;
//   case 15:
//      skills->enchantment++;
//      break;
//   }*/
//}
//
//void DecSkillValue(int skillID)
//{
//   switch (skillID)
//   {
//   case 1:
//      skills->two_handedWeapon--;
//      break;
//   case 2:
//      skills->one_handedWeapon--;
//      break;
//   case 3:
//      skills->lightWeapon--;
//      break;
//   case 4:
//      skills->destruction--;
//      break;
//   case 5:
//      skills->witchcraft--;
//      break;
//   case 6:
//      skills->recovery--;
//      break;
//   case 7:
//      skills->heavyArmor--;
//      break;
//   case 8:
//      skills->mediumArmor--;
//      break;
//   case 9:
//      skills->lightArmor--;
//      break;
//   case 10:
//      skills->stealth--;
//      break;
//   case 11:
//      skills->breakingLocks--;
//      break;
//   case 12:
//      skills->theft--;
//      break;
//   case 13:
//      skills->alchemy--;
//      break;
//   case 14:
//      skills->blacksmithing--;
//      break;
//   case 15:
//      skills->enchantment--;
//      break;
//   }
//}