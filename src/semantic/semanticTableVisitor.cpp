//
// Created by jason on 3/30/22.
//
#include <fstream>
#include "SymbolTable.h"
#include "./AST/ast.h"
#include "semanticTableVisitor.h"
void SemanticTableVisitor::visit(ProgNode* node){
    SymbolTable* globalTable = new SymbolTable();
    globalTable->setScope("Global");
    node->symbolTable = globalTable;
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }
//    std::cout<< *node->symbolTable;
}

void SemanticTableVisitor::visit(ClassDeclNode *node) {
    SymbolTable* classTable = new SymbolTable();
    classTable->setScope("Class");
    node->symbolTable = classTable;
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
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
    node->setData(name);
    node->getParent()->symbolTable->insert(entry);
    //std::cout<<*node->symbolTable;
}

void SemanticTableVisitor::visit(ImplNode *node) {
    node->symbolTable = node->getParent()->symbolTable;
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        if(a->getType() =="id"){
            node->setData(a->getData());
        }
        a->accept(this);
    }

}

void SemanticTableVisitor::visit(MembDeclNode* node){
    node->symbolTable = node->getParent()->symbolTable;
    std::vector<Node*> children = node->getLeftMostChild()->getSiblings();
    for (auto &a: children) {
        a->accept(this);
    }
}

void SemanticTableVisitor::visit(FuncDeclNode* node) {
    //std::cout<<"debug func decl"<<std::endl;
    SymbolTable* funcTable = new SymbolTable();
    funcTable->setScope("Function");
    node->symbolTable = funcTable;
    std::string name, kind, type;
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());

    for (auto &a: children) {
        a->accept(this);
    }
    name = children[2]->getData();
    type = children[0]->getData();
    kind = "function";
    SymbolTableRow entry(name, kind, type, node->symbolTable);
    node->setData(name);
    if(name != "") {
        //SymbolTableRow temp = node->symbolTable->search(name);
        //std::cout << "FOUND IN " << node->getName() << " " << temp;
    }
    node->getParent()->symbolTable->insert(entry);
}
void SemanticTableVisitor::visit(VarDecl* node){
    std::vector<Node *> children = node->reverse(node->getLeftMostChild()->getSiblings());
    std::string name, kind, type;
    std::vector<std::string> dimList;
    if (children[0] != nullptr) {
        for (auto &a: children) {
            a->accept(this);
        }
        for(auto &a:children){
            if (a->getType() =="id"){
                name=a->getData();
            }
            else if (a->getType() == "type"){
                kind = a->getData();
            }
            else if (a->getType() == "dimList"){
                std::vector<Node *> dimListItems = a->getLeftMostChild()->getSiblings();
                for (auto &a: dimListItems) {
                    dimList.push_back(a->getData());
                }
            }
        }
    }
    if (dimList.size() == 0) {
        dimList.push_back("Null");
    }
    else{
        for (auto &a: dimList){
            kind = kind +"[" +a+"]";
        }
    }
    type = "variable";
    VarDeclROW entry(name, kind, type, nullptr, dimList);
    node->getParent()->symbolTable->insert(entry);
}

void SemanticTableVisitor::visit(FuncDefNode* node){
    SymbolTable* funcTable = new SymbolTable();
    funcTable->setScope("Function");
    node->symbolTable = funcTable;
    std::string name, kind, type;
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        //Add a referance to the above symtable???
        a->accept(this);
    }
    for (auto &a: children){
        if (a->getType() == "id"){
            name = a->getData();
        }
        else if (a->getType() == "type"){
            type = a->getData();
        }
    }
    kind = "function";
    SymbolTableRow entry(name, kind, type, node->symbolTable);
    node->setData(name);
    node->getParent()->symbolTable->insert(entry);
    //SymbolTableRow temp = node->symbolTable->search(node->getName());
}

void SemanticTableVisitor::visit(ProgramBlock* node){
    //SymbolTable statTable;
    node->symbolTable = node->getParent()->symbolTable;
    //statTable.setScope(node->getType());
    std::vector<Node*> children = node->getLeftMostChild()->getSiblings();
    for (auto &a: children) {
        //Add a referance to the above symtable???
        a->accept(this);
    }
}
void SemanticTableVisitor::visit(FPAramNode* node){
    node->symbolTable = node->getParent()->symbolTable;
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
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
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    //TODO here
    if (children[0] != nullptr) {
        for (auto &a: children) {
            //Add a referance to the above symtable???
            a->accept(this);
        }
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
