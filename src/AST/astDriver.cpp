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
    test2->makeSiblings(test3);
    test->adoptChildren(test2);
    std::cout<< "YAY!!!" <<std::endl;
    delete test;
    delete test3;


}
