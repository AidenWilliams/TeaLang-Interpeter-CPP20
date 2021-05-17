//
// Created by Aiden Williams on 03/05/2021.
//

#include "Parser.h"


void parser::Parser::moveTokenWindow(int step){
    currentToken += step;
    nextToken += step;
}

parser::ASTProgramNode* parser::Parser::parseProgram() {

    auto statements = new std::vector<ASTStatementNode*>;

    while(currentToken->type != lexer::TOK_END){
        statements->push_back(parser::parseStatement());
        moveTokenWindow();
    }

    return new ASTProgramNode(*statements);
}