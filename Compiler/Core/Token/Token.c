// Token.c
#include "Token.h"

#include <stdio.h>

static const char* Token_Names[] = {
    // Specials
    [SPE_EOF]   = "EOF",
    [SPE_ERROR] = "ERROR",

    // Literals
    [LIT_CHAR]    = "LIT_CHAR",
    [LIT_INTEGER] = "LIT_INTEGER",
    [LIT_FLOAT]   = "LIT_FLOAT",
    [LIT_STRING]  = "LIT_STRING",
    [LIT_BOOLEAN] = "LIT_BOOLEAN",
    [IDENTIFIER]  = "IDENTIFIER",

    // Operators
    [OP_PLUS]   = "OP_PLUS",   [OP_MINUS]  = "OP_MINUS",
    [OP_STAR]   = "OP_STAR",   [OP_MODULO] = "OP_MODULO",
    [OP_DIV]    = "OP_DIV",    [OP_ASSIGN] = "OP_ASSIGN",

    // Comparison Operators 
    [OP_EQ_EQ]  = "OP_EQ_EQ",  [OP_NOT_EQ] = "OP_NOT_EQ",
    [OP_LT]     = "OP_LT",     [OP_GT]     = "OP_GT",
    [OP_LT_EQ]  = "OP_LT_EQ",  [OP_GT_EQ]  = "OP_GT_EQ",

    // Compound Assignment
    [OP_PLUS_EQ]  = "OP_PLUS_EQ",  [OP_MINUS_EQ] = "OP_MINUS_EQ",
    [OP_STAR_EQ]  = "OP_STAR_EQ",  [OP_DIV_EQ]   = "OP_DIV_EQ",

    // Other Operators
    [OP_DOT]   = "OP_DOT",   [OP_ARROW] = "OP_ARROW",

    // Keywords - Types
    [KEY_CHAR]  = "KEY_CHAR",  [KEY_INT]    = "KEY_INT",    [KEY_FLOAT]  = "KEY_FLOAT",
    [KEY_BOOL]  = "KEY_BOOL",  [KEY_DOUBLE] = "KEY_DOUBLE", [KEY_VOID]   = "KEY_VOID",
    [KEY_SLICE] = "KEY_SLICE", [KEY_ARRAY]  = "KEY_ARRAY",  [KEY_PTR]    = "KEY_PTR",
    [KEY_REF]   = "KEY_REF",   [KEY_BYTE]   = "KEY_BYTE",
    
    // Keywords - Logical Operators
    [KEY_AND] = "KEY_AND", [KEY_OR] = "KEY_OR", [KEY_NOT] = "KEY_NOT",

    // Keywords - Statements & Control Flow
    [KEY_IF]        = "KEY_IF",        [KEY_ELSE]     = "KEY_ELSE",     [KEY_SWITCH] = "KEY_SWITCH", [KEY_MATCH] = "KEY_MATCH",
    [KEY_WHILE]     = "KEY_WHILE",     [KEY_FOR]      = "KEY_FOR",      [KEY_BREAK]  = "KEY_BREAK",  [KEY_CONTINUE] = "KEY_CONTINUE",
    [KEY_STRUCT]    = "KEY_STRUCT",    [KEY_ENUM]     = "KEY_ENUM",     [KEY_CLASS]  = "KEY_CLASS",  [KEY_FUNC] = "KEY_FUNC", 
    [KEY_RETURN]    = "KEY_RETURN",    [KEY_IMPORT]   = "KEY_IMPORT",   [KEY_NAMESPACE] = "KEY_NAMESPACE", [KEY_MODULE] = "KEY_MODULE",
    [KEY_PUBLIC]    = "KEY_PUBLIC",    [KEY_PRIVATE]  = "KEY_PRIVATE",  [KEY_EXTEND] = "KEY_EXTEND",  [KEY_SELF] = "KEY_SELF",
    [KEY_ADDR]      = "KEY_ADDR",      [KEY_MOVE]     = "KEY_MOVE",

    // Keywords - Modifiers
    [KEY_CONST] = "KEY_CONST", [KEY_MUT] = "KEY_MUT",

    // Punctuation
    [PUNC_BSLASH]   = "PUNC_BSLASH",
    [PUNC_LPAREN]   = "PUNC_LPAREN",   [PUNC_RPAREN]   = "PUNC_RPAREN", 
    [PUNC_LBRACE]   = "PUNC_LBRACE",   [PUNC_RBRACE]   = "PUNC_RBRACE",
    [PUNC_LBRACKET] = "PUNC_LBRACKET", [PUNC_RBRACKET] = "PUNC_RBRACKET",
    [PUNC_SEMI]     = "PUNC_SEMI",     [PUNC_COLON]    = "PUNC_COLON",
    [PUNC_COMMA]    = "PUNC_COMMA",    [PUNC_AT]       = "PUNC_AT",
};

const char* Token_TypeToString(Val_TokenType Type) {
    return Token_Names[Type];
}

void Token_Print(Val_Token* Token) {
    printf("Token { Type: %s, Value: ", Token_TypeToString(Token->Type));
    StringView_Print(&Token->Value);
    printf(", Line: %u, Col: %u }\n", Token->Line, Token->Column);
}