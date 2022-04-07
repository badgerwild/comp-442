//
// Created by jason on 3/30/22.
//

#include "linkerVisitor.h"
#include <iostream>
#include "SymbolTable.h"
#include "./AST/ast.h"
LinkerVisitor::LinkerVisitor() {}

LinkerVisitor::~LinkerVisitor() {

}

void LinkerVisitor::visit(ProgNode *node) {
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }
}

void LinkerVisitor::visit(ClassDeclNode *node) {
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }
}

void LinkerVisitor::visit(MembDeclNode *node) {
    std::vector<Node*> children = node->getLeftMostChild()->getSiblings();
    for (auto &a: children) {
        a->accept(this);
    }
}

void LinkerVisitor::visit(FuncDeclNode *node){}

void LinkerVisitor::visit(FuncDefNode *node) {
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        //Add a referance to the above symtable???
        a->accept(this);
    }
}
void LinkerVisitor::visit(ProgramBlock *node) {
    std::vector<Node*> children = node->getLeftMostChild()->getSiblings();
    for (auto &a: children) {
        //Add a referance to the above symtable???
        a->accept(this);
    }
}
/*
void LinkerVisitor::visit(AssignStat *node){}

void LinkerVisitor::visit(IdNode *node) {}

void LinkerVisitor::visit(NotNode *node) {}

void LinkerVisitor::visit(AddOp *node) {}

void LinkerVisitor::visit(NumNode *node) {}

void LinkerVisitor::visit(VarDecl *node) {

}

void LinkerVisitor::visit(TypeNode *node) {}
*/
void LinkerVisitor::visit(FParamList *node) {
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    if (children[0] != nullptr) {
        for (auto &a: children) {
            //Add a referance to the above symtable???
            a->accept(this);
        }
    }
}

void LinkerVisitor::visit(FPAramNode *node) {
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    if (children[0] != nullptr) {
        for (auto &a: children) {
            //Add a referance to the above symtable???
            a->accept(this);
        }
    }
}

void LinkerVisitor::visit(DimList *node) {}
//TODO handle case where class is not implemented;


void LinkerVisitor::visit(ImplNode *node) {
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    SymbolTable* classTable = nullptr;
    SymbolTable* funcTable = nullptr;
    std::string fName {};
    for (auto &a: children) {
        if (a->getType() == "id") {
            node->setData(a->getData());
        }
        else if (a->getType() == "funcDef") {
            fName = a->getData();
            funcTable = a->symbolTable;
            for (auto &entry: node->getParent()->symbolTable->getTableEntries()) {
                if (node->getData() == entry.getName()) {
                    classTable = entry.getSubTable();
                    int debug = 0;
                }
            }
        }
        if (funcTable == nullptr) {
            node->errors.push_back("FUNCTION " + fName + "has not been declared");
            std::cout << "FUNCTION " + fName + "has not been declared" << std::endl;
        }
        else {
            for (SymbolTableRow &row: classTable->getTableEntries()) {
                if (fName == row.getName()) {
                    row.setSubTable(funcTable);
                }
            }
            //possible linking the table to the parent table???
            funcTable->setParentTable(classTable);
            a->accept(this);
        }
    }
    /*
    for (auto &entry: node->getParent()->symbolTable->getTableEntries()){
        if (node->getData() == entry.getName()) {
            classTable = entry.getSubTable();
            int debug = 0;
        }
    }
    if(funcTable == nullptr){
        node->errors.push_back("FUNCTION " + fName + "has not been declared");
        std::cout<<"FUNCTION " + fName + "has not been declared"<<std::endl;
    }
    else {
        for (SymbolTableRow &a: classTable->getTableEntries()) {
            if (fName == a.getName()) {
                a.setSubTable(funcTable);
            }
        }
        //possible linking the table to the parent table???
        funcTable->setParentTable(classTable);
    }
    */
}
