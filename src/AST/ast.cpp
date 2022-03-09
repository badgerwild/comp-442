//
// Created by jason on 3/5/22.
//
#include "ast.h"
Node::Node(){}
Node::~Node(){}


void Node::setType(std::string ty) {
    this->type =ty;
}
void InnerNode::adoptChildren(std::shared_ptr<Node> &child) {
    this->leftMostChild = child;

}
void Node::makeSiblings(std::shared_ptr<Node> &sibling) {
    this->rightSibling = sibling;
}

void Node::setIsLeaf(bool isLeaf) {
    this->isLeaf = isLeaf;
}

void Node::setParent(const std::weak_ptr<Node> &parent) {
    this->parent = parent;
}

void Node::setLeftMostSibling(const std::shared_ptr<Node> &leftMostSibling) {
    this->leftMostSibling = leftMostSibling;
}

void Node::setRightSibling(const std::shared_ptr<Node> &rightSibling) {
    this->rightSibling = rightSibling;
}

//TODO
void InnerNode::makeFamily(std::string op, std::shared_ptr<Node> &children){
   this->leftMostChild = children;

}

void InnerNode::setNumberOfChildren(int num) {
    this->numberOfChildren = num;
}

void InnerNode::setTypeOfChildren(const std::string &typeOfChild) {
    typeOfChildren.insert(typeOfChild);
}


void Leaf::setData(const std::string &data) {
    Leaf::data = data;
}

void IntermediateInnerNode::setData(const std::string &data) {
    IntermediateInnerNode::data = data;
}

const std::string &IntermediateInnerNode::getData() const {
    return data;
}

ProgNode::ProgNode() {}

ProgNode::~ProgNode() {

}

ClassListNode::ClassListNode() {}

ClassListNode::~ClassListNode() {

}

FuncDefList::FuncDefList() {}

FuncDefList::~FuncDefList() {

}

ClassDeclNode::ClassDeclNode() {}

ClassDeclNode::~ClassDeclNode() {

}

FuncDefNode::FuncDefNode() {}

FuncDefNode::~FuncDefNode() {

}

MembListNode::MembListNode() {}

MembListNode::~MembListNode() {

}

ProgramBlock::ProgramBlock() {}

ProgramBlock::~ProgramBlock() {

}

VarDecl::VarDecl() {}

VarDecl::~VarDecl() {

}

DimList::DimList() {}

DimList::~DimList() {

}

AssignStat::AssignStat() {}

AssignStat::~AssignStat() {

}

PutStat::PutStat() {}

PutStat::~PutStat() {

}

ReturnStat::ReturnStat() {}

ReturnStat::~ReturnStat() {

}

GetStat::GetStat() {}

GetStat::~GetStat() {

}

ForStat::ForStat() {}

ForStat::~ForStat() {

}

AddOp::AddOp() {}

AddOp::~AddOp() {

}

MultOp::MultOp() {}

MultOp::~MultOp() {

}

NotNode::NotNode() {}

NotNode::~NotNode() {

}

SignNode::SignNode() {}

SignNode::~SignNode() {

}

DotNode::DotNode() {}

DotNode::~DotNode() {

}

DataMemberNode::DataMemberNode() {}

DataMemberNode::~DataMemberNode() {

}

FCallNode::FCallNode() {}

FCallNode::~FCallNode() {

}

RelExprNode::RelExprNode() {}

RelExprNode::~RelExprNode() {

}

FuncDeclNode::FuncDeclNode() {}

FuncDeclNode::~FuncDeclNode() {

}

FPAramNode::FPAramNode() {}

FPAramNode::~FPAramNode() {

}

InherListNode::InherListNode() {}

InherListNode::~InherListNode() {

}

ScopeSpec::ScopeSpec() {}

ScopeSpec::~ScopeSpec() {

}

FParamList::FParamList() {}

FParamList::~FParamList() {

}

AParamsNode::AParamsNode() {}

AParamsNode::~AParamsNode() {

}

StatNode::StatNode() {}

StatNode::~StatNode() {

}

DotParamNode::DotParamNode() {}

DotParamNode::~DotParamNode() {

}

MembDeclNode::MembDeclNode() {}

MembDeclNode::~MembDeclNode() {

}

ExprNode::ExprNode() {}

ExprNode::~ExprNode() {

}

ArithExprNode::ArithExprNode() {}

ArithExprNode::~ArithExprNode() {

}

TermNode::TermNode() {}

TermNode::~TermNode() {

}

StatOrVarDeclNode::StatOrVarDeclNode() {}

StatOrVarDeclNode::~StatOrVarDeclNode() {

}

FactorNode::FactorNode() {}

FactorNode::~FactorNode() {

}

TypeNode::TypeNode() {}

TypeNode::~TypeNode() {

}

IdNode::IdNode() {}

IdNode::~IdNode() {

}

NumNode::NumNode() {}

NumNode::~NumNode() {

}

RelOpNode::RelOpNode() {}

RelOpNode::~RelOpNode() {

}

EpsilonNode::EpsilonNode() {}

EpsilonNode::~EpsilonNode() {

}

IfStat::IfStat() {}

IfStat::~IfStat() {

}

IndexList::IndexList() {}

IndexList::~IndexList() {

}
