//
// Created by jason on 1/22/22.
//

#ifndef COMP_442_LEXER_H
#define COMP_442_LEXER_H
#include <string>
#include <vector>
#include <memory>
#include "Token.h"
#include "DFA/DFA.h"
#include "logger/logSubject.h"
#include "logger/lexerLogObservers.h"

class DfaSingleton {
private:
    DFA dfa;
    //static std::shared_ptr<DfaSingleton> inst_;
    DfaSingleton();
    DfaSingleton(const DfaSingleton&);
    DfaSingleton& operator=(const DfaSingleton);

public:
    static std::shared_ptr<DfaSingleton>& getInstance();
    std::vector<int> getDfaState();
    std::vector<char> getAlphabet();
    std::vector<std::vector<int>> getTable(std::vector<int> alpha, std::vector<char> states);

};


class Lexer{
private:
    std::string fileName;
    std::vector<std::string> program;
    int charPosition;
    int lineNumber;
    //TODO make these into pointers
    std::vector<int> states;
    std::vector<char> inputs;
    std::vector<std::vector<int>> lookUpTable;
    std::shared_ptr<lexerLogObservers> logObserver;
    Logger* logger;


public:
    Lexer();
    Lexer(Logger *logger_, std::string file);
    Lexer(Logger *logger_, std::shared_ptr<lexerLogObservers> logObserver, std::string file);
    //Lexer(std::vector<int> states, std::vector<char> inputs, std::vector<std::vector<int>> lookUpTable);
    ~Lexer();
    Lexer(const Lexer &toCopy);
    Lexer& operator=(const Lexer &toAssign);
    int getProgramSize();
    int getLineNumber();
    void dfaSetUp();
    void addFile(std::string file);
    void readFile();
    Token nextToken();
    int tableLookUp(int state, char input);
    char nextChar();
    bool isFinal(int stateName);
    bool backTrack(int stateName);

};

#endif //COMP_442_LEXER_H
