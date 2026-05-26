#include "../Include/Token.hpp"
#include "Lexer.hpp"
#include <vector>
#include <iostream>
#include <unordered_map>
#include <cctype>

Lexer::Lexer(const std::string& TextSource) : Pos(0), Line(1), Column(1), Source(TextSource) {};

char Lexer::Current() {
    if (Pos >= Source.size()) { 
        return '\0'; 
    } 
    return Source[Pos]; 
}
char Lexer::Peek(int Forward) { 
    if (Pos >= Source.size()) return '\0'; 
    if (Pos + Forward >= Source.size()) return '\0';
    return Source[Pos + Forward]; 
}
void Lexer::Advance() {
    if (Pos >= Source.size()) return;

    if (Source[Pos] == '\n') {
        Line++;
        Column = 1;
    } else if (Source[Pos] == '\r') {
        if (Pos + 1 < Source.size() && Source[Pos + 1] == '\n') {
            Pos++; 
            return;
        }
        Line++;
        Column = 1;
    } else {
        Column++;
    }
    Pos++;
}
void Lexer::SkipWhitespace() {
    while (Current() == ' ' || Current() == '\t' || Current() == '\n' || Current() == '\r') {
        Advance();
    }
}

void Lexer::SkipComment(bool IsMultiline) {
    Advance(); Advance();
    if (IsMultiline) {
        while (Current() != '\0') {
            if (Current() == '*' && Peek(1) == '/') {
                Advance(); Advance();
                return;
            }
            Advance();
        }
        Error("Unterminated multiline comment", Line, Column);
    } else {
        while (Current() != '\n' && Current() != '\0') {
            Advance();
        }
    }
}

Token Lexer::ReadIdentifierOrKeyword() {
    static const std::unordered_map<std::string, TokenType> Keywords = {
        {"int",     TokenType::INT      },
        {"float",   TokenType::FLOAT    },
        {"bool",    TokenType::BOOL     },
        {"char",    TokenType::CHAR     },
        {"void",    TokenType::VOID     },
        {"return",  TokenType::RETURN   },
        {"import",  TokenType::IMPORT   },
        {"ref",     TokenType::REF      },
        {"if",      TokenType::IF       },
        {"else",    TokenType::ELSE     },
        {"while",   TokenType::WHILE    },
        {"for",     TokenType::FOR      },
        {"function",TokenType::FUNCTION },
        {"as",      TokenType::AS       },
        {"not",     TokenType::NOT      },
        {"or",      TokenType::OR       },
        {"and",     TokenType::AND      },
        {"const",   TokenType::CONST    },

    };  
    std::string Word;
    int StartLine = Line; int StartColumn = Column;
    while (isalpha(Current()) || isdigit(Current()) || Current() == '_') {
        Word += Current(); Advance();
    }
    if (Word == "true" || Word == "false") {
    return Token{TokenType::BOOL_LIT, Word, StartLine, StartColumn};
    }

    auto IT = Keywords.find(Word);
    if (IT != Keywords.end()) {
        return Token{IT->second, Word, StartLine, StartColumn};
    }
    return Token{TokenType::IDENTIFIER, Word, StartLine, StartColumn};
}

Token Lexer::ReadString() {
    std::string Word;
    int StartLine = Line; int StartColumn = Column;
    Advance();
    while (Current() != '"' && Current() != '\0' && Current() != '\n') {
        if (Current() == '\\') {
            if (Peek(1) == 'n') {
                Word += '\n'; Advance(); Advance(); 
            } else if (Peek(1) == 't') {
                Word += '\t'; Advance(); Advance();
            } else if (Peek(1) == '"') {
                Word += '"'; Advance(); Advance();
            } else if (Peek(1) == '\'') {
                Word += '\''; Advance(); Advance();
            } else if (Peek(1) == '\\') {
                Word += '\\'; Advance(); Advance();
            } else {
                Error("Invaild Escape Character", StartLine, StartColumn);
            }
            continue;
        }
        Word += Current(); Advance();
    }
    if (Current() == '\n') {
        Error("Unterminated string, unexpected newline", StartLine, StartColumn);
    }
    if (Current() == '\0') {
        Error("Unterminated string", StartLine, StartColumn);
    }
    Advance();
    return Token{TokenType::STRING_LIT, Word, StartLine, StartColumn};
}

Token Lexer::ReadNumber() {
    std::string Number;
    int StartLine = Line; 
    int StartColumn = Column;

    while (isdigit(Current())) {
        Number += Current(); Advance(); 
    }

    if (Current() == '.') {
        if (isdigit(Peek(1))) {
            Number += '.'; Advance();
            while (isdigit(Current())) {
                Number += Current(); Advance();
            }
            if (Current() == '.') {
                Error("Malformed float literal, unexpected second '.'", StartLine, StartColumn);
            }
            if (isalpha(Current()) || Current() == '_') {
                int ErrorLine = Line;
                int ErrorColumn = Column;
                std::string FullInvalid = Number;
                while (isalnum(Current()) || Current() == '_' || Current() == '.') {
                    FullInvalid += Current();
                    Advance();
                }
                Error("Invalid numeric literal: '" + FullInvalid + "'", ErrorLine, ErrorColumn);
            }
            return {TokenType::FLOAT_LIT, Number, StartLine, StartColumn};
        } else {
            Error("Malformed float literal, trailing '.'", StartLine, StartColumn);
        }
    }

    if (isalpha(Current()) || Current() == '_') {
        int ErrorLine = Line;
        int ErrorColumn = Column;
        std::string FullInvalid = Number;
        while (isalnum(Current()) || Current() == '_' || Current() == '.') {
            FullInvalid += Current();
            Advance();
        }
        Error("Invalid numeric literal: '" + FullInvalid + "'", ErrorLine, ErrorColumn);
    }

    return {TokenType::INTEGER_LIT, Number, StartLine, StartColumn};
}

