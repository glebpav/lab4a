#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CommandHelper.h"
#include "../Utils.h"
#include "../model/FileHelper.h"

ResponsesTypes addNewItem(Node **treeRoot) {
    char *newKey, *newValue;

    if (!getSaveStingValue(&newKey, "Please, input new KEY\n"))
        return EXIT_RESPONSE;
    if (!getSaveStingValue(&newValue, "Please, input new VALUE\n"))
        return EXIT_RESPONSE;

    ResponsesTypes response = addNode(treeRoot, newKey, newValue);

    if (isException(response)) throughException(response);
    else printSuccessMessage(response);

    free(newKey);
    free(newValue);

    return SUCCESS_RESPONSE;
}

ResponsesTypes deleteItem(Node **treeRoot) {

    char *deletingNodeKey;
    if (!getSaveStingValue(&deletingNodeKey, "Please, input KEY of deleting Node\n"))
        return EXIT_RESPONSE;

    Vector *arrayOfDeletingNodes = getNode(treeRoot, deletingNodeKey);
    Node **deletingItemPtr = NULL;

    if (arrayOfDeletingNodes == NULL) {
        throughException(UNKNOWN_KEY_EXCEPTION);
        return SUCCESS_RESPONSE;
    }
    if (arrayOfDeletingNodes->arrayLength != 1) {
        int groupItemIdx;
        if (!getSaveIntValue(&groupItemIdx, "Please, input IDX of deleting Item\n"))
            return EXIT_RESPONSE;
        if (groupItemIdx < 0 || groupItemIdx >= arrayOfDeletingNodes->arrayLength){
            throughException(INPUT_NOT_IN_RANGE_EXCEPTION);
            return SUCCESS_RESPONSE;
        }

        deletingItemPtr = getItemFromVector(*arrayOfDeletingNodes, groupItemIdx);
    } else deletingItemPtr = getItemFromVector(*arrayOfDeletingNodes, 0);

    deleteNode(deletingItemPtr);

    destroyVector(arrayOfDeletingNodes);
    return SUCCESS_RESPONSE;
}

ResponsesTypes directBypassCommand(Node **treeRoot) {

    Vector *nodeArray = directBypass(*treeRoot);

    if (nodeArray == NULL) printf("Tree is empty\n");
    else {
        printf("Direct bypass:\n");
        for (int i = 0; i < nodeArray->arrayLength; ++i) {
            Node **node = getItemFromVector(*nodeArray, i);
            printf("key = %s; data = %s\n", (*node)->key, (*node)->data);
        }
        destroyVector(nodeArray);
    }

    return SUCCESS_RESPONSE;
}

ResponsesTypes directBypassSpecial(Node **treeRoot) {
    return SUCCESS_RESPONSE;
}

ResponsesTypes searchItem(Node **treeRoot) {

    char *requiredKey;

    if (!getSaveStingValue(&requiredKey, "Please, input required KEY\n"))
        return EXIT_RESPONSE;

    Vector *foundNodeArray = getNode(treeRoot, requiredKey);

    if (foundNodeArray != NULL) {
        if (foundNodeArray->arrayLength == 1) {
            Node **node = getItemFromVector(*foundNodeArray, 0);
            printf("key = %s  data = %s\n", (*node)->key, (*node)->data);
        } else {
            printf("key = %s  data:[ ", requiredKey);
            for (int i = 0; i < foundNodeArray->arrayLength; ++i) {
                Node **node = getItemFromVector(*foundNodeArray, i);
                printf("%s, ", (*node)->data);
            }
            printf("]\n");
        }
        printSuccessMessage(SUCCESS_RESPONSE);
        destroyVector(foundNodeArray);
    } else {
        throughException(UNKNOWN_KEY_EXCEPTION);
    }
    free(requiredKey);
    return SUCCESS_RESPONSE;
}

ResponsesTypes searchItemSpecial(Node **treeRoot) {
    return SUCCESS_RESPONSE;
}

void printTreeLevel(Node *treeRoot, int level) {
    if (treeRoot != NULL) {
        printTreeLevel(treeRoot->left, level + 1);
        for (int i = 0; i < level; i++) printf("   ");
        // printf("%p; ", treeRoot);
        printf("%s\n", treeRoot->key);
        printTreeLevel(treeRoot->right, level + 1);
    }
}

ResponsesTypes printTree(Node **treeRoot) {
    printTreeLevel(*treeRoot, 1);
    return SUCCESS_RESPONSE;
}

ResponsesTypes readTreeFromFile(Node **treeRoot) {

    char *fileName;
    int stringArrayLen = 0;
    char **stringArray = NULL;
    ResponsesTypes response;

    response = getSaveStingValue(&fileName, "Input name of file\n");
    if (isException(response)) {
        throughException(response);
        return response;
    }

    response = readFile(fileName, &stringArray, &stringArrayLen);
    free(fileName);
    if (isException(response)) {
        throughException(response);
        return SUCCESS_RESPONSE;
    }

    response = getTreeFromString(stringArray, stringArrayLen, treeRoot);

    for (int i = 0; i < stringArrayLen; ++i) free(stringArray[i]);
    free(stringArray);

    if (isException(response)) throughException(response);

    return SUCCESS_RESPONSE;
}

ResponsesTypes exitProgram(Node **treeRoot) {
    return EXIT_RESPONSE;
}