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

    template <typename T>
    class ASTFactorNode : public ASTExprNode {
    public:
        ASTFactorNode(T type, unsigned int lineNumber) :
                type(type),
                lineNumber(lineNumber)
        {};
        ~ASTFactorNode() = default;
        T type;
        unsigned int lineNumber;
        void accept(visitor::Visitor*) override;
    };

    class ASTTermNode : public ASTExprNode {
    public:
        ASTTermNode(ASTFactorNode<TYPE>* factor, std::vector<std::pair<std::string, ASTFactorNode<TYPE>*>> repeatExpr,
                    unsigned int lineNumber) :
                factor(factor),
                repeatExpr(std::move(repeatExpr)),
                lineNumber(lineNumber)
        {};
        ~ASTTermNode() = default;

        ASTFactorNode<TYPE>* factor;
        std::vector<std::pair<std::string, ASTFactorNode<TYPE>*>> repeatExpr;
        unsigned int lineNumber;
        void accept(visitor::Visitor*) override;
    };

    class ASTSimpleExprNode : public ASTExprNode {
    public:
        ASTSimpleExprNode(ASTTermNode* term, std::vector<std::pair<std::string, ASTTermNode*>> repeatExpr, unsigned int lineNumber) :
                term(term),
                repeatExpr(std::move(repeatExpr)),
                lineNumber(lineNumber)
        {};
        ~ASTSimpleExprNode() = default;

        ASTTermNode* term;
        std::vector<std::pair<std::string, ASTTermNode*>> repeatExpr;
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
        ~ASTFunctionCallNode() = default;

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
        ~ASTAssignmentNode() = default;

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
        ~ASTDeclarationNode() = default;

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
        ~ASTPrintNode() = default;

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
        ~ASTReturnNode() = default;

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
        ~ASTBlockNode() = default;

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
        ~ASTIfNode() = default;

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
        ~ASTForNode() = default;

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
        ~ASTWhileNode() = default;

        ASTExprNode *condition;
        ASTBlockNode *block;
        unsigned int lineNumber;
        void accept(visitor::Visitor*) override;
    };

    class ASTFunctionDefinitionNode : public ASTStatementNode {
    public:
        ASTFunctionDefinitionNode(std::string identifier, std::vector<std::pair<std::string, TYPE>> parameters,
                                  TYPE type, ASTBlockNode* block, unsigned int lineNumber) :
                    identifier(std::move(identifier)),
                    parameters(std::move(parameters)),
                    type(type),
                    block(block),
                    lineNumber(lineNumber)
        {};
        ~ASTFunctionDefinitionNode() = default;

        std::string identifier;
        std::vector<std::pair<std::string, TYPE>> parameters;
        std::vector<std::string> variable_names;
        TYPE type;
        ASTBlockNode* block;
        unsigned int lineNumber;
        void accept(visitor::Visitor*) override;
    };

    class ASTProgramNode : public ASTNode {
    public:
        explicit ASTProgramNode(std::vector<ASTStatementNode*> statements) :
                statements(std::move(statements))
        {};
        ~ASTProgramNode() = default;

        std::vector<ASTStatementNode*> statements;
        void accept(visitor::Visitor*) override;
    };
}


#endif //TEALANG_COMPILER_CPP20_AST_H
