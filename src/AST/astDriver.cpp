//
// Created by jason on 3/5/22.
//
#include <iostream>
#include "astFactory.h"

int main(){
    NodeFactory factory;
    auto num = factory.makeNode("num");
    auto id = factory.makeNode("id");
    std::vector<Node*> kids ={num, id};
    auto add = InnerNode::makeFamily("addOp", kids);

    auto put =  factory.makeNode("putStat");
    put->adoptChildren(add);
    auto id1 = factory.makeNode("id");
    auto id2 = factory.makeNode("id");
    std::vector<Node*> kids1 ={id1, id2};
    auto mult = InnerNode::makeFamily("multOp", kids1);

    auto id3 = factory.makeNode("id");
    std::vector<Node*> kids2 ={id3, mult};
    auto add2 = InnerNode::makeFamily("addOp", kids2);
    auto id4 = factory.makeNode("id");
    std::vector<Node*> kids3 ={id4, add2};


    auto ass = InnerNode::makeFamily("assignStat", kids3);
    auto id5 = factory.makeNode("id");
    auto put1 =  factory.makeNode("putStat");
    put1->adoptChildren(id5);
    auto num1 = factory.makeNode("num");
    auto id6 = factory.makeNode("id");
    std::vector<Node*> kids4 ={id6, num1};
    auto ass1 = InnerNode::makeFamily("assignStat", kids4);

    auto id7 = factory.makeNode("id");
    auto put2 =  factory.makeNode("putStat");
    put2->adoptChildren(id7);

    auto num2 = factory.makeNode("num");
    auto id8 = factory.makeNode("id");
    std::vector<Node*> kids5 ={id8, num2};
    auto ass2 = InnerNode::makeFamily("assignStat", kids5);

    auto id9 = factory.makeNode("id");
    auto put3 =  factory.makeNode("putStat");
    put3->adoptChildren(id9);

    auto num3 = factory.makeNode("num");
    auto id10 = factory.makeNode("id");
    std::vector<Node*> kids6 ={id10, num3};
    auto ass3 = InnerNode::makeFamily("assignStat", kids6);

    auto type = factory.makeNode("type");
    auto int11 = factory.makeNode("id");
    auto dimList = factory.makeNode("dimList");
    std::vector<Node*> kids7 ={type, int11, dimList};
    auto var = InnerNode::makeFamily("varDecl", kids7);

    auto type1 = factory.makeNode("type");
    auto int12 = factory.makeNode("id");
    auto dimList1 = factory.makeNode("dimList");
    std::vector<Node*> kids8 ={type1, int12, dimList1};
    auto var1 = InnerNode::makeFamily("varDecl", kids8);

    auto type2 = factory.makeNode("type");
    auto int13 = factory.makeNode("id");
    auto dimList2 = factory.makeNode("dimList");
    std::vector<Node*> kids9 ={type2, int13, dimList2};
    auto var2 = InnerNode::makeFamily("varDecl", kids9);

    std::vector<Node*> kids10 = {var2, var1, var, ass3, put3, ass2, put2, ass1, put1, ass, put};
    auto program = InnerNode::makeFamily("programBlock", kids10);

    auto classList = factory.makeNode("classList");
    auto func = factory.makeNode("funcDefList");

    std::vector<Node*> kids11 = {classList, func, program};
    auto prog = InnerNode::makeFamily("prog", kids11);
    Node::traverse(prog,0);


    //std::vector<Node*> kids;
    //kids.push_back(kid1);
    //kids.push_back(kid2);
    //auto head = InnerNode::makeFamily("prog", kids);
    //test2->adoptChildren(kid1);

//    Node::traverse(test, 0);
    //std::vector<Node*> listOfStuff = test2->getSiblings();
    //for (auto &a: listOfStuff) {
      //  std::cout<< a->getType()<<std::endl;
    //}




    std::cout<< "YAY!!!" <<std::endl;


}
