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

    class ASTStatementNode : public ASTNode {
    public:
        ASTStatementNode() = default;
        ~ASTStatementNode() = default;
        void accept(visitor::Visitor*) override = 0;
    };

    class ASTExprNode : public ASTNode {
    public:
        ASTExprNode() = default;
        ~ASTExprNode() = default;
        void accept(visitor::Visitor*) override = 0;
    };

}

#endif //TEALANG_COMPILER_CPP20_AST_H
