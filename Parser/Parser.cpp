//
// Created by Aiden Williams on 03/05/2021.
//
#include <iostream>
#include "Parser.h"
//TODO: TEST EVERY CASE AND KEEP NOTE
//TODO: FIX UNALIGNED CURRENT TOKEN (PARSE EXPRESSION)
parser::Parser::Parser(std::vector<lexer::Token> tokens) {
    // Initialise the currentToken and pointer for the next token
    currentToken = tokens.front();
    nextLoc = tokens.begin() + 1;
}

void parser::Parser::moveTokenWindow(int step){
    // Move window by step
    currentToken = *(nextLoc + step - 1);
    nextLoc += step;
}

parser::ASTProgramNode* parser::Parser::parseProgram(bool block) {
    auto statements = new std::vector<ASTStatementNode*>;
    // Loop over each token and stop with an END token
    while(currentToken.type != lexer::TOK_END){
        // Ignore comments and skip '}' if parsing a block
        if (currentToken.type != lexer::TOK_SINGLE_LINE_COMMENT
            && currentToken.type != lexer::TOK_MULTI_LINE_COMMENT
            && (!block || currentToken.type != lexer::TOK_CLOSING_CURLY))
            statements->push_back(parseStatement());
        // Get next Token
        moveTokenWindow();
        // TODO: FIX LOOP AND REMOVE IF
        if (currentToken.type == lexer::TOK_END || block && currentToken.type == lexer::TOK_CLOSING_CURLY)
            break;
    }
    return new ASTProgramNode(*statements);
}

