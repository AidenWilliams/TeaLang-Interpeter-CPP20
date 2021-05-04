//
// Created by Aiden Williams on 03/05/2021.
//

#ifndef TEALANG_COMPILER_CPP20_AST_H
#define TEALANG_COMPILER_CPP20_AST_H


#include <string>
#include <vector>
#include "../Visitor/Visitor.h"

namespace parser {
    // Types
    enum TYPE {FLOAT, INT, BOOL, STRING};

    // Abstract Nodes
    class ASTNode {
    public:
        ASTNode() = default;
        ~ASTNode() = default;
        virtual void accept(visitor::Visitor*) = 0;
    };

    // Expression Nodes
    class ASTExprNode : public ASTNode {
    public:
        ASTExprNode() = default;
        ~ASTExprNode() = default;
        void accept(visitor::Visitor*) override = 0;
    };

    template <typename T>
    class ASTLiteralNode : public ASTExprNode {
    public:
        ASTLiteralNode(T val, unsigned int lineNumber) :
                val(val),
                lineNumber(lineNumber)
        {};
        ~ASTLiteralNode() = default;
        T val;
        unsigned int lineNumber;
        void accept(visitor::Visitor*) override;
    };

    class ASTBinaryExprNode : public ASTExprNode {
    public:
        ASTBinaryExprNode(std::string op, ASTExprNode* left, ASTExprNode* right, unsigned int lineNumber) :
                op(std::move(op)),
                left(left),
                right(right),
                lineNumber(lineNumber)
        {};
        ~ASTBinaryExprNode() = default;;
        std::string op;
        ASTExprNode *left;
        ASTExprNode *right;
        unsigned int lineNumber;
        void accept(visitor::Visitor*) override;
    };

    class ASTIdentifierNode : public ASTExprNode {
    public:
        explicit ASTIdentifierNode(std::string identifier, unsigned int lineNumber) :
                identifier(identifier),
                lineNumber(lineNumber)
        {};
        std::string identifier;
        unsigned int lineNumber;
        void accept(visitor::Visitor*) override;
    };

    class ASTUnaryExprNode : public ASTExprNode {
    public:
        ASTUnaryExprNode(std::string op, ASTExprNode* expr, unsigned int lineNumber) :
                op(std::move(op)),
                expr(expr),
                lineNumber(lineNumber)
        {};
        std::string op;
        ASTExprNode *expr;
        unsigned int lineNumber;
        void accept(visitor::Visitor*) override;
    };

    class ASTFunctionCallNode : public ASTExprNode {
    public:
        ASTFunctionCallNode(std::string identifier, std::vector<ASTExprNode*> parameters, unsigned int lineNumber) :
                identifier(std::move(identifier)),
                parameters(std::move(parameters)),
                lineNumber(lineNumber)
        {};
        std::string identifier;
        std::vector<ASTExprNode*> parameters;
        unsigned int lineNumber;
        void accept(visitor::Visitor*) override;
    };
    // Statement Nodes
    class ASTStatementNode : public ASTNode {
    public:
        ASTStatementNode() = default;
        ~ASTStatementNode() = default;
        void accept(visitor::Visitor*) override = 0;
    };

    class ASTAssignmentNode : public ASTStatementNode {
    public:
        ASTAssignmentNode(std::string identifier, ASTExprNode* expr, unsigned int lineNumber) :
                identifier(std::move(identifier)),
                expr(expr),
                lineNumber(lineNumber)
        {};
        std::string identifier;
        ASTExprNode *expr;
        unsigned int lineNumber;
        void accept(visitor::Visitor*) override;
    };

    class ASTDeclarationNode : public ASTStatementNode {
    public:
        ASTDeclarationNode(TYPE type, std::string identifier, ASTExprNode* expr, unsigned int lineNumber) :
                type(type),
                identifier(std::move(identifier)),
                expr(expr),
                lineNumber(lineNumber)
        {};
        TYPE type;
        std::string identifier;
        ASTExprNode *expr;
        unsigned int lineNumber;
        void accept(visitor::Visitor*) override;
    };

    class ASTPrintNode : public ASTStatementNode {
    public:
        ASTPrintNode(ASTExprNode* expr, unsigned int lineNumber) :
                expr(expr),
                lineNumber(lineNumber)
        {};
        ASTExprNode *expr;
        unsigned int lineNumber;
        void accept(visitor::Visitor*) override;
    };

    class ASTReturnNode : public ASTStatementNode {
    public:
        ASTReturnNode(ASTExprNode* expr, unsigned int lineNumber) :
                expr(expr),
                lineNumber(lineNumber)
        {};
        ASTExprNode *expr;
        unsigned int lineNumber;
        void accept(visitor::Visitor*) override;
    };

    // Block statement nodes
    class ASTBlockNode : public ASTStatementNode {
    public:
        ASTBlockNode(std::vector<ASTStatementNode*> statements, unsigned int lineNumber) :
                statements(std::move(statements)),
                lineNumber(lineNumber)
        {};
        std::vector<ASTStatementNode*> statements;
        unsigned int lineNumber;
        void accept(visitor::Visitor*) override;
    };

    class ASTIfNode : public ASTStatementNode {
    public:
        ASTIfNode(ASTExprNode* condition, ASTBlockNode* if_block, unsigned int lineNumber, ASTBlockNode* else_block=nullptr):
                condition(condition),
                if_block(if_block),
                else_block(else_block),
                lineNumber(lineNumber)
        {};
        ASTExprNode *condition;
        ASTBlockNode *if_block;
        ASTBlockNode *else_block;
        unsigned int lineNumber;
        void accept(visitor::Visitor*) override;
    };

    class ASTForNode : public ASTStatementNode {
    public:
        ASTForNode(ASTExprNode* condition, ASTBlockNode* block, unsigned int lineNumber,ASTDeclarationNode* declaration=nullptr, ASTAssignmentNode* assignment=nullptr) :
                declaration(declaration),
                condition(condition),
                assignment(assignment),
                block(block),
                lineNumber(lineNumber)
        {};
        ASTDeclarationNode* declaration;
        ASTExprNode *condition;
        ASTAssignmentNode* assignment;
        ASTBlockNode *block;
        unsigned int lineNumber;
        void accept(visitor::Visitor*) override;
    };

    class ASTWhileNode : public ASTStatementNode {
    public:
        ASTWhileNode(ASTExprNode* condition, ASTBlockNode* block, unsigned int lineNumber) :
                condition(condition),
                block(block),
                lineNumber(lineNumber)
        {};
        ASTExprNode *condition;
        ASTBlockNode *block;
        unsigned int lineNumber;
        void accept(visitor::Visitor*) override;
    };

}


#endif //TEALANG_COMPILER_CPP20_AST_H
