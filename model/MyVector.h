#ifndef LAB4A_MYVECTOR_H
#define LAB4A_MYVECTOR_H

typedef struct Vector {
    void **array;
    unsigned arrayLength;
    unsigned typeSize;
} Vector;

Vector initVector(int typeSize);

Vector *initVectorPtr(int typeSize);

void addItemToVector(Vector *vector, void *item);

void deleteItemFromVector(Vector *vector, int deletingItemIdx);

void setItemVector(Vector *vector, void *data);

void* getItemFromVector(Vector vector, int itemIdx);

void destroyVector(Vector *vector);

#endif //LAB4A_MYVECTOR_H
