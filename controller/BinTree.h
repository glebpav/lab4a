#ifndef LAB4A_BINTREE_H
#define LAB4A_BINTREE_H

#include "../view/ResponsesHandler.h"
#include "../model/MyVector.h"

typedef struct Node {
    char *key;
    char *data;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
} Node;

Node *initTree();
Vector *getMinNodeArray(Node *treeRoot);
Vector *getMaxNodeArray(Node *treeRoot);
void freeTree(Node *treeRoot);
Vector *getNode(Node **TreeRoot, char *requiredKey, bool exactMatch);
ResponsesTypes addNode(Node **treeRoot, char *key, char *value);
ResponsesTypes deleteNode(Node **deletingNodePtr);
Vector *directBypass(Node *treeRoot);

#endif //LAB4A_BINTREE_H
