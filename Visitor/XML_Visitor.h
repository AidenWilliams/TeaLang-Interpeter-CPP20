//
// Created by aiden on 25/06/2021.
//

#ifndef TEALANG_COMPILER_CPP20_XML_VISITOR_H
#define TEALANG_COMPILER_CPP20_XML_VISITOR_H
#include <fstream>
#include "Visitor.h"
#include "../Parser/AST.h"

namespace visitor{

    class XMLVisitor : public Visitor {

    public:
        XMLVisitor(): indentationLevel(0) {
            xmlfile.open("program.xml");
        }
        ~XMLVisitor(){
            xmlfile.close();
        }

        void visit(parser::ASTProgramNode* v) override;

        void visit(parser::ASTLiteralNode<int>* v) override;
        void visit(parser::ASTLiteralNode<float>* v) override;
        void visit(parser::ASTLiteralNode<bool>* v) override;
        void visit(parser::ASTLiteralNode<std::string>* v) override;
        void visit(parser::ASTBinaryNode* v) override;
        void visit(parser::ASTIdentifierNode* v) override;
        void visit(parser::ASTUnaryNode* v) override;
        void visit(parser::ASTFunctionCallNode* v) override;

        void visit(parser::ASTSFunctionCallNode* v) override;
        void visit(parser::ASTDeclarationNode* v) override;
        void visit(parser::ASTAssignmentNode* v) override;
        void visit(parser::ASTPrintNode* v) override;
        void visit(parser::ASTBlockNode* v) override;
        void visit(parser::ASTIfNode* v) override;
        void visit(parser::ASTForNode* v) override;
        void visit(parser::ASTWhileNode* v) override;
        void visit(parser::ASTFunctionDeclarationNode* v) override;
        void visit(parser::ASTReturnNode* v) override;

    private:
        std::ofstream xmlfile;
        unsigned int indentationLevel;
        const std::string TAB = "    ";
        std::string indentation();
        std::string type(parser::TYPE t);
        static std::string xmlSafeOp(std::string op);
    };
}
#endif //TEALANG_COMPILER_CPP20_XML_VISITOR_H
