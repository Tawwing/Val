// Vector.h 

#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>

typedef struct {
    void** Items;
    int Count;
    int Capacity;
} Vector;

void Vector_Init(Vector* Array, int Capacity);
void Vector_Push(Vector* Array, void* Item);
void Vector_Free(Vector* Array);

#endif 