#pragma once
#include <string>

enum class TokenType {
    // Literals
    CHAR_LIT, INTEGER_LIT, FLOAT_LIT, STRING_LIT, BOOL_LIT, IDENTIFIER,
    
    // Keywords - Types
    INT, FLOAT, BOOL, CHAR, VOID,

    // Keywords - General
    FUNCTION, RETURN, IMPORT, AS, NOT, CONST,
    REF, IF, ELSE, WHILE, FOR, OR, AND,

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

std::string TokenTypeToString(TokenType Type);

struct Token {
    TokenType Type;
    std::string Value;
    int Line;
    int Column;
    std::string ToString() {
        return TokenTypeToString(Type);
    }
};

inline std::string TokenTypeToString(TokenType Type) {
    switch (Type) {
        // Literals
        case TokenType::INTEGER_LIT: return "INTEGER_LIT";
        case TokenType::FLOAT_LIT:   return "FLOAT_LIT";
        case TokenType::STRING_LIT:  return "STRING_LIT";
        case TokenType::BOOL_LIT:    return "BOOL_LIT";
        case TokenType::CHAR_LIT:    return "CHAR_LIT";
        case TokenType::IDENTIFIER:  return "IDENTIFIER";
        
        // Keywords - Types
        case TokenType::INT:   return "INT";
        case TokenType::FLOAT: return "FLOAT";
        case TokenType::BOOL:  return "BOOL";
        case TokenType::CHAR:  return "CHAR";
        case TokenType::VOID:  return "VOID";
        
        // Keywords - General
        case TokenType::FUNCTION: return "FUNCTION";
        case TokenType::RETURN:   return "RETURN";
        case TokenType::IMPORT:   return "IMPORT";
        case TokenType::AS:       return "AS";
        case TokenType::NOT:      return "NOT";
        case TokenType::REF:      return "REF";
        case TokenType::IF:       return "IF";
        case TokenType::ELSE:     return "ELSE";
        case TokenType::WHILE:    return "WHILE";
        case TokenType::FOR:      return "FOR";
        case TokenType::OR:       return "OR";
        case TokenType::AND:      return "AND";
        case TokenType::CONST:    return "CONST";
        
        // Symbols
        case TokenType::PLUS:     return "PLUS";
        case TokenType::MINUS:     return "MINUS";
        case TokenType::STAR:      return "STAR";
        case TokenType::SLASH:     return "SLASH";
        case TokenType::PERCENT:   return "PERCENT";
        case TokenType::ASSIGN:    return "ASSIGN";
        case TokenType::EQ:        return "EQ";
        case TokenType::NEQ:       return "NEQ";
        case TokenType::LT:        return "LT";
        case TokenType::GT:        return "GT";
        case TokenType::LTE:       return "LTE";
        case TokenType::GTE:       return "GTE";
        case TokenType::LBRACE:    return "LBRACE";
        case TokenType::RBRACE:    return "RBRACE";
        case TokenType::LPAREN:    return "LPAREN";
        case TokenType::RPAREN:    return "RPAREN";
        case TokenType::LBRACKET:  return "LBRACKET";
        case TokenType::RBRACKET:  return "RBRACKET";
        case TokenType::SEMICOLON: return "SEMICOLON";
        case TokenType::COLON:     return "COLON";
        case TokenType::COMMA:     return "COMMA";
        case TokenType::DOT:       return "DOT";
        
        // Special
        case TokenType::END_OF_FILE: return "END_OF_FILE";
        
        default: return "UNKNOWN";
    }
}