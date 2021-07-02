//
// Created by aiden on 30/06/2021.
//

#include "Interpreter_Visitor.h"

namespace visitor {
    // Tools
    bool Interpreter::insert(const interpreter::Variable<int>& v){
        if (v.type.empty()){
            throw VariableTypeException();
        }
        auto result = find(v);
        if (found(result)){
            // found the variable already
            // add the value
            // since we know that the result exists, then we can use the [] without any 'side effect' of creating a new entry
            // unfortunately intTable[identifier] kills the cpp compiler
            // so in order to pop_back a value from the values vector we have to completely replace the object
            // Copy the result variable
            interpreter::Variable<int> cpy(result->second);
            // pop the value from the copy
            cpy.values.emplace_back(v.latestValue);
            // remove the result
            intTable.erase(result);
            // insert the copy
            insert(cpy);
            return false;
        }else{
            // The variable doesnt exist so we add a new one
            auto ret = intTable.insert(std::pair<std::string, interpreter::Variable<int>>(v.identifier, v) );
            return ret.second;
        }
    }
    bool Interpreter::insert(const interpreter::Variable<float>& v){
        if (v.type.empty()){
            throw VariableTypeException();
        }
        auto result = find(v);
        if (found(result)){
            // found the variable already
            // add the value
            // since we know that the result exists, then we can use the [] without any 'side effect' of creating a new entry
            // unfortunately intTable[identifier] kills the cpp compiler
            // so in order to pop_back a value from the values vector we have to completely replace the object
            // Copy the result variable
            interpreter::Variable<float> cpy(result->second);
            // pop the value from the copy
            cpy.values.emplace_back(v.latestValue);
            // remove the result
            floatTable.erase(result);
            // insert the copy
            insert(cpy);
            return false;
        }else{
            // The variable doesnt exist so we add a new one
            auto ret = floatTable.insert(std::pair<std::string, interpreter::Variable<float>>(v.identifier, v) );
            return ret.second;
        }
    }
    bool Interpreter::insert(const interpreter::Variable<bool>& v){
        if (v.type.empty()){
            throw VariableTypeException();
        }
        auto result = find(v);
        if (found(result)){
            // found the variable already
            // add the value
            // since we know that the result exists, then we can use the [] without any 'side effect' of creating a new entry
            // unfortunately intTable[identifier] kills the cpp compiler
            // so in order to pop_back a value from the values vector we have to completely replace the object
            // Copy the result variable
            interpreter::Variable<bool> cpy(result->second);
            // pop the value from the copy
            cpy.values.emplace_back(v.latestValue);
            // remove the result
            boolTable.erase(result);
            // insert the copy
            insert(cpy);
            return false;
        }else{
            // The variable doesnt exist so we add a new one
            auto ret = boolTable.insert(std::pair<std::string, interpreter::Variable<bool>>(v.identifier, v) );
            return ret.second;
        }
    }
    bool Interpreter::insert(const interpreter::Variable<std::string>& v){
        if (v.type.empty()){
            throw VariableTypeException();
        }
        auto result = find(v);
        if (found(result)){
            // found the variable already
            // add the value
            // since we know that the result exists, then we can use the [] without any 'side effect' of creating a new entry
            // unfortunately intTable[identifier] kills the cpp compiler
            // so in order to pop_back a value from the values vector we have to completely replace the object
            // Copy the result variable
            interpreter::Variable<std::string> cpy(result->second);
            // pop the value from the copy
            cpy.values.emplace_back(v.latestValue);
            // remove the result
            stringTable.erase(result);
            // insert the copy
            insert(cpy);
            return false;
        }else{
            // The variable doesnt exist so we add a new one
            auto ret = stringTable.insert(std::pair<std::string, interpreter::Variable<std::string>>(v.identifier, v) );
            return ret.second;
        }
    }

    bool Interpreter::insert(const interpreter::Function& f){
        if (f.type.empty()){
            throw FunctionTypeException();
        }
        auto ret = functionTable.insert(std::pair<std::string, interpreter::Function>(f.identifier, f) );
        return ret.second;
    }

