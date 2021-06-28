//
// Created by Aiden Williams on 26/06/2021.
//

#ifndef TEALANG_COMPILER_CPP20_SEMANTIC_VISITOR_H
#define TEALANG_COMPILER_CPP20_SEMANTIC_VISITOR_H

#include "Visitor.h"
#include "../Parser/AST.h"
#include <utility>
#include <vector>
#include <map>
#include "../Lexer/Token.h"

namespace visitor {
    class variable{
    public:
        variable(std::string identifier, std::string type, unsigned int lineNumber) :
                identifier(std::move(identifier)),
                type(type),
                lineNumber(lineNumber)
        {};
        ~variable() = default;

        std::string identifier;
        std::string type;
        unsigned int lineNumber;

        // lookup(std::vector<>, std::string identifier);
    };

    class function{
    public:
        function(std::string identifier, std::string type, std::vector<std::string> paramTypes, unsigned int lineNumber) :
                identifier(std::move(identifier)),
                type(type),
                paramTypes(std::move(paramTypes)),
                lineNumber(lineNumber)
        {};
        ~function() = default;

        std::string identifier;
        std::string type;
        std::vector<std::string> paramTypes;
        unsigned int lineNumber;

        // lookup(std::vector<>, std::string identifier);
    };

    class SemanticScope {
    public:
        SemanticScope() = default;
        ~SemanticScope() = default;

        // Python equivalent of:
        // variableTable = {identifier: {identifier, TYPE, lineNumber}}
        std::map<std::string, variable> variableTable;
        // Python equivalent of:
        // functionTable = {identifier: {identifier, FUNCTION_TYPE, [ARGUMENT_TYPES,], lineNumber}}
        std::map<std::string, function> functionTable;
    };


    class SemanticAnalyser : public Visitor {
    public:
        SemanticAnalyser()
        {
            scopes.emplace_back(new SemanticScope());
            currentType = std::string();
        };
        ~SemanticAnalyser() = default;

        std::vector<SemanticScope*> scopes;
        std::string currentType;

        void visit(parser::ASTProgramNode* programNode) override;

//        void visit(parser::ASTLiteralNode<int>* literalNode) override;
//        void visit(parser::ASTLiteralNode<float>* literalNode) override;
//        void visit(parser::ASTLiteralNode<bool>* literalNode) override;
//        void visit(parser::ASTLiteralNode<std::string>* literalNode) override;
//        void visit(parser::ASTBinaryNode* binaryNode) override;
//        void visit(parser::ASTIdentifierNode* identifierNode) override;
//        void visit(parser::ASTUnaryNode* unaryNode) override;
//        void visit(parser::ASTFunctionCallNode* functionCallNode) override;
//
//        void visit(parser::ASTSFunctionCallNode* sFunctionCallNode) override;
//        void visit(parser::ASTDeclarationNode* declarationNode) override;
//        void visit(parser::ASTAssignmentNode* assignmentNode) override;
//        void visit(parser::ASTPrintNode* printNode) override;
//        void visit(parser::ASTBlockNode* blockNode) override;
//        void visit(parser::ASTIfNode* ifNode) override;
//        void visit(parser::ASTForNode* forNode) override;
//        void visit(parser::ASTWhileNode* whileNode) override;
//        void visit(parser::ASTFunctionDeclarationNode* functionDeclarationNode) override;
//        void visit(parser::ASTReturnNode* returnNode) override;
    };
}



#endif //TEALANG_COMPILER_CPP20_SEMANTIC_VISITOR_H
