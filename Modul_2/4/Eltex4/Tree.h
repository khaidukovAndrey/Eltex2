#pragma once
#include <stdio.h>


typedef struct Tree
{
   int elem;
   int depth;
   struct Tree *left;
   struct Tree *right;
}Tree;

//Tree *NewTree(int elem);
Tree *TreeAdd(Tree *tree, int elem);
Tree *TreeSearch(Tree *tree, int elem);
void TreePrint(Tree *t);
void FindMaxDepth(Tree *t, int *maxDepth);
void BetterTreePrint(Tree *t, char *filename);
void SearchNumsOnLevel(Tree *t, int level, char **nums);
void intToStr(char **nums, int n);