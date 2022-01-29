//
// Created by jason on 1/22/22.
//
#include <iostream>
#include <fstream>
#include <utility>
#include "lexer.h"
#include "../DFA/DFA.h"
//TODO populate all these functions
Lexer::Lexer(std::vector<int> states, std::vector<char> inputs, std::vector<std::vector<int>> lookUpTable) {
    this->lineNumber = 0;
    this->states = states;
    this->inputs = inputs;
    this->lookUpTable = lookUpTable;
}

Lexer::~Lexer() {}

void Lexer::addFile(std::string file) {
    this->fileName = file;
}

void Lexer::readFile() {
    std::string temp;
    std::vector<std::string> lineStorage;
    std::ifstream programFile(this->fileName);
    if (programFile.is_open()){
        while (getline(programFile, temp)){
            lineStorage.push_back(temp);
        }
    }
    else {
        std::cout<< "file not found";
    }
    programFile.close();
    this->program = lineStorage;
}
//TODO Finish this function first thing. then should be good to move on to nextToken
int Lexer::tableLookUp(int state, char input) {
    return 1;
}

char Lexer::nextChar() {
    int maxLen = this->program[lineNumber].size();
    if(this->charPosition > maxLen) {
        ++this->lineNumber;
        this->charPosition = 0;
    }
    char temp = this->program[lineNumber][charPosition];
    ++this->charPosition;
    return temp;
}

bool Lexer::isFinal() {
    return true;
}
Token Lexer::nextToken() {
int state = 1;
Token token;
std::string lex{};
std::string type{};
char lookUp{};
while (token.isEmpty()){
    lookUp = nextChar();
    state = tableLookUp(state, lookUp);
    lex.push_back(lookUp);
    if (isFinal()){
        if (/*backTrack()*/ 8 ==8){
            //TODO use backtracking to determin char and return type or whatever we need to do
            type = "SOMETHING";
        }
        else {
            //base case without backtracking
            type = "SOMETHING ELSE";
        }
        token.create(lex, type, this->lineNumber);
    }
    ++this->lineNumber;
    return token;
}

}