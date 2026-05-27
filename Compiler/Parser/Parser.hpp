#pragma once
#include <vector>
#include <memory>
#include "../Include/Token.hpp"
#include "../Include/AST.hpp"

class Parser {
public:
    Parser(std::vector<Token> Tokens);
    std::vector<std::unique_ptr<Stmt>> Parse();

private:
    std::vector<Token> Tokens;
    int Pos = 0;

    // Helpers
    Token Current();
    Token Peek(int Forward);
    void  Advance();
    Token Expect(TokenType Type, const std::string& Message);
    bool  Check(TokenType Type);
    [[noreturn]] void Error(const std::string& Message, int AtLine, int AtColumn);

    // Statments
    std::unique_ptr<Stmt> ParseStatement();
    std::unique_ptr<Stmt> ParseImport();
    std::unique_ptr<Stmt> ParseFunctionDecl();
    std::unique_ptr<Stmt> ParseExprStmt();
    
    // Experssion
    std::unique_ptr<Expr> ParseExpr();
    std::unique_ptr<Expr> ParseCall();

    // Extra
    std::unique_ptr<Parameter> ParseParam();
    
    // Utils
    bool IsDatatype();
};