//
// Created by Aiden Williams on 03/05/2021.
//

#include "Parser.h"

parser::Parser::Parser(std::vector<lexer::Token> tokens) {
    currentToken = tokens.front();
    nextLoc = tokens.begin() + 1;
}

void parser::Parser::moveTokenWindow(int step){
    currentToken = *(nextLoc + step - 1);
    nextLoc += step;
}

parser::ASTProgramNode* parser::Parser::parseProgram() {

    auto statements = new std::vector<ASTStatementNode*>;

    while(currentToken.type != lexer::TOK_END){
        statements->push_back(parseStatement());
        moveTokenWindow();
    }

    return new ASTProgramNode(*statements);
}

parser::ASTStatementNode* parser::Parser::parseStatement() {
    switch(currentToken.type){
        case lexer::TOK_LET:
            return parseDeclaration();
//        case lexer::TOK_SET:
//            return parse_assignment_statement();
//
//        case lexer::TOK_PRINT:
//            return parse_print_statement();
//
//        case lexer::TOK_IF:
//            return parse_if_statement();
//
//        case lexer::TOK_WHILE:
//            return parse_while_statement();
//
//        case lexer::TOK_RETURN:
//            return parse_return_statement();
//
//        case lexer::TOK_DEF:
//            return parse_function_definition();
//
//        case lexer::TOK_LEFT_CURLY:
//            return parse_block();

        default:
            throw std::runtime_error("Invalid statement starting with '" +
                                     currentToken.value
                                     + "' encountered on line " +
                                     std::to_string(currentToken.lineNumber) + ".");
    }
}

parser::ASTDeclarationNode* parser::Parser::parseDeclaration() {
    // Determine line number
    unsigned int lineNumber = currentToken.lineNumber;

    // Get next token
    moveTokenWindow();
    // Get identifier for new variable

    if(currentToken.type != lexer::TOK_IDENTIFIER)
        throw std::runtime_error("Expected variable name after 'let' on line "
                                 + std::to_string(currentToken.lineNumber) + ".");

    std::string identifier = currentToken.value;

    // Get next token
    moveTokenWindow();

    // Ensure proper syntax
    if(currentToken.type != lexer::TOK_COLON)
        throw std::runtime_error("Expected ':' after " + identifier + " on line "
                                 + std::to_string(currentToken.lineNumber) + ".");

    // Get next token
    moveTokenWindow();
    // Get type
    TYPE type;
    try{
        type = parseType(identifier);
    }catch (error_t T){
        throw std::runtime_error("Expected type for " + identifier + " after ':' on line "
                                 + std::to_string(currentToken.lineNumber) + ".");
    }

    // Get next token
    moveTokenWindow();
    // Ensure proper syntax
    if(currentToken.type != lexer::TOK_EQUALS)
        throw std::runtime_error("Expected assignment operator '=' for " + identifier + " on line "
                                 + std::to_string(currentToken.lineNumber) + ".");

    // Get next token
    moveTokenWindow();
    // Get expression after =
    ASTExprNode* expr = parseExpression();

    // Get next token
    moveTokenWindow();
    // Ensure proper syntax
    if(currentToken.type != lexer::TOK_SEMICOLON)
        throw std::runtime_error("Expected ';' after assignment of " + identifier + " on line "
                                 + std::to_string(currentToken.lineNumber) + ".");

    // Create ASTExpressionNode to return
    return new ASTDeclarationNode(type, identifier, expr, lineNumber);
}

parser::ASTExprNode* parser::Parser::parseExpression() {
    ASTExprNode *simple_expr = parseSimpleExpression();
    unsigned int lineNumber = currentToken.lineNumber;

    if( currentToken.type == lexer::TOK_LESS_THAN || currentToken.type == lexer::TOK_MORE_THAN ||
        currentToken.type == lexer::TOK_EQAUL_TO || currentToken.type == lexer::TOK_NOT_EQAUL_TO ||
        currentToken.type == lexer::TOK_LESS_THAN_EQUAL_TO || currentToken.type == lexer::TOK_MORE_THAN_EQUAL_TO) {

        moveTokenWindow();
        return new ASTBinaryExprNode(currentToken.value, simple_expr, parseSimpleExpression(), lineNumber);
    }

    return simple_expr;
}

parser::ASTExprNode* parser::Parser::parseSimpleExpression() {
    ASTExprNode *term = parseTerm();
    unsigned int lineNumber = currentToken.lineNumber;

    if( currentToken.type == lexer::TOK_PLUS || currentToken.type == lexer::TOK_MINUS ||
        currentToken.type == lexer::TOK_OR) {
        moveTokenWindow();
        return new ASTBinaryExprNode(currentToken.value, term, parseSimpleExpression(), lineNumber);
    }

    return term;
}

