//
// Created by jason on 4/4/22.
//
#include <iostream>
#include "./semantic/SymbolTable.h"
#include "./AST/ast.h"
//#include "./semantic/semanticTableVisitor.h"
#include "moonTagVisitor.h"

MoonTagVisitor::MoonTagVisitor(int moonVarNum) : moonVarNum(moonVarNum) {}

MoonTagVisitor::~MoonTagVisitor() {

}

void MoonTagVisitor::visit(ProgNode* node){
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }
//    std::cout<< *node->symbolTable;
}

void MoonTagVisitor::visit(ClassDeclNode *node) {
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }
}

void MoonTagVisitor::visit(ImplNode *node) {
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }

}

void MoonTagVisitor::visit(MembDeclNode* node){
    std::vector<Node*> children = node->getLeftMostChild()->getSiblings();
    for (auto &a: children) {
        a->accept(this);
    }
}

void MoonTagVisitor::visit(FuncDeclNode* node) {
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
/*
    for (auto &a: children) {
        a->accept(this);
    }
    */
}
void MoonTagVisitor::visit(VarDecl* node) {
    std::vector<Node *> children = node->reverse(node->getLeftMostChild()->getSiblings());
    if (children[0] != nullptr) {
        for (auto &a: children) {
            a->accept(this);
        }
    }
}

void MoonTagVisitor::visit(FuncDefNode* node) {
    std::vector<Node *> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }
}
void MoonTagVisitor::visit(ProgramBlock* node){
    std::vector<Node*> children = node->getLeftMostChild()->getSiblings();
    for (auto &a: children) {
        a->accept(this);
    }
}
void MoonTagVisitor::visit(FPAramNode* node){
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
void MoonTagVisitor::visit(FParamList* node){
    node->symbolTable = node->getParent()->symbolTable;
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    if (children[0] != nullptr) {
        for (auto &a: children) {
            //Add a referance to the above symtable???
            a->accept(this);
        }
    }

}

void MoonTagVisitor::visit(AssignStat *node){
    //SymbolTable statTable;
    node->symbolTable = node->getParent()->symbolTable;
    std::vector<Node*> children = node->getLeftMostChild()->getSiblings();
    for (auto &a: children) {
        a->accept(this);
    }

}

void MoonTagVisitor::visit(ExprNode *node){
    //SymbolTable statTable;
    node->symbolTable = node->getParent()->symbolTable;
    std::vector<Node*> children = node->getLeftMostChild()->getSiblings();
    for (auto &a: children) {
        a->accept(this);
    }

}

void MoonTagVisitor::visit(ArithExprNode *node){
    //SymbolTable statTable;
    node->symbolTable = node->getParent()->symbolTable;
    std::vector<Node*> children = node->getLeftMostChild()->getSiblings();
    for (auto &a: children) {
        a->accept(this);
    }

}

void MoonTagVisitor::visit(AddOp *node){
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

void MoonTagVisitor::visit(MultOp *node){
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
void MoonTagVisitor::visit(TermNode *node){
    node->symbolTable = node->getParent()->symbolTable;
    std::vector<Node*> children = node->getLeftMostChild()->getSiblings();
    for (auto &a: children) {
        a->accept(this);
    }
}
void MoonTagVisitor::visit(FactorNode *node){
    node->symbolTable = node->getParent()->symbolTable;
    std::vector<Node*> children = node->getLeftMostChild()->getSiblings();
    for (auto &a: children) {
        a->accept(this);
    }
}

void MoonTagVisitor::visit(IfStat *node) {
    node->symbolTable = node->getParent()->symbolTable;
    std::vector<Node*> children = node->getLeftMostChild()->getSiblings();
    for (auto &a: children) {
        a->accept(this);
    }
}

void MoonTagVisitor::visit(RelExprNode *node) {
    node->symbolTable = node->getParent()->symbolTable;
    std::vector<Node*> children = node->getLeftMostChild()->getSiblings();
    for (auto &a: children) {
        a->accept(this);
    }
}

void MoonTagVisitor::visit(ForStat *node) {
    node->symbolTable = node->getParent()->symbolTable;
    std::vector<Node*> children = node->getLeftMostChild()->getSiblings();
    for (auto &a: children) {
        a->accept(this);
    }
}
void MoonTagVisitor::visit(PutStat *node) {
    node->symbolTable = node->getParent()->symbolTable;
    std::vector<Node*> children = node->getLeftMostChild()->getSiblings();
    for (auto &a: children) {
        a->accept(this);
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