    std::_Rb_tree_iterator<std::pair<const std::basic_string<char, std::char_traits<char>, std::allocator<char>>, interpreter::Variable<int>>>
    Interpreter::find(const interpreter::Variable<int>& v) {
        return intTable.find(v.identifier);
    }
    std::_Rb_tree_iterator<std::pair<const std::basic_string<char, std::char_traits<char>, std::allocator<char>>, interpreter::Variable<float>>>
    Interpreter::find(const interpreter::Variable<float>& v) {
        return floatTable.find(v.identifier);
    }
    std::_Rb_tree_iterator<std::pair<const std::basic_string<char, std::char_traits<char>, std::allocator<char>>, interpreter::Variable<bool>>>
    Interpreter::find(const interpreter::Variable<bool>& v) {
        return boolTable.find(v.identifier);
    }
    std::_Rb_tree_iterator<std::pair<const std::basic_string<char, std::char_traits<char>, std::allocator<char>>, interpreter::Variable<std::string>>>
    Interpreter::find(const interpreter::Variable<std::string>& v) {
        return stringTable.find(v.identifier);
    }

    std::_Rb_tree_iterator<std::pair<const std::basic_string<char, std::char_traits<char>, std::allocator<char>>, interpreter::Function>>
    Interpreter::find(const interpreter::Function& f) {
        return functionTable.find(f.identifier);
    }

    bool Interpreter::found(
            std::_Rb_tree_iterator<std::pair<const std::basic_string<char, std::char_traits<char>, std::allocator<char>>, interpreter::Variable<int>>> result) {
        return result != intTable.end();
    }
    bool Interpreter::found(
            std::_Rb_tree_iterator<std::pair<const std::basic_string<char, std::char_traits<char>, std::allocator<char>>, interpreter::Variable<float>>> result) {
        return result != floatTable.end();
    }
    bool Interpreter::found(
            std::_Rb_tree_iterator<std::pair<const std::basic_string<char, std::char_traits<char>, std::allocator<char>>, interpreter::Variable<bool>>> result) {
        return result != boolTable.end();
    }
    bool Interpreter::found(
            std::_Rb_tree_iterator<std::pair<const std::basic_string<char, std::char_traits<char>, std::allocator<char>>, interpreter::Variable<std::string>>> result) {
        return result != stringTable.end();
    }

    bool Interpreter::found(
            std::_Rb_tree_iterator<std::pair<const std::basic_string<char, std::char_traits<char>, std::allocator<char>>, interpreter::Function>> result) {
        return result != functionTable.end();;
    }

    template<> int Interpreter::pop<int>(const std::string& identifier) {
        auto result = find(interpreter::Variable<int>(identifier));
        if(!found(result)){
            throw std::runtime_error("Failed to find variable with identifier " + identifier);
        }
        int ret = result->second.values.back();
        // unfortunately intTable[identifier] kills the cpp compiler
        // so in order to pop_back a value from the values vector we have to completely replace the object
        // Copy the result variable
        interpreter::Variable<int> cpy(result->second);
        // pop the value from the copy
        cpy.values.pop_back();
        // remove the result
        intTable.erase(result);
        // insert the copy
        insert(cpy);
        // return the popped value
        return ret;
    }

    template<> float Interpreter::pop<float>(const std::string& identifier) {
        auto result = find(interpreter::Variable<float>(identifier));
        if(!found(result)){
            throw std::runtime_error("Failed to find variable with identifier " + identifier);
        }
        float ret = result->second.values.back();
        // unfortunately intTable[identifier] kills the cpp compiler
        // so in order to pop_back a value from the values vector we have to completely replace the object
        // Copy the result variable
        interpreter::Variable<float> cpy(result->second);
        // pop the value from the copy
        cpy.values.pop_back();
        // remove the result
        floatTable.erase(result);
        // insert the copy
        insert(cpy);
        // return the popped value
        return ret;
    }

    template<> bool Interpreter::pop<bool>(const std::string& identifier) {
        auto result = find(interpreter::Variable<bool>(identifier));
        if(!found(result)){
            throw std::runtime_error("Failed to find variable with identifier " + identifier);
        }
        bool ret = result->second.values.back();
        // unfortunately intTable[identifier] kills the cpp compiler
        // so in order to pop_back a value from the values vector we have to completely replace the object
        // Copy the result variable
        interpreter::Variable<bool> cpy(result->second);
        // pop the value from the copy
        cpy.values.pop_back();
        // remove the result
        boolTable.erase(result);
        // insert the copy
        insert(cpy);
        // return the popped value
        return ret;
    }

