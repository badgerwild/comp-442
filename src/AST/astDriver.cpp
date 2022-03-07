//
// Created by jason on 3/5/22.
//
#include <iostream>
#include "astFactory.h"

int main(){
    NodeFactory factory;
    auto test = factory.makeNode("prog");
    std::cout<< "YAY!!!" <<std::endl;

}
