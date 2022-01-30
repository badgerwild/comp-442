//
// Created by jason on 1/22/22.
//
#include <iostream>
#include <fstream>
#include <utility>
#include "lexer.h"
#include "../DFA/indexTemplate.h"
#include "../DFA/DFA.h"
const int FINAL = -2;
const int NOTFINAL = -3;
const int BACKTRACK = -4;
const int NORMAL = -5;

Lexer::Lexer(std::vector<int> states, std::vector<char> inputs, std::vector<std::vector<int>> lookUpTable) {
    this->lineNumber = 0;
    this->states = states;
    this->inputs = inputs;
    this->lookUpTable = lookUpTable;
    this->charPosition = 0;
}

Lexer::~Lexer() {}

int Lexer::getProgramSize() {
    return program.size();
}

int Lexer::getLineNumber() {
    return lineNumber;
}

void Lexer::addFile(std::string file) {
    this->fileName = file;
}

void Lexer::readFile() {
    std::string temp;
    std::vector<std::string> lineStorage;
    std::ifstream programFile(this->fileName);
    if (programFile.is_open()){
        while (getline(programFile, temp)){
            temp+= '\n';
            lineStorage.push_back(temp);
        }
    }
    else {
        std::cout<< "file not found";
    }
    programFile.close();
    this->program = lineStorage;
}
int Lexer::tableLookUp(int state, char input) {
    int stateIndex{}, charIndex{}, newState{};
    stateIndex = findIndex<int>(state, states);
    charIndex = findIndex<char>(input, inputs);
    if (charIndex == -1 || stateIndex == -1){
        newState = -1;
    }
    else {
        newState = lookUpTable[stateIndex][charIndex];
    }
    return newState;
}

char Lexer::nextChar() {
    int maxLen = this->program[lineNumber].size();
    char temp = this->program[lineNumber][charPosition];
    ++this->charPosition;
    //if(this->charPosition > maxLen) {
    if (temp == '\n'){
        ++this->lineNumber;
        this->charPosition = 0;
    }
    return temp;
}

bool Lexer::isFinal(int stateName) {
    int tempIndex = findIndex<int>(stateName, this->states);
    int find = this->inputs.size();
    int status = this->lookUpTable[tempIndex][find];
    bool val = status == FINAL;
    return val;
}

bool Lexer::backTrack(int stateName) {
    int tempIndex = findIndex<int>(stateName, this->states);
    int find = this->inputs.size()+1;
    int status = this->lookUpTable[tempIndex][find];
    bool val = status == BACKTRACK;
    return val;
}
//TODO Figure out a proper stop condition
Token Lexer::nextToken() {
int state = 1;
Token token;
std::string lex{};
int type{};
char lookUp{};
while (token.isEmpty()){
    lookUp = nextChar();
    if (lookUp == '\n'){
        continue;
    }
    state = tableLookUp(state, lookUp);
    lex.push_back(lookUp);
    if (isFinal(state)){
        type = state;
        //TODO save lookup as previous state and revert to it upon backtrack
        if (backTrack(state)){
            lex.pop_back();
        }
        token.create(lex, type, this->lineNumber);
    }
}
    return token;
}