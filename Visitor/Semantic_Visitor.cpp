//
// Created by Aiden Williams on 26/06/2021.
//
/*
 *

 */

#include "Semantic_Visitor.h"

namespace visitor{
    // Semantic Scope

    bool SemanticScope::insert(const Variable& v){
        auto ret = variableTable.insert(std::pair<std::string, Variable>(v.identifier, v) );
        return ret.second;
    }

    bool SemanticScope::insert(const Function& f){
        auto ret = functionTable.insert(std::pair<std::string, Function>(f.identifier, f) );
        return ret.second;
    }

    std::_Rb_tree_iterator<std::pair<const std::basic_string<char, std::char_traits<char>, std::allocator<char>>, Variable>>
    SemanticScope::find(const Variable& v) {
        return variableTable.find(v.identifier); //->first == v.identifier;
    }

    std::_Rb_tree_iterator<std::pair<const std::basic_string<char, std::char_traits<char>, std::allocator<char>>, Function>>
    SemanticScope::find(const Function& f) {
        return functionTable.find(f.identifier); //->first == f.identifier;
    }

    void erase(const Variable& v);
    void erase(const Function& f);

    // Semantic Scope

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

    // Statements


//    void SemanticAnalyser::visit(parser::ASTSFunctionCallNode *sFunctionCallNode) {
//        // Generate Function
//        Function f(sFunctionCallNode.)
//    }

    void SemanticAnalyser::visit(parser::ASTDeclarationNode *declarationNode) {
        // Generate Variable
        Variable v(declarationNode->type, declarationNode->identifier, declarationNode->lineNumber);
        // Check current scope
        auto scope = scopes.back();
        // Try to insert v
        auto search = scope->find(v);
        // compare the found key and the actual key
        // if identical than the variable is already declared
        if(search->first == v.identifier){
            // The variable has already been declared in the current scope
            throw std::runtime_error("Variable with identifier " + v.identifier + " on line "
                                     + std::to_string(v.lineNumber) + " already declared on line "
                                     + std::to_string(search->second.lineNumber));
        }
        // Go check the expression node
        // This will change the current type
        declarationNode->exprNode->accept(this);
        // Check current type with the declaration type
        // since the language does not perform any implicit/automatic typecast (as said in spec)
        if(declarationNode->type == currentType){
            scope->insert(v);
        }else{
            // throw an error since type casting is not supported
            throw std::runtime_error("Variable " + v.identifier + " was declared of type " + v.type + " on line "
                                     + std::to_string(v.lineNumber) + " but has been assigned invalid value of type"
                                     + currentType + ".\nImplicit and Automatic Typecasting is not supported by TeaLang.");
        }
    }
    // Statements
}