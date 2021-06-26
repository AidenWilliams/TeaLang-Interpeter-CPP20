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

void XMLVisitor::visit(parser::ASTProgramNode *programNode) {
    // Add initial <program> tag
    xmlfile << indentation() << "<program>" << std::endl;
    // Add indentation level
    indentationLevel++;
    // For each statement, generate XML for it
    for(auto &statement : programNode -> statements)
        statement -> accept(this);
    // Remove indentation level
    indentationLevel--;
    // Add closing tag
    xmlfile << indentation() << "</program>" << std::endl;
}

void XMLVisitor::visit(parser::ASTLiteralNode<int> *literalNode) {
    // Add initial <int> tag
    xmlfile << indentation() << "<int>";
    // Add value
    xmlfile << std::to_string(literalNode->val);
    // Add closing tag
    xmlfile << "</int>" << std::endl;
}

void XMLVisitor::visit(parser::ASTLiteralNode<float> *literalNode) {
    // Add initial <float> tag
    xmlfile << indentation() << "<float>";
    // Add value
    xmlfile << std::to_string(literalNode->val);
    // Add closing tag
    xmlfile << "</float>" << std::endl;
}

void XMLVisitor::visit(parser::ASTLiteralNode<bool> *literalNode) {
    // Add initial <bool> tag
    xmlfile << indentation() << "<bool>";
    // Add value
    xmlfile << ((literalNode->val) ? "true" : "false");
    // Add closing tag
    xmlfile << "</bool>" << std::endl;
}

void XMLVisitor::visit(parser::ASTLiteralNode<std::string> *literalNode) {
    // Add initial <string> tag
    xmlfile << indentation() << "<string>";
    // Add value
    xmlfile << literalNode->val;
    // Add closing tag
    xmlfile << "</string>" << std::endl;
}

void XMLVisitor::visit(parser::ASTBinaryNode *binaryNode) {
    // Add initial <bin> tag
    xmlfile << indentation() << "<bin op = \"" + xmlSafeOp(binaryNode->op) +
                                "\">" << std::endl;
    // Add indentation level
    indentationLevel++;
    // Left node
    binaryNode -> left -> accept(this);
    // Right node
    binaryNode -> right -> accept(this);
    // Remove indentation level
    indentationLevel--;
    // Add closing tag
    xmlfile << indentation() << "</bin>" << std::endl;
}

void XMLVisitor::visit(parser::ASTIdentifierNode *identifierNode) {
    // Add initial <id> tag
    xmlfile << indentation() << "<id>";
    // Add value
    xmlfile << identifierNode -> identifier;
    // Add closing tag
    xmlfile << "</id>" << std::endl;

}

void XMLVisitor::visit(parser::ASTUnaryNode *unaryExprNode) {
    // Add initial <unary> tag
    xmlfile << indentation() << "<unary op = \"" + unaryExprNode ->  + "\">"
            << std::endl;
    // Add indentation level
    indentationLevel++;
    // Value
    unaryExprNode -> exprNode -> accept(this);
    // Remove indentation level
    indentationLevel--;
    // Add closing tag
    xmlfile << indentation() << "</unary>" << std::endl;
}

void XMLVisitor::visit(parser::ASTFunctionCallNode *functionCallNode) {
    // Add initial <functionEcall> tag
    xmlfile << indentation() << "<functionEcall>" << std::endl;
    // Add indentation level
    indentationLevel++;
    // Function identifier
    xmlfile << indentation() << "<id>" + functionCallNode->identifier + "</id>" << std::endl;
    // For each parameter
    for(auto &param : functionCallNode -> parameters){
        xmlfile << indentation() << "<param>" << std::endl;
        // Add indentation level
        indentationLevel++;
        // Parameter
        param->accept(this);
        // Remove indentation level
        indentationLevel++;
        xmlfile << indentation() << "</param>" << std::endl;
    }
    // Remove indentation level
    indentationLevel--;
    // Add closing tag
    xmlfile << indentation() << "</functionEcall>" << std::endl;
}

void XMLVisitor::visit(parser::ASTSFunctionCallNode *sFunctionCallNode) {
    // Add initial <functionScall> tag
    xmlfile << indentation() << "<functionScall>" << std::endl;
    // Add indentation level
    indentationLevel++;
    // Function identifier
    xmlfile << indentation() << "<id>" + sFunctionCallNode->identifier + "</id>" << std::endl;
    // For each parameter
    for(auto &param : sFunctionCallNode -> parameters){
        xmlfile << indentation() << "<param>" << std::endl;
        // Add indentation level
        indentationLevel++;
        // Parameter
        param->accept(this);
        // Remove indentation level
        indentationLevel++;
        xmlfile << indentation() << "</param>" << std::endl;
    }
    // Remove indentation level
    indentationLevel--;
    // Add closing tag
    xmlfile << indentation() << "</functionScall>" << std::endl;
}