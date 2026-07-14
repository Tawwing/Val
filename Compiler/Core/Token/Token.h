// Token.h

#ifndef TOKEN_H
#define TOKEN_H

#include "Lib/StringView/StringView.h"

#include <stdint.h>

typedef enum {
    // Specials
    SPE_EOF = 0, SPE_ERROR = 1,
    
    // Literals
    LIT_CHAR,   LIT_INTEGER, LIT_FLOAT, 
    LIT_STRING, LIT_BOOLEAN, IDENTIFIER,

    // Operators 
    OP_PLUS, OP_MINUS,   // "+" | "-"
    OP_STAR, OP_MODULO,  // "*" | "%"
    OP_DIV,  OP_ASSIGN,  // "/" | "="

    // Comparison Operators 
    OP_EQ_EQ, OP_NOT_EQ, // "==" |  "!="    
    OP_LT,    OP_GT,     // "<"  |  ">"         
    OP_LT_EQ, OP_GT_EQ,  // "<=" |  ">="

    // Compound Assignment
    OP_PLUS_EQ,  OP_MINUS_EQ,   // "+=" | "-="
    OP_STAR_EQ,  OP_DIV_EQ,     // "*=" | "/="

    // Other Operators
    OP_DOT, OP_ARROW, // "." | "->"

    // Keywords - Types
    KEY_CHAR,  KEY_INT,     KEY_FLOAT, // "char"   | "int"    | "float"
    KEY_BOOL,  KEY_DOUBLE,  KEY_VOID,  // "bool"   | "double" | "void"
    KEY_SLICE, KEY_ARRAY,   KEY_PTR,   // "slice"  | "array"  | "ptr"
    KEY_REF,   KEY_BYTE,               // "ref"    | "byte" 
    
    // Keywords - Logical Operators
    KEY_AND, KEY_OR, KEY_NOT, // "and" | "or" | "not"

     // Keywords - Statements & Control Flow
    KEY_IF,     KEY_ELSE,    KEY_SWITCH,    KEY_MATCH,
    KEY_WHILE,  KEY_FOR,     KEY_BREAK,     KEY_CONTINUE,
    KEY_STRUCT, KEY_ENUM,    KEY_CLASS,     KEY_FUNC, 
    KEY_RETURN, KEY_IMPORT,  KEY_NAMESPACE, KEY_MODULE,
    KEY_PUBLIC, KEY_PRIVATE, KEY_EXTEND,    KEY_SELF,
    KEY_ADDR,   KEY_MOVE,

    // Keywords - Modifiers
    KEY_CONST, KEY_MUT,

    // Punctuation
    PUNC_BSLASH,                  // "\" 
    PUNC_LPAREN,   PUNC_RPAREN,   // "(" | ")" 
    PUNC_LBRACE,   PUNC_RBRACE,   // "{" | "}"
    PUNC_LBRACKET, PUNC_RBRACKET, // "[" | "]"
    PUNC_SEMI,     PUNC_COLON,    // ";" | ":"
    PUNC_COMMA,    PUNC_AT,       // "," | "@"

} Val_TokenType;

typedef struct {
    Val_TokenType Type;
    StringView Value;
    uint32_t Line; 
    uint32_t Column;
} Val_Token;

const char* Token_TypeToString(Val_TokenType Type);
void Token_Print(Val_Token* Token);

#endif 