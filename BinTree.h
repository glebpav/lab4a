#ifndef LAB4A_BINTREE_H
#define LAB4A_BINTREE_H

#include "ResponsesHandler.h"

typedef struct Node {
    char *key;
    char *data;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
} Node;

Node *initTree();
ResponsesTypes freeTree(Node **treeRoot);
ResponsesTypes addNode(Node **treeRoot, char *key, char *value);
ResponsesTypes deleteNode(Node **treeRoot);

#endif //LAB4A_BINTREE_H
