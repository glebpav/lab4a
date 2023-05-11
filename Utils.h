#ifndef LAB4A_UTILS_H
#define LAB4A_UTILS_H

#include "view/ResponsesHandler.h"
#include "model/MyVector.h"

ResponsesTypes getSaveIntValue(int *value, char *messageToUser);

ResponsesTypes getSaveStingValue(char **value, char *messageToUser);

int strcmpForSubStr(char *s1, char *s2);

Vector *getStringDifference(char *str1, char *str2);

#endif //LAB4A_UTILS_H
