// Vector.h 

#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include <stdint.h>

typedef struct {
    void** Items;
    uint32_t Count;
    uint32_t Capacity;
} Vector;

void Vector_Init(Vector* Array, uint32_t Capacity);
void Vector_Push(Vector* Array, void* Item);
void Vector_Free(Vector* Array);

#endif 