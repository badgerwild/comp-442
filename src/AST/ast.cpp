//
// Created by jason on 3/5/22->
//
#include <iostream>
#include "ast.h"
#include "astFactory.h"

Node::Node(){
    parent = nullptr;
    leftMostSibling = nullptr;
    rightSibling = nullptr;
    leftMostChild = nullptr;
    symbolTable = nullptr;

}
Node::~Node(){}


void Node::setType(std::string ty) {
    this->type =ty;
}



Node::Node(Node const& toCopy){
    this->type = toCopy.type;
    this->isLeaf = toCopy.isLeaf;
    this->parent = toCopy.parent;
    this->leftMostSibling = toCopy.leftMostSibling;
    this->rightSibling = toCopy.rightSibling;
    //return *this;

}

Node& Node::operator=(const Node &toAssign) {
    this->type = toAssign.type;
    this->isLeaf = toAssign.isLeaf;
    this->parent = toAssign.parent;
    this->leftMostSibling = toAssign.leftMostSibling;
    this->rightSibling = toAssign.rightSibling;
    return *this;
}

std::vector<Node*> Node::getSiblings() {
    std::vector<Node*> kidList;
    if (this == NULL){
        kidList.push_back(nullptr);
    }else {
        kidList.push_back(this);
        if (rightSibling != nullptr) {
            auto right = rightSibling;
            while (right != nullptr) {
                kidList.push_back(right);
                right = right->rightSibling;

            }
        }
    }
    return kidList;
}

std::vector<Node*> Node::reverse(std::vector<Node*> rev) {
    std::vector<Node*> revSibblings;
    for (auto &a: rev){
        revSibblings.push_back((rev.back()));
        rev.pop_back();
    }
    return revSibblings;
}

void Node::deleteAll() {
    deleteAllHelper(this);
}

//delete function that does a postorder traversal and delete of all nodes.
void Node::deleteAllHelper(Node *node) {
    if (node->leftMostChild != nullptr) {
        auto siblingList =reverse(node->leftMostChild->getSiblings());
        for (auto &a: siblingList) {
            auto temp1 = a->getType();
            deleteAllHelper(a);
        }
    }
//    std::cout << node->getType() <<std::endl;
    delete(node);
}

//preorder traverse of AST
void Node::traverse(Node *node, int depth) {
    //std::string debug = node->getType();
    std::cout << node->getType() << "--> $ " <<node->getData()<< " $ " <<std::endl;
    if (node->leftMostChild != nullptr) {
        depth++;
        for (auto &a: node->reverse(node->leftMostChild->getSiblings())) {
            auto temp = a->getType();
            for(int i = 0; i < depth; i++){
                std::cout<< "|";
            }

            traverse(a, depth);
        }
    }
}

int InnerNode::getNumberOfChildren() {
    return numberOfChildren;
}

void InnerNode::adoptChildren(Node *child) {
    if (leftMostChild == nullptr){
    this->leftMostChild = child;
    auto next = child;
    while (next!= nullptr){
       next->setParent( this);
       next = next-> getRightSibling();
    }
    }
    else{
        this->leftMostChild->makeSiblings(child);
    }

}

void InnerNode::deleteChild() {
}
void Node::makeSiblings(Node *sibling) {
    if (this->rightSibling == nullptr){
        this->rightSibling = sibling;
        //sibling->leftMostSibling = std::make_shared<Node>();
        sibling->leftMostSibling = this;

    }else{
        auto temp = this;
        while (temp->rightSibling != nullptr){
            temp = temp->rightSibling;
        }
        temp->rightSibling = sibling;
        sibling->leftMostSibling = this;
    }
    sibling->parent = this->parent;
}
void Node::setIsLeaf(bool isLeaf) {
    this->isLeaf = isLeaf;
}

void Node::setParent(Node *parent) {
    this->parent = parent;
}

void Node::setLeftMostSibling(Node *leftMostSibling) {
    this->leftMostSibling = leftMostSibling;
}

void Node::setRightSibling(Node *rightSibling) {
    this->rightSibling = rightSibling;
}

Node *Node::getRightSibling(){
    return rightSibling;
}

const std::string &Node::getType() const {
    return type;
}

Node *Node::getLeftMostChild() const {
    return leftMostChild;
}

//TODO
 Node *InnerNode::makeFamily(std::string op, std::vector<Node *> children){
   NodeFactory fac;
    auto parentNode = fac.makeNode(op);
    children[0]->setLeftMostSibling(children[0]);
    for (int i = 0; i< children.size()-1;++i){
        children[i]->makeSiblings(children[i+1]);
    }
    parentNode->adoptChildren(children[0]);
    return parentNode;
}

void InnerNode::setNumberOfChildren(int num) {
    this->numberOfChildren = num;
}

void InnerNode::setTypeOfChildren(const std::string &typeOfChild) {
    typeOfChildren.insert(typeOfChild);
}


void Node::setData(const std::string &data) {
    this->data = data;
}

void Leaf::adoptChildren(Node *child) {};

void IntermediateInnerNode::setData(const std::string &data) {
    IntermediateInnerNode::data = data;
}

