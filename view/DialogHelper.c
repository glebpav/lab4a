#include <stdio.h>
#include <string.h>
#include "../Utils.h"
#include "ResponsesHandler.h"

int getExitOperationIdx() {
    return 9;
}

int selectOperation(const char *commandsMessages[], int countOfMessages) {
    int userInput;
    printf("\n");
    printf(" +------------------------------------------+\n");
    for (int i = 0; i < countOfMessages; ++i) {
        printf(" | %s ", commandsMessages[i]);
        printf("%.*s|\n", 40 - strlen(commandsMessages[i]), "                                                     ");
        printf(" +------------------------------------------+\n");
    }
    printf("\nSelect one command out of given:\n>> ");
    do {
        if (getSaveIntValue(&userInput, "") == EXIT_RESPONSE) return getExitOperationIdx();
        if (userInput > countOfMessages || userInput <= 0) throughException(INPUT_NOT_IN_RANGE_EXCEPTION);
        else break;
    } while (1);
    return userInput - 1;
}