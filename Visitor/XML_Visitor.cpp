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
