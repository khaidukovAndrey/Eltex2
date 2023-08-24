#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Tree.h"

#define FIELD_WIDTH 1    //менять ширину


int counter;

Tree *TreeAdd(Tree *tree, int elem)
{
   int dpth = 0;
   char flag = 1;
   if (tree == NULL)
   {
      (tree) = (Tree *)malloc(sizeof(Tree));
      (tree)->elem = elem;
      (tree)->left = NULL;
      (tree)->right = NULL;
      tree->depth = 0;
      return tree;
   }
   Tree *tmp = tree;
   while (flag)
   {
      dpth++;
      if (elem < tmp->elem)
      {
         if (tmp->left == NULL)
         {
            tmp->left = (Tree *)malloc(sizeof(Tree));
            flag = 0;
         }
         tmp = tmp->left;
      }
      else
      {
         if (tmp->right == NULL)
         {
            tmp->right = (Tree *)malloc(sizeof(Tree));
            flag = 0;
         }
         tmp = tmp->right;
      }
   }
   tmp->elem = elem;
   tmp->left = NULL;
   tmp->right = NULL;
   tmp->depth = dpth;
   return tree;
}

Tree *TreeSearch(Tree *tree, int elem)
{
   if ((tree == NULL) || (tree->elem = elem))
      return tree;
   if (elem < tree->elem)
      return TreeSearch(tree->left, elem);
   else
      return TreeSearch(tree->right, elem);
}

void TreePrint(Tree *t)
{
   if (t != NULL) {
      TreePrint(t->left);
      printf("%d\n", t->elem);
      TreePrint(t->right);
   }
}

void FindMaxDepth(Tree *t, int *maxDepth)
{
   if (t != NULL) {
      FindMaxDepth(t->left, maxDepth);
      if (t->depth > *maxDepth)
         *maxDepth = t->depth;
      FindMaxDepth(t->right, maxDepth);
   }
}

void BetterTreePrint(Tree *t, char *filename)
{
   FILE *f;
   fopen_s(&f, filename, "w");
   int iIdentSize = 0;
   int identSize = 2;
   int maxDepth = 0;
   int countElementsOnLevel = 1;
   char **nums;
   FindMaxDepth(t, &maxDepth);
   identSize = identSize << maxDepth;
   for (int i = 0; i <= maxDepth; i++)
   {
      counter = 0;
      identSize = identSize >> 1;
      iIdentSize = identSize * 2 - 1;
      nums = (char *)malloc(sizeof(char *) * countElementsOnLevel);
      for (int j = 0; j < countElementsOnLevel; j++)
         nums[j] = (char *)malloc(sizeof(char) * 12);
      SearchNumsOnLevel(t, i, nums);

      if (i > 0)
      {
         for (int j = 0; j < identSize; j++)
            for (int i = 0; i < FIELD_WIDTH; i++)
            {
               fprintf(f, " ");
            }
         for (int j = 0; j < countElementsOnLevel; j++)
         {
            if (strcmp(nums[j], "") != 0)
               fprintf(f, "|");    //менять ширину
            else
               for (int i = 0; i < FIELD_WIDTH; i++)
               {
                  fprintf(f, " ");
               }
            if (j < countElementsOnLevel - 1)
               if (j % 2 == 0 && (strcmp(nums[j], "") != 0 || strcmp(nums[j + 1], "") != 0))
                  for (int k = 0; k < iIdentSize; k++)
                     for (int i = 0; i < FIELD_WIDTH; i++)
                     {
                        fprintf(f, "-");
                     }
               else
                  for (int k = 0; k < iIdentSize; k++)
                     for (int i = 0; i < FIELD_WIDTH; i++)
                     {
                        fprintf(f, " ");
                     }
         }
         fprintf(f, "\n");
      }

      for (int j = 0; j < identSize; j++)
         for (int i = 0; i < FIELD_WIDTH; i++)
         {
            fprintf(f, " ");
         }
      for (int j = 0; j < countElementsOnLevel; j++)
      {
         if (strcmp(nums[j], "") != 0)
            fprintf(f, "%1s", nums[j]);    //менять ширину
         else
            for (int i = 0; i < FIELD_WIDTH; i++)
            {
               fprintf(f, " ");
            }
         if (j < countElementsOnLevel - 1)
            for (int k = 0; k < iIdentSize; k++)
               for (int i = 0; i < FIELD_WIDTH; i++)
               {
                  fprintf(f, " ");
               }
      }
      countElementsOnLevel = countElementsOnLevel << 1;
      fprintf(f, "\n");
   }
   fclose(f);
}

void SearchNumsOnLevel(Tree *t, int level, char **nums)
{
   if (t->depth == level)
   {
      intToStr(nums, t->elem);
      counter++;
      return;
   }
   if (t->left != NULL)
      SearchNumsOnLevel(t->left, level, nums);
   else
   {
      for (int i = 0; i < (1 << (level - t->depth - 1)); i++)
      {
         strcpy_s(nums[counter], _countof(nums[counter]), "");
         counter++;
      }
   }

   if (t->right != NULL)
      SearchNumsOnLevel(t->right, level, nums);
   else
   {
      for (int i = 0; i < (1 << (level - t->depth - 1)); i++)
      {
         strcpy_s(nums[counter], _countof(nums[counter]), "");
         counter++;
      }
   }
}

void intToStr(char **nums, int tEl)
{
   char k = 0;
   int length = 0;
   int c, i, j;
   do
   {
      nums[counter][k] = (tEl % 10) + '0';
      tEl /= 10;
      k++;
   } while (tEl / 10 != 0 || tEl % 10 != 0);
   nums[counter][k] = '\0';
   length = strlen(nums[counter]);
   for (i = 0, j = length - 1; i < j; i++, j--)
   {
      c = nums[counter][i];
      nums[counter][i] = nums[counter][j];
      nums[counter][j] = c;
   }
}