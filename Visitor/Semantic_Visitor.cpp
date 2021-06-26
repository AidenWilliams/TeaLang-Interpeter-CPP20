//
// Created by Aiden Williams on 26/06/2021.
//

#include "Semantic_Visitor.h"

// Semantic Analyses

// Program
void visitor::SemanticAnalyser::visit(parser::ASTProgramNode *programNode) {
    // For each statement, accept
    for(auto &statement : programNode -> statements)
        statement -> accept(this);
}
// Program

// Expressions

void visitor::SemanticAnalyser::visit(parser::ASTLiteralNode<int>*) {
    currentType = parser::INT;
}

void visitor::SemanticAnalyser::visit(parser::ASTLiteralNode<float>*) {
    currentType = parser::FLOAT;
}

void visitor::SemanticAnalyser::visit(parser::ASTLiteralNode<bool>*) {
    currentType = parser::BOOL;
}

void visitor::SemanticAnalyser::visit(parser::ASTLiteralNode<std::string>*) {
    currentType = parser::STRING;
}

void visitor::SemanticAnalyser::visit(parser::ASTBinaryNode* binaryNode) {
    // Get operator from binary node
    std::string op = binaryNode -> op;
    // Visit left node first
    binaryNode -> left -> accept(this);
    parser::TYPE left_type = currentType;
    // Visit right node
    binaryNode -> right -> accept(this);
    parser::TYPE right_type = currentType;
    // Start checking operator cases
    // These only work for int/float
    if(op == "*" || op == "/" || op == "-"){
        if((left_type != parser::INT && left_type != parser::FLOAT) ||
           (right_type != parser::INT && right_type != parser::FLOAT))
            throw std::runtime_error("Expected numerical operands for '" + op +
                                     "' operator on line " + std::to_string(binaryNode->lineNumber) + ".");
        // If both int, then expression is int, otherwise float
        currentType = (left_type == parser::INT && right_type == parser::INT) ?
                                  parser::INT : parser::FLOAT;
    }
    // + works for all types except bool
    else if(op == "+") {
        if(left_type == parser::BOOL || right_type == parser::BOOL)
            throw std::runtime_error("Invalid operand for '+' operator, expected numerical or string"
                                     " operand on line " + std::to_string(binaryNode->lineNumber) + ".");
        // If both string, no error
        if(left_type == parser::STRING && right_type == parser::STRING)
            currentType = parser::STRING;
        // only one is string, error
        else if(left_type == parser::STRING || right_type == parser::STRING)
            throw std::runtime_error("Mismatched operands for '+' operator, found " + type(left_type) +
                                     " on the left, but " + type(right_type) + " on the right (line " +
                                     std::to_string(binaryNode->lineNumber) + ").");
        // FLOAT/int possibilities remain. If both int, then result is int, otherwise result is float
        else
            currentType = (left_type == parser::INT && right_type == parser::INT) ?
                                      parser::INT : parser::FLOAT;
    }
    // and/or only work for bool
    else if(op == "and" || op == "or") {
        if (left_type == parser::BOOL && right_type == parser::BOOL)
            currentType = parser::BOOL;
        else throw std::runtime_error("Expected two boolean-type operands for '" + op + "' operator " +
                                      "on line " + std::to_string(binaryNode->lineNumber) + ".");
    }
    // rel-ops only work for numeric types
    else if(op == "<" || op == ">" || op == "<=" || op == ">=") {
        if ((left_type != parser::FLOAT && left_type != parser::INT) ||
            (right_type != parser::FLOAT && right_type != parser::INT))
            throw std::runtime_error("Expected two numerical operands for '" + op + "' operator " +
                                     "on line " + std::to_string(binaryNode->lineNumber) + ".");
        currentType = parser::BOOL;
    }
    // == and != only work for like types
    else if(op == "==" || op == "!=") {
        if (left_type != right_type && (left_type != parser::FLOAT || right_type != parser::INT) &&
            (left_type != parser::INT || right_type != parser::FLOAT))
            throw std::runtime_error("Expected arguments of the same type '" + op + "' operator " +
                                     "on line " + std::to_string(binaryNode->lineNumber) + ".");
        currentType = parser::BOOL;
    }
    else
        throw std::runtime_error("Unhandled semantic error in binary operator.");
}

// Expressions