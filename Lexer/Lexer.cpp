//
// Created by aiden on 26/04/2021.
//

#include "Lexer.h"


lexer::Lexer::Lexer(){
    int epsilon = -1;

    const unsigned int LEN_STATES = 7;

    bool is_final[LEN_STATES] = {false};

    for (int i = 0; i < LEN_STATES; i++){
        is_final[i] = lexer::TRANSITION_TYPE(i) == OTHER || lexer::TRANSITION_TYPE(i) == NEWLINE
                      || lexer::TRANSITION_TYPE(i) == END;
    }
}