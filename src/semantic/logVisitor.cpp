//
// Created by jason on 3/30/22.
//

#include "logVisitor.h"
#include <fstream>
#include "visitors.h"
#include "SymbolTable.h"
#include "./AST/ast.h"
#include "../utils/remove_suffix.h"
//FINAL
const std::string PATH = "/home/jason/collective/comp-442/comp-442/src/logs/";
//const std::string PATH = "/home/jason/collective/comp-442/comp-442/src/semantic/logs/";
const std::string OUTSYMBOLTABLES = ".outsymboltables";
const std::string OUTERRORS = ".outerrors";


//Error and output reporting visitors
LogVisitor::LogVisitor() {

}

LogVisitor::LogVisitor(std::string file) {
    std::string outName = stripSuffix(file);
    outputFiles[1] = PATH+outName+OUTERRORS;
    outputFiles[0] = PATH +outName+OUTSYMBOLTABLES;
/*
    for (int i =0; i<2;++i){
        outPut[i].open(outputFiles[i]);
    }
    */
    outPut[0].open(outputFiles[0]);
    outPut[1].open(outputFiles[1]);
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

void LogVisitor::visit(ImplNode *node) {
    std::vector<Node*> children = node->getLeftMostChild()->getSiblings();
    for (auto &a: children) {
        a->accept(this);
    }
}

void LogVisitor::visit(FuncDeclNode *node) {
    /*
    outPut[0]<<"******************************************************"<<std::endl;
    outPut[0]<<"FUNC DECL " <<std::endl;
    outPut[0] <<"SYMBOL TABLE FOR: type:" <<node->getType() << " Name: " << node->getParent()->getName()<<" :: " <<node->getData()<< std::endl;
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
     */
};

void LogVisitor::visit(FuncDefNode *node) {
    outPut[0]<<"******************************************************"<<std::endl;
    outPut[0]<<"FUNC DEF " <<std::endl;
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
void LogVisitor::visit(ProgramBlock *node) {
    std::vector<Node*> children = node->getLeftMostChild()->getSiblings();
    for (auto &a: children) {
        a->accept(this);
    }

};



void LogVisitor::visit(AssignStat *node) {
    std::vector<Node*> children = node->getLeftMostChild()->getSiblings();
    for (auto &a: children) {
        a->accept(this);
    }

};

void LogVisitor::visit(IdNode *node) {};

void LogVisitor::visit(NotNode *node) {};

void LogVisitor::visit(AddOp *node) {
    outPut[1]<<"******************************************************"<<std::endl;
    outPut[1]<< " Error for " <<node->getType() << std::endl;
    for (auto &a: node->errors){
        outPut[1] << a<<std::endl;
    }
    outPut[1]<<"******************************************************"<<std::endl;

};

void LogVisitor::visit(MultOp *node) {}

void LogVisitor::visit(NumNode *node) {};

void LogVisitor::visit(VarDecl *node) {};

void LogVisitor::visit(TypeNode *node) {};

void LogVisitor::visit(FParamList *node) {};

void LogVisitor::visit(FPAramNode *node) {};

void LogVisitor::visit(DimList *node) {};

void LogVisitor::visit(ForStat *node) {};