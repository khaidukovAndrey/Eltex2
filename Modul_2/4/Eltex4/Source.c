#include <stdlib.h>
#include <time.h>
#include "Tree.h"



int main()
{
   Tree *t = NULL;
   char fileName[] = "out.txt";
   srand(time(NULL));
   for (int i = 0; i < 10; i++)
   {
      t = TreeAdd(t, (rand() % 10));
   }
   BetterTreePrint(t, fileName);
   return 0;
}