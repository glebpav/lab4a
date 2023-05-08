#include <stdlib.h>
#include <stdio.h>
#include "ResponsesHandler.h"
#include "BinTree.h"
#include "string.h"

Node *initTree() {
    Node *treeRoot = calloc(1, sizeof(Node));
    treeRoot->key = NULL;
    treeRoot->data = NULL;
    treeRoot->left = NULL;
    treeRoot->right = NULL;
    treeRoot->parent = NULL;
    return treeRoot;
}

Vector *getNode(Node **treeRoot, char *requiredKey) {

    Vector *foundNodeArray = initVectorPtr(sizeof(Node));
    Node *selectedNode = *treeRoot;
    int comparingResult;

    while (selectedNode != NULL) {
        comparingResult = strcmp(selectedNode->key, requiredKey);
        if (comparingResult == 0) {
            addItemToVector(foundNodeArray, selectedNode);
            selectedNode = selectedNode->right;
        } else if (comparingResult > 0) selectedNode = selectedNode->left;
        else selectedNode = selectedNode->right;
    }

    if (foundNodeArray->arrayLength == 0) return NULL;
    return foundNodeArray;

}

Node *initNode(char *key, char *value, Node *parent) {
    Node *newNode = calloc(1, sizeof(Node));

    newNode->key = strdup(key);
    newNode->data = strdup(value);
    newNode->parent = parent;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

ResponsesTypes freeTree(Node **treeRoot) {

    Vector *nodeArray = directBypass(*treeRoot);

    for (int i = 0; i < nodeArray->arrayLength; ++i) {
        free(getItemFromVector(*nodeArray, i));
    }
    destroyVector(nodeArray);

    return SUCCESS_RESPONSE;
}

ResponsesTypes addNode(Node **treeRoot, char *key, char *value) {

    if (key == NULL || value == NULL) return EMPTY_FIELD_EXCEPTION;

    Node *selectedNode = *treeRoot;
    Node *previousNode = NULL;
    int comparisonResult = 0;

    if (selectedNode == NULL) {
        selectedNode = initNode(key, value, NULL);
        *treeRoot = selectedNode;
        return SUCCESS_RESPONSE;
    }

    while (selectedNode != NULL) {
        previousNode = selectedNode;
        comparisonResult = strcmp(selectedNode->key, value);
        if (comparisonResult > 0) {
            if (selectedNode->right != NULL && strcmp(selectedNode->key, selectedNode->right->key) == 0)
                selectedNode = selectedNode->right;
            else
                selectedNode = selectedNode->left;
        } else if (comparisonResult < 0) selectedNode = selectedNode->right;
        else break;
    }

    selectedNode = initNode(key, value, previousNode);
    if (comparisonResult > 0) previousNode->left = selectedNode;
    else {
        selectedNode->right = previousNode->right;
        previousNode->right = selectedNode;
    }

    return SUCCESS_RESPONSE;
}

ResponsesTypes deleteNode(Node **treeRoot, char *deletingItemKey) {

    Vector *arrayOfDeletingNodes = getNode(treeRoot, deletingItemKey);

    if (arrayOfDeletingNodes->arrayLength != 1) {
        for (int i = 0; i < arrayOfDeletingNodes->arrayLength - 1; ++i) {

        }
    }

    return SUCCESS_RESPONSE;
}

void directByPassStep(Node *node, Vector *dataArray) {
    printf("size of array is: %d\n", dataArray->arrayLength);
    if (node == NULL) return;
    addItemToVector(dataArray, node);
    directByPassStep(node->left, dataArray);
    directByPassStep(node->right, dataArray);
}

Vector *directBypass(Node *treeRoot) {
    Vector *nodeArray = initVectorPtr(sizeof(Node));
    if (treeRoot == NULL) return NULL;
    directByPassStep(treeRoot, nodeArray);
    printf("out of here\n");
    return nodeArray;
}
