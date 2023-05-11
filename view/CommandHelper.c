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

    Vector *arrayOfDeletingNodes = getNode(treeRoot, deletingNodeKey, true);
    free(deletingNodeKey);
    Node **deletingItemPtr = NULL;

    if (arrayOfDeletingNodes == NULL) {
        throughException(UNKNOWN_KEY_EXCEPTION);
        return SUCCESS_RESPONSE;
    }
    if (arrayOfDeletingNodes->arrayLength != 1) {
        int groupItemIdx;
        if (!getSaveIntValue(&groupItemIdx, "Please, input IDX of deleting Item\n")) {
            destroyVector(arrayOfDeletingNodes);
            return EXIT_RESPONSE;
        }
        while (groupItemIdx < 0 || groupItemIdx >= arrayOfDeletingNodes->arrayLength) {
            throughException(INPUT_NOT_IN_RANGE_EXCEPTION);
            if (!getSaveIntValue(&groupItemIdx, "Please, input IDX of deleting Item\n")) {
                destroyVector(arrayOfDeletingNodes);
                return EXIT_RESPONSE;
            }
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

    char *subStr;

    if (!getSaveStingValue(&subStr, "Please, input SUBSTR for key\n"))
        return EXIT_RESPONSE;

    return SUCCESS_RESPONSE;
}

ResponsesTypes searchItem(Node **treeRoot) {
    char *requiredKey;

    if (!getSaveStingValue(&requiredKey, "Please, input required KEY\n"))
        return EXIT_RESPONSE;

    Vector *foundNodeArray = getNode(treeRoot, requiredKey, true);

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
    char *requiredKey;

    if (!getSaveStingValue(&requiredKey, "Please, input required KEY\n"))
        return EXIT_RESPONSE;

    if (treeRoot == NULL || *treeRoot == NULL) {
        throughException(EMPTY_FIELD_EXCEPTION);
        return SUCCESS_RESPONSE;
    }

    Vector *maxNodeArray = getMaxNodeArray(*treeRoot);
    Vector *minNodeArray = getMinNodeArray(*treeRoot);
    Vector *printingNodes = NULL;

    if (maxNodeArray == NULL && minNodeArray == NULL) {
        throughException(COMMON_EXCEPTION);
        destroyVector(maxNodeArray);
        destroyVector(minNodeArray);
        free(requiredKey);
        return SUCCESS_RESPONSE;
    } else if (maxNodeArray == NULL) printingNodes = minNodeArray;
    else if (minNodeArray == NULL) printingNodes = maxNodeArray;
    else {
        Node *nodeMin = getItemFromVector(*minNodeArray, 0);
        Node *nodeMax = getItemFromVector(*maxNodeArray, 0);
        Vector *dif1 = getStringDifference(requiredKey, nodeMin->key);
        Vector *dif2 = getStringDifference(requiredKey, nodeMax->key);

        int difIdx = 0;
        int finalDif = 0;
        while (dif1->arrayLength < difIdx && dif2->arrayLength < difIdx) {
            int *item1 = getItemFromVector(*dif1, difIdx);
            int *item2 = getItemFromVector(*dif2, difIdx);
            finalDif = *item1 - *item2;
            difIdx += 1;
            if (finalDif != 0) break;
        }

        if (finalDif > 0) {
            printingNodes = minNodeArray;
            destroyVector(maxNodeArray);
        } else {
            printingNodes = maxNodeArray;
            destroyVector(minNodeArray);
        }

        destroyVector(dif2);
        destroyVector(dif1);
    }

    if (printingNodes != NULL) {
        if (printingNodes->arrayLength == 1) {
            Node *node = getItemFromVector(*printingNodes, 0);
            printf("The further Node is:\n");
            printf("key = %s  data = %s\n", node->key, node->data);
        } else {
            printf("The further Nodes are:\n");
            printf("key = %s  data: [ ", requiredKey);
            for (int i = 0; i < printingNodes->arrayLength; ++i) {
                Node *node = getItemFromVector(*printingNodes, i);
                printf("%s; ", node->data);
            }
            printf("]\n");
        }
        printSuccessMessage(SUCCESS_RESPONSE);
        destroyVector(printingNodes);
    } else throughException(UNKNOWN_KEY_EXCEPTION);

    free(requiredKey);
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

    response = getSaveStingValue(&fileName, "Please, input file NAME\n");
    if (fileName == NULL) return SUCCESS_RESPONSE;

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