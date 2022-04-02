//
// Created by jason on 1/22/22.
//
#include <iostream>
#include <fstream>
#include <unordered_set>
#include "lexer.h"
#include "../DFA/indexTemplate.h"

#include "../DFA/DFA.h"
const int FINAL = -2;
const int NOTFINAL = -3;
const int BACKTRACK = -4;
const int NORMAL = -5;
const char SYMBOLS[20] = {'|','+', ',','&', '*', ';', '!', '.', '[',']','(', ')', '{','}', '>','<','=',':','-', '/'};
const std::unordered_set<char> NOTADD{'\t', ' '};


DfaSingleton::DfaSingleton() {
    dfa = DFA();
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
    dfa.addState(State(21, false, true));
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
//invlaid ID states
    dfa.addState(State(50, true, true ));
    dfa.addState(State(51, true, true ));
    dfa.addState(State(52, false, false));
    dfa.addState(State(53, true, true));
    dfa.addState(State(54, false, false));
    dfa.addState(State(55, false, false));
    dfa.addState(State(56, false, false));
    dfa.addState(State(57, false, true));
    dfa.addState(State(58, false, false));
    dfa.addState(State(59, false, true));
    dfa.addState(State(60, true, true));
    dfa.addState(State(61, false, true));
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
    dfa.addTransition(54,1,'/');

//invalid transitions
    dfa.addTransition(52, 1, '_');
    //space
    dfa.addTransition(1,1, ' ');
    dfa.addTransition(1,1, '\t');
    //return
    dfa.addTransition(6,1,'\r');
    // state 2 transition functions

    for (char i = '0'; i < '9' ; ++i) {
        dfa.addTransition(2,2, i);
    }
    dfa.addTransition(4,2, ' ');
    dfa.addTransition(4,2, '\t');
    dfa.addTransition(4,2,'\r');
    dfa.addTransition(4,2, '\n');
//Any
    dfa.addTransition(4,2, ' ');
    for (const char &c: SYMBOLS){
        dfa.addTransition(4,2, c);
    }

    dfa.addTransition(9,8, ' ');
    dfa.addTransition(9,8, '\t');
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
    dfa.addTransition(4,3, '\t');
    dfa.addTransition(10,3,'.');
    for (const char &c: SYMBOLS){
        if (c!= '.') {
            dfa.addTransition(4, 3, c);
        }
    }


    dfa.addTransition(5, 3, '_');
    //dfa.addTransition(6,1,'\r');
//state 5
    dfa.addTransition(1,5, '\t');
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
    dfa.addTransition(1,4, '\t');

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
    dfa.addTransition(18, 11, '\n');
    for (char i = '0'; i<= '9' ; ++i) {
        dfa.addTransition(12, 11, i);
    }
    // float with a single zero accept on symbol
    for (const char &c: SYMBOLS){
        dfa.addTransition(18, 11, c);
    }

    //float with single digit to accept on symbol
    for (const char &c: SYMBOLS){
        dfa.addTransition(18, 12, c);
    }
    dfa.addTransition(18, 12, '\n');
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
        dfa.addTransition(51,14, '\t');
        dfa.addTransition(51, 14, '\n');
    }

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
    dfa.addTransition(34, 33, '\n');
    dfa.addTransition(34, 33, '\t');
    dfa.addTransition(34, 33, ' ');


    dfa.addTransition(35, 33, '=');

    dfa.addTransition(37, 36, '\n');
    dfa.addTransition(37, 36, '\t');
    dfa.addTransition(37, 36, ' ');

    dfa.addTransition(38, 36, '>');
    dfa.addTransition(39, 36, '=');
    for (char i = '1'; i<= '9';++i){
        dfa.addTransition(37, 36, i);
    }
    for (char i = 'a'; i<= 'z';++i){
        dfa.addTransition(37, 36, i);
    }
    for (char i = 'A'; i<= 'Z';++i){
        dfa.addTransition(37, 36, i);
    }

    dfa.addTransition(41, 40, '\n');
    dfa.addTransition(41, 40, '\t');
    dfa.addTransition(41, 40, ' ');
    dfa.addTransition(41, 40, '(');
    dfa.addTransition(42, 40, '=');

    dfa.addTransition(44, 43, '\n');
    dfa.addTransition(44, 43, ' ');
    dfa.addTransition(44,43, '\t');
    dfa.addTransition(45, 43, ':');

    dfa.addTransition(47, 46, '\n');
    dfa.addTransition(47, 46, '\t');
    dfa.addTransition(47, 46, ' ');
    dfa.addTransition(48, 46, '>');

    for (char i = '1'; i<= '9';++i){
        dfa.addTransition(47, 46, i);
    }
    for (char i = 'a'; i<= 'z';++i){
        dfa.addTransition(47, 46, i);
    }
    for (char i = 'A'; i<= 'Z';++i){
        dfa.addTransition(47, 46, i);
    }

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
    dfa.addTransition(52, 1, '_');
    dfa.addTransition(52, 52, '_');
    //Panik
    for (char i = 'a'; i<= 'z'; ++i ){
        dfa.addTransition(52, 52, i);
    }
    for (char i = 'A'; i<= 'Z'; ++i ){
        dfa.addTransition(52, 52, i);
    }
    for (char i = '0'; i < '9'; ++i) {
        dfa.addTransition(52, 52, i);
    }

    //kalm
    for (const char &c: SYMBOLS){
        dfa.addTransition(53, 52, c);
    }
    dfa.addTransition(53, 52, '\n');
    dfa.addTransition(53, 52, '\r');