parser::ASTStatementNode* parser::Parser::parseStatement() {
    // Parse a singular statement
    // The current token type determines what can be parsed
    switch(currentToken.type){
        // Variable declaration case
        case lexer::TOK_LET:
            return parseDeclaration();
        // An identifier can either be a function call or an assignment
        case lexer::TOK_IDENTIFIER:
            // If next token is '(' then we found a function call
            if(nextLoc->type == lexer::TOK_OPENING_CURVY)
                return new ASTSFunctionCallNode(*parseFunctionCall(true));
            else {
                // if not, its should be an Assignment
                return parseAssignment();
            }
        // Print case
        case lexer::TOK_PRINT:
            return parsePrint();
        // If case
        case lexer::TOK_IF:
            return parseIf();
        // For case
        case lexer::TOK_FOR:
            return parseFor();
        // While case
        case lexer::TOK_WHILE:
            return parseWhile();
        // Return case
        case lexer::TOK_RETURN:
            return parseReturn();
        // Function declaration cases
        case lexer::TOK_INT_TYPE:
        case lexer::TOK_FLOAT_TYPE:
        case lexer::TOK_BOOL_TYPE:
        case lexer::TOK_STRING_TYPE:
            return parseFunctionDeclaration();
        // Block parsing case
        case lexer::TOK_OPENING_CURLY:
            return parseBlock();
        // Any other case is an error case
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
    // Current token is LET
    // Get next token
    moveTokenWindow();
    // Confirm current token is IDENTIFIER
    if(currentToken.type != lexer::TOK_IDENTIFIER)
        throw std::runtime_error("Expected variable name after 'let' on line "
                                 + std::to_string(currentToken.lineNumber) + ".");
    // Get identifier for new variable
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

parser::ASTAssignmentNode *parser::Parser::parseAssignment(bool _for) {
    // Determine line number
    unsigned int lineNumber = currentToken.lineNumber;
    // Current token is an IDENTIFIER
    std::string identifier = currentToken.value;
    // Get next token
    moveTokenWindow();
    // Token must be =
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
    // Ensure proper; syntax
    if(!_for && currentToken.type != lexer::TOK_SEMICOLON)
        throw std::runtime_error("Expected ';' after assignment of " + identifier + " on line "
                                + std::to_string(currentToken.lineNumber) + ".");
    // Create ASTAssignmentNode to return
    return new ASTAssignmentNode(identifier, expr, lineNumber);
}

parser::ASTPrintNode *parser::Parser::parsePrint() {
    // Determine line number
    unsigned int lineNumber = currentToken.lineNumber;
    // Current token is PRINT
    // Get next token
    moveTokenWindow();
    // Get expression after print
    ASTExprNode* expr = parseExpression();
    // Get next token
    moveTokenWindow();
    // Ensure proper syntax
    if(currentToken.type != lexer::TOK_SEMICOLON)
        throw std::runtime_error("Expected ';' after print on line "
                                 + std::to_string(currentToken.lineNumber) + ".");
    // Create ASTPrintNode to return
    return new ASTPrintNode(expr, lineNumber);
}

parser::ASTBlockNode *parser::Parser::parseBlock() {
    // Determine line number
    unsigned int lineNumber = currentToken.lineNumber;
    // Current token is {
    // Get next token
    moveTokenWindow();
    // By definition a block is a program enclosed in { }
    ASTBlockNode block = ASTBlockNode(*parseProgram(true), lineNumber);
    // closing } is handled by parseProgram
    // Create ASTBlockNode to return
    return new ASTBlockNode(block.statements, lineNumber);
}

parser::ASTIfNode *parser::Parser::parseIf() {
    // Determine line number
    unsigned int lineNumber = currentToken.lineNumber;
    // Current token is IF
    // Get next token
    moveTokenWindow();
    // Ensure proper syntax with starting (
    if(currentToken.type != lexer::TOK_OPENING_CURVY)
        throw std::runtime_error("Expected '(' after if on line "
                                 + std::to_string(currentToken.lineNumber) + ".");
    // Get next token
    moveTokenWindow();
    // Get condition after (
    ASTExprNode* condition = parseExpression();
    // Get next token
    moveTokenWindow();
    // Ensure proper syntax with closing )
    if(currentToken.type != lexer::TOK_CLOSING_CURVY)
        throw std::runtime_error("Expected ')' after condition on line "
                                 + std::to_string(currentToken.lineNumber) + ".");
    // Get next token
    moveTokenWindow();
    // Ensure proper syntax with starting {
    if(currentToken.type != lexer::TOK_OPENING_CURLY)
        throw std::runtime_error("Expected '{' after ')' on line "
                                 + std::to_string(currentToken.lineNumber) + ".");
    // get if block
    ASTBlockNode *ifBlock = parseBlock();
    // Check for ELSE
    ASTBlockNode *elseBlock = nullptr;
    if(nextLoc[0].type == lexer::TOK_ELSE){
        // Get next token
        moveTokenWindow(2);
        // Ensure proper syntax with starting {
        if(currentToken.type != lexer::TOK_OPENING_CURLY)
            throw std::runtime_error("Expected '{' after else on line "
                                     + std::to_string(currentToken.lineNumber) + ".");
        // get else block
        elseBlock = parseBlock();
    }
    // Create ASTIfNode to return
    return new ASTIfNode(condition, ifBlock, lineNumber,elseBlock);
}

parser::ASTForNode *parser::Parser::parseFor() {
    // Determine line number
    unsigned int lineNumber = currentToken.lineNumber;
    // Current token is FOR
    // Get next token
    moveTokenWindow();
    // Ensure proper syntax with starting (
    if(currentToken.type != lexer::TOK_OPENING_CURVY)
        throw std::runtime_error("Expected '(' after for on line "
                                 + std::to_string(lineNumber) + ".");
    // Get next token
    moveTokenWindow();
    // Check for declaration
    ASTDeclarationNode *declaration = nullptr;
    if(currentToken.type == lexer::TOK_LET){
        // get declaration
        declaration = parseDeclaration();
    }else{
        if(currentToken.type != lexer::TOK_SEMICOLON)
            throw std::runtime_error("Expected ';' after 'for( ;' on line "
                                     + std::to_string(currentToken.lineNumber) + ".");
    }
    // Get next token
    moveTokenWindow();
    // get condition
    ASTExprNode *condition = parseExpression();
    // Get next token
    moveTokenWindow();
    // Ensure proper syntax
    if(currentToken.type != lexer::TOK_SEMICOLON)
        throw std::runtime_error("Expected ';' after condition on line "
                                 + std::to_string(currentToken.lineNumber) + ".");
    // Get next token
    moveTokenWindow();
    // Check for assignment
    ASTAssignmentNode *assignment = nullptr;
    if(currentToken.type == lexer::TOK_IDENTIFIER){
        // get declaration
        assignment = parseAssignment(true);
    }

    // Ensure proper syntax with closing )
    if(currentToken.type != lexer::TOK_CLOSING_CURVY)
        throw std::runtime_error("Expected ')' after condition on line "
                                 + std::to_string(currentToken.lineNumber) + ".");
    // Get next token
    moveTokenWindow();
    // Ensure proper syntax with starting {
    if(currentToken.type != lexer::TOK_OPENING_CURLY)
        throw std::runtime_error("Expected '{' after ')' on line "
                                 + std::to_string(currentToken.lineNumber) + ".");
    // get if block
    ASTBlockNode *loopBlock = parseBlock();

    // Create ASTForNode to return
    return new ASTForNode(condition, loopBlock, lineNumber, declaration, assignment);
}

parser::ASTWhileNode *parser::Parser::parseWhile() {
    // Determine line number
    unsigned int lineNumber = currentToken.lineNumber;
    // Current token is WHILE
    // Get next token
    moveTokenWindow();
    // Ensure proper syntax with starting (
    if(currentToken.type != lexer::TOK_OPENING_CURVY)
        throw std::runtime_error("Expected '(' after while on line "
                                 + std::to_string(currentToken.lineNumber) + ".");
    // Get next token
    moveTokenWindow();
    // Get condition after (
    ASTExprNode* condition = parseExpression();
    // Get next token
    moveTokenWindow();
    // Ensure proper syntax with closing )
    if(currentToken.type != lexer::TOK_CLOSING_CURVY)
        throw std::runtime_error("Expected ')' after condition on line "
                                 + std::to_string(currentToken.lineNumber) + ".");
    // Get next token
    moveTokenWindow();
    // Ensure proper syntax with starting {
    if(currentToken.type != lexer::TOK_OPENING_CURLY)
        throw std::runtime_error("Expected '{' after ')' on line "
                                 + std::to_string(currentToken.lineNumber) + ".");
    // get loop Block
    ASTBlockNode *loopBlock = parseBlock();
    // Create ASTWhileNode to return
    return new ASTWhileNode(condition, loopBlock, lineNumber);
}

parser::ASTReturnNode *parser::Parser::parseReturn() {
    // Determine line number
    unsigned int lineNumber = currentToken.lineNumber;
    // Current token is RETURN
    // Get next token
    moveTokenWindow();
    // Get expression after
    ASTExprNode* expr = parseExpression();
    // Get next token
    moveTokenWindow();

    if(currentToken.type != lexer::TOK_SEMICOLON)
        throw std::runtime_error("Expected ';' after expression on line "
                                 + std::to_string(currentToken.lineNumber) + ".");
    // Create ASTReturnNode to return
    return new ASTReturnNode(expr, lineNumber);
}

parser::ASTFunctionDeclarationNode *parser::Parser::parseFunctionDeclaration() {
    // Determine line number
    unsigned int lineNumber = currentToken.lineNumber;
    // Get type
    TYPE type;
    try{
        type = parseType(currentToken.value);
    }catch (error_t T){
        throw std::runtime_error("Expected type for " + currentToken.value + " on line "
                                 + std::to_string(currentToken.lineNumber) + ".");
    }
    // Get next token
    moveTokenWindow();
    // ensure identifier is here
    ASTIdentifierNode *identifier;
    if (currentToken.type == lexer::TOK_IDENTIFIER){
        identifier = new ASTIdentifierNode(currentToken.value, lineNumber);
    }else{
        throw std::runtime_error("Expected function name after type on line "
                                 + std::to_string(currentToken.lineNumber) + ".");
    }
    // Get next token
    moveTokenWindow(2);
    // If next token is not right bracket, we have parameters
    auto parameters =  new std::vector<std::pair<std::string, TYPE>>;
    if(currentToken.type != lexer::TOK_CLOSING_CURVY) {
        parameters = parseFormalParams();
    }
    // Ensure right close bracket after fetching parameters
    if(currentToken.type != lexer::TOK_CLOSING_CURVY)
        throw std::runtime_error("Expected ')' on line "
                                 + std::to_string(currentToken.lineNumber)
                                 + " after function parameters.");
    // Get next token
    moveTokenWindow();
    // Ensure proper syntax with starting {
    if(currentToken.type != lexer::TOK_OPENING_CURLY)
        throw std::runtime_error("Expected '{' after ')' on line "
                                 + std::to_string(currentToken.lineNumber) + ".");
    // get loop Block
    ASTBlockNode *functionBlock = parseBlock();
    // Create ASTFunctionDeclarationNode to return
    return new ASTFunctionDeclarationNode(type, identifier->identifier, *parameters, functionBlock, lineNumber);
}


std::vector<std::pair<std::string, parser::TYPE>> *parser::Parser::parseFormalParams() {
    //current token is identifier
    // Determine line number
    unsigned int lineNumber = currentToken.lineNumber;
    auto parameters = new std::vector<std::pair<std::string, parser::TYPE>>;
    // get first identifier
    // ensure identifier is here
    ASTIdentifierNode *identifier;
    if (currentToken.type == lexer::TOK_IDENTIFIER){
        identifier = new ASTIdentifierNode(currentToken.value, lineNumber);
    }else{
        throw std::runtime_error("Expected function name after type on line "
                                 + std::to_string(currentToken.lineNumber) + ".");
    }
    // Get next token
    moveTokenWindow();
    // Ensure proper syntax with : after identifier
    if(currentToken.type != lexer::TOK_COLON)
        throw std::runtime_error("Expected ':' after "+identifier->identifier+" on line "
                                 + std::to_string(currentToken.lineNumber) + ".");
    // Get next token
    moveTokenWindow();
    // get first TYPE
    TYPE type;
    try{
        type = parseType(currentToken.value);
    }catch (error_t T){
        throw std::runtime_error("Expected type for " + currentToken.value + " on line "
                                 + std::to_string(currentToken.lineNumber) + ".");
    }
    // Add first param
    parameters->emplace_back(std::pair<std::string, parser::TYPE>{identifier->identifier, type } );
    // If next token is a comma there are more
    while(nextLoc->type == lexer::TOK_COMMA) {
        // Move current token, to token after comma
        moveTokenWindow(2);
        // repeat the above steps
        if (currentToken.type == lexer::TOK_IDENTIFIER){
            identifier = new ASTIdentifierNode(currentToken.value, lineNumber);
        }else{
            throw std::runtime_error("Expected function name after type on line "
                                     + std::to_string(currentToken.lineNumber) + ".");
        }
        // Get next token
        moveTokenWindow();
        // Ensure proper syntax with : after identifier
        if(currentToken.type != lexer::TOK_COLON)
            throw std::runtime_error("Expected ':' after "+identifier->identifier+" on line "
                                     + std::to_string(currentToken.lineNumber) + ".");
        // Get next token
        moveTokenWindow();
        // get  TYPE
        try{
            type = parseType(currentToken.value);
        }catch (error_t T){
            throw std::runtime_error("Expected type for " + currentToken.value + " on line "
                                     + std::to_string(currentToken.lineNumber) + ".");
        }
        // Add first param
        parameters->emplace_back(std::pair<std::string, parser::TYPE>{identifier->identifier, type } );
    }
    // Current token is on the last param, we need to move beyond that to get the closing )
    moveTokenWindow();
    return parameters;
}


parser::ASTExprNode* parser::Parser::parseExpression() {
    ASTExprNode *simple_expr = parseSimpleExpression();
    unsigned int lineNumber = currentToken.lineNumber;
    std::string op;
    // Check if the next token is a relational operator
    if( nextLoc[0].type == lexer::TOK_LESS_THAN || nextLoc[0].type == lexer::TOK_MORE_THAN ||
            nextLoc[0].type == lexer::TOK_EQAUL_TO || nextLoc[0].type == lexer::TOK_NOT_EQAUL_TO ||
            nextLoc[0].type == lexer::TOK_LESS_THAN_EQUAL_TO || nextLoc[0].type == lexer::TOK_MORE_THAN_EQUAL_TO) {
        // store the operator
        op = nextLoc[0].value;
        // Move over current expression and operator (making the right side expression the current token)
        moveTokenWindow(2);
        // Parse right side expression and return
        return new ASTBinaryNode(op, simple_expr, parseExpression(), lineNumber);
    }
    return simple_expr;
}

parser::ASTExprNode* parser::Parser::parseSimpleExpression() {
    ASTExprNode *term = parseTerm();
    unsigned int lineNumber = currentToken.lineNumber;
    std::string op;
    // Check if the next token is an addition operator
    if( nextLoc[0].type == lexer::TOK_PLUS || nextLoc[0].type == lexer::TOK_MINUS ||
            nextLoc[0].type == lexer::TOK_OR) {
        // store the operator
        op = nextLoc[0].value;
        // Move over current simple expression and operator (making the right side simple expression the current token)
        moveTokenWindow(2);
        // Parse right side simple expression and return
        return new ASTBinaryNode(op, term, parseSimpleExpression(), lineNumber);
    }

    return term;
}

parser::ASTExprNode* parser::Parser::parseTerm() {
    ASTExprNode *factor = parseFactor();
    unsigned int lineNumber = currentToken.lineNumber;
    std::string op;
    // Check if the next token is an multiplication operator
    if( nextLoc[0].type == lexer::TOK_ASTERISK || nextLoc[0].type == lexer::TOK_DIVIDE ||
            nextLoc[0].type == lexer::TOK_AND) {
        // store the operator
        op = nextLoc[0].value;
        // Move over current term and operator (making the right side term the current token)
        moveTokenWindow(2);
        // Parse right side term and return
        return new ASTBinaryNode(op, factor, parseTerm(), lineNumber);
    }

    return factor;
}

parser::ASTExprNode* parser::Parser::parseFactor() {
    // Determine line number
    unsigned int lineNumber = currentToken.lineNumber;
    // Define operator for Unary
    std::string op;
    // check current token type
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
            else {
                // if not, its just an identifier
                return new ASTIdentifierNode(currentToken.value, lineNumber);
            }
        // Subexpression case
        case lexer::TOK_OPENING_CURVY:
            return parseSubExpression();
        // Unary expression case
        case lexer::TOK_MINUS:
        case lexer::TOK_NOT:
            // Current token is either not or -
            // store the operator
            op = currentToken.value;
            // Move over it
            moveTokenWindow();
            // return an ASTUnaryNode
            return new ASTUnaryNode(parseExpression(), currentToken, currentToken.lineNumber);
        default:
            throw std::runtime_error("Expected expression on line "
                                     + std::to_string(currentToken.lineNumber) + ".");
    }
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
        parameters->emplace_back(parseExpression());
    }
    // Current token is on the last param, we need to move beyond that to get the closing )
    moveTokenWindow();
    return parameters;
}

parser::ASTFunctionCallNode* parser::Parser::parseFunctionCall(bool semicolon) {
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
    if(semicolon){
        // Get next token
        moveTokenWindow();
        if(currentToken.type != lexer::TOK_SEMICOLON)
            throw std::runtime_error("Expected ';' after ')' on line "
                                     + std::to_string(currentToken.lineNumber) + ".");
    }
    return new ASTFunctionCallNode(identifier, *parameters, line_number);
}

parser::ASTExprNode* parser::Parser::parseSubExpression() {
    // current token is the curvy bracket
    // move over first curvy bracket
    moveTokenWindow();
    // Now we should be able to get an expression
    ASTExprNode *exprNode = parseExpression();
    // move over expression
    moveTokenWindow();
    // Ensure ')' is there
    if(currentToken.type != lexer::TOK_CLOSING_CURVY)
        throw std::runtime_error("Expected ')' on line "
                                 + std::to_string(currentToken.lineNumber)
                                 + " after expression.");
    return exprNode;
}

parser::TYPE parser::Parser::parseType(const std::string& identifier) const {
    // Parse type by checking the token type of the current token
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
