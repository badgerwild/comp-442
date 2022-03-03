//
// Created by jason on 2/13/22.
//
#include <iostream>
#include "parser.h"
#include "../logger/logSubject.h"

using namespace std;
const string D = "short_demo";
const string E = "short_err";
const string B = "bubbleSort";
const string S = "polynomial1";
const string V = "variableAndIdnest";
const string X = "expression";
const string F = "class_func_etc";

int main() {
    cout<< "Parser started " <<endl;
    string file = S;
   Logger theLogger{};
    Parser test = Parser(&theLogger, file);
    test.readSource();
    cout<<"****************************************************" <<endl;
    if(test.parse()){
        cout<< file << " Sucessfully parsed" <<endl;
    }
    else{
        cout<< file << " had errors parsed" <<endl;
    }
    cout<<"*****************************************************" <<endl;

    cout<<"Parser Finished" <<endl;

}