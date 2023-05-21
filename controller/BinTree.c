#include <stdlib.h>
#include <stdio.h>
#include "../view/ResponsesHandler.h"
#include "BinTree.h"
#include "string.h"
#include "../Utils.h"

Node *initTree() {
    Node *treeRoot = calloc(1, sizeof(Node));
    treeRoot->key = NULL;
    treeRoot->data = NULL;
    treeRoot->left = NULL;
    treeRoot->right = NULL;
    treeRoot->parent = NULL;
    return treeRoot;
}

Vector *getMinNodeArray(Node *treeRoot) {
    Vector *nodeArray = initVectorPtr(sizeof(Node));
    Node *minNode = treeRoot;
    while (minNode->left != NULL)
        minNode = minNode->left;

    Node *thisNode = treeRoot;
    while (thisNode != NULL) {
        if (strcmp(thisNode->key, minNode->key) == 0) {
            addItemToVector(nodeArray, thisNode);
        }
        thisNode = thisNode->left;
    }
    return nodeArray;
}

Vector *getMaxNodeArray(Node *treeRoot) {
    Vector *nodeArray = initVectorPtr(sizeof(Node));
    Node *maxNode = treeRoot;
    while (maxNode->right != NULL)
        maxNode = maxNode->right;

    Node *thisNode = treeRoot;
    while (thisNode != NULL) {
        if (strcmp(thisNode->key, maxNode->key) == 0) {
            addItemToVector(nodeArray, thisNode);
        }
        thisNode = thisNode->right;
    }
    return nodeArray;
}

Vector *getNode(Node **treeRoot, char *requiredKey, bool exactMatch) {

    Vector *foundNodeArray = initVectorPtr(sizeof(Node *));
    Node *selectedNode = *treeRoot;
    int comparingResult;

    while (selectedNode != NULL) {
        if (exactMatch) comparingResult = strcmp(selectedNode->key, requiredKey);
        else {
            comparingResult = strcmpForSubStr(selectedNode->key, requiredKey);
            if (comparingResult == 1) {
                comparingResult = strcmp(selectedNode->key, requiredKey);
            }
        }
        if (comparingResult == 0) {
            addItemToVector(foundNodeArray, &selectedNode);
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

void freeTree(Node *node) {
    if (node == NULL) return;

    freeTree(node->left);
    freeTree(node->right);

    free(node->data);
    free(node->key);
    free(node);
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

        while (selectedNode->right != NULL
               && strcmp(selectedNode->key, key) != 0
               && strcmp(selectedNode->key, selectedNode->right->key) == 0) {
            selectedNode = selectedNode->right;
        }

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

ResponsesTypes deleteNode(Node **deletingNodePtr) {

    Node *deletingNode = *deletingNodePtr;

    if (deletingNode->parent != NULL && strcmp(deletingNode->parent->key, deletingNode->key) == 0) {
        free(deletingNode->data);
        free(deletingNode->key);
        deletingNode->data = strdup(deletingNode->parent->data);
        deletingNode->key = strdup(deletingNode->parent->key);
        deleteNode(&(deletingNode->parent));
        return SUCCESS_RESPONSE;
    }

    // in case NO child nodes
    if (deletingNode->right == NULL && deletingNode->left == NULL && deletingNode->parent != NULL) {
        // printf("in case NO child nodes\n");
        // printf("set address to null: %p\n", deletingNode);
        // (*deletingNodePtr) = NULL;
        // free(deletingNode);
        int compRes = strcmp(deletingNode->parent->key, deletingNode->key);

        free(deletingNode->key);
        free(deletingNode->data);

        if (compRes < 0) {
            Node *bufNode = deletingNode->parent;
            free(bufNode->right);
            bufNode->right = NULL;
        } else {
            Node *bufNode = deletingNode->parent;
            free(bufNode->left);
            bufNode->left = NULL;
        }
    }

        // in case NO right child
    else if (deletingNode->right == NULL) {
        // printf("in case NO right child\n");
        free(deletingNode->key);
        deletingNode->key = deletingNode->left->key;
        free(deletingNode->data);
        deletingNode->data = deletingNode->left->data;
        Node *bufNode = deletingNode->right->right;
        free(deletingNode->left);
        deletingNode->left = bufNode;
        if (deletingNode->left != NULL) deletingNode->left->parent = deletingNode;
        deletingNode->right = deletingNode->left->right;
        if (deletingNode->right != NULL) deletingNode->right->parent = deletingNode;
    }

        // in case NO left child
    else if (deletingNode->left == NULL) {
        // printf("in case NO left child\n");
        free(deletingNode->key);
        deletingNode->key = deletingNode->right->key;
        free(deletingNode->data);
        deletingNode->data = deletingNode->right->data;
        deletingNode->left = deletingNode->right->left;
        if (deletingNode->left != NULL) deletingNode->right->parent = deletingNode;
        Node *bufNode = deletingNode->right->right;
        free(deletingNode->right);
        deletingNode->right = bufNode;
        if (deletingNode->right != NULL) deletingNode->right->parent = deletingNode;
    }

        // in case TWO children
    else {
        // printf("in case TWO children\n");
        // find min in right subTree
        Node **nodeSuccessorPtr = &(deletingNode->right);
        while ((*nodeSuccessorPtr)->left != NULL) {
            (*nodeSuccessorPtr) = (*nodeSuccessorPtr)->left;
        }
        // replace deleting node data
        size_t sizeOfKey = (1 + strlen((*nodeSuccessorPtr)->key)) * sizeof(char);
        size_t sizeOfData = (1 + strlen((*nodeSuccessorPtr)->data)) * sizeof(char);

        deletingNode->key = realloc(deletingNode->key, sizeOfKey);
        deletingNode->data = realloc(deletingNode->data, sizeOfData);
        memcpy(deletingNode->key, (*nodeSuccessorPtr)->key, sizeOfKey);
        memcpy(deletingNode->data, (*nodeSuccessorPtr)->data, sizeOfData);
        deleteNode(nodeSuccessorPtr);
    }

    return SUCCESS_RESPONSE;
}

void directByPassStep(Node *node, Vector *dataArray) {
    if (node == NULL) return;
    addItemToVector(dataArray, &node);
    directByPassStep(node->left, dataArray);
    directByPassStep(node->right, dataArray);
}

Vector *directBypass(Node *treeRoot) {
    Vector *nodeArray = initVectorPtr(sizeof(Node *));
    if (treeRoot == NULL) return NULL;
    directByPassStep(treeRoot, nodeArray);
    return nodeArray;
}
