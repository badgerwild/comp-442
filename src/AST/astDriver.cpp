//
// Created by jason on 3/5/22.
//
#include <iostream>
#include "astFactory.h"

int main(){
    NodeFactory factory;
    auto test = factory.makeNode("prog");
    auto test2 = factory.makeNode("term");
    //test->makeSiblings(test2);
    auto test3 = factory.makeNode("type");
    auto test4 = factory.makeNode("num");
    test2->makeSiblings(test3);
    test2->makeSiblings(test4);
    test->adoptChildren(test2);
    auto kid1 = factory.makeNode("id");
    auto kid2 = factory.makeNode("relOp");
    std::vector<Node*> kids;
    kids.push_back(kid1);
    kids.push_back(kid2);
    auto head = InnerNode::makeFamily("prog", kids);




    std::cout<< "YAY!!!" <<std::endl;
    delete test;
    delete test3;


}
