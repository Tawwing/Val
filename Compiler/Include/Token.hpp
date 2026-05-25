#pragma once
#include <string>

enum class TokenType {
    // Literals
    INTEGER_LIT, FLOAT_LIT, STRING_LIT, IDENTIFIER,
    BOOL_LIT,
    
    // Keywords - Types
    INT, FLOAT, BOOL, CHAR, VOID,

    // Keywords - General
    FUNCTION, RETURN, IMPORT, AS, NOT,
    REF, MUT, IF, ELSE, WHILE, FOR, OR, AND,

    // Symbols
    PLUS, MINUS, STAR, SLASH, PERCENT,
    ASSIGN, EQ, NEQ,
    LT, GT, LTE, GTE,
    LBRACE, RBRACE,
    LPAREN, RPAREN,
    LBRACKET, RBRACKET,
    SEMICOLON, COLON, COMMA, DOT,

    // Special
    END_OF_FILE
};

struct Token {
    TokenType Type;
    std::string Value;
    int Line;
    int Column;
};