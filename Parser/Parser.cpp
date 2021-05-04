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

    while(currentToken->type != lexer::TOK_INVALID){
        statements->emplace_back(parseStatement());
        moveTokenWindow();
    }

    return new ASTProgramNode(*statements);
}

parser::ASTStatementNode *parser::Parser::parseStatement() {
    // Will be a switch case of the below functions
    return nullptr;
}

parser::ASTAssignmentNode *parser::Parser::parseAssignment(const std::string& identifier) {
    // 〈Identifier〉‘=’ already verified
    moveTokenWindow(2);
    // Get Expression
    ASTExprNode* expr = parseExpression();
    moveTokenWindow();
    //verify semicolon
    if(currentToken->type != lexer::TOK_SEMICOLON)
        throw std::runtime_error("Expected ';' after assignment of " + identifier + " on line "
                                 + std::to_string(currentToken->lineNumber) + ".");

    return new ASTAssignmentNode(identifier, expr, currentToken->lineNumber);
}