// comments
    dfa.addTransition(58, 54, '/');
    for (char i = 'a'; i<= 'z'; ++i ){
        dfa.addTransition(58, 58, i);
    }
    for (char i = 'A'; i<= 'Z'; ++i ){
        dfa.addTransition(58, 58, i);
    }
    for (char i = '0'; i < '9'; ++i) {

        dfa.addTransition(58, 58, i);

    }
    for (const char &c: SYMBOLS) {
        dfa.addTransition(58, 58, c);
    }
    dfa.addTransition(58, 58, '\t');
    dfa.addTransition(58, 58, ' ');
    dfa.addTransition(59, 58, '\n');
    dfa.addTransition(59, 58, '\r');


// Multi line comments:
    dfa.addTransition(55, 54, '*');
    for (char i = 'a'; i<= 'z'; ++i ){
        dfa.addTransition(55, 55, i);
    }
    for (char i = 'A'; i<= 'Z'; ++i ){
        dfa.addTransition(55, 55, i);
    }
    for (char i = '0'; i < '9'; ++i) {
        dfa.addTransition(55, 55, i);

    }
    for (const char &c: SYMBOLS) {
        if (c != '*') {
            dfa.addTransition(55, 55, c);
        }
    }
    dfa.addTransition(55, 55, '\t');
    dfa.addTransition(55, 55, ' ');
    dfa.addTransition(55, 55, '\n');

    dfa.addTransition(56, 55, '*');
    dfa.addTransition(57, 56, '/');


//comments that continue after a *
    for (char i = 'a'; i<= 'z'; ++i ){
        dfa.addTransition(55, 56, i);
    }
    for (char i = 'A'; i<= 'Z'; ++i ){
        dfa.addTransition(55, 56, i);
    }
    for (char i = '0'; i < '9'; ++i) {

        dfa.addTransition(55, 56, i);

    }
    for (const char &c: SYMBOLS) {
        if (c != '*' && c!= '/') {
            dfa.addTransition(55, 56, c);
        }
    }
    dfa.addTransition(56, 56, '*');
    dfa.addTransition(55, 56, '\t');
    dfa.addTransition(55, 56, ' ');
    dfa.addTransition(55, 56, '\n');


    dfa.addTransition(61, 56, '\r');
    dfa.addTransition(61, 55, '\r');


    //div
    for (char i = 'a'; i<= 'z'; ++i ){
        dfa.addTransition(60, 54, i);
    }
    for (char i = 'A'; i<= 'Z'; ++i ){
        dfa.addTransition(60, 54, i);
    }
    for (char i = '0'; i < '9'; ++i) {

        dfa.addTransition(60, 54, i);

    }
    for (const char &c: SYMBOLS){
        if( c != '/' && c!= '*') {
            dfa.addTransition(60, 54, c);
        }
    }
    dfa.addTransition(60, 54, '\n');
    dfa.addTransition(60, 54, '\t');
    dfa.addTransition(60, 54, ' ');

    // inst_ = nullptr;

}

std::shared_ptr<DfaSingleton>& DfaSingleton::getInstance() {
    static std::shared_ptr<DfaSingleton> inst_ = nullptr;
    if (!inst_){
        inst_.reset(new DfaSingleton());
    }
    return inst_;
}

std::vector<char> DfaSingleton::getAlphabet() {
    return dfa.alphabet();
}

std::vector<int> DfaSingleton::getDfaState() {
    return dfa.stateList();
}

std::vector<std::vector<int>> DfaSingleton::getTable(std::vector<int> alpha, std::vector<char> states){
    return dfa.generateTable(alpha, states);
}

Lexer::Lexer() {
    std::shared_ptr<DfaSingleton> dfa = DfaSingleton::getInstance();
    this->states = dfa->getDfaState();
    this->inputs = dfa->getAlphabet();
    this->lookUpTable = dfa->getTable(this->states, this->inputs);
    this->lineNumber = 0;
    this->charPosition = 0;
    std::vector<std::string> outFiles = {fileName+".outlexerrors", fileName+".outlextokens"};

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
    //replaces last '\n' with a '\r'
    lineStorage[lineStorage.size()-1][lineStorage[lineStorage.size()-1].size()-1] = '\r';
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
    if (newState == -1 && state == 55) {
        newState = 55;
    }
    else if(newState == -1 && state ==58 ) {
        newState = 58;
    }
    else if (newState == -1 && state == 56){
        newState = 55;
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
    if (lookUp == '\000'){
        continue;
    }
    state = tableLookUp(state, lookUp);
    //if (lookUp != ' ') {
    if (NOTADD.find(lookUp) == NOTADD.end()) {
        lex.push_back(lookUp);
    }
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
            if (NOTADD.find(lookUp) == NOTADD.end()) {
                lex.pop_back();
            }
            if (lookUp != '\r') {
                --charPosition;
            }
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
//DEBUG
//std::cout<< lineNumber<< std::endl;
    return token;
}
