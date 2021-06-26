//
// Created by aiden on 25/06/2021.
//


#include "XML_Visitor.h"

using namespace visitor;


std::string XMLVisitor::indentation() {
    std::string tabs;
    // Add a tab (4 spaces) according to the indentation level
    for(unsigned int i = 0; i < indentationLevel; i++)
        tabs += TAB;
    return tabs;
}

std::string XMLVisitor::type(parser::TYPE t) {
    switch(t){
        case parser::INT:
            return "int";
        case parser::FLOAT:
            return "float";
        case parser::BOOL:
            return "bool";
        case parser::STRING:
            return "string";
        default:
            throw std::runtime_error("Invalid type encountered in syntax tree when generating XML.");
    }
}

std::string XMLVisitor::xmlSafeOp(std::string op) {
    // changes unsafe characters into safe ones for XML parser
    if(op == "<")
        return "&lt;";
    if(op == ">")
        return "&gt;";
    if(op == "<=")
        return "&lt;=";
    if(op == ">=")
        return "&gt;=";
    return op;
}

void XMLVisitor::visit(parser::ASTProgramNode *program) {
    // Add initial <program> tag
    xmlfile << indentation() << "<program>" << std::endl;
    // Indent
    indentationLevel++;
    // For each statement, generate XML for it
    for(auto &statement : program -> statements)
        statement -> accept(this);
    // Unindent
    indentationLevel--;
    // Add closing tag
    xmlfile << indentation() << "</program>" << std::endl;
}

void XMLVisitor::visit(parser::ASTLiteralNode<int> *lit) {
    // Add initial <int> tag
    xmlfile << indentation() << "<int>";
    // Add value
    xmlfile << std::to_string(lit->val);
    // Add closing tag
    xmlfile << "</int>" << std::endl;
}

void XMLVisitor::visit(parser::ASTLiteralNode<float> *lit) {
    // Add initial <real> tag
    xmlfile << indentation() << "<float>";
    // Add value
    xmlfile << std::to_string(lit->val);
    // Add closing tag
    xmlfile << "</float>" << std::endl;
}

void XMLVisitor::visit(parser::ASTLiteralNode<bool> *lit) {
    // Add initial <bool> tag
    xmlfile << indentation() << "<bool>";
    // Add value
    xmlfile << ((lit->val) ? "true" : "false");
    // Add closing tag
    xmlfile << "</bool>" << std::endl;
}