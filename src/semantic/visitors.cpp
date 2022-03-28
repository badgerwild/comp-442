//
// Created by jason on 3/17/22.
//

#include <fstream>
#include "visitors.h"
#include "SymbolTable.h"
#include "./AST/ast.h"


const std::string PATH = "/home/jason/collective/comp-442/comp-442/src/semantic/logs/";
const std::string OUTSYMBOLTABLES = ".outsymboltables";
const std::string OUTERRORS = ".outerrors";

void SemanticTableVisitor::visit(ProgNode* node){
    SymbolTable* globalTable = new SymbolTable();
    globalTable->setScope("Global");
    node->symbolTable = globalTable;
    std::vector<Node*> children = node->getLeftMostChild()->getSiblings();
    for (auto &a: children) {
        a->accept(this);
    }
//    std::cout<< *node->symbolTable;
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
    node->setData(name);
    node->getParent()->symbolTable->insert(entry);
    //std::cout<<*node->symbolTable;
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
    std::vector<Node*> children = node->getLeftMostChild()->getSiblings();
    SymbolTableRow temp = node->symbolTable->search(node->getName());
    std::cout<<"FOUND IN "<<node->getName()<<" " << temp;
    for (auto &a: children) {
        a->accept(this);
    }
    name = children[2]->getData();
    type = children[0]->getData();
    kind = "function";
    SymbolTableRow entry(name, kind, type, node->symbolTable);
    node->setData(name);
    node->getParent()->symbolTable->insert(entry);
}
void SemanticTableVisitor::visit(VarDecl* node){
        std::vector<Node *> children = node->getLeftMostChild()->getSiblings();
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
    std::vector<Node*> children = node->getLeftMostChild()->getSiblings();
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

//Error and output reporting visitors
LogVisitor::LogVisitor() {

}

LogVisitor::LogVisitor(std::string file) {
    outputFiles[1] = PATH+file+OUTERRORS;
    outputFiles[0] = PATH + file + OUTSYMBOLTABLES;

    for (int i =0; i<2;++i){
        outPut[i].open(outputFiles[i]);
    }
}

LogVisitor::~LogVisitor() {
    outPut[0].close();
    outPut[1].close();
}
void LogVisitor::visit(ProgNode *node){
    outPut[0]<<"******************************************************"<<std::endl;
    outPut[0] <<"SYMBOL TABLE FOR: " <<node->getType()<<std::endl;
    outPut[0]<<*node->symbolTable;
    outPut[0]<<"******************************************************"<<std::endl;
    outPut[0]<<std::endl;
    outPut[1]<<"******************************************************"<<std::endl;
    outPut[1]<< "PLACE holder Error for " <<node->getType() << std::endl;
    outPut[1]<<"******************************************************"<<std::endl;
    std::vector<Node*> children = node->getLeftMostChild()->getSiblings();
    for (auto &a: children) {
        a->accept(this);
    }
} ;

void LogVisitor::visit(ClassDeclNode *node) {
    outPut[0]<<"******************************************************"<<std::endl;
    outPut[0] <<"SYMBOL TABLE FOR: " <<node->getType()<<" :: "<<node->getData()<<std::endl;
    outPut[0]<<*node->symbolTable;
    outPut[0]<<"******************************************************"<<std::endl;
    outPut[0]<<std::endl;
    outPut[1]<<"******************************************************"<<std::endl;
    outPut[1]<< "PLACE holder Error for " <<node->getType() << std::endl;
    outPut[1]<<"******************************************************"<<std::endl;
    std::vector<Node*> children = node->getLeftMostChild()->getSiblings();
    for (auto &a: children) {
        a->accept(this);
    }
};

void LogVisitor::visit(MembDeclNode *node) {
    std::vector<Node*> children = node->getLeftMostChild()->getSiblings();
    for (auto &a: children) {
        a->accept(this);
    }
};

void LogVisitor::visit(FuncDeclNode *node) {
    outPut[0]<<"******************************************************"<<std::endl;
    outPut[0] <<"SYMBOL TABLE FOR: " <<node->getType()<<" :: " <<node->getData()<< std::endl;
    outPut[0]<<*node->symbolTable;
    outPut[0]<<"******************************************************"<<std::endl;
    outPut[0]<<std::endl;
    outPut[1]<<"******************************************************"<<std::endl;
    outPut[1]<< "PLACE holder Error for " <<node->getType() << std::endl;
    outPut[1]<<"******************************************************"<<std::endl;
    std::vector<Node*> children = node->getLeftMostChild()->getSiblings();
    for (auto &a: children) {
        a->accept(this);
    }
};

void LogVisitor::visit(FuncDefNode *node) {
    outPut[0]<<"******************************************************"<<std::endl;
    outPut[0] <<"SYMBOL TABLE FOR: " <<node->getType()<< "::" <<node->getData()<<std::endl;
    outPut[0]<<*node->symbolTable;
    outPut[0]<<"******************************************************"<<std::endl;
    outPut[0]<<std::endl;
    outPut[1]<<"******************************************************"<<std::endl;
    outPut[1]<< "PLACE holder Error for " <<node->getType() << std::endl;
    outPut[1]<<"******************************************************"<<std::endl;
    std::vector<Node*> children = node->getLeftMostChild()->getSiblings();
    for (auto &a: children) {
        a->accept(this);
    }
}
void LogVisitor::visit(ProgramBlock *node) {};

void LogVisitor::visit(AssignStat *node) {};

void LogVisitor::visit(IdNode *node) {};

void LogVisitor::visit(NotNode *node) {};

void LogVisitor::visit(AddOp *node) {};

void LogVisitor::visit(NumNode *node) {};

void LogVisitor::visit(VarDecl *node) {};

void LogVisitor::visit(TypeNode *node) {};

void LogVisitor::visit(FParamList *node) {};

void LogVisitor::visit(FPAramNode *node) {};

void LogVisitor::visit(DimList *node) {};