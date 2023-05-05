#include <stdlib.h>
#include "Utils.h"
#include "stdio.h"
#include "ResponsesHandler.h"

int getInt(int *var) {
    int clearBuffer, res = scanf("%d", var);
    while ((clearBuffer = getchar()) != '\n' && clearBuffer != EOF) {}
    return res;
}

char *getLine(void) {
    char *line = malloc(100), *linep = line;
    size_t lenmax = 100, len = lenmax;
    int c;

    if (line == NULL)
        return NULL;

    for (;;) {
        c = fgetc(stdin);
        if (c == EOF)
            break;

        if (--len == 0) {
            len = lenmax;
            char *linen = realloc(linep, lenmax *= 2);

            if (linen == NULL) {
                free(linep);
                return NULL;
            }
            line = linen + (line - linep);
            linep = linen;
        }

        if ((*line++ = c) == '\n')
            break;
    }
    *line--;
    *line = '\0';
    return linep;
}

ResponsesTypes getSaveStingValue(char **value, char *messageToUser) {
    printf("%s", messageToUser);
    *value = getLine();
    return value == NULL ? EXIT_RESPONSE : SUCCESS_RESPONSE;
}

ResponsesTypes getSaveIntValue(int *value, char *messageToUser) {
    int res;
    printf("%s", messageToUser);
    do {
        res = getInt(value);
        if (res == 0) throughException(NOT_INT_VALUE_EXCEPTION);
        else if (res == EOF) return EXIT_RESPONSE;
    } while (res <= 0);
    return SUCCESS_RESPONSE;
}
