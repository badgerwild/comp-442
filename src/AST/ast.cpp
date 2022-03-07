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
