#include <iostream>
#include <memory>
#include "Lexer/Lexer.h"
#include "Lexer/Token.h"
#include "Parser/Parser.h"
#include "Parser/AST.h"
#include "Visitor/Visitor.h"
#include "Visitor/XML_Visitor.h"
#include "Visitor/Semantic_Visitor.h"

int main(int argc, char **argv) {
    int x = 't';
    {
        int x = 10;
        {
            int x = 10;
        }
    }
    int y = 10.10;
    std::cout << y << std::endl;
    if (std::string("-l") == argv[1]){
//        std::cout << "TESTING LEXER" << std::endl;
        lexer::Lexer lexer;
        lexer.extraxtLexemes(argv[2]);
        std::cout << "value: type" << std::endl;
        int j = 0;
        for (const auto& i: lexer.tokens){
            std::cout << j++ << " : " << i.value << " : " << i.type << std::endl;
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
        visitor::Variable v("declarationNode->type", "declarationNode->identifier", 1);
        visitor::Variable v2("2declarationNode->type", "2declarationNode->identifier", 2);
        auto scope = visitor::SemanticScope();
        if (scope.insert(v)){
            std::cout << "Im new\n";
        }
        if (!scope.insert(v)){
            std::cout << "Im already here\n";
        }
        auto i = scope.find(v);
        auto j = scope.find(v);
        if (j->first == v.identifier){
            std::cout << "Im found\n";
        }else{
            std::cout << "Im not found\n";
        }
//        lexer::Lexer lexer;
//        lexer.extraxtLexemes(argv[2]);
//
//        parser::Parser parser(lexer.tokens);
//        auto programNode = std::shared_ptr<parser::ASTProgramNode>(parser.parseProgram());
//
//        visitor::XMLVisitor xmlVisitor;
//        auto *programNode1 = new parser::ASTProgramNode(programNode);
//        xmlVisitor.visit(programNode1);
//
//        delete programNode1;
    }
    return 0;
}

/*
 *

 */