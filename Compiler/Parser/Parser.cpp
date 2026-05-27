#include <memory>
#include <vector>
#include <iostream>
#include "./Parser.hpp"
#include "../Include/Token.hpp"
#include "../Include/AST.hpp"

// Constructor
Parser::Parser(std::vector<Token> Tokens): Tokens(std::move(Tokens)) , Pos(0){};

// Helpers
Token Parser::Current() {
    if (Pos >= Tokens.size()) {
        return Token{TokenType::END_OF_FILE, "", 0, 0};
    }
    return Tokens[Pos];
}

Token Parser::Peek(int Forward) {
    if (Pos >= Tokens.size() || Pos + Forward >= Tokens.size()) { 
        return Token{TokenType::END_OF_FILE, "", 0, 0};
    }
    return Tokens[Pos + Forward];
}

void Parser::Advance() {
    if (Pos >= Tokens.size()) { return; }
    else { Pos++; }
}

bool Parser::Check(TokenType Type) {
    return Current().Type == Type;
}

Token Parser::Expect(TokenType Type, const std::string& Message) {
    if (Check(Type)) {
        Token T = Current();
        Advance();
        return T;
    } else {
        Error("Expect " + TokenTypeToString(Type) + " but got " + Current().ToString(),
              Current().Line, Current().Column);
    }
}

void Parser::Error(const std::string& Message, int AtLine, int AtColumn) {
    std::string Caret(AtColumn - 1, ' ');
    Caret += '^';
    
    std::cerr   << "[Val/Parser]: Error at line " << AtLine << ", column " << AtColumn << ":\n\n"
                << "    " << Message << "\n";
    exit(1);
}

// Statements 
std::unique_ptr<Stmt> Parser::ParseImport() {
    Expect(TokenType::IMPORT, "Expected 'import' Keyword");
    Expect(TokenType::LT, "Expected '<' after 'import'");
    Token Identifier = Expect(TokenType::IDENTIFIER, "Expected 'Identifier' after '<'");
    Expect(TokenType::GT, "Expeceted '>' after " + Identifier.Value);

    return std::make_unique<Import>(Identifier.Value);
}

std::unique_ptr<Stmt> Parser::ParseFunctionDecl() {
    Expect(TokenType::FUNCTION, "Expected 'function' Keyword");
    Token Identifier = Expect(TokenType::IDENTIFIER, "Expected 'Identifier' after 'function'");
    Expect(TokenType::LPAREN, "Expected '(' symbol after " + Identifier.Value);

    std::vector<Parameter> Parameters;


    Expect(TokenType::RPAREN, "Expected ')' to close up '('");
    Expect(TokenType::COLON, "Expected ':' to defind a return type");
    if (IsDatatype() || Current().Type == TokenType::IDENTIFIER){
        std::unique_ptr<FunctionDecl> Node = std::make_unique<FunctionDecl>();
        Node->Name = Identifier.Value;
        Node->ReturnType = Current(); Advance();

        //TODO: Check if there is a body, or just a function declarctions
        // If body then, collect stmt 
        // else, return. 
        return Node;
    } else {
        Error("ReturnType must be a type or an identifier", Current().Line, Current().Column);
    }
}

std::vector<std::unique_ptr<Stmt>> Parser::Parse() {
    std::vector<std::unique_ptr<Stmt>> AST;
    while (Current().Type != TokenType::END_OF_FILE) {
        if (Check(TokenType::IMPORT)) {
            AST.push_back(ParseImport()); continue;
        } else if (Check(TokenType::FUNCTION)) {
            AST.push_back(ParseFunctionDecl()); continue;
        } else {
            Error("Unknown Token to procress", Current().Line, Current().Column);
        }
    }
    return AST; 
}

// Extra
std::unique_ptr<Parameter> Parser::ParseParam() {
    std::unique_ptr<Parameter> Node = std::make_unique<Parameter>();
    if (IsDatatype() || Current().Type == TokenType::CONST || Current().Type == TokenType::IDENTIFIER ) {
        if (Current().Type == TokenType::CONST) {
            Node->IsConst = true;
            Advance();
        } else {
            Node->IsConst = false;
        }
        Node->Type = Current(); Advance();
        Node->Name = Current().Value; Advance();
        return Node;
    } else {
        Error("ParseParams Failed", Current().Line, Current().Column);
    }
}

// Utils
bool Parser::IsDatatype() {
    return (
        Current().Type == TokenType::INT  || Current().Type == TokenType::FLOAT ||
        Current().Type == TokenType::BOOL || Current().Type == TokenType::CHAR  || 
        Current().Type == TokenType::VOID || Current().Type == TokenType::REF 
    ); 
}