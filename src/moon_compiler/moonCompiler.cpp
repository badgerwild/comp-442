//
// Created by jason on 4/10/22.
//

#include <iostream>
#include "../parser/parser.h"
#include "../semantic/semanticTableVisitor.h"
#include "../semantic/linkerVisitor.h"
#include "../semantic/typeCheckVisitors.h"
#include "../semantic/tempVariableVisitor.h"
#include "../semantic/sizeVisitor.h"
#include "../semantic/logVisitor.h"

#include "../compliler/codeGenerationVisitor.h"
using namespace std;

int main(int argc, char *argv[]){
    std::string file = argv[1];
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


        tableBuilder->visit(dynamic_cast<ProgNode*>(ast));
        tableLinker->visit(dynamic_cast<ProgNode*>(ast));
        typer->visit(dynamic_cast<ProgNode*>(ast));
        tempVariables->visit(dynamic_cast<ProgNode*>(ast));
        sizeMaker->visit(dynamic_cast<ProgNode*>(ast));
        log->visit(dynamic_cast<ProgNode*>(ast));

        codeMaker->visit(dynamic_cast<ProgNode*>(ast));
        cout<<"Compilation sucessful for " <<file<<endl;
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
        cout<< file << " Compilation failed" <<endl;
    }
    cout<<"*****************************************************" <<endl;
}