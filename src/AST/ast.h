//
// Created by jason on 3/5/22.
//

#ifndef COMP_442_AST_H
#define COMP_442_AST_H
#include <memory>
#include <vector>
#include <string>
#include <map>
#include <functional>
#include <unordered_set>
//Node base class
class Node{
protected:
    std::string type;
    bool isLeaf;
    std::weak_ptr<Node> parent;
    std::shared_ptr<Node> leftMostSibling;
    std::shared_ptr<Node> rightSibling;

public:
    Node();
    virtual ~Node();
    void makeSiblings(std::shared_ptr<Node>& sibling);
    void setType(std::string ty);
    void setIsLeaf(bool isLeaf);
    void setRightSibling(const std::shared_ptr<Node> &rightSibling);
    void setLeftMostSibling(const std::shared_ptr<Node> &leftMostSibling);
    void setParent(const std::weak_ptr<Node> &parent);
};
/*Class for inner nodes of the tree,
 * number of children is the number of cildren that are allowed for this node type, this
 * is handled by the factory class
 * */
class InnerNode: public Node{
private:
   int numberOfChildren;
    std::shared_ptr<Node> leftMostChild;
   std::unordered_set<std::string> typeOfChildren;
public:
    InnerNode() = default;
    ~InnerNode() = default;
    void setNumberOfChildren(int num);
    virtual void adoptChildren(std::shared_ptr<Node>& child);
    void makeFamily(std::string op, std::shared_ptr<Node> &children);
    void addChildType(std::string child);
    void setTypeOfChildren(const std::string &typeOfChild);
    //TODO validator fucntion
};
/* Class for non-determinstic nodes, that are replaced, overides
 * the adopt child function from base innerNode class and child replaces this node
 */
class IntermediateInnerNode: public InnerNode{
private:
    std::string data;
public:
    const std::string &getData() const;

    void setData(const std::string &data);
    void adoptChildren(std::shared_ptr<Node>& child) override;
};
/* Leaf node
 * Children cannot be added to it, so it only inherits from base class
 */
class Leaf: public Node{
private:
 std::string data;

public:
    void setData(const std::string &data);

};

#endif //COMP_442_AST_H