    template<> std::string Interpreter::pop<std::string>(const std::string& identifier) {
        auto result = find(interpreter::Variable<std::string>(identifier));
        if(!found(result)){
            throw std::runtime_error("Failed to find variable with identifier " + identifier);
        }
        std::string ret = result->second.values.back();
        // unfortunately intTable[identifier] kills the cpp compiler
        // so in order to pop_back a value from the values vector we have to completely replace the object
        // Copy the result variable
        interpreter::Variable<std::string> cpy(result->second);
        // pop the value from the copy
        cpy.values.pop_back();
        // remove the result
        stringTable.erase(result);
        // insert the copy
        insert(cpy);
        // return the popped value
        return ret;
    }

    // Tools

    void Interpreter::visit(parser::ASTProgramNode *programNode) {
        // For each statement, accept
        for(auto &statement : programNode -> statements)
            statement -> accept(this);
    }

    // Expressions
    // Literal visits add a new literal variable to the 'literalTYPE' variable in the variableTable
    void Interpreter::visit(parser::ASTLiteralNode<int> *literalNode) {
        interpreter::Variable<int> v("int", "literal", literalNode->val, literalNode->lineNumber);
//        pop<int>("literal");
        insert(v);
        currentType = "int";
        currentID = "literal";
    }

    void Interpreter::visit(parser::ASTLiteralNode<float> *literalNode) {
        interpreter::Variable<float> v("float", "literal", literalNode->val, literalNode->lineNumber);
//        pop<float>("literal");
        insert(v);
        currentType = "float";
        currentID = "literal";
    }

    void Interpreter::visit(parser::ASTLiteralNode<bool> *literalNode) {
        interpreter::Variable<bool> v("bool", "literal", literalNode->val, literalNode->lineNumber);
//        pop<bool>("literal");
        insert(v);
        currentType = "bool";
        currentID = "literal";
    }

    void Interpreter::visit(parser::ASTLiteralNode<std::string> *literalNode) {
        interpreter::Variable<std::string> v("string", "literal", literalNode->val, literalNode->lineNumber);
//        pop<std::string>("literal");
        insert(v);
        currentType = "string";
        currentID = "literal";
    }

