//
// Created by jason on 2/13/22.
//
#include <iostream>
#include "parser.h"

using namespace std;
const string D = "short_demo.txt";
const string B = "bubble.txt";
const string S = "poly.txt";
const string V = "variableAndIdnest.txt";
const string X = "expression.txt";
const string F = "class_func_etc.txt";


int main() {
    cout<< "Parser started " <<endl;
    string file = D;
    Parser test = Parser(file);
    test.readSource();
    cout<<"****************************************************" <<endl;
    test.parse();
}