//
// Created by Aiden Williams on 03/05/2021.
//

#ifndef TEALANG_COMPILER_CPP20_AST_H
#define TEALANG_COMPILER_CPP20_AST_H

#include <string>
#include <utility>
#include <vector>
//#include "../Visitor/Visitor.h"

namespace parser {
    // Types
    enum TYPE {
        FLOAT, INT, BOOL, STRING
    };

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
        std::string op;
        ASTExprNode *left;
        ASTExprNode *right;
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

    class ASTIdentifierNode : public ASTExprNode {
    public:
        explicit ASTIdentifierNode(std::string identifier, unsigned int lineNumber) :
                identifier(std::move(identifier)),
                lineNumber(lineNumber)
        {};
        ~ASTIdentifierNode() = default;

        std::string identifier;
        unsigned int lineNumber;
        void accept(visitor::Visitor*) override;
    };

    class ASTUnaryNode : public ASTExprNode {
    public:
        explicit ASTUnaryNode(ASTExprNode* exprNode, unsigned int lineNumber) :
            exprNode(exprNode),
            lineNumber(lineNumber)
        {};
        ~ASTUnaryNode() = default;
        ASTExprNode* exprNode;
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

    // Program Node
    class ASTProgramNode : public ASTNode {
    public:
//        explicit ASTProgramNode(std::vector<ASTStatementNode *> statements);

        explicit ASTProgramNode(std::vector<ASTStatementNode*> statements) :
                statements(std::move(statements))
        {};
        ~ASTProgramNode() = default;

        std::vector<ASTStatementNode*> statements;
        void accept(visitor::Visitor*) override;
    };

    class ASTSFunctionCallNode : public ASTStatementNode {
        // Identical to the expression node but is a statement
    public:
        ASTSFunctionCallNode(std::string identifier, std::vector<ASTExprNode*> parameters, unsigned int lineNumber) :
                identifier(std::move(identifier)),
                parameters(std::move(parameters)),
                lineNumber(lineNumber)
        {};

        explicit ASTSFunctionCallNode(const ASTFunctionCallNode& expr) :
                identifier(expr.identifier),
                parameters(expr.parameters),
                lineNumber(expr.lineNumber)
        {};

        ~ASTSFunctionCallNode() = default;

        std::string identifier;
        std::vector<ASTExprNode*> parameters;
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

    class ASTPrintStatment : public ASTStatementNode {
    public:
        ASTPrintStatment(ASTExprNode* expr, unsigned int lineNumber) :
                expr(expr),
                lineNumber(lineNumber)
        {};
        ~ASTPrintStatment() = default;

        std::string identifier;
        ASTExprNode *expr;
        unsigned int lineNumber;
        void accept(visitor::Visitor*) override;
    };

    class ASTBlockNode : public ASTStatementNode {
    public:
        ASTBlockNode(std::vector<ASTStatementNode*> statements, unsigned int lineNumber) :
                statements(std::move(statements)),
                lineNumber(lineNumber)
        {};

        ASTBlockNode(const ASTProgramNode& program, unsigned int lineNumber) :
                statements(program.statements),
                lineNumber(lineNumber)
        {};

        ~ASTBlockNode() = default;

        std::vector<ASTStatementNode*> statements;
        unsigned int lineNumber;
        void accept(visitor::Visitor*) override;
    };

    class ASTIfNode : public ASTStatementNode {
    public:
        ASTIfNode(ASTExprNode* condition, ASTBlockNode* ifBlock, unsigned int lineNumber, ASTBlockNode* elseBlock = nullptr) :
                condition(condition),
                ifBlock(ifBlock),
                elseBlock(elseBlock),
                lineNumber(lineNumber)
        {};
        ~ASTIfNode() = default;

        ASTExprNode *condition;
        ASTBlockNode *ifBlock;
        ASTBlockNode *elseBlock;
        unsigned int lineNumber;
        void accept(visitor::Visitor*) override;
    };
    class ASTForNode : public ASTStatementNode {
    public:
        ASTForNode( ASTExprNode* condition, ASTBlockNode* loopBlock, unsigned int lineNumber,
                    ASTDeclarationNode* declaration = nullptr, ASTAssignmentNode* assignment = nullptr) :
                condition(condition),
                declaration(declaration),
                assignment(assignment),
                loopBlock(loopBlock),
                lineNumber(lineNumber)
        {};
        ~ASTForNode() = default;

        ASTDeclarationNode *declaration;
        ASTExprNode *condition;
        ASTAssignmentNode *assignment;
        ASTBlockNode *loopBlock;
        unsigned int lineNumber;
        void accept(visitor::Visitor*) override;
    };


    class ASTWhileNode : public ASTStatementNode {
    public:
        ASTWhileNode(ASTExprNode* condition, ASTBlockNode* loopBlock, unsigned int lineNumber) :
                condition(condition),
                loopBlock(loopBlock),
                lineNumber(lineNumber)
        {};
        ~ASTWhileNode() = default;

        ASTExprNode *condition;
        ASTBlockNode *loopBlock;
        unsigned int lineNumber;
        void accept(visitor::Visitor*) override;
    };

    class ASTFunctionDeclarationNode : public ASTStatementNode {
    public:
        ASTFunctionDeclarationNode(  TYPE type, std::string identifier, std::vector<std::pair<std::string, TYPE>> parameters,
                                    ASTBlockNode* functionBlock, unsigned int lineNumber) :
                type(type),
                identifier(std::move(identifier)),
                parameters(std::move(parameters)),
                functionBlock(functionBlock),
                lineNumber(lineNumber)
        {};
        ~ASTFunctionDeclarationNode() = default;

        TYPE type;
        std::string identifier;
        std::vector<std::pair<std::string, TYPE>> parameters;
        ASTBlockNode* functionBlock;
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
}
#endif //TEALANG_COMPILER_CPP20_AST_H
