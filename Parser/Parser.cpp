//
// Created by Aiden Williams on 03/05/2021.
//

#include "Parser.h"


void parser::Parser::moveTokenWindow(int step){
    currentToken += step;
    nextToken += step;
}

parser::ASTProgramNode* parser::Parser::parseProgram() {

    auto statements = new std::vector<ASTNode*>;

//    while(currentToken->type != lexer::TOK_){
//        statements->push_back(parse_statement());
//        consume_token();
//    }
//
//    return new ASTProgramNode(*statements);
}