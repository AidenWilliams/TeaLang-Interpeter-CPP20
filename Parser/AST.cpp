//
// Created by Aiden Williams on 03/05/2021.
//

#include "AST.h"

parser::ASTProgramNode::ASTProgramNode(std::vector<ASTStatementNode *> statements) :
    statements(std::move(statements))
{}