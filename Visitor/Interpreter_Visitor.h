//
// Created by aiden on 30/06/2021.
//

#ifndef TEALANG_COMPILER_CPP20_INTERPRETER_VISITOR_H
#define TEALANG_COMPILER_CPP20_INTERPRETER_VISITOR_H

#include "Visitor.h"
#include "../Parser/AST.h"
#include <utility>
#include <vector>
#include <map>
#include <memory>
#include "../Lexer/Token.h"

namespace interpreter {
    class Variable{
    public:
        Variable(std::string type, std::string identifier, std::string val, unsigned int lineNumber) :
                type(std::move(type)),
                identifier(std::move(identifier)),
                val(std::move(val)),
                lineNumber(lineNumber)
        {};
        ~Variable() = default;

        std::string type;
        std::string identifier;
        std::string val;
        unsigned int lineNumber;
    };

    class Function{
    public:
        Function(std::string identifier,std::string type, std::vector<std::string> paramTypes, unsigned int lineNumber) :
                identifier(std::move(identifier)),
                type(std::move(type)),
                paramTypes(std::move(paramTypes)),
                lineNumber(lineNumber)
        {};
        ~Function() = default;

        std::string identifier;
        std::string type;
        std::vector<std::string> paramTypes;
        unsigned int lineNumber;
    };

    class Interpreter : public visitor::Visitor {
    private:
        // Python equivalent of:
        // variableTable = {identifier: {TYPE, identifier, val, lineNumber}}
        std::map<std::string, Variable> variableTable;
        // Python equivalent of:
        // functionTable = {identifier: { identifier, [ARGUMENT_TYPES,], lineNumber}}
        std::map<std::string, Function> functionTable;
    public:
        Interpreter() = default;
        ~Interpreter() = default;

        bool insert(const Variable& v);
        bool insert(const Function& f);

        std::_Rb_tree_iterator<std::pair<const std::basic_string<char, std::char_traits<char>, std::allocator<char>>, Variable>>
        find(const Variable& v);
        std::_Rb_tree_iterator<std::pair<const std::basic_string<char, std::char_traits<char>, std::allocator<char>>, Function>>
        find(const Function& f);

        bool found(std::_Rb_tree_iterator<std::pair<const std::basic_string<char, std::char_traits<char>, std::allocator<char>>, Function>> result);
        bool found(std::_Rb_tree_iterator<std::pair<const std::basic_string<char, std::char_traits<char>, std::allocator<char>>, Variable>> result);

//        void visit(parser::ASTProgramNode* programNode) override;

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

#endif //TEALANG_COMPILER_CPP20_INTERPRETER_VISITOR_H
