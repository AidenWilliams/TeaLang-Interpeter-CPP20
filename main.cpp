#include <iostream>
#include <memory>
#include "Lexer/Lexer.h"
#include "Lexer/Token.h"
#include "Parser/Parser.h"
#include "Parser/AST.h"
#include "Visitor/Visitor.h"
#include "Visitor/XML_Visitor.h"


int main(int argc, char **argv) {
    if (std::string("-l") == argv[1]){
//        std::cout << "TESTING LEXER" << std::endl;
        lexer::Lexer lexer;
        lexer.extraxtLexemes(argv[2]);
        std::cout << "value: type" << std::endl;
        for (const auto& i: lexer.tokens){
            std::cout << i.value << " : " << i.type << std::endl;
        }
    }else if (std::string("-p") == argv[1]){
//        std::cout << "TESTING PARSER" << std::endl;
        lexer::Lexer lexer;
        lexer.extraxtLexemes(argv[2]);

        parser::Parser parser(lexer.tokens);
        auto programNode = std::shared_ptr<parser::ASTProgramNode>(parser.parseProgram());
//        parser::ASTProgramNode* programNode = parser.parseProgram();
    }else if (std::string("-x") == argv[1]){
//        std::cout << "TESTING XML Generator" << std::endl;
        lexer::Lexer lexer;
        lexer.extraxtLexemes(argv[2]);

        parser::Parser parser(lexer.tokens);
        std::shared_ptr<parser::ASTProgramNode> programNode = parser.parseProgram();

        visitor::XMLVisitor xmlVisitor;
//        xmlVisitor.visit(programNode);
    }
    return 0;
}
