#include <stdio.h>
#include "ResponsesHandler.h"
#include "BinTree.h"
#include "DialogHelper.h"
#include "MyVector.h"

// gcc main.c -o main BinTree.c ResponsesHandler.c CommandHelper.c DialogHelper.c FileHelper.c Utils.c MyVector.c

int getNum(int num) {
    return num;
}

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

    return 0;
}

