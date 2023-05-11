#include "ResponsesHandler.h"
#include <stdlib.h>
#include <string.h>
#include "stdio.h"

char *getResponseMessage(ResponsesTypes responsesTypes) {
    switch (responsesTypes) {
        case NOT_INT_VALUE_EXCEPTION:
            return strdup("given input is not integer");
        case INPUT_NOT_IN_RANGE_EXCEPTION:
            return strdup("input value is not int given range");
        case TABLE_OVERFLOW_EXCEPTION:
            return strdup("table is overflow, clear it first");
        case NO_SUCH_FILE_EXCEPTION:
            return strdup("no such fileDescriptor");
        case INCORRECT_FILE_FORMAT_EXCEPTION:
            return strdup("file format is incorrect");
        case UNKNOWN_KEY_EXCEPTION:
            return strdup("given key or version doesn't exist");
        case EMPTY_FIELD_EXCEPTION:
            return strdup("passed field is empty");
        case COMMON_EXCEPTION:
            return strdup("stupid error");
        case SUCCESS_RESPONSE:
            return strdup("success!");
        case FILE_EXCEPTION:
            return strdup("error occurred with your file");
        default:
            return strdup("unknown message");
    }
}

void throughException(ResponsesTypes exceptionType) {
    char *errorMessage = getResponseMessage(exceptionType);
    printf("\033[1;31m");
    printf("ERROR: %s\n", errorMessage);
    printf("\033[0m");
    free(errorMessage);
}

void printSuccessMessage(ResponsesTypes response) {
    char *responseMessage = getResponseMessage(response);
    printf("\033[1;32m");
    printf("Message: %s\n", responseMessage);
    printf("\033[0m");
    free(responseMessage);
}

bool isException(ResponsesTypes response) {
    if (response == NOT_INT_VALUE_EXCEPTION
        || response == INPUT_NOT_IN_RANGE_EXCEPTION
        || response == TABLE_OVERFLOW_EXCEPTION
        || response == NO_SUCH_FILE_EXCEPTION
        || response == INCORRECT_FILE_FORMAT_EXCEPTION
        || response == UNKNOWN_KEY_EXCEPTION
        || response == FILE_EXCEPTION)
        return true;
    return false;
}