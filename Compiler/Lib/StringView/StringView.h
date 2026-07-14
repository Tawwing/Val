// StringView.h

#include <stdbool.h>

#ifndef STRINGVIEW_H
#define STRINGVIEW_H

typedef struct {
    const char* Pointer;
    unsigned int Length;
} StringView;

void StringView_Print(StringView* sv);
bool StringView_Equals(StringView* sv, const char* str);

#endif