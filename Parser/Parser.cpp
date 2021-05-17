//
// Created by Aiden Williams on 03/05/2021.
//

#include "Parser.h"

bool parser::Parser::verifyFoundFactor(){
    // if literal or identifier
    if (foundLiteral() || foundIdentifier()){
        moveTokenWindow();
        return true;
    // if function call
    }else if (foundFunctionCall()){
        moveTokenWindow(2);
        return true;
    // if sub expression
    }else if (currentToken->type == lexer::TOK_OPENING_CURVY){
        unsigned int lineNumber = currentToken->lineNumber;
        moveTokenWindow();
        parseExpression();
        if(currentToken->type != lexer::TOK_CLOSING_CURVY){
            throw std::runtime_error("Expected ')' for opening '(' on line "
                                     + std::to_string(lineNumber) + ".");
        }
        moveTokenWindow();
        return true;
        // if Unary
    }else if (currentToken->type == lexer::TOK_NOT || currentToken->type == lexer::TOK_MINUS){
        moveTokenWindow();
        parseExpression();
        return true;
    }
    return false;
}


bool parser::Parser::foundAssignment() {
    return  currentToken->type == lexer::TOK_IDENTIFIER &&
            nextToken->type == lexer::TOK_EQUALS;
}

bool parser::Parser::foundLiteral() {
    return  currentToken->type == lexer::TOK_BOOL_TYPE ||
            currentToken->type == lexer::TOK_FLOAT_TYPE ||
            currentToken->type == lexer::TOK_INT_TYPE ||
            currentToken->type == lexer::TOK_STRING_TYPE;
}

bool parser::Parser::foundFunctionCall() {
    return  currentToken->type == lexer::TOK_IDENTIFIER &&
            nextToken->type == lexer::TOK_OPENING_CURLY;
}

bool parser::Parser::foundIdentifier() {
    return  currentToken->type == lexer::TOK_IDENTIFIER;
}

bool parser::Parser::foundMultiplicativeOp() {
    return  currentToken->type == lexer::TOK_ASTERISK ||
            currentToken->type == lexer::TOK_DIVIDE ||
            currentToken->type == lexer::TOK_AND;
}

bool parser::Parser::foundAdditiveOp() {
    return  currentToken->type == lexer::TOK_PLUS ||
            currentToken->type == lexer::TOK_MINUS ||
            currentToken->type == lexer::TOK_OR;
}

bool parser::Parser::foundRelationalOp() {
    return  currentToken->type == lexer::TOK_LESS_THAN ||
            currentToken->type == lexer::TOK_MORE_THAN ||
            currentToken->type == lexer::TOK_EQAUL_TO ||
            currentToken->type == lexer::TOK_NOT_EQAUL_TO ||
            currentToken->type == lexer::TOK_LESS_THAN_EQUAL_TO ||
            currentToken->type == lexer::TOK_MORE_THAN_EQUAL_TO;
}

bool parser::Parser::foundSemicolon() {
    return  currentToken->type == lexer::TOK_SEMICOLON;
}

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

parser::ASTExprNode *parser::Parser::parseExpression() {
    if (verifyFoundFactor());
}


parser::ASTStatementNode *parser::Parser::parseStatement() {
    // Will be a switch case of the below functions
    if (foundAssignment()){
        return parseAssignment(currentToken->value);
    }
    return nullptr;
}

parser::ASTAssignmentNode *parser::Parser::parseAssignment(const std::string& identifier) {
    moveTokenWindow(2);
    // Get Expression
    ASTExprNode* expr = parseExpression();
    moveTokenWindow();
    //verify semicolon
    if(!foundSemicolon())
        throw std::runtime_error("Expected ';' after assignment of " + identifier + " on line "
                                 + std::to_string(currentToken->lineNumber) + ".");

    return new ASTAssignmentNode(identifier, expr, currentToken->lineNumber);
}