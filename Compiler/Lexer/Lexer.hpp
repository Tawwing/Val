#pragma once
#include <string>
#include <vector>
#include "../Include/Token.hpp"

class Lexer {
public:
    Lexer(const std::string& source);
    std::vector<Token> Tokenize();

private:
    std::string Source;
    int Pos; int Line; int Column;

    char Current(); char Peek(int Forward);
    void Advance();

    void SkipWhitespace();
    void SkipComment(bool IsMultiline);

    Token ReadString();
    Token ReadChar();
    Token ReadNumber();
    Token ReadIdentifierOrKeyword();
    Token ReadSymbol();

    std::string GetLine(int LineNumber);
    [[noreturn]] void Error(const std::string& Message, int AtLine, int AtColumn);
};