    void Interpreter::visit(parser::ASTBinaryNode *binaryNode) {
        // First get the operator
        std::string op = binaryNode -> op;
        // Accept left expression
        binaryNode->left->accept(this);
        // Push left node into 0CurrentVariable
        if (currentType == "string"){
            insert(interpreter::Variable<std::string>("string", "0CurrentVariable",
                                                find(interpreter::Variable<std::string>(currentID))->second.values.back(),
                                                binaryNode->lineNumber));
        }else if (currentType == "int"){
            insert(interpreter::Variable<int>("int", "0CurrentVariable",
                                                      find(interpreter::Variable<int>(currentID))->second.values.back(),
                                                      binaryNode->lineNumber));
        }else if (currentType == "float"){
            insert(interpreter::Variable<float>("float", "0CurrentVariable",
                                                      find(interpreter::Variable<float>(currentID))->second.values.back(),
                                                      binaryNode->lineNumber));
        }else if (currentType == "bool"){
            insert(interpreter::Variable<bool>("bool", "0CurrentVariable",
                                                      find(interpreter::Variable<bool>(currentID))->second.values.back(),
                                                      binaryNode->lineNumber));
        }

        // Accept right expression
        binaryNode->right->accept(this);
        // We know both variables have the same type
        // So we check the currentType's type to see which operations we can do
        // check op type
        if (currentType == "string") {
            switch (lexer::determineOperatorType(binaryNode->op)) {
                /*
                 * The following code will follow this structure
                 *
                 * insert(Variable(TYPE, CURRENTVARIABLE, EXPRESSION, LINENUMBER)
                 *
                 * the EXPRESSION is built by popping the CURRENTVARIABLE list of values and operating with the currentID variable
                 * which is retreived via the find function.
                 * here I do not check with found() because we already know this variable exists as either the
                 * literal variable or any other variable as it is changed by the visits to the literal or identifier nodes.
                 *
                 * I am sure that there is a cleaner way of doing this but I still think this is pretty clean
                 *
                 * ...albeit very long and repetitive
                 *
                 */
                case lexer::TOK_NOT_EQAUL_TO:
                    insert(interpreter::Variable<bool>("bool", "0CurrentVariable",
                                                            pop<std::string>()
                                                            !=
                                                            find(interpreter::Variable<std::string>(currentID))->second.values.back(),
                                                            binaryNode->lineNumber));
                    break;
                case lexer::TOK_EQAUL_TO:
                    insert(interpreter::Variable<bool>("bool", "0CurrentVariable",
                                                                pop<std::string>()
                                                                ==
                                                                find(interpreter::Variable<std::string>(currentID))->second.values.back(),
                                                                binaryNode->lineNumber));
                    break;
                case lexer::TOK_PLUS:
                    insert(interpreter::Variable<std::string>("string", "0CurrentVariable",
                                                                pop<std::string>()
                                                                +
                                                                find(interpreter::Variable<std::string>(currentID))->second.values.back(),
                                                                binaryNode->lineNumber));
                    break;
                default:
                    // Should never get here because of the semantic pass but still included because of the default case
                    throw std::runtime_error("Expression on line " + std::to_string(binaryNode->lineNumber)
                                             + " has incorrect operator " + binaryNode->op
                                             + " acting between expressions of type " + currentType);
            }
        }else if (currentType == "int"){
            switch (lexer::determineOperatorType(binaryNode->op)) {
                case lexer::TOK_NOT_EQAUL_TO:
                    insert(interpreter::Variable<bool>("bool", "0CurrentVariable",
                                                       pop<int>()
                                                       !=
                                                       find(interpreter::Variable<int>(currentID))->second.values.back(),
                                                       binaryNode->lineNumber));
                    break;
                case lexer::TOK_EQAUL_TO:
                    insert(interpreter::Variable<bool>("bool", "0CurrentVariable",
                                                       pop<int>()
                                                       ==
                                                       find(interpreter::Variable<int>(currentID))->second.values.back(),
                                                       binaryNode->lineNumber));
                    break;
                case lexer::TOK_MORE_THAN:
                    insert(interpreter::Variable<bool>("bool", "0CurrentVariable",
                                                       pop<int>()
                                                       >
                                                       find(interpreter::Variable<int>(currentID))->second.values.back(),
                                                       binaryNode->lineNumber));
                    break;
                case lexer::TOK_LESS_THAN:
                    insert(interpreter::Variable<bool>("bool", "0CurrentVariable",
                                                       pop<int>()
                                                       <
                                                       find(interpreter::Variable<int>(currentID))->second.values.back(),
                                                       binaryNode->lineNumber));
                    break;
                case lexer::TOK_MORE_THAN_EQUAL_TO:
                    insert(interpreter::Variable<bool>("bool", "0CurrentVariable",
                                                       pop<int>()
                                                       >=
                                                       find(interpreter::Variable<int>(currentID))->second.values.back(),
                                                       binaryNode->lineNumber));
                    break;
                case lexer::TOK_LESS_THAN_EQUAL_TO:
                    insert(interpreter::Variable<bool>("bool", "0CurrentVariable",
                                                      pop<int>()
                                                      <=
                                                      find(interpreter::Variable<int>(currentID))->second.values.back(),
                                                      binaryNode->lineNumber));
                    break;
                // int and float accepted operators
                case lexer::TOK_PLUS:
                    insert(interpreter::Variable<int>("int", "0CurrentVariable",
                                                       pop<int>()
                                                       +
                                                       find(interpreter::Variable<int>(currentID))->second.values.back(),
                                                       binaryNode->lineNumber));
                    break;
                case lexer::TOK_ASTERISK:
                    insert(interpreter::Variable<int>("int", "0CurrentVariable",
                                                      pop<int>()
                                                      *
                                                      find(interpreter::Variable<int>(currentID))->second.values.back(),
                                                      binaryNode->lineNumber));
                    break;
                case lexer::TOK_DIVIDE:
                    // if divide by 0 happens, gcc will raise its own error, no need to change the structure to accomodate for this
                    insert(interpreter::Variable<int>("int", "0CurrentVariable",
                                                      pop<int>()
                                                      /
                                                      find(interpreter::Variable<int>(currentID))->second.values.back(),
                                                      binaryNode->lineNumber));
                    break;
                case lexer::TOK_MINUS:
                    insert(interpreter::Variable<int>("int", "0CurrentVariable",
                                                      pop<int>()
                                                      -
                                                      find(interpreter::Variable<int>(currentID))->second.values.back(),
                                                      binaryNode->lineNumber));
                    break;
                default:
                    // Should never get here because of the semantic pass but still included because of the default case
                    throw std::runtime_error("Expression on line " + std::to_string(binaryNode->lineNumber)
                                             + " has incorrect operator " + binaryNode->op
                                             + " acting between expressions of type " + currentType);
            }
        }else if (currentType == "float") {
            switch (lexer::determineOperatorType(binaryNode->op)) {
                case lexer::TOK_NOT_EQAUL_TO:
                    insert(interpreter::Variable<bool>("bool", "0CurrentVariable",
                                                       pop<float>()
                                                       !=
                                                       find(interpreter::Variable<float>(currentID))->second.values.back(),
                                                       binaryNode->lineNumber));
                    break;
                case lexer::TOK_EQAUL_TO:
                    insert(interpreter::Variable<bool>("bool", "0CurrentVariable",
                                                       pop<float>()
                                                       ==
                                                       find(interpreter::Variable<float>(currentID))->second.values.back(),
                                                       binaryNode->lineNumber));
                    break;
                case lexer::TOK_MORE_THAN:
                    insert(interpreter::Variable<bool>("bool", "0CurrentVariable",
                                                       pop<float>()
                                                       >
                                                       find(interpreter::Variable<float>(currentID))->second.values.back(),
                                                       binaryNode->lineNumber));
                    break;
                case lexer::TOK_LESS_THAN:
                    insert(interpreter::Variable<bool>("bool", "0CurrentVariable",
                                                       pop<float>()
                                                       <
                                                       find(interpreter::Variable<float>(currentID))->second.values.back(),
                                                       binaryNode->lineNumber));
                    break;
                case lexer::TOK_MORE_THAN_EQUAL_TO:
                    insert(interpreter::Variable<bool>("bool", "0CurrentVariable",
                                                       pop<float>()
                                                       >=
                                                       find(interpreter::Variable<float>(currentID))->second.values.back(),
                                                       binaryNode->lineNumber));
                    break;
                case lexer::TOK_LESS_THAN_EQUAL_TO:
                    insert(interpreter::Variable<bool>("bool", "0CurrentVariable",
                                                       pop<float>()
                                                       <=
                                                       find(interpreter::Variable<float>(currentID))->second.values.back(),
                                                       binaryNode->lineNumber));
                    break;
                    // int and float accepted operators
                case lexer::TOK_PLUS:
                    insert(interpreter::Variable<float>("float", "0CurrentVariable",
                                                       pop<float>()
                                                       +
                                                       find(interpreter::Variable<float>(currentID))->second.values.back(),
                                                       binaryNode->lineNumber));
                    break;
                case lexer::TOK_ASTERISK:
                    insert(interpreter::Variable<float>("float", "0CurrentVariable",
                                                        pop<float>()
                                                        *
                                                        find(interpreter::Variable<float>(currentID))->second.values.back(),
                                                        binaryNode->lineNumber));
                    break;
                case lexer::TOK_DIVIDE:
                    // if divide by 0 happens, gcc will raise its own error, no need to change the structure to accomodate for this
                    insert(interpreter::Variable<float>("float", "0CurrentVariable",
                                                        pop<float>()
                                                        /
                                                        find(interpreter::Variable<float>(currentID))->second.values.back(),
                                                        binaryNode->lineNumber));
                    break;
                case lexer::TOK_MINUS:
                    insert(interpreter::Variable<float>("float", "0CurrentVariable",
                                                        pop<float>()
                                                        -
                                                        find(interpreter::Variable<float>(currentID))->second.values.back(),
                                                        binaryNode->lineNumber));
                    break;
                default:
                    // Should never get here because of the semantic pass but still included because of the default case
                    throw std::runtime_error("Expression on line " + std::to_string(binaryNode->lineNumber)
                                             + " has incorrect operator " + binaryNode->op
                                             + " acting between expressions of type " + currentType);
            }
        }else if (currentType == "bool"){
            switch (lexer::determineOperatorType(binaryNode->op)) {
                case lexer::TOK_NOT_EQAUL_TO:
                    insert(interpreter::Variable<bool>("bool", "0CurrentVariable",
                                                        pop<bool>()
                                                        !=
                                                        find(interpreter::Variable<bool>(currentID))->second.values.back(),
                                                        binaryNode->lineNumber));
                    break;
                case lexer::TOK_EQAUL_TO:
                    insert(interpreter::Variable<bool>("bool", "0CurrentVariable",
                                                       pop<bool>()
                                                       ==
                                                       find(interpreter::Variable<bool>(currentID))->second.values.back(),
                                                       binaryNode->lineNumber));
                    break;
                case lexer::TOK_AND:
                    insert(interpreter::Variable<bool>("bool", "0CurrentVariable",
                                                       pop<bool>()
                                                       &&
                                                       find(interpreter::Variable<bool>(currentID))->second.values.back(),
                                                       binaryNode->lineNumber));
                    break;
                case lexer::TOK_OR:
                    insert(interpreter::Variable<bool>("bool", "0CurrentVariable",
                                                       pop<bool>()
                                                       ||
                                                       find(interpreter::Variable<bool>(currentID))->second.values.back(),
                                                       binaryNode->lineNumber));
                    break;
                case lexer::TOK_MORE_THAN:
                    insert(interpreter::Variable<bool>("bool", "0CurrentVariable",
                                                       pop<bool>()
                                                       >
                                                       find(interpreter::Variable<bool>(currentID))->second.values.back(),
                                                       binaryNode->lineNumber));
                    break;
                case lexer::TOK_LESS_THAN:
                    insert(interpreter::Variable<bool>("bool", "0CurrentVariable",
                                                       pop<bool>()
                                                       <
                                                       find(interpreter::Variable<bool>(currentID))->second.values.back(),
                                                       binaryNode->lineNumber));
                    break;
                case lexer::TOK_MORE_THAN_EQUAL_TO:
                    insert(interpreter::Variable<bool>("bool", "0CurrentVariable",
                                                       pop<bool>()
                                                       >=
                                                       find(interpreter::Variable<bool>(currentID))->second.values.back(),
                                                       binaryNode->lineNumber));
                    break;
                case lexer::TOK_LESS_THAN_EQUAL_TO:
                    insert(interpreter::Variable<bool>("bool", "0CurrentVariable",
                                                       pop<bool>()
                                                       <=
                                                       find(interpreter::Variable<bool>(currentID))->second.values.back(),
                                                       binaryNode->lineNumber));
                    break;
                default:
                    // Should never get here because of the semantic pass but still included because of the default case
                    throw std::runtime_error("Expression on line " + std::to_string(binaryNode->lineNumber)
                                             + " has incorrect operator " + binaryNode->op
                                             + " acting between expressions of type " + currentType);
            }
        }
    }

