// Vector.c

#include "Vector.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

void Vector_Init(Vector* Array, uint32_t Capacity) 
{
    if (Capacity < 8) { Capacity = 8; }
    
    Array->Items = malloc(Capacity * sizeof(void*));

    if (Array->Items == NULL) 
    {
        fprintf(stderr, "[Vector]: Memory Allocation failed\n");
        exit(1);
    }
    
    Array->Count = 0;
    Array->Capacity = Capacity;
}

void Vector_Push(Vector* Array, void* Item) 
{

    if (Array->Count == Array->Capacity) 
    {

        if (Array->Capacity == 0) 
        {
            Array->Capacity = 8;
            Array->Items = malloc(8 * sizeof(void*));

            if (Array->Items == NULL) 
            {
                fprintf(stderr, "[Vector]: Memory Allocation failed\n");
                exit(1);
            } 
        } 
        else 
        {
            Array->Capacity = Array->Capacity * 2;
            Array->Items = realloc(Array->Items, Array->Capacity * sizeof(void*));

            if (Array->Items == NULL) 
            {
                fprintf(stderr, "[Vector]: Memory Allocation failed\n");
                exit(1);
            }
        }
    }

    Array->Items[Array->Count] = Item;
    Array->Count = Array->Count + 1;
};

void Vector_Free(Vector* Array) 
{
    if (Array->Items != NULL) {
        free(Array->Items);
    }

    Array->Items = NULL;
    Array->Count = 0;
    Array->Capacity = 0;
};