parser::ASTExprNode* parser::Parser::parseTerm() {
    ASTExprNode *factor = parseFactor();

    unsigned int lineNumber = currentToken.lineNumber;

    if( currentToken.type == lexer::TOK_ASTERISK || currentToken.type == lexer::TOK_DIVIDE ||
        currentToken.type == lexer::TOK_AND) {
        moveTokenWindow();
        return new ASTBinaryExprNode(currentToken.value, factor, parseTerm(), lineNumber);
    }

    return factor;
}

parser::ASTExprNode* parser::Parser::parseFactor() {
    // Determine line number
    unsigned int lineNumber = currentToken.lineNumber;

    switch(currentToken.type){

        // Literal Cases
        case lexer::TOK_INT:
            return new ASTLiteralNode<int>(std::stoi(currentToken.value), lineNumber);

        case lexer::TOK_FLOAT:
            return new ASTLiteralNode<float>(std::stof(currentToken.value), lineNumber);

        case lexer::TOK_TRUE:
            return new ASTLiteralNode<bool>(true, lineNumber);
        case lexer::TOK_FALSE:
            return new ASTLiteralNode<bool>(false, lineNumber);

        case lexer::TOK_STRING: {
            // Remove " character from front and end of lexeme
            std::string str = currentToken.value.substr(1, currentToken.value.size() - 2);

            // Replace \" with quote
            size_t pos = str.find("\\\"");
            while (pos != std::string::npos) {
                // Replace
                str.replace(pos, 2, "\"");
                // Get next occurrence from current position
                pos = str.find("\\\"", pos + 2);
            }

            // Replace \n with newline
            pos = str.find("\\n");
            while (pos != std::string::npos) {
                // Replace
                str.replace(pos, 2, "\n");
                // Get next occurrence from current position
                pos = str.find("\\n", pos + 2);
            }

            // Replace \t with tab
            pos = str.find("\\t");
            while (pos != std::string::npos) {
                // Replace
                str.replace(pos, 2, "\t");
                // Get next occurrence from current position
                pos = str.find("\\t", pos + 2);
            }

            // Replace \b with backslash
            pos = str.find("\\b");
            while (pos != std::string::npos) {
                // Replace
                str.replace(pos, 2, "\\");
                // Get next occurrence from current position
                pos = str.find("\\b", pos + 2);
            }

            return new ASTLiteralNode<std::string>(std::move(str), lineNumber);
        }

        // Identifier or function call case
        case lexer::TOK_IDENTIFIER:
            // If next token is '(' then we found a function call
            if(nextLoc->type == lexer::TOK_OPENING_CURVY)
                return parseFunctionCall();
            // if not, its just an identifier
            else return new ASTIdentifierNode(currentToken.value, lineNumber);
        // Subexpression case
        case lexer::TOK_OPENING_CURVY:

        // Unary expression case
        case lexer::TOK_MINUS:
        case lexer::TOK_NOT:

        default:
            throw std::runtime_error("Expected expression on line "
                                     + std::to_string(currentToken.lineNumber) + ".");

    }

}

parser::ASTFunctionCallNode* parser::Parser::parseFunctionCall() {
    // current token is the function identifier
    std::string identifier = currentToken.value;
    auto *parameters = new std::vector<ASTExprNode*>;
    unsigned int line_number = currentToken.lineNumber;

    // Get next token
    moveTokenWindow();
    // Ensure proper syntax
    if(currentToken.type != lexer::TOK_OPENING_CURVY)
        throw std::runtime_error("Expected '(' on line "
                                 + std::to_string(currentToken.lineNumber) + ".");

    // Get next token
    moveTokenWindow();
    // If next token is not right bracket, we have parameters
    if(currentToken.type != lexer::TOK_CLOSING_CURVY) {
        parameters = parseActualParams();
    }

    // Ensure right close bracket after fetching parameters
    if(currentToken.type != lexer::TOK_CLOSING_CURVY)
        throw std::runtime_error("Expected ')' on line "
                                 + std::to_string(currentToken.lineNumber)
                                 + " after function parameters.");

    return new ASTFunctionCallNode(identifier, *parameters, line_number);
}

std::vector<parser::ASTExprNode*>* parser::Parser::parseActualParams() {
    auto parameters = new std::vector<ASTExprNode*>;
    // Add first param
    parameters->push_back(parseExpression());

    // If next token is a comma there are more
    while(nextLoc->type == lexer::TOK_COMMA) {
        // Move current token, to token after comma
        moveTokenWindow(2);
        // Add this token
        parameters->push_back(parseExpression());
    }
    // Current token is on the last param, we need to move beyond that to get the closing )
    moveTokenWindow();

    return parameters;
}

parser::TYPE parser::Parser::parseType(const std::string& identifier) const {
    switch(currentToken.type){
        case lexer::TOK_INT_TYPE:
            return INT;

        case lexer::TOK_FLOAT_TYPE:
            return FLOAT;

        case lexer::TOK_BOOL_TYPE:
            return BOOL;

        case lexer ::TOK_STRING_TYPE:
            return STRING;

        default:
            throw std::runtime_error("Expected type for " + identifier + " on line "
                                     + std::to_string(currentToken.lineNumber) + ".");
    }
}