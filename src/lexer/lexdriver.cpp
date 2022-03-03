//
// Created by jason on 1/28/22.
//
#include <iostream>
#include <fstream>
#include <vector>
#include "../DFA/DFA.h"
#include "lexer.h"
#include "../logger/logSubject.h"
#include "../logger/observer.h"

using namespace std;
int main(){
    //LEXER SETUP
    Logger theLogger{};
    //Lexer scanner = Lexer(states, alphabet, tableau);
    string filePre ="/home/jason/collective/comp-442/comp-442/src/lexer/";
    string fileName = "a";//change this for different input file
    string fileSuf = ".txt";
    Lexer scanner = Lexer(&theLogger, filePre+fileName+fileSuf);
    scanner.readFile();
    bool condition = false;
    while (!condition) {
            Token t = scanner.nextToken();
            condition = t.isEOF();
    }
    return 0;
}