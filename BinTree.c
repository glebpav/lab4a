#include <stdlib.h>
#include "ResponsesHandler.h"
#include "BinTree.h"
#include "string.h"
#include "stdio.h"

Node *initTree() {
    Node *treeRoot = calloc(1, sizeof(Node));
    treeRoot->key = NULL;
    treeRoot->data = NULL;
    treeRoot->left = NULL;
    treeRoot->right = NULL;
    treeRoot->parent = NULL;
    return treeRoot;
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
        if (comparisonResult > 0) selectedNode = selectedNode->left;
        else selectedNode = selectedNode->right;
    }

    selectedNode = initNode(key, value, previousNode);
    if (comparisonResult > 0) previousNode->left = selectedNode;
    else previousNode->right = selectedNode;

    return SUCCESS_RESPONSE;
}

ResponsesTypes deleteNode(Node **treeRoot) {

    return SUCCESS_RESPONSE;
}
