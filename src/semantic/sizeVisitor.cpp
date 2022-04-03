//
// Created by jason on 4/1/22.
//
#include <vector>
#include "SymbolTable.h"
#include "../AST/ast.h"
#include "sizeVisitor.h"
void SizeVisitor::visit(ProgNode* node){
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }
    for (auto &entry: node->symbolTable->getTableEntries()){
        if (entry.getSymbolType() == "integer"){
            entry.setSize(4);
            node->symbolTable->tableOffset-=4;
            entry.setOffSet(node->symbolTable->tableOffset);
        }
        else if(entry.getSymbolType() == "float"){
            entry.setSize(8);
            node->symbolTable->tableOffset-=8;
            entry.setOffSet(node->symbolTable->tableOffset);
        }
        else{
            entry.setSize(0);
        }
    }
//    std::cout<< *node->symbolTable;
}

void SizeVisitor::visit(ClassDeclNode *node) {
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }
    for (auto &entry: node->symbolTable->getTableEntries()){
        if (entry.getSymbolType() == "integer"){
            entry.setSize(4);
            node->symbolTable->tableOffset-=4;
            entry.setOffSet(node->symbolTable->tableOffset);
        }
        else if(entry.getSymbolType() == "float"){
            entry.setSize(8);
            node->symbolTable->tableOffset-=8;
            entry.setOffSet(node->symbolTable->tableOffset);
        }
        else{
            entry.setSize(0);
        }
    }
}

void SizeVisitor::visit(ImplNode *node) {
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }
}

void SizeVisitor::visit(MembDeclNode* node){
    std::vector<Node*> children = node->getLeftMostChild()->getSiblings();
    for (auto &a: children) {
        a->accept(this);
    }
}

void SizeVisitor::visit(FuncDeclNode* node) {
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
}
void SizeVisitor::visit(VarDecl* node){
    std::vector<Node *> children = node->reverse(node->getLeftMostChild()->getSiblings());
    std::vector<std::string> dimList;
    if (children[0] != nullptr) {
        for (auto &a: children) {
            a->accept(this);
        }
    }
}

void SizeVisitor::visit(FuncDefNode* node){
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }
    for (auto &entry: node->symbolTable->getTableEntries()){
        if (entry.getSymbolType() == "integer"){
            entry.setSize(4);
            node->symbolTable->tableOffset-=4;
            entry.setOffSet(node->symbolTable->tableOffset);
        }
        else if(entry.getSymbolType() == "float"){
            entry.setSize(8);
            node->symbolTable->tableOffset-=8;
            entry.setOffSet(node->symbolTable->tableOffset);
        }
        else{
            entry.setSize(0);
        }
    }
}

void SizeVisitor::visit(ProgramBlock* node){
    std::vector<Node*> children = node->getLeftMostChild()->getSiblings();
    for (auto &a: children) {
        a->accept(this);
    }
}
void SizeVisitor::visit(FPAramNode* node){
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }
}
void SizeVisitor::visit(FParamList* node){
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    if (children[0] != nullptr) {
        for (auto &a: children) {
            a->accept(this);
        }
    }

}

void SizeVisitor::visit(AssignStat *node){
    std::vector<Node*> children = node->getLeftMostChild()->getSiblings();
    for (auto &a: children) {
        a->accept(this);
    }

}

void SizeVisitor::visit(ExprNode *node){
    std::vector<Node*> children = node->getLeftMostChild()->getSiblings();
    for (auto &a: children) {
        a->accept(this);
    }

}

void SizeVisitor::visit(ArithExprNode *node){
    std::vector<Node*> children = node->getLeftMostChild()->getSiblings();
    for (auto &a: children) {
        a->accept(this);
    }

}

void SizeVisitor::visit(AddOp *node){
    std::vector<Node *> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }
}

void SizeVisitor::visit(MultOp *node){
    std::vector<Node*> children = node->getLeftMostChild()->getSiblings();
    for (auto &a: children) {
        a->accept(this);
    }
}
void SizeVisitor::visit(TermNode *node){
    std::vector<Node*> children = node->getLeftMostChild()->getSiblings();
    for (auto &a: children) {
        a->accept(this);
    }
}
void SizeVisitor::visit(FactorNode *node){
    std::vector<Node*> children = node->getLeftMostChild()->getSiblings();
    for (auto &a: children) {
        a->accept(this);
    }
}

SizeVisitor::SizeVisitor() {}

SizeVisitor::~SizeVisitor() {

}

//do nothing with these ones:
/*
void SizeVisitor::visit(AssignStat* node){
}
void SizeVisitor::visit(IdNode* node){
}
void SizeVisitor::visit(NotNode* node){
}
void SizeVisitor::visit(AddOp* node){
}
void SizeVisitor::visit(NumNode* node){
}
void SizeVisitor::visit(DimList* node){
}

void SizeVisitor::visit(TypeNode* node){
}
*/