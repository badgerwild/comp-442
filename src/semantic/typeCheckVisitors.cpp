//
// Created by jason on 4/1/22.
//

#include "typeCheckVisitors.h"

TypeVisitor::TypeVisitor() {}

TypeVisitor::~TypeVisitor() {

}

void TypeVisitor::visit(ProgNode *node){
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }

} ;

void TypeVisitor::visit(ClassDeclNode *node) {
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }
};

void TypeVisitor::visit(MembDeclNode *node){
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }
} ;

void TypeVisitor::visit(FuncDeclNode *node){
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }
} ;

void TypeVisitor::visit(FuncDefNode *node){
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }
} ;

void TypeVisitor::visit(ProgramBlock *node){
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }
} ;

void TypeVisitor::visit(VarDecl *node){
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }
} ;
void TypeVisitor::visit(FParamList *node){
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }
} ;

void TypeVisitor::visit(FPAramNode *node){
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }

} ;

void TypeVisitor::visit(ImplNode *node){
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }

} ;

void TypeVisitor::visit(AssignStat *node){
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }
} ;

void TypeVisitor::visit(ExprNode *node){
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }
} ;

void TypeVisitor::visit(ArithExprNode *node){
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }
    node->setDataType(node->getLeftMostChild()->getDataType());
} ;

void TypeVisitor::visit(AddOp *node){
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }
    std::string child1Type = children[0]->getDataType();
    std::string child2Type = children[1]->getDataType();
    if (child1Type == child2Type){
        node->setDataType(node->getLeftMostChild()->getDataType());
    }
    else {
        node->setDataType("invalid");
        node->errors.push_back("invlaid type at mult op");
    }
} ;

void TypeVisitor::visit(MultOp *node){
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());

    for (auto &a: children) {
        a->accept(this);
    }
    std::string child1Type = children[0]->getDataType();
    std::string child2Type = children[1]->getDataType();
    if (child1Type == child2Type){
        node->setDataType(node->getLeftMostChild()->getDataType());
    }
    else {
        node->setDataType("invalid");

        node->errors.push_back("invlaid type at mult op");
    }
} ;

void TypeVisitor::visit(TermNode *node){
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }
    node->setDataType(node->getLeftMostChild()->getDataType());

} ;
void TypeVisitor::visit(FactorNode *node){
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }
    node->setDataType(node->getLeftMostChild()->getDataType());
}
//TODO figure out how to attach this to the temp variables that have been created already. WTF
void TypeVisitor::visit(IdNode *node){
    if (node->getParent()->symbolTable != nullptr) {
        if (node->getParent()->getType() == "factor") {
            SymbolTableRow temp = node->getParent()->symbolTable->search(node->getData());
            node->setDataType(temp.getSymbolType());
        //     std::cout << temp;
        }
    }

}

