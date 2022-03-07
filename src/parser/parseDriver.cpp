//
// Created by jason on 2/13/22.
//
#include <iostream>
#include "parser.h"

using namespace std;
const string D = "short_demo";
const string E = "short_err";
const string B = "bubble";
const string S = "poly";
const string V = "variableAndIdnest";
const string X = "expression";
const string F = "class_func_etc";

int main() {
    cout<< "Parser started " <<endl;
    string file = S;
    Parser test = Parser(file);
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