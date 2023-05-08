#include <stdio.h>
#include "errno.h"
#include "FileHelper.h"
#include "string.h"
#include "stdlib.h"
#include "BinTree.h"

ResponsesTypes readFile(char *fileName, char ***outputString, int *outputStringLen) {
    FILE *fp;

    char *prefix = strdup("files/");
    char *filePath = calloc(strlen(prefix) + strlen(fileName) + 1, sizeof(char));
    filePath = strcat(filePath, prefix);
    filePath = strcat(filePath, fileName);

    free(prefix);
    if ((fp = fopen(filePath, "r+")) == NULL) {
        free(filePath);
        return NO_SUCH_FILE_EXCEPTION;
    }
    free(filePath);

    char *item = calloc(128, sizeof(char));
    *outputStringLen = 0;

    while (1) {
        int ret = fscanf(fp, "%s", item);
        if (ret == 1) {
            *outputString = realloc(*outputString, (1 + *outputStringLen) * sizeof(char*));
            (*outputString)[*outputStringLen] = calloc(1,(1 + strlen(item)) * sizeof(char));
            (*outputString)[*outputStringLen] = strdup(item);
            *outputStringLen += 1;
        } else if (errno != 0) {
            perror("scanf:");
            break;
        } else if (ret == EOF) {
            break;
        } else {
            puts("No or partial match.\n");
            break;
        }
    }
    if (feof(fp)) {
        fclose(fp);
    }
    free(item);
}

ResponsesTypes getTreeFromString(char **stringArray, int stringArrayLen, Node **treeRoot) {

    printf("address of string array: %p\n", stringArray);

    if (stringArrayLen % 2 != 0) return INCORRECT_FILE_FORMAT_EXCEPTION;

    for (int i = 0; i < stringArrayLen; i+=2) {
        char *key = stringArray[i];
        char *value = stringArray[i + 1];
        ResponsesTypes response = addNode(treeRoot, key, value);
        if (isException(response)) throughException(response);
    }

    return SUCCESS_RESPONSE;
}










