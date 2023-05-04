#include <stdio.h>
#include "DialogHelper.h"
#include "Utils.h"
#include "ResponsesHandler.h"

int getExitOperationIdx() {
    return 7;
}

int selectOperation(const char *commandsMessages[], int countOfMessages) {
    int userInput;
    printf("\n");
    for (int i = 0; i < countOfMessages; ++i) printf("%s\n", commandsMessages[i]);
    printf("Select one command out of given:\n");
    do {
        if (!getSaveIntValue(&userInput, "")) return 0;
        if (userInput > countOfMessages || userInput <= 0) throughException(INPUT_NOT_IN_RANGE_EXCEPTION);
        else break;
    } while (1);
    return userInput - 1;
}