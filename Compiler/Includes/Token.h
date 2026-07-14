// Token.h

#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
    // Specials
    SPE_EOF = 0, SPE_ERROR = 1,

} Val_TokenType;

typedef struct {
    Val_TokenType Type;
    const char* Value;
    int Line; int Column;
} Val_Token;

#endif 