Token Lexer::ReadSymbol() {
    int StartLine = Line;
    int StartColumn = Column;
    char CurrentChar = Current();
    
    switch (CurrentChar) {
        case '+': Advance(); return {TokenType::PLUS, "+", StartLine, StartColumn};
        case '-': Advance(); return {TokenType::MINUS, "-", StartLine, StartColumn};
        case '*': Advance(); return {TokenType::STAR, "*", StartLine, StartColumn};
        case '/': Advance(); return {TokenType::SLASH, "/", StartLine, StartColumn};
        case '%': Advance(); return {TokenType::PERCENT, "%", StartLine, StartColumn};
        
        case '=': 
            if (Peek(1) == '=') {
                Advance(); Advance();
                return {TokenType::EQ, "==", StartLine, StartColumn};
            }
            Advance();
            return {TokenType::ASSIGN, "=", StartLine, StartColumn};
            
        case '!':
            if (Peek(1) == '=') {
                Advance(); Advance();
                return {TokenType::NEQ, "!=", StartLine, StartColumn};
            }
            Error("Unexpected '!', did you mean 'not'?", StartLine, StartColumn);
            break;
                    
        case '<': 
            if (Peek(1) == '=') {
                Advance(); Advance();
                return {TokenType::LTE, "<=", StartLine, StartColumn};
            }
            Advance();
            return {TokenType::LT, "<", StartLine, StartColumn};
            
        case '>': 
            if (Peek(1) == '=') {
                Advance(); Advance();
                return {TokenType::GTE, ">=", StartLine, StartColumn};
            }
            Advance();
            return {TokenType::GT, ">", StartLine, StartColumn};
            
        case '{': Advance(); return {TokenType::LBRACE, "{", StartLine, StartColumn};
        case '}': Advance(); return {TokenType::RBRACE, "}", StartLine, StartColumn};
        case '(': Advance(); return {TokenType::LPAREN, "(", StartLine, StartColumn};
        case ')': Advance(); return {TokenType::RPAREN, ")", StartLine, StartColumn};
        case '[': Advance(); return {TokenType::LBRACKET, "[", StartLine, StartColumn};
        case ']': Advance(); return {TokenType::RBRACKET, "]", StartLine, StartColumn};
        case ';': Advance(); return {TokenType::SEMICOLON, ";", StartLine, StartColumn};
        case ':': Advance(); return {TokenType::COLON, ":", StartLine, StartColumn};
        case ',': Advance(); return {TokenType::COMMA, ",", StartLine, StartColumn};
        case '.': Advance(); return {TokenType::DOT, ".", StartLine, StartColumn};
        
        default:
            Advance();
            Error("Unknown symbol: '" + std::string(1, CurrentChar) + "'", StartLine, StartColumn);
            break;
    }
}

std::string Lexer::GetLine(int LineNumber) {
    int Current = 1;
    std::string Line;
    for (char C : Source) {
        if (Current == LineNumber) {
            if (C == '\n') break;
            Line += C;
        }
        if (C == '\n') Current++;
    }
    return Line;
}

void Lexer::Error(const std::string& Message, int AtLine, int AtColumn) {
    std::string ErrorLine = GetLine(AtLine);
    std::string Caret(AtColumn - 1, ' ');
    Caret += '^';
    
    std::cerr   << "[Val/Lexer]: Error at line " << AtLine << ", column " << AtColumn << ":\n\n"
                << "    " << ErrorLine << "\n"
                << "    " << Caret << "\n"
                << "    " << Message << "\n";
    exit(1);
}

std::vector<Token> Lexer::Tokenize() {
    std::vector<Token> Tokens;
    while (Current() != '\0') {
        SkipWhitespace();
        if (Current() == '\0') break;
        
        // Single-line Comment
        if (Current() == '/' && Peek(1) == '/') { 
            SkipComment(false); 
            continue; 
        }
        // Muti-line Comment
        if (Current() == '/' && Peek(1) == '*') { 
            SkipComment(true);  
            continue; 
        }
        // String literal 
        if (Current() == '"') { 
            Tokens.push_back(ReadString()); 
            continue; 
        }
        // Number literal
        if (isdigit(Current())) { 
            Tokens.push_back(ReadNumber()); 
            continue; 
        }
        // Keyword or Identifier
        if (isalpha(Current()) || Current() == '_') { 
            Tokens.push_back(ReadIdentifierOrKeyword()); 
            continue; 
        }
        // Symbols
        Tokens.push_back(ReadSymbol()); 
        continue;
    }
    
    Tokens.push_back(Token{TokenType::END_OF_FILE, "", Line, Column});
    return Tokens;
}