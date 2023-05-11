#ifndef LAB4A_GRPAHVISHELPER_H
#define LAB4A_GRPAHVISHELPER_H

#include "../controller/BinTree.h"
#include "stdio.h"

void printTreeGraphVis(Node *tree, FILE *stream);

void printTreeGraphVisSubNode(Node *node, int nodeIdx, FILE *stream);

void printNullNode(int nullCount, FILE *stream);

#endif //LAB4A_GRPAHVISHELPER_H