const std::string &Node::getData() const {
    return data;
}

const SymbolTableRow &Node::getSymbolTableEntry() const {
    return symbolTableEntry;
}

Node *Node::getParent() const {
    return parent;
}

void Node::setName(const std::string &name) {
    this->name = name;
}

const std::string &Node::getName() const {
    return name;
}

void IntermediateInnerNode::adoptChildren(Node *child) {
    if (leftMostChild == nullptr){
        this->leftMostChild = child;
        auto next = child;
        while (next!= nullptr){
            next->setParent( this);
            next = next-> getRightSibling();
        }
    }
    else{
        this->leftMostChild->makeSiblings(child);
    }
}



IntermediateInnerNode::IntermediateInnerNode() {}

IntermediateInnerNode::~IntermediateInnerNode() {

}

ProgNode::ProgNode() {}

ProgNode::~ProgNode() {
    delete parent;
    delete leftMostSibling;
    delete rightSibling;
    delete symbolTable;
    deleteChild();
}



ClassListNode::ClassListNode() {}

ClassListNode::~ClassListNode() {
    delete symbolTable;
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

void VarDecl::addEntry(VarDeclRow vec) {
    symbolTableEntry = vec;
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
    delete symbolTable;

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
ImplNode::ImplNode() {}

ImplNode::~ImplNode() {

}

/// All accept methods for the visitor patter are here:
void ProgNode::accept(Visitor* visitor) {
    visitor->visit(this);
}
void ClassListNode::accept(Visitor* visitor) {
    visitor->visit(this);
}
void FuncDefList::accept(Visitor* visitor) {
    visitor->visit(this);
}
void ClassDeclNode::accept(Visitor* visitor) {
    visitor->visit(this);
}
void FuncDefNode::accept(Visitor* visitor) {
    visitor->visit(this);
}
void MembListNode::accept(Visitor* visitor) {
    visitor->visit(this);
}
void ProgramBlock::accept(Visitor* visitor) {
    visitor->visit(this);
}
void VarDecl::accept(Visitor* visitor) {
    visitor->visit(this);
}
void DimList::accept(Visitor* visitor) {
    visitor->visit(this);
}
void AssignStat::accept(Visitor* visitor) {
    visitor->visit(this);
}
void ArithExprNode::accept(Visitor *visitor) {
    visitor->visit(this);
}

void PutStat::accept(Visitor* visitor) {
    visitor->visit(this);
}
void ReturnStat::accept(Visitor* visitor) {
    visitor->visit(this);
}
void RelExprNode::accept(Visitor* visitor) {
    visitor->visit(this);
}
void GetStat::accept(Visitor* visitor) {
    visitor->visit(this);
}
void IfStat::accept(Visitor* visitor) {
    visitor->visit(this);
}
void ForStat::accept(Visitor* visitor) {
    visitor->visit(this);
}
void AddOp::accept(Visitor* visitor) {
    visitor->visit(this);
}
void MultOp::accept(Visitor* visitor) {
    visitor->visit(this);
}
void NotNode::accept(Visitor* visitor) {
    visitor->visit(this);
}
void SignNode::accept(Visitor* visitor) {
    visitor->visit(this);
}
void DotNode::accept(Visitor* visitor) {
    visitor->visit(this);
}
void DataMemberNode::accept(Visitor* visitor) {
    visitor->visit(this);
}
void FCallNode::accept(Visitor* visitor) {
    visitor->visit(this);
}
void RelOpNode::accept(Visitor* visitor) {
    visitor->visit(this);
}
void FuncDeclNode::accept(Visitor* visitor) {
    visitor->visit(this);
}
void FPAramNode::accept(Visitor* visitor) {
    visitor->visit(this);
}
void InherListNode::accept(Visitor* visitor) {
    visitor->visit(this);
}
void ScopeSpec::accept(Visitor* visitor) {
    visitor->visit(this);
}
void IndexList::accept(Visitor* visitor) {
    visitor->visit(this);
}
void FParamList::accept(Visitor* visitor) {
    visitor->visit(this);
}
void AParamsNode::accept(Visitor* visitor) {
    visitor->visit(this);
}
void StatNode::accept(Visitor* visitor) {
    visitor->visit(this);
}
void DotParamNode::accept(Visitor* visitor) {
    visitor->visit(this);
}
void MembDeclNode::accept(Visitor* visitor) {
    visitor->visit(this);
}
void TermNode::accept(Visitor* visitor) {
    visitor->visit(this);
}
void StatOrVarDeclNode::accept(Visitor* visitor) {
    visitor->visit(this);
}
void FactorNode::accept(Visitor* visitor) {
    visitor->visit(this);
}
void TypeNode::accept(Visitor* visitor) {
    visitor->visit(this);
}
void IdNode::accept(Visitor* visitor) {
    visitor->visit(this);
}
void NumNode::accept(Visitor* visitor) {
    visitor->visit(this);
}
void EpsilonNode::accept(Visitor* visitor) {
    visitor->visit(this);
}

void ExprNode::accept(Visitor *visitor) {
    visitor->visit(this);
}




void ImplNode::accept(Visitor *visitor) {
    visitor->visit(this);
}
