//
// Created by jason on 3/16/22.
//
#include <iostream>
#include "../parser/parser.h"
#include "SymbolTable.h"
#include "visitors.h"
using namespace std;
const string D = "short_demo";
const string E = "short_err";
const string B = "bubble";
const string S = "poly";
const string V = "variableAndIdnest";
const string X = "expression";
const string F = "class_func_etc";
const string C = "shortClass_demo";

const string A = "ast_demo_1";

int main() {
    //TODO: IMPORTANT FOR DEMO
    cout<< "Parser started " <<endl;
    string file = C;
    Parser test = Parser(file);
    SemanticTableVisitor* tableBuilder = new SemanticTableVisitor();
    test.readSource();
    cout<<"****************************************************" <<endl;
    auto ast = test.parse();
    if(ast->getType() != "Null"){
        cout<< file << " Sucessfully parsed" <<endl;
        Node::traverse(ast, 0);

        tableBuilder->visit(dynamic_cast<ProgNode*>(ast));
        ast->deleteAll();
        delete(tableBuilder);
    }
    else{
        cout<< file << " had errors parsed" <<endl;
    }
    cout<<"*****************************************************" <<endl;

    cout<<"Parser Finished" <<endl;

    /*

    //temp test of Symbiltable
    vector<int> param;
    SymbolTable test1 = SymbolTable("Global", nullptr, 0);
    SymbolTable test3 = SymbolTable("foot", &test1, 0);
    FuncTableRow test2 = FuncTableRow("bean", "Void", "Function", param, nullptr);
    FuncTableRow test4 = FuncTableRow("spud", "int", "Function", param, &test3);
    test1.insert(test2);
    test1.insert(test4);

    cout << test1;
*/
}
