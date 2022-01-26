//
// Created by jason on 1/22/22.
//

#ifndef COMP_442_LEXER_H
#define COMP_442_LEXER_H
#include <string>
// temporary transition table just to test integer DFA
const std::string TRANS_TABLE_HEADER[] = {"state", "int_1_9", "zero", "final"};
const  char TRANS_TABLE[][4]= {{'a','b', 'c', 'N'},{'b','b', 'b', 'Y'},{'c', char(0), char(0), 'Y' }};

class Lexer{


};

#endif //COMP_442_LEXER_H
