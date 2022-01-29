//
// Created by jason on 1/22/22.
//

#ifndef COMP_442_LEXER_H
#define COMP_442_LEXER_H
#include <string>
#include <vector>
#include "Token.h"

class Lexer{
    std::string fileName;
    std::vector<std::string> program;
    int charPosition;
    int lineNumber;
    //TODO make these into pointers
    std::vector<int> states;
    std::vector<char> inputs;
    std::vector<std::vector<int>> lookUpTable;


    Lexer(std::vector<int> states, std::vector<char> inputs, std::vector<std::vector<int>> lookUpTable);
    ~Lexer();
    void addFile(std::string file);
    void readFile();
    Token nextToken();
    int tableLookUp(int state, char input);
    char nextChar();
    bool isFinal();


//TODO backTrack() function, whatever the this does???
    bool backTrack();


};

#endif //COMP_442_LEXER_H
