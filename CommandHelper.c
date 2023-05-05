#include <stdlib.h>
#include <stdio.h>
#include "CommandHelper.h"
#include "Utils.h"

ResponsesTypes addNewItem(Node **treeRoot) {
    char *newKey, *newValue;

    if (!getSaveStingValue(&newKey, "Please, input new KEY\n"))
        return exitProgram(treeRoot);
    if (!getSaveStingValue(&newValue, "Please, input new VALUE\n"))
        return exitProgram(treeRoot);

    ResponsesTypes response = addNode(treeRoot, newKey, newValue);

    if (isException(response)) throughException(response);
    else printSuccessMessage(response);

    free(newKey);
    free(newValue);

    return SUCCESS_RESPONSE;
}

ResponsesTypes deleteItem(Node **treeRoot) {
    return SUCCESS_RESPONSE;
}

ResponsesTypes directBypass(Node **treeRoot) {
    return SUCCESS_RESPONSE;
}

ResponsesTypes directBypassSpecial(Node **treeRoot) {
    return SUCCESS_RESPONSE;
}

ResponsesTypes searchItem(Node **treeRoot) {
    return SUCCESS_RESPONSE;
}

ResponsesTypes searchItemSpecial(Node **treeRoot) {
    return SUCCESS_RESPONSE;
}

void printTreeLevel(Node *treeRoot, int level) {
    if (treeRoot) {
        printTreeLevel(treeRoot->left, level + 1);
        for (int i = 0; i < level; i++) printf("   ");
        printf("%s\n", treeRoot->key);
        printTreeLevel(treeRoot->right, level + 1);
    }
}

ResponsesTypes printTree(Node **treeRoot) {
    printTreeLevel(*treeRoot, 1);
    return SUCCESS_RESPONSE;
}

ResponsesTypes readTreeFromFile(Node **treeRoot) {
    return SUCCESS_RESPONSE;
}

ResponsesTypes exitProgram(Node **treeRoot) {

    return EXIT_RESPONSE;
}
