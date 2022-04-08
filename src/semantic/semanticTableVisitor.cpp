//
// Created by jason on 3/30/22.
//
#include <fstream>
#include <iostream>
#include "SymbolTable.h"
#include "./AST/ast.h"
#include "semanticTableVisitor.h"

std::string SemanticTableVisitor::createTempVarName() {
    std::string returnValue;
    returnValue = "Temp" + std::to_string(++tempVarNum);
    return returnValue;
}
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
    classTable->setParentTable(node->getParent()->symbolTable);
    classTable->setScope("Class");
    std::string name;
    node->symbolTable = classTable;
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
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
    //node->symbolTableEntry = entry;
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
    //classTable->setParentTable(node->getParent()->symbolTable);
    //std::cout<<"Creating funcDecl node table" <<std::endl;
    /*
    SymbolTable* funcTable = new SymbolTable();
    funcTable->setScope("Function");
    node->symbolTable = funcTable;
     */
    std::string name, kind, type;
    std::vector<std::string> dimList;
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
/*
    for (auto &a: children) {
        a->accept(this);
    }
    */
    for(auto &a:children){
        if (a->getType() =="id"){
            name=a->getData();
        }
        else if (a->getType() == "type"){
            type = a->getData();
        }
        else if (a->getType() == "dimList"){
            std::vector<Node *> dimListItems = a->getLeftMostChild()->getSiblings();
            for (auto &a: dimListItems) {
                dimList.push_back(a->getData());
            }
        }
    }
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
                type = a->getData();
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
    kind = "variable";
    VarDeclRow entry(name, kind, type, nullptr, dimList);
    node->getParent()->symbolTable->insert(entry);
    node->symbolTableEntry = entry;
}

void SemanticTableVisitor::visit(FuncDefNode* node){
    SymbolTable* funcTable = new SymbolTable();
    //funcTable->setParentTable(node->getParent()->symbolTable);

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
    node->setData(name);
    funcTable->setScope(node->getParent()->getData()+"-->"+node->getData());
    if (node->getParent()->getType() !="impl") {
        SymbolTableRow entry(name, kind, type, nullptr);
        node->getParent()->symbolTable->insert(entry);
    }
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
        a->accept(this);
    }
    for (auto &a: children){
        if (a->getType() == "id"){
            name = a->getData();
        }
        else if (a->getType() == "type"){
            type = a->getData();
        }
        else if (a->getType() == "dimList")
            if(a->getLeftMostChild() != nullptr){
            std::vector<Node *> dimListItems = a->getLeftMostChild()->getSiblings();
                for (auto &d: dimListItems) {
                    dimList.push_back(d->getData());
                }
            }
            else{
                dimList.push_back("Null");
            }
        }
    kind = "parameter";
    VarDeclRow entry(name, kind, type, nullptr, dimList);
    node->symbolTable->insert(entry);
}
void SemanticTableVisitor::visit(FParamList* node){
    node->symbolTable = node->getParent()->symbolTable;
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    if (children[0] != nullptr) {
        for (auto &a: children) {
            //Add a referance to the above symtable???
            a->accept(this);
        }
    }

}

void SemanticTableVisitor::visit(AssignStat *node){
    //SymbolTable statTable;
    node->symbolTable = node->getParent()->symbolTable;
    std::vector<Node*> children = node->getLeftMostChild()->getSiblings();
    for (auto &a: children) {
        a->accept(this);
    }

}

void SemanticTableVisitor::visit(ExprNode *node){
    //SymbolTable statTable;
    node->symbolTable = node->getParent()->symbolTable;
    std::vector<Node*> children = node->getLeftMostChild()->getSiblings();
    for (auto &a: children) {
        a->accept(this);
    }

}

void SemanticTableVisitor::visit(ArithExprNode *node){
    //SymbolTable statTable;
    node->symbolTable = node->getParent()->symbolTable;
    std::vector<Node*> children = node->getLeftMostChild()->getSiblings();
    for (auto &a: children) {
        a->accept(this);
    }

}

void SemanticTableVisitor::visit(AddOp *node){
    node->symbolTable = node->getParent()->symbolTable;

    std::vector<Node *> children = node->reverse(node->getLeftMostChild()->getSiblings());
    /*
    std::string name, kind, type;
     */
    for (auto &a: children) {
        a->accept(this);
    }
    /*
     name = this->createTempVarName();
     kind = "tempvar";
     type = "integer";
    SymbolTableRow entry(name, kind, type, nullptr);
    node->getParent()->symbolTable->insert(entry);
     */
    //std::vector<Node*> children = node->getLeftMostChild()->getSiblings();
}

void SemanticTableVisitor::visit(MultOp *node){
    node->symbolTable = node->getParent()->symbolTable;
    std::vector<Node*> children = node->getLeftMostChild()->getSiblings();
   /*
    std::string name, kind, type;
    */
    for (auto &a: children) {
        a->accept(this);
    }
    /*
    name = this->createTempVarName();
    kind = "tempvar";
    type = "integer";
    SymbolTableRow entry(name, kind, type, nullptr);
    node->getParent()->symbolTable->insert(entry);
     */
}
void SemanticTableVisitor::visit(TermNode *node){
    node->symbolTable = node->getParent()->symbolTable;
    std::vector<Node*> children = node->getLeftMostChild()->getSiblings();
    for (auto &a: children) {
        a->accept(this);
    }
}
void SemanticTableVisitor::visit(FactorNode *node){
    node->symbolTable = node->getParent()->symbolTable;
    std::vector<Node*> children = node->getLeftMostChild()->getSiblings();
    for (auto &a: children) {
        a->accept(this);
    }
}

void SemanticTableVisitor::visit(IfStat *node) {
    node->symbolTable = node->getParent()->symbolTable;
    std::vector<Node*> children = node->getLeftMostChild()->getSiblings();
    for (auto &a: children) {
        a->accept(this);
    }
}

void SemanticTableVisitor::visit(RelExprNode *node) {
    node->symbolTable = node->getParent()->symbolTable;
    std::vector<Node*> children = node->getLeftMostChild()->getSiblings();
    for (auto &a: children) {
        a->accept(this);
    }
}

void SemanticTableVisitor::visit(ForStat *node) {
    node->symbolTable = node->getParent()->symbolTable;
    std::vector<Node*> children = node->getLeftMostChild()->getSiblings();
    for (auto &a: children) {
        a->accept(this);
    }
}
void SemanticTableVisitor::visit(PutStat *node) {
    node->symbolTable = node->getParent()->symbolTable;
    std::vector<Node*> children = node->getLeftMostChild()->getSiblings();
    for (auto &a: children) {
        a->accept(this);
    }
}
void SemanticTableVisitor::visit(IdNode* node){
    if (node->getParent()->getType() == "assignStat") {
        node->symbolTable = node->getParent()->symbolTable;
    }
}

//do nothing with these ones:
/*
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
*/