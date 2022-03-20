//
// Created by jason on 3/17/22.
//

#include "visitors.h"
#include "SymbolTable.h"
#include "./AST/ast.h"

void SemanticTableVisitor::visit(ProgNode* node){
    SymbolTable* globalTable = new SymbolTable();
    globalTable->setScope("Global");
    node->symbolTable = globalTable;
    std::vector<Node*> children = node->getLeftMostChild()->getSiblings();
    for (auto &a: children) {
        a->accept(this);
    }
    std::cout<< *node->symbolTable;
}

void SemanticTableVisitor::visit(ClassDeclNode *node) {
    SymbolTable* classTable = new SymbolTable();
    classTable->setScope("Class");
    node->symbolTable = classTable;
    std::vector<Node*> children = node->getLeftMostChild()->getSiblings();
    std::string name;
    //temp until I add in member declist and finialize the number of children of the classdecl node
    for (auto &a: children){
        if (a->getType() =="id"){
           name = a->getData();
        }
    }
    for (auto &a: children) {
        a->accept(this);
    }
    std::string kind = "Class";
    SymbolTableRow entry(name, kind, node->symbolTable);
    node->getParent()->symbolTable->insert(entry);
    std::cout<<*node->symbolTable;
}

void SemanticTableVisitor::visit(MembDeclNode* node){
  node->symbolTable = node->getParent()->symbolTable;
    std::vector<Node*> children = node->getLeftMostChild()->getSiblings();
    for (auto &a: children) {
        a->accept(this);
    }
}

void SemanticTableVisitor::visit(FuncDeclNode* node) {
    SymbolTable* funcTable = new SymbolTable();
    funcTable->setScope("Function");
    node->symbolTable = funcTable;
    std::string name, kind, type;
    std::vector<Node*> children = node->getLeftMostChild()->getSiblings();
    for (auto &a: children) {
        a->accept(this);
    }
    name = children[2]->getData();
    type = children[0]->getData();
    kind = "function";
    SymbolTableRow entry(name, kind, type, node->symbolTable);
    node->getParent()->symbolTable->insert(entry);

    std::cout<< *node->symbolTable;
}
void SemanticTableVisitor::visit(VarDecl* node){
    std::vector<Node*> children = node->getLeftMostChild()->getSiblings();
    std::string name, kind, type;
    std::vector<std::string> dimList;
    for (auto &a: children) {
        //Add a referance to the above symtable???
        a->accept(this);
    }
    name = children[2]->getData();
    kind = children[1]->getData();
    if (children[0]->getType() != "Null") {
        std::vector<Node *> dimListItems = children[0]->getLeftMostChild()->getSiblings();
        for (auto &a: dimListItems) {
            dimList.push_back(a->getData());
        }
    }
    else{
        dimList.push_back("Null");
    }
    type = "variable";
    //VarDeclROW entry(name, kind, type, nullptr, dimList);
    VarDeclROW entry(name, kind, type, nullptr, dimList);
    node->addEntry(entry);
    node->getParent()->symbolTable->insert(entry);
    char debug = 'b';
}

void SemanticTableVisitor::visit(FuncDefNode* node){
     SymbolTable* funcTable = new SymbolTable();
     funcTable->setScope("Function");
     node->symbolTable = funcTable;
    std::vector<Node*> children = node->getLeftMostChild()->getSiblings();
    for (auto &a: children) {
        //Add a referance to the above symtable???
        a->accept(this);
    }
    std::cout<< *node->symbolTable;
}
//TODO sort out difference between stat block and program block
void SemanticTableVisitor::visit(ProgramBlock* node){
    //SymbolTable statTable;
    node->symbolTable = node->getParent()->symbolTable;
    //statTable.setScope(node->getType());
    std::vector<Node*> children = node->getLeftMostChild()->getSiblings();
    for (auto &a: children) {
        //Add a referance to the above symtable???
        a->accept(this);
    }
    for (auto &a: children){
        if(a->getType() =="varDecl"){
            node->symbolTable->insert(a->getSymbolTableEntry());
        }
    }
}
void SemanticTableVisitor::visit(FPAramNode* node){
    node->symbolTable = node->getParent()->symbolTable;
    std::vector<Node*> children = node->getLeftMostChild()->getSiblings();
    std::string name, kind, type;
    std::vector<std::string> dimList;
    for (auto &a: children) {
        //Add a referance to the above symtable???
        a->accept(this);
    }
    name = children[2]->getData();
    kind = children[1]->getData();
    if (children[0]->getType() != "Null" && children[0]->getLeftMostChild() != NULL) {
        std::vector<Node *> dimListItems = children[0]->getLeftMostChild()->getSiblings();
        for (auto &a: dimListItems) {
            dimList.push_back(a->getData());
        }
    }
    else{
        dimList.push_back("Null");
    }
    type = "parameter";
    //VarDeclROW entry(name, kind, type, nullptr, dimList);
    VarDeclROW entry(name, kind, type, nullptr, dimList);
    //node->addEntry(entry);
    node->symbolTable->insert(entry);
}
void SemanticTableVisitor::visit(FParamList* node){
    node->symbolTable = node->getParent()->symbolTable;
    std::vector<Node*> children = node->getLeftMostChild()->getSiblings();
    for (auto &a: children) {
        //Add a referance to the above symtable???
        a->accept(this);
    }

}
void SemanticTableVisitor::visit(AssignStat* node){
}
void SemanticTableVisitor::visit(IdNode* node){
}
void SemanticTableVisitor::visit(NotNode* node){
    }
void SemanticTableVisitor::visit(AddOp* node){
}
void SemanticTableVisitor::visit(NumNode* node){
}
void SemanticTableVisitor::visit(DimList* node){
}

void SemanticTableVisitor::visit(TypeNode* node){
}



