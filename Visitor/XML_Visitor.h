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
        XMLVisitor();
        ~XMLVisitor();

        void visit(parser::ASTProgramNode*) override;

        void visit(parser::ASTLiteralNode<int>*) override;
        void visit(parser::ASTLiteralNode<float>*) override;
        void visit(parser::ASTLiteralNode<bool>*) override;
        void visit(parser::ASTLiteralNode<std::string>*) override;
        void visit(parser::ASTBinaryExprNode*) override;
        void visit(parser::ASTIdentifierNode*) override;
        void visit(parser::ASTUnaryExprNode*) override;
        void visit(parser::ASTFunctionCallNode*) override;

        void visit(parser::ASTSFunctionCallNode*) override;
        void visit(parser::ASTDeclarationNode*) override;
        void visit(parser::ASTAssignmentNode*) override;
        void visit(parser::ASTPrintNode*) override;
        void visit(parser::ASTBlockNode*) override;
        void visit(parser::ASTIfNode*) override;
        void visit(parser::ASTForNode*) override;
        void visit(parser::ASTWhileNode*) override;
        void visit(parser::ASTFunctionDeclarationNode*) override;
        void visit(parser::ASTReturnNode*) override;

    private:
        std::ofstream xmlfile;
        unsigned int indentationLlevel;
        const std::string TAB = "    ";
        std::string indentation();
        std::string type(parser::TYPE);
        std::string xmlSafeOp(std::string);
    };

}
#endif //TEALANG_COMPILER_CPP20_XML_VISITOR_H
