#ifndef LAB4A_RESPONSESHANDLER_H
#define LAB4A_RESPONSESHANDLER_H

#include <stdbool.h>

typedef enum ResponsesTypes {
    NOT_INT_VALUE_EXCEPTION,
    INPUT_NOT_IN_RANGE_EXCEPTION,
    TABLE_OVERFLOW_EXCEPTION,
    NO_SUCH_FILE_EXCEPTION,
    INCORRECT_FILE_FORMAT_EXCEPTION,
    UNKNOWN_KEY_EXCEPTION,
    COMMON_EXCEPTION,
    FILE_EXCEPTION,
    EMPTY_FIELD_EXCEPTION,
    SUCCESS_RESPONSE,
    EXIT_RESPONSE
} ResponsesTypes;

bool isException(ResponsesTypes response);
char *getResponseMessage(ResponsesTypes responsesTypes);
void throughException(ResponsesTypes exceptions);
void printSuccessMessage(ResponsesTypes response);


#endif //LAB4A_RESPONSESHANDLER_H
