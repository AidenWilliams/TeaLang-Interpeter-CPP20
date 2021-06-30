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

    std::string _program_ =
            "float Square (x : float) {\n"
            "\treturn x*x;\n"
            "}\n"
            "bool XGreaterThanY (x : float , y : float) {\n"
            "\tlet ans : bool = true;\n"
            "\tif (y > x) {ans = false ;}\n"
            "\treturn ans;\n"
            "}\n"
            "bool XGreaterThanYv2 (x : float , y : float) {\n"
            "\treturn x > y;\n"
            "}\n"
            "float AverageOfThree (x : float , y : float , z : float) {\n"
            "\tlet total : float = x + y + z ;\n"
            "\treturn total / 3;\n"
            "}\n"
            "\n"
            "string JoinStr (s1 : string , s2 : string) {\n"
            "\tlet s3 : string = s1 + s2 ;\n"
            "\treturn s3 ;\n"
            "}\n"
            "let x: float = 2.4;\n"
            "let y : float = Square (2.5);\n"
            "print y ; //6.25\n"
            "print XGreaterThanY (x , 2.3 ) ; // t r u e\n"
            "print XGreaterThanYv2 (Square ( 1.5 ) , y ) ; // f a l s e\n"
            "print AverageOfThree (x , y , 1.2 ) ; //3.28\n"
            "print JoinStr(”Hello” , ” World ” ) ; // H e l l o World\n";



    if (std::string("-l") == argv[1]){
//        std::cout << "TESTING LEXER" << std::endl;
        lexer::Lexer lexer;
        lexer.extraxtLexemes(_program_);
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
    }else if (std::string("-x") == argv[1]){
//        std::cout << "TESTING XML Generator" << std::endl;

        lexer::Lexer lexer;
        lexer.extraxtLexemes(argv[2]);

        parser::Parser parser(lexer.tokens);
        auto programNode = std::shared_ptr<parser::ASTProgramNode>(parser.parseProgram());

        visitor::XMLVisitor xmlVisitor;
        auto *programNode1 = new parser::ASTProgramNode(programNode);
        xmlVisitor.visit(programNode1);

        delete programNode1;
    }else if (std::string("-s") == argv[1]){
//        std::cout << "TESTING Semantic Analyzer" << std::endl;

        lexer::Lexer lexer;
        lexer.extraxtLexemes(_program_); //argv[2]

        parser::Parser parser(lexer.tokens);
        auto programNode = std::shared_ptr<parser::ASTProgramNode>(parser.parseProgram());

        visitor::SemanticAnalyser semanticAnalyser;
        auto *programNode1 = new parser::ASTProgramNode(programNode);
        semanticAnalyser.visit(programNode1);

        delete programNode1;
    }
    return 0;
}

/*
 *

 */