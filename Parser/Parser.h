//
// Created by Aiden Williams on 03/05/2021.
//

#ifndef TEALANG_COMPILER_CPP20_PARSER_H
#define TEALANG_COMPILER_CPP20_PARSER_H

#include <vector>
#include <string>
#include <stdexcept>
#include "../Visitor/Visitor.h"
#include "../Lexer/Lexer.h"
#include "../Lexer/Token.h"
#include "AST.h"

namespace parser {
    class Parser {
    public:
        explicit Parser(std::vector<lexer::Token> tokens);

        ASTProgramNode* parseProgram();
        ASTStatementNode* parseStatement();
        ASTDeclarationNode* parseDeclaration();
        ASTExprNode* parseExpression();
        ASTExprNode* parseSimpleExpression();
        ASTExprNode* parseTerm();
        ASTExprNode* parseFactor();
        ASTFunctionCallNode* parseFunctionCall();
        std::vector<ASTExprNode*>* parseActualParams();

        [[nodiscard]] TYPE parseType(const std::string& identifier) const;

    private:
        lexer::Token currentToken;
        std::vector<lexer::Token>::iterator nextLoc;

        void moveTokenWindow(int step = 1);
    };
}
#endif //TEALANG_COMPILER_CPP20_PARSER_H
