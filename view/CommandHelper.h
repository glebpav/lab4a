#ifndef LAB4A_COMMANDHELPER_H
#define LAB4A_COMMANDHELPER_H

#include "ResponsesHandler.h"
#include "../controller/BinTree.h"

ResponsesTypes addNewItem(Node **treeRoot);

ResponsesTypes deleteItem(Node **treeRoot);

ResponsesTypes directBypassCommand(Node **treeRoot);

ResponsesTypes directBypassSpecial(Node **treeRoot);

ResponsesTypes searchItem(Node **treeRoot);

ResponsesTypes searchItemSpecial(Node **treeRoot);

ResponsesTypes printTree(Node **treeRoot);

ResponsesTypes printTreeInGraphViz(Node **treeRoot);

ResponsesTypes readTreeFromFile(Node **treeRoot);

ResponsesTypes exitProgram(Node **treeRoot);

#endif //LAB4A_COMMANDHELPER_H
