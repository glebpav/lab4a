#include "Utils.h"
#include "stdio.h"
#include "ResponsesHandler.h"

int getInt(int *var) {
    int clearBuffer, res = scanf("%d", var);
    while ((clearBuffer = getchar()) != '\n' && clearBuffer != EOF) {}
    return res;
}


int getSaveIntValue(int *value, char *messageToUser) {
    int res;
    printf("%s", messageToUser);
    do {
        res = getInt(value);
        if (res == 0) throughException(NOT_INT_VALUE_EXCEPTION);
        else if (res == EOF) return 0;
    } while (res <= 0);
    return res;
}
