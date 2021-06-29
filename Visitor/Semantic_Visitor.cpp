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
        scopes.emplace_back(std::make_shared<SemanticScope>(true));
        // For each statement, accept
        for(auto &statement : programNode -> statements)
            statement -> accept(this);
        scopes.pop_back();
    }
    // Program

    // Expressions
    // Literal visits change the currentType value
    void SemanticAnalyser::visit(parser::ASTLiteralNode<int> *literalNode) {
        currentType = "int";
    }

    void SemanticAnalyser::visit(parser::ASTLiteralNode<float> *literalNode) {
        currentType = "float";
    }

    void SemanticAnalyser::visit(parser::ASTLiteralNode<bool> *literalNode) {
        currentType = "bool";
    }

    void SemanticAnalyser::visit(parser::ASTLiteralNode<std::string> *literalNode) {
        currentType = "string";
    }

    // Expressions

    // Statements
    void SemanticAnalyser::visit(parser::ASTSFunctionCallNode *sFunctionCallNode) {
        // Generate Function
        // First get the param types vector
        std::vector<std::string> paramTypes;
        for (const auto& param : sFunctionCallNode->parameters){
            param->accept(this);
            paramTypes.emplace_back(currentType);
        }
        // now generate the function object
        Function f(sFunctionCallNode->identifier, paramTypes, sFunctionCallNode->lineNumber);
        // Now confirm this exists in the function table for any scope
        for(const auto& scope : scopes){
            if(scope->find(f)->first == f.identifier) return;
        }
        // Function hasn't been found in any scope
        throw std::runtime_error("Function with identifier " + f.identifier + " called on line "
                                 + std::to_string(f.lineNumber) + " has not been declared.");
    }

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
            throw std::runtime_error("Variable with identifier " + v.identifier + " declared on line "
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

    void SemanticAnalyser::visit(parser::ASTAssignmentNode *assignmentNode) {
        // Get the exprNode type
        assignmentNode->exprNode->accept(this);
        /* Check for a variable with:
         * identifier = assignmentNode.identifier
         * type = currentType
         */
        // Generate Variable
        Variable v(currentType, assignmentNode->identifier, assignmentNode->lineNumber);
        // Now confirm this exists in the function table for any scope
        for(const auto& scope : scopes){
            auto result = scope->find(v);
            if(result->first == v.identifier){
                // if identifier has been found
                // check that the types match
                if(result->second.type != v.type){
                    // throw an error since type casting is not supported
                    throw std::runtime_error("Variable " + v.identifier + " declared on line " + std::to_string(result->second.lineNumber)
                                                + " cannot be assigned a value of type " + v.type
                                                + ".\nImplicit and Automatic Typecasting is not supported by TeaLang.");
                }
                return;
            }
        }
        // Variable hasn't been found in any scope
        throw std::runtime_error("Variable with identifier " + v.identifier + " called on line "
                                 + std::to_string(v.lineNumber) + " has not been declared.");
    }

    void SemanticAnalyser::visit(parser::ASTPrintNode *printNode) {
        // Get the exprNode type
        printNode -> exprNode -> accept(this);
    }

    void SemanticAnalyser::visit(parser::ASTBlockNode *blockNode) {
        // Create new scope
        scopes.emplace_back(std::make_shared<SemanticScope>());
        // Visit each statement in the block
        for(auto &statement : blockNode -> statements)
            statement -> accept(this);
        // Close scope
        scopes.pop_back();
    }

    void SemanticAnalyser::visit(parser::ASTIfNode *ifNode) {
        // Get the condition type
        ifNode -> condition -> accept(this);
        // Make sure it is boolean
        if(currentType != "bool")
            throw std::runtime_error("Invalid if-condition on line " + std::to_string(ifNode->lineNumber)
                                     + ", expected boolean expression.");
        // Check the if block
        ifNode -> ifBlock -> accept(this);
        // If there is an else block, check it too
        if(ifNode -> elseBlock)
            ifNode -> elseBlock -> accept(this);
    }

    void SemanticAnalyser::visit(parser::ASTForNode *forNode) {
        // Create new scope for loop params
        // This allows the creation of a new variable only used by the loop
        scopes.emplace_back(std::make_shared<SemanticScope>());
        // First go over the declaration
        forNode -> declaration -> accept(this);
        // Get the condition type
        forNode -> condition -> accept(this);
        // Make sure it is boolean
        if(currentType != "bool")
            throw std::runtime_error("Invalid for-condition on line " + std::to_string(forNode->lineNumber)
                                     + ", expected boolean expression.");
        // Now go over the assignment
        forNode -> assignment -> accept(this);
        // Now go over the loop block
        forNode -> loopBlock ->accept(this);
        // Close loop scope
        // This discards any declared variable in the for(;;) section
        scopes.pop_back();
    }

    void SemanticAnalyser::visit(parser::ASTWhileNode *whileNode) {
        // Get the condition type
        whileNode -> condition -> accept(this);
        // Make sure it is boolean
        if(currentType != "bool")
            throw std::runtime_error("Invalid while-condition on line " + std::to_string(whileNode->lineNumber)
                                     + ", expected boolean expression.");
        // Check the while block
        whileNode -> loopBlock -> accept(this);
    }

    void SemanticAnalyser::visit(parser::ASTFunctionDeclarationNode *functionDeclarationNode) {
        // If current scope is not global then do not allow declaration
        auto scope = scopes.back();
        if (!scope->isGlobal()){
            throw std::runtime_error("Tried declaring function with identifier " + functionDeclarationNode->identifier
                                     + " in a non-global scope.");
        }
        // Generate Function
        // First get the param types vector
        std::vector<std::string> paramTypes;
        for (const auto& param : functionDeclarationNode->parameters){
            paramTypes.emplace_back(param.first);
        }
        // now generate the function object
        Function f(functionDeclarationNode->identifier, paramTypes, functionDeclarationNode->lineNumber);
        // Try to insert f
        auto search = scope->find(f);
        // compare the found key and the actual key
        // if identical than the function is already declared
        // Overloading is a problem for task 2 so we do not care if the params area actually different
        if(search->first == f.identifier){
            // The variable has already been declared in the current scope
            // Overloading is a problem for task 2
            throw std::runtime_error("Function with identifier " + f.identifier + " declared on line "
                                     + std::to_string(f.lineNumber) + " already declared on line "
                                     + std::to_string(search->second.lineNumber));
        }
        // Go check the block node
        returns = false;
        functionDeclarationNode->functionBlock->accept(this);
        // confirm function has a return and that the return type is as defined in the declaration node
        // if(currentType != functionDeclarationNode->type)
        if(!returns){
            throw std::runtime_error("Function with identifier " + f.identifier + " declared on line "
                                     + std::to_string(f.lineNumber) + " does not have a return statement.");
        }
        // Now that the return is confirmed
        // Check current type with the declaration type
        // since the language does not perform any implicit/automatic typecast (as said in spec)
        if(functionDeclarationNode->type == currentType){
            scope->insert(f);
        }else{
            // throw an error since type casting is not supported
            throw std::runtime_error("Function " + f.identifier + " was declared of type " + f.type + " on line "
                                     + std::to_string(f.lineNumber) + " but has been assigned invalid value of type"
                                     + currentType + ".\nImplicit and Automatic Typecasting is not supported by TeaLang.");
        }
    }

    void SemanticAnalyser::visit(parser::ASTReturnNode *returnNode) {
        // Ensure returns is false
        if(returns){
            throw ReturnsException();
        }
        // Update current expression and update currentType
        returnNode -> exprNode -> accept(this);
        // mark returns as true
        returns = true;
    }
    // Statements
}