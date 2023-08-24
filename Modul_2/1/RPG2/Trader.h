#pragma once
#include "Player.h"

struct Trader
{
   int gold;
   struct Weapon *weapon;
   struct Armor *armor;
   struct Spell *spell;
} *trader;


void InitTrader()
{
   trader = malloc(sizeof(struct Trader));
   trader->weapon = malloc(sizeof(struct Weapon));
   trader->spell = malloc(sizeof(struct Spell));
   trader->armor = malloc(sizeof(struct Armor));
   trader->gold = 500;
   trader->weapon = &weaponList[0];
   trader->spell = &spellList[0];
   trader->armor = &armorList[0];
}