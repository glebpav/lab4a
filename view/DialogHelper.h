#ifndef LAB4A_DIALOGHELPER_H
#define LAB4A_DIALOGHELPER_H

#include "../controller/BinTree.h"
#include "CommandHelper.h"

const char *commandsMessages[] = {
        " 1. Add new Item",
        " 2. Delete Item",
        " 3. Direct bypass",
        " 4. Direct bypass by sub string (*)",
        " 5. Search Item",
        " 6. Search the most different Item (*)",
        " 7. Print tree in console",
        " 8. Print tree in graphvis",
        " 9. Read tree from file",
        "10. Exit program =("
};

ResponsesTypes (*commandsPointers[])(Node **) = {
        addNewItem,
        deleteItem,
        directBypassCommand,
        directBypassSpecial,
        searchItem,
        searchItemSpecial,
        printTree,
        printTreeInGraphViz,
        readTreeFromFile,
        exitProgram
};

const int countOfCommands = sizeof(commandsMessages) / sizeof(commandsMessages[0]);

int selectOperation(const char *commandsMessages[], int countOfMessages);

int getExitOperationIdx();


#endif //LAB4A_DIALOGHELPER_H
