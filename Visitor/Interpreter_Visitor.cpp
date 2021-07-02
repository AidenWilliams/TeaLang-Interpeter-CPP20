//
// Created by aiden on 30/06/2021.
//

#include "Interpreter_Visitor.h"

namespace visitor {
    bool Interpreter::insert(const interpreter::Variable<int>& v, int value){
        if (v.type.empty()){
            throw VariableTypeException();
        }
        auto result = find(v);
        if (found(result)){
            // found the variable already
            // add the value
            // since we know that the result exists, then we can use the [] without any 'side effect' of creating a new entry
            intTable[v.identifier].values.emplace_back(value);
            return false;
        }else{
            // The variable doesnt exist so we add a new one
            auto ret = intTable.insert(std::pair<std::string, interpreter::Variable<int>>(v.identifier, v) );
            return ret.second;
        }
    }
    bool Interpreter::insert(const interpreter::Variable<float>& v, float value){
        if (v.type.empty()){
            throw VariableTypeException();
        }
        auto result = find(v);
        if (found(result)){
            // found the variable already
            // add the value
            // since we know that the result exists, then we can use the [] without any 'side effect' of creating a new entry
            floatTable[v.identifier].values.emplace_back(value);
            return false;
        }else{
            // The variable doesnt exist so we add a new one
            auto ret = floatTable.insert(std::pair<std::string, interpreter::Variable<float>>(v.identifier, v) );
            return ret.second;
        }
    }
    bool Interpreter::insert(const interpreter::Variable<bool>& v, bool value){
        if (v.type.empty()){
            throw VariableTypeException();
        }
        auto result = find(v);
        if (found(result)){
            // found the variable already
            // add the value
            // since we know that the result exists, then we can use the [] without any 'side effect' of creating a new entry
            boolTable[v.identifier].values.emplace_back(value);
            return false;
        }else{
            // The variable doesnt exist so we add a new one
            auto ret = boolTable.insert(std::pair<std::string, interpreter::Variable<bool>>(v.identifier, v) );
            return ret.second;
        }
    }
    bool Interpreter::insert(const interpreter::Variable<std::string>& v, const std::string& value){
        if (v.type.empty()){
            throw VariableTypeException();
        }
        auto result = find(v);
        if (found(result)){
            // found the variable already
            // add the value
            // since we know that the result exists, then we can use the [] without any 'side effect' of creating a new entry
            stringTable[v.identifier].values.emplace_back(value);
            return false;
        }else{
            // The variable doesnt exist so we add a new one
            auto ret = stringTable.insert(std::pair<std::string, interpreter::Variable<std::string>>(v.identifier, v) );
            return ret.second;
        }
    }

    bool Interpreter::insert(const interpreter::Function& f){
        if (f.type.empty()){
            throw FunctionTypeException();
        }
        auto ret = functionTable.insert(std::pair<std::string, interpreter::Function>(f.identifier, f) );
        return ret.second;
    }

    std::_Rb_tree_iterator<std::pair<const std::basic_string<char, std::char_traits<char>, std::allocator<char>>, interpreter::Variable<int>>>
    Interpreter::find(const interpreter::Variable<int>& v) {
        return intTable.find(v.identifier);
    }
    std::_Rb_tree_iterator<std::pair<const std::basic_string<char, std::char_traits<char>, std::allocator<char>>, interpreter::Variable<float>>>
    Interpreter::find(const interpreter::Variable<float>& v) {
        return floatTable.find(v.identifier);
    }
    std::_Rb_tree_iterator<std::pair<const std::basic_string<char, std::char_traits<char>, std::allocator<char>>, interpreter::Variable<bool>>>
    Interpreter::find(const interpreter::Variable<bool>& v) {
        return boolTable.find(v.identifier);
    }
    std::_Rb_tree_iterator<std::pair<const std::basic_string<char, std::char_traits<char>, std::allocator<char>>, interpreter::Variable<std::string>>>
    Interpreter::find(const interpreter::Variable<std::string>& v) {
        return stringTable.find(v.identifier);
    }

    std::_Rb_tree_iterator<std::pair<const std::basic_string<char, std::char_traits<char>, std::allocator<char>>, interpreter::Function>>
    Interpreter::find(const interpreter::Function& f) {
        return functionTable.find(f.identifier);
    }

    bool Interpreter::found(
            std::_Rb_tree_iterator<std::pair<const std::basic_string<char, std::char_traits<char>, std::allocator<char>>, interpreter::Variable<int>>> result) {
        return result != intTable.end();
    }
    bool Interpreter::found(
            std::_Rb_tree_iterator<std::pair<const std::basic_string<char, std::char_traits<char>, std::allocator<char>>, interpreter::Variable<float>>> result) {
        return result != floatTable.end();
    }
    bool Interpreter::found(
            std::_Rb_tree_iterator<std::pair<const std::basic_string<char, std::char_traits<char>, std::allocator<char>>, interpreter::Variable<bool>>> result) {
        return result != boolTable.end();
    }
    bool Interpreter::found(
            std::_Rb_tree_iterator<std::pair<const std::basic_string<char, std::char_traits<char>, std::allocator<char>>, interpreter::Variable<std::string>>> result) {
        return result != stringTable.end();
    }

    bool Interpreter::found(
            std::_Rb_tree_iterator<std::pair<const std::basic_string<char, std::char_traits<char>, std::allocator<char>>, interpreter::Function>> result) {
        return result != functionTable.end();;
    }

