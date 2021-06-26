//
// Created by Aiden Williams on 26/06/2021.
//

#include "AST.h"


// Accept functions for visitors

//  Program

void parser::ASTProgramNode::accept(visitor::Visitor *v){
    v -> visit(this);
}

//  Program

// Expression

template<>
void parser::ASTLiteralNode<int>::accept(visitor::Visitor *v) {
    v->visit(this);
}

template<>
void parser::ASTLiteralNode<float>::accept(visitor::Visitor *v) {
    v->visit(this);
}

template<>
void parser::ASTLiteralNode<bool>::accept(visitor::Visitor *v) {
    v->visit(this);
}

template<>
void parser::ASTLiteralNode<std::string>::accept(visitor::Visitor *v) {
    v->visit(this);
}

void parser::ASTBinaryNode::accept(visitor::Visitor *v){
    v -> visit(this);
}

void parser::ASTFunctionCallNode::accept(visitor::Visitor *v){
    v -> visit(this);
}

void parser::ASTIdentifierNode::accept(visitor::Visitor *v){
    v -> visit(this);
}

void parser::ASTUnaryNode::accept(visitor::Visitor *v) {
    v -> visit(this);
}

// Expression

// Statement

void parser::ASTSFunctionCallNode::accept(visitor::Visitor *v) {
    ASTStatementNode::accept(v);
}

void parser::ASTDeclarationNode::accept(visitor::Visitor *v){
    v -> visit(this);
}

void parser::ASTAssignmentNode::accept(visitor::Visitor *v){
    v -> visit(this);
}

void parser::ASTPrintNode::accept(visitor::Visitor *v){
    v -> visit(this);
}

void parser::ASTBlockNode::accept(visitor::Visitor *v){
    v -> visit(this);
}

void parser::ASTIfNode::accept(visitor::Visitor *v){
    v -> visit(this);
}

void parser::ASTForNode::accept(visitor::Visitor *v) {
    ASTStatementNode::accept(v);
}

void parser::ASTWhileNode::accept(visitor::Visitor *v){
    v -> visit(this);
}

void parser::ASTFunctionDeclarationNode::accept(visitor::Visitor *v){
    v -> visit(this);
}

void parser::ASTReturnNode::accept(visitor::Visitor *v){
    v -> visit(this);
}

// Statement
