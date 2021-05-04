//
// Created by Aiden Williams on 03/05/2021.
//

#ifndef TEALANG_COMPILER_CPP20_PARSER_H
#define TEALANG_COMPILER_CPP20_PARSER_H

#include <utility>
#include <vector>
#include <string>
#include "../Visitor/Visitor.h"
#include "../Lexer/Lexer.h"
#include "../Lexer/Token.h"
#include "AST.h"

namespace parser {
    class Parser {
    public:
        Parser(std::vector<lexer::Token> tokens) :
                tokens(std::move(tokens))
        {};
        ASTProgramNode* parseProgram();

    private:
        std::vector<lexer::Token> tokens;
        std::vector<lexer::Token>::iterator currentToken;
        std::vector<lexer::Token>::iterator nextToken;

        // Statement Nodes
        ASTStatementNode* parseStatement();
        ASTAssignmentNode* parseAssignment();
        ASTDeclarationNode* parseDeclaration();
        ASTPrintNode* parsePrint();
        ASTReturnNode* parseReturn();
        ASTBlockNode* parseBlock();
        ASTIfNode* parseIf();
        ASTForNode* parseFor();
        ASTWhileNode* parseWhile();
        ASTFunctionDefinitionNode* parseFunctionDefinition();
    };
}


#endif //TEALANG_COMPILER_CPP20_PARSER_H
