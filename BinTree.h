#ifndef LAB4A_BINTREE_H
#define LAB4A_BINTREE_H

typedef struct Node {
    char *key;
    char *data;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
} Node;



#endif //LAB4A_BINTREE_H
