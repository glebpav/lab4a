#ifndef LAB4A_FILEHELPER_H
#define LAB4A_FILEHELPER_H

#include "../view/ResponsesHandler.h"
#include "../controller/BinTree.h"

ResponsesTypes readFile(char *fileName, char ***outputString, int *outputStringLen);

ResponsesTypes getTreeFromString(char **stringArray, int stringArrayLen, Node **treeNode);


#endif //LAB4A_FILEHELPER_H
