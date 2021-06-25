//
// Created by aiden on 25/06/2021.
//


#include "XML_Visitor.h"

using namespace visitor;

XMLVisitor::XMLVisitor() : indentationLevel(0) {
    xmlfile.open("program.xml");
};

std::string XMLVisitor::indentation() {

    std::string tabs;

    // Add a tab (4 spaces) according to the indentation level
    for(unsigned int i = 0; i < indentationLevel; i++)
        tabs += TAB;

    return tabs;
}

XMLVisitor::~XMLVisitor(){
    xmlfile.close();
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