    void Interpreter::visit(parser::ASTIdentifierNode *identifierNode) {
        // Build variable shells
        interpreter::Variable<int> i(identifierNode->identifier);
        interpreter::Variable<float> f(identifierNode->identifier);
        interpreter::Variable<bool> b(identifierNode->identifier);
        interpreter::Variable<std::string> s(identifierNode->identifier);
        // Check that a variable with this identifier exists
        auto resultI = find(i);
        if(found(resultI)) {
            // if identifier has been found
            // change current Type
            currentType = resultI->second.type;
            // change current ID
            currentID = resultI->second.identifier;
            // Then return
            return;
        }
        auto resultF = find(f);
        if(found(resultF)) {
            // if identifier has been found
            // change current Type
            currentType = resultF->second.type;
            // change current ID
            currentID = resultF->second.identifier;
            // Then return
            return;
        }
        auto resultB = find(b);
        if(found(resultB)) {
            // if identifier has been found
            // change current Type
            currentType = resultB->second.type;
            // change current ID
            currentID = resultB->second.identifier;
            // Then return
            return;
        }
        auto resultS = find(s);
        if(found(resultS)) {
            // if identifier has been found
            // change current Type
            currentType = resultS->second.type;
            // change current ID
            currentID = resultS->second.identifier;
            // Then return
            return;
        }
        // Variable hasn't been found (should never get here)
        throw std::runtime_error("Variable with identifier " + i.identifier + " called on line "
                                 + std::to_string(i.lineNumber) + " has not been declared.");
    }

    void Interpreter::visit(parser::ASTUnaryNode *unaryNode) {
        // visit the expression to get the type and id
        unaryNode->exprNode->accept(this);
        // now we check the type
        if(currentType == "int"){
            insert(interpreter::Variable<int>("int", "0CurrentVariable",
                                               pop<int>() * -1,
                                              unaryNode->lineNumber));
        }else if(currentType == "float"){
            insert(interpreter::Variable<float>("float", "0CurrentVariable",
                                              pop<float>() * -1,
                                              unaryNode->lineNumber));
        }else if(currentType == "bool"){
            insert(interpreter::Variable<bool>("bool", "0CurrentVariable",
                                                ! pop<bool>(),
                                                unaryNode->lineNumber));
        }else{
            // should get here
            throw std::runtime_error("Expression on line " + std::to_string(unaryNode->lineNumber)
                                     + " has incorrect operator " + unaryNode->op
                                     + " acting for expression of type " + currentType);
        }
    }

    void Interpreter::visit(parser::ASTFunctionCallNode *functionCallNode) {

    }
    // Expressions

}