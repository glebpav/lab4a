#ifndef LAB4A_DIALOGHELPER_H
#define LAB4A_DIALOGHELPER_H

#include "BinTree.h"
#include "CommandHelper.h"

const char *commandsMessages[] = {
        "1. Add new Item",
        "2. Delete Item",
        "3. Direct bypass",
        "4. Direct bypass by sub string (*)",
        "5. Search Item",
        "6. Search the most different Item (*)",
        "7. Print tree",
        "8. Read tree from file",
        "9. Exit program =("
};

ResponsesTypes (*commandsPointers[])(Node **) = {
        addNewItem,
        deleteItem,
        directBypassCommand,
        directBypassSpecial,
        searchItem,
        searchItemSpecial,
        printTree,
        readTreeFromFile,
        exitProgram
};

const int countOfCommands = sizeof(commandsMessages) / sizeof(commandsMessages[0]);

int selectOperation(const char *commandsMessages[], int countOfMessages);

int getExitOperationIdx();


#endif //LAB4A_DIALOGHELPER_H
