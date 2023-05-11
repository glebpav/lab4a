#include <stdio.h>
#include "MyVector.h"
#include "stdlib.h"
#include "string.h"


Vector initVector(int typeSize) {
    Vector vector = {.array = NULL, .arrayLength = 0, .typeSize=typeSize};
    return vector;
}

Vector *initVectorPtr(int typeSize) {
    Vector *vector = calloc(1, sizeof(Vector));
    vector->typeSize = typeSize;
    return vector;
}

void addItemToVector(Vector *vector, void *item) {
    vector->arrayLength += 1;
    vector->array = realloc(vector->array, sizeof(void *) * vector->arrayLength);
    vector->array[vector->arrayLength - 1] = calloc(1, vector->typeSize);
    memcpy(vector->array[vector->arrayLength - 1], item, vector->typeSize);
}

void deleteItemFromVector(Vector *vector, int deletingItemIdx) {
    if (vector->arrayLength <= 0) return;
    vector->arrayLength -= 1;

    for (int i = deletingItemIdx; i < vector->arrayLength; ++i)
        vector->array[i] = vector->array[i + 1];

    vector->array = realloc(vector->array, sizeof(void *) * vector->arrayLength);
}

void setItemVector(Vector *vector, void *data){

}

void *getItemFromVector(Vector vector, int itemIdx) {
    if (itemIdx >= vector.arrayLength || itemIdx < 0) return NULL;
    return vector.array[itemIdx];
}

void destroyVector(Vector *vector) {
    for (int i = 0; i < vector->arrayLength; ++i)
        free(vector->array[i]);

    vector->arrayLength = 0;
    free(vector->array);
    free(vector);
}