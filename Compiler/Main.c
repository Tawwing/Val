// Main.c

#include <stdio.h>
#include <stdint.h>

#include "Compiler/Lib/Vector/Vector.h"


int main() {
    int a = 13;
    int b = 14;
    Vector v;
    Vector_Init(&v, 8);
    Vector_Push(&v, &a);
    Vector_Push(&v, &b);

    printf("%d\n", v.Capacity);
    printf("%d\n", *(int*)v.Items[0]);
    Vector_Free(&v);
    return 0;
}