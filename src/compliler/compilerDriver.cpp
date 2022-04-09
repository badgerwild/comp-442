//
// Created by jason on 4/3/22.
//

#include <iostream>
#include "../parser/parser.h"
#include "../semantic/semanticTableVisitor.h"
#include "../semantic/linkerVisitor.h"
#include "../semantic/typeCheckVisitors.h"
#include "../semantic/tempVariableVisitor.h"
#include "../semantic/sizeVisitor.h"
#include "../semantic/logVisitor.h"

#include "codeGenerationVisitor.h"
using namespace std;

const string D = "short_demo";
const string E = "short_err";
const string B = "bubble";
const string P = "poly";
const string V = "variableAndIdnest";
const string X = "expression";
const string F = "class_func_etc";
const string C = "shortClass_demo";
 const string A = "ast_demo_1";

//Implemented Compiler feature testing:

const string T = "basic_output"; //basic alloction + output to CLI
const string EX = "expressions"; //expression testing
const string AA = "arrayAccess";




int main() {
    cout<< "Parser started " <<endl;
    string file = T;
    Parser test = Parser(file);
    SemanticTableVisitor* tableBuilder = new SemanticTableVisitor();
    LinkerVisitor* tableLinker = new LinkerVisitor();
    TypeVisitor* typer = new TypeVisitor();
    TempVariableVisitor* tempVariables = new TempVariableVisitor();
    SizeVisitor* sizeMaker = new SizeVisitor();
    LogVisitor* log = new LogVisitor(file);
    CodeGenerationVisitor* codeMaker = new CodeGenerationVisitor(file);
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

        codeMaker->visit(dynamic_cast<ProgNode*>(ast));
        //DEBUG print
        Node::traverse(ast, 0);

        //Delete all the things!!!!
        ast->deleteAll();
        delete(tableBuilder);
        delete(typer);
        delete(tempVariables);
        delete(sizeMaker);
        delete(log);
        delete(tableLinker);
        delete(codeMaker);
    }
    else{
        cout<< file << " had errors parsed" <<endl;
    }
    cout<<"*****************************************************" <<endl;

    cout<<"Parser Finished" <<endl;

}
