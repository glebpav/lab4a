#include <stdio.h>
#include "ResponsesHandler.h"
#include "BinTree.h"
#include "DialogHelper.h"

int main() {
    int operationIdx, exitOperationIdx;
    ResponsesTypes operationResponse;
    Node treeRoot;

    exitOperationIdx = getExitOperationIdx();
    treeRoot = initLocaleTable(MAX_TABLE_SIZE);

    do {
        operationIdx = selectOperation(commandsMessages, countOfCommands);
        operationResponse = commandsPointers[operationIdx](&treeRoot);
    } while (operationIdx != exitOperationIdx && !isException(operationResponse));

    return 0;
}

