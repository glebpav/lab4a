#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "CommandHelper.h"
#include "../Utils.h"
#include "../model/FileHelper.h"
#include "../model/GrpahVisHelper.h"

void printTreeLevel(Node *treeRoot, int level) {
    if (treeRoot != NULL) {
        printTreeLevel(treeRoot->left, level + 1);
        for (int i = 0; i < level; i++) printf("   ");
        // printf("%p; ", treeRoot);
        printf("%s\n", treeRoot->key);
        printTreeLevel(treeRoot->right, level + 1);
    }
}

ResponsesTypes addNewItem(Node **treeRoot) {
    char *newKey, *newValue;

    if (!getSaveStingValue(&newKey, "Please, input new KEY\n"))
        return EXIT_RESPONSE;
    if (!getSaveStingValue(&newValue, "Please, input new VALUE\n"))
        return EXIT_RESPONSE;

    clock_t startTime = clock();
    ResponsesTypes response = addNode(treeRoot, newKey, newValue);
    clock_t spendTime = (clock() - startTime) * 1000 / CLOCKS_PER_SEC;
    printf("Spend: %ld ms\n", spendTime);

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

    clock_t startTime = clock();
    Vector *arrayOfDeletingNodes = getNode(treeRoot, deletingNodeKey, true);
    clock_t spendTime = (clock() - startTime) * 1000 / CLOCKS_PER_SEC;
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

    startTime = clock();
    deleteNode(deletingItemPtr);
    spendTime += (clock() - startTime) * 1000 / CLOCKS_PER_SEC;
    printf("Spend: %ld ms\n", spendTime);

    destroyVector(arrayOfDeletingNodes);
    return SUCCESS_RESPONSE;
}

ResponsesTypes directBypassCommand(Node **treeRoot) {

    clock_t startTime = clock();
    Vector *nodeArray = directBypass(*treeRoot);
    clock_t spendTime = (clock() - startTime) * 1000 / CLOCKS_PER_SEC;

    if (nodeArray == NULL) printf("Tree is empty\n");
    else {
        printf("Direct bypass:\n");
        startTime = clock();
        for (int i = 0; i < nodeArray->arrayLength; ++i) {
            Node **node = getItemFromVector(*nodeArray, i);
            printf("key = %s; data = %s\n", (*node)->key, (*node)->data);
        }
        spendTime += (clock() - startTime) * 1000 / CLOCKS_PER_SEC;
        printf("Spend: %ld ms\n", spendTime);

        destroyVector(nodeArray);
    }

    return SUCCESS_RESPONSE;
}

ResponsesTypes directBypassSpecial(Node **treeRoot) {

    char *subStr;
    clock_t startTime = clock();
    Vector *nodeArray = directBypass(*treeRoot);
    clock_t spendTime = (clock() - startTime) * 1000 / CLOCKS_PER_SEC;

    if (nodeArray == NULL) {
        printf("Tree is empty\n");
        return SUCCESS_RESPONSE;
    }

    if (!getSaveStingValue(&subStr, "Please, input SUBSTR for key\n"))
        return EXIT_RESPONSE;

    startTime = clock();
    bool isAnyPrinted = false;
    for (int i = 0; i < nodeArray->arrayLength; ++i) {
        Node **checkingNode = getItemFromVector(*nodeArray, i);
        // printf("item %s: %d\n", (*checkingNode)->key, strcmpForSubStr(subStr, (*checkingNode)->key));
        if (strcmpForSubStr(subStr, (*checkingNode)->key) == 0) {
            if (isAnyPrinted == false) printf("Your special bypass:\n");
            printf("key = %s; data = %s\n", (*checkingNode)->key, (*checkingNode)->data);
            isAnyPrinted = true;
        }
    }
    spendTime += (clock() - startTime) * 1000 / CLOCKS_PER_SEC;

    if (isAnyPrinted == false) printf("Оooops... No items with <%s> sub string\n", subStr);

    printf("Spend: %ld ms\n", spendTime);
    free(subStr);
    destroyVector(nodeArray);

    return SUCCESS_RESPONSE;
}

ResponsesTypes searchItem(Node **treeRoot) {
    char *requiredKey;

    if (!getSaveStingValue(&requiredKey, "Please, input required KEY\n"))
        return EXIT_RESPONSE;

    clock_t startTime = clock();
    Vector *foundNodeArray = getNode(treeRoot, requiredKey, true);
    clock_t spendTime = (clock() - startTime) * 1000 / CLOCKS_PER_SEC;

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


    printf("Spend: %ld ms\n", spendTime);
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

    clock_t startTime = clock();
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

        /*printf("dif1: ");
        for (int i = 0; i < dif1->arrayLength; ++i) {
            int *q = getItemFromVector(*dif1, i);
            printf("%d, ", *q);
        }
        printf("\n");

        printf("dif2: ");
        for (int i = 0; i < dif1->arrayLength; ++i) {
            int *q = getItemFromVector(*dif2, i);
            printf("%d, ", *q);
        }
        printf("\n");*/


        int difIdx = 0;
        int finalDif = 0;
        while (dif1->arrayLength > difIdx && dif2->arrayLength > difIdx) {
            int *item1 = getItemFromVector(*dif1, difIdx);
            int *item2 = getItemFromVector(*dif2, difIdx);
            finalDif = abs(*item1) - abs(*item2);
            difIdx += 1;
            if (finalDif != 0) break;
        }

        // printf("final dif: %d\n", finalDif);

        if (finalDif > 0) {
            printingNodes = minNodeArray;
            destroyVector(maxNodeArray);
        } else if (finalDif < 0) {
            printingNodes = maxNodeArray;
            destroyVector(minNodeArray);
        } else {
            printingNodes = initVectorPtr(sizeof(Node));
            for (int i = 0; i < minNodeArray->arrayLength; ++i)
                addItemToVector(printingNodes, getItemFromVector(*minNodeArray, i));
            for (int i = 0; i < maxNodeArray->arrayLength; ++i)
                addItemToVector(printingNodes, getItemFromVector(*maxNodeArray, i));
            destroyVector(minNodeArray);
            destroyVector(maxNodeArray);
        }

        destroyVector(dif2);
        destroyVector(dif1);
    }
    clock_t spendTime = (clock() - startTime) * 1000 / CLOCKS_PER_SEC;

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
        destroyVector(printingNodes);
    } else throughException(UNKNOWN_KEY_EXCEPTION);


    printf("Spend: %ld ms\n", spendTime);
    free(requiredKey);
    printSuccessMessage(SUCCESS_RESPONSE);
    return SUCCESS_RESPONSE;
}

ResponsesTypes printTree(Node **treeRoot) {
    printTreeLevel(*treeRoot, 1);
    return SUCCESS_RESPONSE;
}

ResponsesTypes printTreeInGraphViz(Node **treeRoot) {

    if (treeRoot == NULL) {
        throughException(EMPTY_FIELD_EXCEPTION);
        return SUCCESS_RESPONSE;
    }

    FILE *fp;

    fp = fopen("files/treeDiagram.dot", "w+");
    if (fp == NULL) {
        throughException(FILE_EXCEPTION);
        return SUCCESS_RESPONSE;
    }
    printTreeGraphVis(*treeRoot, fp);
    fclose(fp);

    system("dot -Tpng files/treeDiagram.dot -o files/tree.png");
    // system();

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