#include <stdio.h>
#include "view/ResponsesHandler.h"
#include "controller/BinTree.h"
#include "view/DialogHelper.h"
#include "model/MyVector.h"

// gcc main.c -o main BinTree.c ResponsesHandler.c CommandHelper.c DialogHelper.c FileHelper.c Utils.c MyVector.c

int main() {
    int operationIdx, exitOperationIdx;
    ResponsesTypes operationResponse;
    Node *treeRoot;

    exitOperationIdx = getExitOperationIdx();
    treeRoot = NULL;

    do {
        operationIdx = selectOperation(commandsMessages, countOfCommands);
        operationResponse = commandsPointers[operationIdx](&treeRoot);
    } while (operationIdx != exitOperationIdx && !isException(operationResponse));

    freeTree(treeRoot);
    printf("Goodbye, dear!\n");

    return 0;
}

