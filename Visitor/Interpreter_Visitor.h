//
// Created by aiden on 30/06/2021.
//

#ifndef TEALANG_COMPILER_CPP20_INTERPRETER_VISITOR_H
#define TEALANG_COMPILER_CPP20_INTERPRETER_VISITOR_H

#include "Visitor.h"
#include "Semantic_Visitor.h"
#include <utility>
#include <vector>
#include <map>
#include <memory>

namespace interpreter {
    template <typename T>
    class Variable : public visitor::Variable{
    public:
        Variable(const std::string& type, const std::string& identifier, T value, unsigned int lineNumber) :
                visitor::Variable(type, identifier, lineNumber),
                value(value)
                {
                    values.emplace_back(value);
                };

        ~Variable() = default;
        T value;
        std::vector<T> values;
    };

    class Function : public visitor::Function{
    public:
        Function(const std::string& type, const std::string& identifier, const std::vector<std::string>& paramTypes,
                 std::shared_ptr<parser::ASTBlockNode> blockNode, unsigned int lineNumber)
                 :
                 visitor::Function(type, identifier, paramTypes, lineNumber),
                 blockNode(std::move(blockNode))
                 {};

        ~Function() = default;

        std::shared_ptr<parser::ASTBlockNode> blockNode;
    };
}

namespace visitor {
    class Interpreter : public Visitor {
    private:
        // Python equivalent of:
        // variableTable = {identifier: {TYPE, identifier, val, lineNumber}}
        std::map<std::string, interpreter::Variable<int>>           intTable;
        std::map<std::string, interpreter::Variable<float>>         floatTable;
        std::map<std::string, interpreter::Variable<bool>>          boolTable;
        std::map<std::string, interpreter::Variable<std::string>>   stringTable;
        // Python equivalent of:
        // functionTable = {identifier: { identifier, [ARGUMENT_TYPES,], lineNumber}}
        std::map<std::string, interpreter::Function> functionTable;
    public:
        Interpreter() = default;
        ~Interpreter() = default;

        bool insert(const interpreter::Variable<int>& v);
        bool insert(const interpreter::Variable<float>& v);
        bool insert(const interpreter::Variable<bool>& v);
        bool insert(const interpreter::Variable<std::string>& v);
        bool insert(const interpreter::Function& f);

        std::_Rb_tree_iterator<std::pair<const std::basic_string<char, std::char_traits<char>, std::allocator<char>>, interpreter::Variable<int>>>
        find(const interpreter::Variable<int>& v);
        std::_Rb_tree_iterator<std::pair<const std::basic_string<char, std::char_traits<char>, std::allocator<char>>,  interpreter::Variable<float>>>
        find(const  interpreter::Variable<float>& v);
        std::_Rb_tree_iterator<std::pair<const std::basic_string<char, std::char_traits<char>, std::allocator<char>>, interpreter::Variable<bool>>>
        find(const interpreter::Variable<bool>& v);
        std::_Rb_tree_iterator<std::pair<const std::basic_string<char, std::char_traits<char>, std::allocator<char>>, interpreter::Variable<std::string>>>
        find(const interpreter::Variable<std::string>& v);
        std::_Rb_tree_iterator<std::pair<const std::basic_string<char, std::char_traits<char>, std::allocator<char>>, interpreter::Function>>
        find(const interpreter::Function& f);

        bool found(std::_Rb_tree_iterator<std::pair<const std::basic_string<char, std::char_traits<char>, std::allocator<char>>, interpreter::Variable<int>>> result);
        bool found(std::_Rb_tree_iterator<std::pair<const std::basic_string<char, std::char_traits<char>, std::allocator<char>>, interpreter::Variable<float>>> result);
        bool found(std::_Rb_tree_iterator<std::pair<const std::basic_string<char, std::char_traits<char>, std::allocator<char>>, interpreter::Variable<bool>>> result);
        bool found(std::_Rb_tree_iterator<std::pair<const std::basic_string<char, std::char_traits<char>, std::allocator<char>>, interpreter::Variable<std::string>>> result);
        bool found(std::_Rb_tree_iterator<std::pair<const std::basic_string<char, std::char_traits<char>, std::allocator<char>>, interpreter::Function>> result);

        void visit(parser::ASTProgramNode* programNode) override;

        void visit(parser::ASTLiteralNode<int>* literalNode) override;
        void visit(parser::ASTLiteralNode<float>* literalNode) override;
        void visit(parser::ASTLiteralNode<bool>* literalNode) override;
        void visit(parser::ASTLiteralNode<std::string>* literalNode) override;
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
