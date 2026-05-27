#pragma once
#include "./Token.hpp"
#include <string>
#include <vector>
#include <memory>

// Bases
struct Expr { virtual ~Expr() = default; };
struct Stmt { virtual ~Stmt() = default; };

// Forward Declartions
struct Identifier    : Expr {};
struct MemberAccess  : Expr {};
struct Call          : Expr {};

struct StringLiteral : Expr {};
struct IntLiteral    : Expr {};
struct FloatLiteral  : Expr {};
struct BoolLiteral   : Expr {};
struct CharLiteral   : Expr {};
struct BinaryOP      : Expr {};
struct UnaryOP       : Expr {};
struct Grouping      : Expr {};

struct Import        : Stmt {};
struct FunctionDecl  : Stmt {};
struct VarDecl       : Stmt {};
struct IfStmt        : Stmt {};
struct WhileStmt     : Stmt {};
struct ForStmt       : Stmt {};
struct BreakStmt     : Stmt {};
struct ContinueStmt  : Stmt {};
struct AssignStmt    : Stmt {};
struct BlockStmt     : Stmt {};
struct ExprStmt      : Stmt {};
struct ReturnStmt    : Stmt {};

struct Parameter {};
// Parameter 
struct Parameter {
    bool IsConst;
    std::string Name;  
    Token Type;  
};

// Expressions
struct Identifier : Expr {
    std::string Name;
};

struct MemberAccess : Expr {
    std::unique_ptr<Expr> Object;
    std::string Member;
};

struct Call : Expr {
    std::unique_ptr<Expr> Callee;
    std::vector<std::unique_ptr<Expr>> Arguments;
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
struct CharLiteral : Expr {
    char Value;
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

struct VarDecl : Stmt {
    bool IsConst;
    std::string Name;
    Token Type;
    std::unique_ptr<Expr> Init;
};

struct IfStmt : Stmt {
    std::unique_ptr<Expr> Condition;
    std::vector<std::unique_ptr<Stmt>> Then;
    std::unique_ptr<Stmt> Else; 
};

struct AssignStmt : Stmt {
    std::string Name;
    std::unique_ptr<Expr> Value;
};

struct BlockStmt : Stmt {
    std::vector<std::unique_ptr<Stmt>> Body;
};

struct ExprStmt : Stmt {
    std::unique_ptr<Expr> Expression;
};

struct ReturnStmt : Stmt {
    std::unique_ptr<Expr> Value;
};