//
// Created by jason on 3/6/22.
//

#ifndef COMP_442_ASTFACTORY_H
#define COMP_442_ASTFACTORY_H
#include <unordered_map>
#include "ast.h"
const int NOLIMIT = -1;
const std::string EPSILON = "epsilon";
class NodeFactory{
private:
    std::unordered_map<std::string, std::function<std::shared_ptr<Node>()>> factories;
public:
    NodeFactory();
    ~NodeFactory();
    std::shared_ptr<Node> makeNode(std::string type);
    std::shared_ptr<Node> makeLeaf(std::string type, std::string data);


};


#endif //COMP_442_ASTFACTORY_H
