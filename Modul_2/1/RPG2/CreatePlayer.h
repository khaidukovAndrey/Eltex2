#pragma once
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include "Player.h"


int PlayerCreation();
int RaceSelection();
int DistributionSkillPoints();
void SetRaceSkills(int mw, int ma, int ar, int st, int cr);
int Naming();

static int unallocatedSkillPoints = 10;
