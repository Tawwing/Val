// StringView.c

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "StringView.h"

void StringView_Print(StringView* View) 
{
    printf("%.*s", View->Length, View->Pointer);
}

bool StringView_Equals(StringView* View, const char* Str) 
{

    if ((strncmp(View->Pointer, Str, View->Length) == 0) && (strlen(Str) == View->Length)) 
    {
        return true;
    }

    return false;
}