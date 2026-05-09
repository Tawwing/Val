#include "../Include/Token.hpp"
#include "Lexer.hpp"
#include <vector>

Lexer::Lexer(const std::string& TextSource) : Pos(0), Line(1), Column(1), Source(TextSource) {};

char Lexer::Current()            { if (Pos >= Source.size()) return '\0'; return Source[Pos]; }
char Lexer::Peek(int Forward)    { if (Pos >= Source.size()) return '\0'; return Source[Pos + Forward]; }
void Lexer::Advance()            { if (Pos >= Source.size()) return; Pos++; }

void Lexer::SkipWhitespace() {
    while (Current() == ' ' || Current() == '\t' || Current() == '\n' || Current() == '\r') {
        if (Current() == '\n') {
            Line++; Column = 0;
        }
        else {
            Column++;
        }
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
            if (Current() == '\n') {
                Line++;
                Column = 1;
                Advance();
                continue;
            }
            Advance();
            Column++;
        }
    } else {
        while (Current() != '\n' && Current() != '\0') {
            Advance();
        }
        if (Current() == '\n') {
            Advance();
            Line++;
            Column = 1;
        }
    }
}

std::vector<Token> Lexer::Tokenize() {

}