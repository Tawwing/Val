#include <stdio.h>

#include "Lib/Vector/Vector.h"


int main() {
    int a = 10;
    Vector v;
    Vector_Init(&v, 126);
    Vector_Push(&v, &a);

    printf("%d\n", *(int*)v.Items[0]);
    Vector_Free(&v);
    return 0;
}