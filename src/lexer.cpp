//
// Created by jason on 1/22/22.
//
#include <iostream>
#include <fstream>
#include "lexer.h"
#include "../DFA/indexTemplate.h"
#include "../DFA/DFA.h"
const int FINAL = -2;
const int NOTFINAL = -3;
const int BACKTRACK = -4;
const int NORMAL = -5;
const char SYMBOLS[18] = {'+', ',','&', '*', ';', '!', '.', '[',']','(', ')', '{','}', '>','<','=',':','-'};
Lexer::Lexer() {

    DFA dfa = DFA();
    dfa.addState(State(1,false, false));
    dfa.addState(State(2,false, false));
    dfa.addState(State(3,false, false));
    dfa.addState(State(4, true, true));
    dfa.addState(State(5,false,false));
    //Invalid char state
    dfa.addState(State(-1, false, true));
    // EOF State
    dfa.addState(State(6, false, true));
    //id states
    dfa.addState(State(7, false, false));
    dfa.addState(State(8, false, false));
    dfa.addState(State(9,true, true));
    //float states
    dfa.addState(State(10, false, false));
    dfa.addState(State(11, false, false));
    dfa.addState(State(12, false, false));
    dfa.addState(State(13, false, false));
    dfa.addState(State(14, false, false));
    dfa.addState(State(15, false, false));
    dfa.addState(State(16, false, false));
    dfa.addState(State(17, false, false));
    dfa.addState(State(18, true, true));
    dfa.addState(State(19, false, false));

    //single punc states
    dfa.addState(State(20, false, true));
    dfa.addState(State(20, false, true));
    dfa.addState(State(22, false, true));
    dfa.addState(State(23, false, true));
    dfa.addState(State(24, false, true));
    dfa.addState(State(25, false, true));
    dfa.addState(State(26, false, true));
    dfa.addState(State(27, false, true));
    dfa.addState(State(28, false, true));
    dfa.addState(State(29, false, true));
    dfa.addState(State(30, false, true));
    dfa.addState(State(31, false, true));
    dfa.addState(State(32, false, true));
// double punk states
    dfa.addState(State(33, false, false));
    dfa.addState(State(34, true, true));
    dfa.addState(State(35, false, true));
    dfa.addState(State(36, false, false));
    dfa.addState(State(37, true, true));
    dfa.addState(State(38, false, true));
    dfa.addState(State(39, false, true));
    dfa.addState(State(40, false, false));
    dfa.addState(State(41, true, true));
    dfa.addState(State(42, false, true));
    dfa.addState(State(43, false, false));
    dfa.addState(State(44, true, true));
    dfa.addState(State(45, false, true));
    dfa.addState(State(46, false, false));
    dfa.addState(State(47, true, true));
    dfa.addState(State(48, false, true));
    dfa.addState(State(49, false, true));

    dfa.addState(State(50, true, true ));
    dfa.addState(State(51, true, true ));

//State 1 transition functions
//int
    for(char i = '1'; i<='9';++i){
        dfa.addTransition(2,1, i);
    }

    dfa.addTransition(3,1, '0');
    // to id
    for (char i = 'a'; i<= 'z'; ++i ){
        dfa.addTransition(8, 1, i);
    }
    for (char i = 'A'; i<= 'Z'; ++i ){
        dfa.addTransition(8, 1, i);
    }

//single punk
    dfa.addTransition(20, 1, '+');
    dfa.addTransition(21, 1, ',');
    dfa.addTransition(22, 1, '&');
    dfa.addTransition(23, 1, '|');
    dfa.addTransition(24, 1, '!');
    dfa.addTransition(25, 1, ';');
    dfa.addTransition(26, 1, '.');
    dfa.addTransition(27, 1, '[');
    dfa.addTransition(28, 1, ']');
    dfa.addTransition(29, 1, ')');
    dfa.addTransition(30, 1, '(');
    dfa.addTransition(31, 1, '{');
    dfa.addTransition(32, 1, '}');
    dfa.addTransition(49, 1, '*');
    //double punk
    dfa.addTransition(33, 1, '>');
    dfa.addTransition(36, 1, '<');
    dfa.addTransition(40, 1, '=');
    dfa.addTransition(43, 1, ':');
    dfa.addTransition(46, 1, '-');

//invalid transitions
    dfa.addTransition(17, 1, '_');
    //space
    dfa.addTransition(1,1, ' ');
    //return
    dfa.addTransition(6,1,'\r');
    // state 2 transition functions

    for (char i = '0'; i < '9' ; ++i) {
        dfa.addTransition(2,2, i);
    }
    dfa.addTransition(4,2, ' ');
    dfa.addTransition(4,2,'\r');
    dfa.addTransition(4,2, '\n');
//Any
    dfa.addTransition(4,2, ' ');
    for (const char &c: SYMBOLS){
        dfa.addTransition(4,2, c);
    }

    dfa.addTransition(9,8, ' ');
    for (const char &c: SYMBOLS){
        dfa.addTransition(9,8, c);
    }
    dfa.addTransition(10, 3, '.');
    dfa.addTransition(10,2,'.');
    //int + char = invlaid int state 5

    for (char i = 'a'; i<= 'z'; ++i ){
        dfa.addTransition(5, 2, i);
    }
    for (char i = 'A'; i<= 'Z'; ++i ){
        dfa.addTransition(5, 2, i);
    }
    dfa.addTransition(5, 2, '_');

    // state 3 transsion functions
    for (char i = '0'; i<= '9'; ++i) {
        dfa.addTransition(5,3, i);
    }
    dfa.addTransition(4,3, ' ');
    dfa.addTransition(10,3,'.');

    dfa.addTransition(5, 3, '_');
    //dfa.addTransition(6,1,'\r');
//state 5
    dfa.addTransition(1,5, ' '); //TODO what the fuck is this

    //Panik
    for (char i = 'a'; i<= 'z'; ++i ){
        dfa.addTransition(5, 5, i);
    }
    for (char i = 'A'; i<= 'Z'; ++i ){
        dfa.addTransition(5, 5, i);
    }
    for (char i = '0'; i < '9'; ++i) {
        dfa.addTransition(5, 5, i);
    }
    dfa.addTransition(17, 5, '.');
    //kalm
    for (const char &c: SYMBOLS){
        if (c != '.') {
            dfa.addTransition(50, 5, c);
        }
    }
    dfa.addTransition(50, 5, '\n');

    //state 6
    dfa.addTransition(1,4, ' ');

    //state 8
    for (char i = 'a'; i<= 'z'; ++i ){
        dfa.addTransition(8, 8, i);
    }
    for (char i = 'A'; i<= 'Z'; ++i ){
        dfa.addTransition(8, 8, i);
    }
    for (char i = '0'; i < '9'; ++i) {
        dfa.addTransition(8, 8, i);
    }

    dfa.addTransition(8, 8, '_');
    dfa.addTransition(9, 8, '\n');
    for (const char &c: SYMBOLS){
        dfa.addTransition(9, 8, c);
    }


    // Float
    dfa.addTransition(11, 10, '0');
    for (char i = '1'; i<= '9' ; ++i) {
        dfa.addTransition(12, 10, i);
    }
    dfa.addTransition(18, 11, '\n'); //TODO add more accept character
    for (char i = '0'; i<= '9' ; ++i) {
        dfa.addTransition(12, 11, i);
    }
    // float with a single zero accept on symbol
    for (const char &c: SYMBOLS){
        dfa.addTransition(11, 18, c);
    }

   //float with single digit to accept on symbol
    for (const char &c: SYMBOLS){
        dfa.addTransition(12, 18, c);
    }
    dfa.addTransition(12, 18, '\n');
    // dfa.addTransition(18, 12, '\n'); //TODO add more accept character
    for (char i = '1'; i<= '9' ; ++i) {
        dfa.addTransition(13, 12, i);
    }
    dfa.addTransition(19, 12, '0');
    dfa.addTransition(14, 12, 'e');

    dfa.addTransition(18, 13, '\n'); //TODO add more accept character
    dfa.addTransition(12, 13, '0');// 0 back to 12
    dfa.addTransition(14, 13, 'e');

    for (char i = '1'; i<= '9' ; ++i) {
        dfa.addTransition(13, 13, i);
    }

    dfa.addTransition(15, 14, '+');
    dfa.addTransition(15, 14, '-');
   // panik
    for (char i = '0'; i<= '9' ; ++i) {
        dfa.addTransition(17, 14, i);
    }
    for (char i = 'A'; i<= 'Z' ; ++i) {
        dfa.addTransition(17, 14, i);
    }
    for (char i = 'a'; i<= 'z' ; ++i) {
        dfa.addTransition(17, 14, i);
    }
    for (const char &c: SYMBOLS) {
        if (c != '+' && c !='-'){
            dfa.addTransition(51, 14, c);
        }
        dfa.addTransition(51, 14, ' ');
        dfa.addTransition(51, 14, '\n');
    }



//TODO fill in the transistions
    dfa.addTransition(17, 15, '0');//invlaid

    for (char i = '1'; i<= '9' ; ++i) {
        dfa.addTransition(16, 15, i);
    }
    for (char i = '0'; i<= '9' ; ++i) {
        dfa.addTransition(16, 16, i);
    }
    dfa.addTransition(18, 16, '\n');

    dfa.addTransition(19, 19, '0');

    for (char i = '1'; i<= '9' ; ++i) {
        dfa.addTransition(13, 19, i);
    }
    //punk trans
    dfa.addTransition(34, 33, '\n');//EXPAND
    dfa.addTransition(35, 33, '=');

    dfa.addTransition(37, 36, '\n');
    dfa.addTransition(38, 36, '>');
    dfa.addTransition(39, 36, '=');

    dfa.addTransition(41, 40, '\n');
    dfa.addTransition(42, 40, '=');

    dfa.addTransition(44, 43, '\n');
    dfa.addTransition(44, 43, ' ');
    dfa.addTransition(45, 43, ':');

    dfa.addTransition(47, 46, '\n');
    dfa.addTransition(48, 46, '>');
//Panik
    for (char i = 'a'; i<= 'z'; ++i ){
        dfa.addTransition(17, 17, i);
    }
    for (char i = 'A'; i<= 'Z'; ++i ){
        dfa.addTransition(17, 17, i);
    }
    dfa.addTransition(17, 17, '.');
    for (char i = '0'; i < '9'; ++i) {
            dfa.addTransition(17, 17, i);
    }

    //kalm
    for (const char &c: SYMBOLS){
        if (c != '.') {
            dfa.addTransition(51, 17, c);
        }
    }
    dfa.addTransition(51, 17, '\n');


// creating state and alphabet vectors
    std::vector<int> dfaStates = dfa.stateList();
    std::vector<char> alphabet = dfa.alphabet();
// generating the look up table
    std::vector<std::vector<int>> tableau = dfa.generateTable(dfaStates, alphabet);
    this->states = dfaStates;
    this->inputs = alphabet;
    this->lookUpTable = tableau;
    this->lineNumber = 0;
    this->charPosition = 0;
}

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
    char temp;
    if ((this->charPosition == maxLen-1) && (lineNumber == this->program.size()-1)){
        temp = '\r';

    }
    else {
        temp = this->program[lineNumber][charPosition];
        ++this->charPosition;
        if ((temp == '\n') && (lineNumber < this->program.size()-1)) {
            ++this->lineNumber;
            this->charPosition = 0;
        }
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

//TODO 1.Deal with Space problem, 2.error recovery add specific error ever where 3. deal with invalid id
Token Lexer::nextToken() {
int state = 1;
Token token;
std::string lex{};
int type{};
char lookUp{};
int line{};
while (token.isEmpty()){
    lookUp = nextChar();
    if (lookUp == '\t'){
        continue;
    }
    state = tableLookUp(state, lookUp);
    lex.push_back(lookUp);
    if (isFinal(state)){
        type = state;
        if (backTrack(state)){
            if (lookUp == '\n') {
                int temp = this-> lineNumber;
                line = temp-1;
            }
            else{
                line = this->lineNumber;
            }
            lex.pop_back();
            --charPosition;
        }
        else {
            line = this->lineNumber;
        }
        if (lex == "\n"){
            state = 1;
            lex.pop_back();
            continue;
        }
        token.create(lex, type, line+1);
    }
}
    return token;
}