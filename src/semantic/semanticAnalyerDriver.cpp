//
// Created by jason on 3/16/22.
//
#include <iostream>
#include "../parser/parser.h"

using namespace std;
const string D = "short_demo";
const string E = "short_err";
const string B = "bubble";
const string S = "poly";
const string V = "variableAndIdnest";
const string X = "expression";
const string F = "class_func_etc";

const string A = "ast_demo_1";

int main() {
    cout<< "Parser started " <<endl;
    string file = D;
    Parser test = Parser(file);
    test.readSource();
    cout<<"****************************************************" <<endl;
    auto ast = test.parse();
    if(ast->getType() != "Null"){
        cout<< file << " Sucessfully parsed" <<endl;
        Node::traverse(ast, 0);
        ast->deleteAll();
    }
    else{
        cout<< file << " had errors parsed" <<endl;
    }
    cout<<"*****************************************************" <<endl;

    cout<<"Parser Finished" <<endl;

}
