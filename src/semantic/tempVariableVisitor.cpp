//
// Created by jason on 4/3/22.
//
#include <iostream>
#include "tempVariableVisitor.h"
#include "SymbolTable.h"
#include "./AST/ast.h"
TempVariableVisitor::TempVariableVisitor() {}

TempVariableVisitor::~TempVariableVisitor() {

}
std::string TempVariableVisitor::createTempVarName() {
    std::string returnValue;
    returnValue = "T" + std::to_string(++tempVarNum);
    return returnValue;
}
void TempVariableVisitor::visit(ProgNode* node){
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }
//    std::cout<< *node->symbolTable;
}

void TempVariableVisitor::visit(ClassDeclNode *node) {
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }
    //std::cout<<*node->symbolTable;
}

void TempVariableVisitor::visit(ImplNode *node) {
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }

}

void TempVariableVisitor::visit(MembDeclNode* node){
    std::vector<Node*> children = node->getLeftMostChild()->getSiblings();
    for (auto &a: children) {
        a->accept(this);
    }
}
void TempVariableVisitor::visit(FuncDeclNode* node) {
//    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
}
void TempVariableVisitor::visit(VarDecl* node){
    std::vector<Node *> children = node->reverse(node->getLeftMostChild()->getSiblings());
    if (children[0] != nullptr) {
        for (auto &a: children) {
            a->accept(this);
        }
    }
}

void TempVariableVisitor::visit(FuncDefNode* node){
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        //Add a referance to the above symtable???
        a->accept(this);
    }
}

void TempVariableVisitor::visit(ProgramBlock* node){
    std::vector<Node*> children = node->getLeftMostChild()->getSiblings();
    for (auto &a: children) {
        //Add a referance to the above symtable???
        a->accept(this);
    }
}
void TempVariableVisitor::visit(FPAramNode* node){
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }

}
void TempVariableVisitor::visit(FParamList* node){
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    if (children[0] != nullptr) {
        for (auto &a: children) {
            a->accept(this);
        }
    }

}

void TempVariableVisitor::visit(AssignStat *node){
    std::vector<Node*> children = node->getLeftMostChild()->getSiblings();
    for (auto &a: children) {
        a->accept(this);
    }

}

void TempVariableVisitor::visit(ExprNode *node){
    std::vector<Node*> children = node->getLeftMostChild()->getSiblings();
    for (auto &a: children) {
        a->accept(this);
    }
    node->moonTag =  children[0]->moonTag;
}

void TempVariableVisitor::visit(ArithExprNode *node){
    std::vector<Node*> children = node->getLeftMostChild()->getSiblings();
    for (auto &a: children) {
        a->accept(this);
    }
    node->moonTag =  children[0]->moonTag;
}

void TempVariableVisitor::visit(AddOp *node){
    std::vector<Node *> children = node->reverse(node->getLeftMostChild()->getSiblings());
    std::string name, kind, type;
    for (auto &a: children) {
        a->accept(this);
    }
    name = this->createTempVarName();
    kind = "tempvar";
    type = node->getDataType();
    SymbolTableRow entry(name, kind, type, nullptr);
    entry.moonTag = name;
    node->moonTag = name;
    node->getParent()->symbolTable->insert(entry);
}

void TempVariableVisitor::visit(MultOp *node){
    std::vector<Node*> children = node->getLeftMostChild()->getSiblings();
    std::string name, kind, type;
    for (auto &a: children) {
        a->accept(this);
    }
    name = this->createTempVarName();
    kind = "tempvar";
    type = node->getDataType();
    SymbolTableRow entry(name, kind, type, nullptr);
    entry.moonTag = name;
    node->moonTag = name;
    node->getParent()->symbolTable->insert(entry);
}
void TempVariableVisitor::visit(TermNode *node){
    std::vector<Node*> children = node->getLeftMostChild()->getSiblings();
    for (auto &a: children) {
        a->accept(this);
    }
    node->moonTag =  children[0]->moonTag;
}
void TempVariableVisitor::visit(FactorNode *node){
    std::vector<Node*> children = node->getLeftMostChild()->getSiblings();
    for (auto &a: children) {
        a->accept(this);
    }
    node->moonTag =  children[0]->moonTag;//MAYBE needs to be more specific later???
}

void TempVariableVisitor::visit(IfStat *node) {
    std::vector<Node*> children = node->getLeftMostChild()->getSiblings();
    for (auto &a: children) {
        a->accept(this);
    }
}

void TempVariableVisitor::visit(RelExprNode *node){
    std::vector<Node*> children = node->getLeftMostChild()->getSiblings();
    std::string name, kind, type;
    for (auto &a: children) {
        a->accept(this);
    }
    name = this->createTempVarName();
    //TODO remove the rel
    kind = "reltempvar";
    type = "integer";//all boolians are integer
    SymbolTableRow entry(name, kind, type, nullptr);
    entry.moonTag = name;
    node->moonTag = name;
    node->getParent()->symbolTable->insert(entry);
}

void TempVariableVisitor::visit(ForStat *node) {
    std::vector<Node*> children = node->getLeftMostChild()->getSiblings();
    for (auto &a: children) {
        a->accept(this);
    }
}

void TempVariableVisitor::visit(PutStat *node) {
    std::vector<Node*> children = node->getLeftMostChild()->getSiblings();
    for (auto &a: children) {
        a->accept(this);
    }
}

void TempVariableVisitor::visit(NumNode* node){
    std::string name = this->createTempVarName();
    //TODO remove lit
    std::string kind = "littempvar";
    std::string type = node->getDataType();//all boolians are integer
    SymbolTableRow entry(name, kind, type, nullptr);
    entry.moonTag = name;
    node->moonTag = name;
    node->getParent()->symbolTable->insert(entry);

}

void TempVariableVisitor::visit(IdNode* node){
    //std::string name = node->getData()+std::to_string(++tempVarNum);
    node->moonTag = node->getData();

}
//do nothing with these ones:
/*
void TempVariableVisitor::visit(AssignStat* node){
}
void TempVariableVisitor::visit(IdNode* node){
}
void TempVariableVisitor::visit(NotNode* node){
}
void TempVariableVisitor::visit(AddOp* node){
}
void TempVariableVisitor::visit(NumNode* node){
}
void TempVariableVisitor::visit(DimList* node){
}

void TempVariableVisitor::visit(TypeNode* node){
}
*/

