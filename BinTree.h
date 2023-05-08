#ifndef LAB4A_BINTREE_H
#define LAB4A_BINTREE_H

#include "ResponsesHandler.h"
#include "MyVector.h"

typedef struct Node {
    char *key;
    char *data;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
} Node;

Node *initTree();
ResponsesTypes freeTree(Node **treeRoot);
Vector *getNode(Node **TreeRoot, char *requiredKey);
ResponsesTypes addNode(Node **treeRoot, char *key, char *value);
ResponsesTypes deleteNode(Node **treeRoot, char *deletingItemKey);
Vector *directBypass(Node *treeRoot);

#endif //LAB4A_BINTREE_H
