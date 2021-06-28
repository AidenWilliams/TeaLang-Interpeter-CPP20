//
// Created by Aiden Williams on 26/06/2021.
//

#include "Semantic_Visitor.h"

namespace visitor{
    // Semantic Analyses

    // Program
    void SemanticAnalyser::visit(parser::ASTProgramNode *programNode) {
        // For each statement, accept
        for(auto &statement : programNode -> statements)
            statement -> accept(this);
    }
    // Program

    // Expressions


    // Expressions

}