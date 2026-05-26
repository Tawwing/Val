#pragma once
#include "./Token.hpp"
#include <string>
#include <vector>
#include <memory>

// Bases
struct Expr { virtual ~Expr() = default; };
struct Stmt { virtual ~Stmt() = default; };

// Parameter 
struct Parameter {
    bool IsConst;
    std::string Name;  
    std::string Type;  
};

// Expressions
struct Identifier : Expr {
    std::string Name;
};

struct MemberAccess : Expr {
    std::unique_ptr<Expr> Object;
    std::string Member;
};

struct StringLiteral : Expr {
    std::string Value;
};
struct IntLiteral : Expr {
    int Value;
};
struct FloatLiteral : Expr {
    float Value;
};
struct BoolLiteral : Expr {
    bool Value;
};

struct Call : Expr {
    std::unique_ptr<Expr> Callee;
    std::vector<std::unique_ptr<Expr>> Arguments;
};

// Statements
struct Import : Stmt {
    std::string Name;

    explicit Import(const std::string& Value) : Name(Value) {};
};

struct FunctionDecl : Stmt {
    std::string Name;       
    Token ReturnType;
    std::vector<Parameter> Parameters; 
    std::vector<std::unique_ptr<Stmt>> Body;
};

struct ExprStmt : Stmt {
    std::unique_ptr<Expr> Expression;
};

struct ReturnStmt : Stmt {
    std::unique_ptr<Expr> Value;
};