    void Interpreter::visit(parser::ASTProgramNode *programNode) {
        // For each statement, accept
        for(auto &statement : programNode -> statements)
            statement -> accept(this);
    }

    // Expressions
    // Literal visits add a new literal variable to the 'literalTYPE' variable in the variableTable
    void Interpreter::visit(parser::ASTLiteralNode<int> *literalNode) {
        interpreter::Variable<int> v("int", "literal", literalNode->val, literalNode->lineNumber);
        insert(v, literalNode->val);
        currentType = "int";
        currentID = "literal";
    }

    void Interpreter::visit(parser::ASTLiteralNode<float> *literalNode) {
        interpreter::Variable<float> v("float", "literal", literalNode->val, literalNode->lineNumber);
        insert(v, literalNode->val);
        currentType = "float";
        currentID = "literal";
    }

    void Interpreter::visit(parser::ASTLiteralNode<bool> *literalNode) {
        interpreter::Variable<bool> v("bool", "literal", literalNode->val, literalNode->lineNumber);
        insert(v, literalNode->val);
        currentType = "bool";
        currentID = "literal";
    }

    void Interpreter::visit(parser::ASTLiteralNode<std::string> *literalNode) {
        interpreter::Variable<std::string> v("string", "literal", literalNode->val, literalNode->lineNumber);
        insert(v, literalNode->val);
        currentType = "string";
        currentID = "literal";
    }

    void Interpreter::visit(parser::ASTBinaryNode *binaryNode) {
        // First get the operator
        std::string op = binaryNode -> op;
        // Accept left expression
        binaryNode->left->accept(this);
        std::string leftID = currentID;
        // Accept right expression
        binaryNode->right->accept(this);
        std::string rightID = currentID;
        // We know both variables have the same type
        // So we check the currentType's type to see which operations we can do
        // check op type
        bool boolV;
        int intV;
        float flaotV;
        std::string stringV;
        if (currentType == "string") {
            switch (lexer::determineOperatorType(binaryNode->op)) {
                // string accepted operators
                case lexer::TOK_NOT_EQAUL_TO:
                    boolV  =    find(interpreter::Variable<std::string>(leftID))->second.values.back()
                                !=
                                find(interpreter::Variable<std::string>(rightID))->second.values.back();

                    insert(interpreter::Variable<bool>("bool", "0CurrentVariable", boolV,
                                                       binaryNode->lineNumber), boolV);
                    break;
                case lexer::TOK_EQAUL_TO:
                    boolV  =    find(interpreter::Variable<std::string>(leftID))->second.values.back()
                                ==
                                find(interpreter::Variable<std::string>(rightID))->second.values.back();

                    insert(interpreter::Variable<bool>("bool", "0CurrentVariable", boolV,
                                                       binaryNode->lineNumber), boolV);
                    break;
                case lexer::TOK_PLUS:
                    stringV  =      find(interpreter::Variable<std::string>(leftID))->second.values.back()
                                    +
                                    find(interpreter::Variable<std::string>(rightID))->second.values.back();

                    insert(interpreter::Variable<std::string>("string", "0CurrentVariable", stringV,
                                                       binaryNode->lineNumber), stringV);
                    break;
                default:
                    throw std::runtime_error("Expression on line " + std::to_string(binaryNode->lineNumber)
                                             + " has incorrect operator " + binaryNode->op
                                             + " acting between expressions of type " + currentType);
            }
        }else if (currentType == "int" || currentType == "float") {
            switch (lexer::determineOperatorType(binaryNode->op)) {
                // string accepted operators
                case lexer::TOK_NOT_EQAUL_TO:
                case lexer::TOK_EQAUL_TO:
                case lexer::TOK_MORE_THAN:
                case lexer::TOK_LESS_THAN:
                case lexer::TOK_MORE_THAN_EQUAL_TO:
                case lexer::TOK_LESS_THAN_EQUAL_TO:
                    // change current type to bool as a condition has been found
                    currentType = "bool";
                    // int and float accepted operators
                case lexer::TOK_PLUS:
                case lexer::TOK_ASTERISK:
                case lexer::TOK_DIVIDE:
                case lexer::TOK_MINUS:
                    // Valid tokens
                    break;
                default:
                    throw std::runtime_error("Expression on line " + std::to_string(binaryNode->lineNumber)
                                             + " has incorrect operator " + binaryNode->op
                                             + " acting between expressions of type " + currentType);
            }
        }else if (currentType == "bool"){
            switch (lexer::determineOperatorType(binaryNode->op)) {
                case lexer::TOK_NOT_EQAUL_TO:
                case lexer::TOK_EQAUL_TO:
                case lexer::TOK_AND:
                case lexer::TOK_NOT:
                case lexer::TOK_MORE_THAN:
                case lexer::TOK_LESS_THAN:
                case lexer::TOK_MORE_THAN_EQUAL_TO:
                case lexer::TOK_LESS_THAN_EQUAL_TO:
                    // current type is already bool
                    // Valid tokens
                    break;
                default:
                    throw std::runtime_error("Expression on line " + std::to_string(binaryNode->lineNumber)
                                             + " has incorrect operator " + binaryNode->op
                                             + " acting between expressions of type " + currentType);
            }
        }
    }

    void Interpreter::visit(parser::ASTIdentifierNode *identifierNode) {

    }

}