#include <stdio.h>
#include "GrpahVisHelper.h"

int getNodeCount() {
    static int nodeCount = -1;
    nodeCount += 1;
    // printf("node idx: %d\n", nodeCount);
    return nodeCount;
}

void printNullNode(int nullCount, FILE *stream) {
    fprintf(stream, "   node%d [shape=point, label=\"<key>\"];\n", nullCount);
    // if (leftOrRight) fprintf(stream, "    node%d:left -> node%d:key;\n", nodeIdx, nullCount);
}

void printTreeGraphVisSubNode(Node *node, int nodeIdx, FILE *stream) {
    static int nullCount = 0;
    int thisNodeIdx = nodeIdx;
    int leftNodeIdx = getNodeCount();
    int rightNodeIdx = getNodeCount();

    fprintf(
            stream,
            "   node%d [shape=record, label=\"{<key>%s| %s |{<left>L|<right>R}}\"];\n",
            thisNodeIdx,
            node->key,
            node->data
    );

    if (node->left) {
        printTreeGraphVisSubNode(node->left, leftNodeIdx, stream);
    } else printNullNode(leftNodeIdx, stream);
    fprintf(stream, "   node%d:left -> node%d;\n", thisNodeIdx, leftNodeIdx);

    if (node->right) {
        printTreeGraphVisSubNode(node->right, rightNodeIdx, stream);
    } else printNullNode(rightNodeIdx, stream);
    fprintf(stream, "   node%d:right -> node%d;\n", thisNodeIdx, rightNodeIdx);
}

void printTreeGraphVis(Node *tree, FILE *stream) {


    fprintf(stream, "digraph {\n");
    fprintf(stream,
            "   node [style=rounded]\n");

    if (!tree) fprintf(stream, "\n");
    else if (!tree->right && !tree->left) fprintf(stream, "    %s;\n", tree->key);
    else printTreeGraphVisSubNode(tree, getNodeCount(), stream);

    fprintf(stream, "   label =\"Binary tree\n\n\";\n"
                    "   labelloc = top;\n"
                    "   labeljust = center;\n");

    fprintf(stream, "}\n");
}
