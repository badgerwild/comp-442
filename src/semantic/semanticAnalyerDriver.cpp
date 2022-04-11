//
// Created by jason on 3/16/22.
//
#include <iostream>
#include "../parser/parser.h"
#include "semanticTableVisitor.h"
#include "linkerVisitor.h"
#include "typeCheckVisitors.h"
#include "tempVariableVisitor.h"
#include "sizeVisitor.h"
#include "logVisitor.h"
using namespace std;
const string D = "short_demo.txt";
const string B = "bubble.txt";
const string P = "poly.txt";
const string V = "variableAndIdnest.txt";
const string F = "class_func_etc.txt";
const string C = "shortClass_demo.txt";
const string S ="c_sampleMain.txt";
const string E = "semantic_error.txt";


int main() {
    cout<< "Parser started " <<endl;
    string file = S;
    Parser test = Parser(file);
    SemanticTableVisitor* tableBuilder = new SemanticTableVisitor();
    LinkerVisitor* tableLinker = new LinkerVisitor();
    TypeVisitor* typer = new TypeVisitor();
    TempVariableVisitor* tempVariables = new TempVariableVisitor();
    SizeVisitor* sizeMaker = new SizeVisitor();
    LogVisitor* log = new LogVisitor(file);
    test.readSource();
    cout<<"****************************************************" <<endl;
    auto ast = test.parse();
    if(ast->getType() != "Null"){
        cout<< file << " Sucessfully parsed" <<endl;
        tableBuilder->visit(dynamic_cast<ProgNode*>(ast));
        tableLinker->visit(dynamic_cast<ProgNode*>(ast));
        typer->visit(dynamic_cast<ProgNode*>(ast));
       tempVariables->visit(dynamic_cast<ProgNode*>(ast));
        sizeMaker->visit(dynamic_cast<ProgNode*>(ast));
        log->visit(dynamic_cast<ProgNode*>(ast));
        //DEBUG print
       // Node::traverse(ast, 0);
        ast->deleteAll();
        delete(tableBuilder);
        delete(typer);
        delete(tempVariables);
        delete(sizeMaker);
        delete(tableLinker);
        delete(log);
    }
    else{
        cout<< file << " had errors parsed" <<endl;
    }
    cout<<"*****************************************************" <<endl;

    cout<<"Parser Finished" <<endl;

}
