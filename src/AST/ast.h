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
    virtual void makeSiblings(std::shared_ptr<Node>& sibling);
    virtual void setType(std::string ty);
    virtual void setIsLeaf(bool isLeaf);
    virtual void setRightSibling(const std::shared_ptr<Node> &rightSibling);
    virtual void setLeftMostSibling(const std::shared_ptr<Node> &leftMostSibling);
    virtual void setParent(const std::weak_ptr<Node> &parent);
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
    virtual ~InnerNode() = default;
    //possibly set these as virtual??
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

class ProgNode: public InnerNode{
public:
    ProgNode();

    virtual ~ProgNode();
};

class ClassListNode: public InnerNode{
public:
    ClassListNode();

    virtual ~ClassListNode();

};

class FuncDefList: public InnerNode{
public:FuncDefList();

    virtual ~FuncDefList();
};

class ClassDeclNode: public InnerNode{
public:
    ClassDeclNode();
    virtual ~ClassDeclNode();
};

class FuncDefNode: public InnerNode{
public:
    FuncDefNode();

    virtual ~FuncDefNode();
};

class MembListNode: public InnerNode{
public:
    MembListNode();

    virtual ~MembListNode();
};

class ProgramBlock: public InnerNode{
public:
    ProgramBlock();

    virtual ~ProgramBlock();
};

class VarDecl: public InnerNode{
public:
    VarDecl();
    virtual ~VarDecl();
};

class DimList: public InnerNode{
public:
    DimList();

    virtual ~DimList();
};

class AssignStat: public InnerNode{
public:
    AssignStat();

    virtual ~AssignStat();
};

class PutStat: public InnerNode{
public:
    PutStat();
    virtual ~PutStat();
};

class ReturnStat: public InnerNode{
public:
    ReturnStat();

    virtual ~ReturnStat();
};

class GetStat: public InnerNode{
public:
    GetStat();
    virtual ~GetStat();
};

class IfStat: public InnerNode{

public:
    IfStat();

    virtual ~IfStat();
};

class ForStat: public InnerNode{
public:
    ForStat();

    virtual ~ForStat();
};

class AddOp: public InnerNode{
public:
    AddOp();

    virtual ~AddOp();

};

class MultOp: public InnerNode{
public:
    MultOp();

    virtual ~MultOp();

};

class NotNode: public InnerNode{
public:
    NotNode();
    virtual ~NotNode();

};

class SignNode: public InnerNode{
public:
    SignNode();

    virtual ~SignNode();

};

class DotNode: public InnerNode{
public:
    DotNode();

    virtual ~DotNode();

};

class DataMemberNode: public InnerNode{
public:
    DataMemberNode();

    virtual ~DataMemberNode();

};

class FCallNode: public InnerNode{
public:
    FCallNode();

    virtual ~FCallNode();
};

class RelExprNode: public InnerNode{
public:
    RelExprNode();

    virtual ~RelExprNode();

};

class FuncDeclNode: public InnerNode{
public:

    FuncDeclNode();

    virtual ~FuncDeclNode();
};

class FPAramNode: public InnerNode{

public:
    FPAramNode();

    virtual ~FPAramNode();

};

class InherListNode: public InnerNode{
public:
    InherListNode();

    virtual ~InherListNode();
};

class ScopeSpec: public InnerNode{
public:
    ScopeSpec();

    virtual ~ScopeSpec();
};
class IndexList: public InnerNode{
public:
    IndexList();

    virtual ~IndexList();
};
class FParamList: public InnerNode{
public:
    FParamList();

    virtual ~FParamList();

};

class AParamsNode: public InnerNode{
public:
    AParamsNode();

    virtual ~AParamsNode();

};

class StatNode: public IntermediateInnerNode {
public:
    StatNode();

    virtual ~StatNode();

};

class DotParamNode: public IntermediateInnerNode{
public:
    DotParamNode();
    virtual ~DotParamNode();
};


class MembDeclNode: public IntermediateInnerNode{
public:
    MembDeclNode();
    virtual ~MembDeclNode();

};

class ExprNode: public IntermediateInnerNode{
public:
    ExprNode();

    virtual ~ExprNode();
};

class ArithExprNode: public IntermediateInnerNode{
public:
    ArithExprNode();
    virtual ~ArithExprNode();
};

class TermNode: public IntermediateInnerNode{
public:
    TermNode();
    virtual ~TermNode();
};

class StatOrVarDeclNode: public IntermediateInnerNode{
public:
    StatOrVarDeclNode();
    virtual ~StatOrVarDeclNode();
};

class FactorNode: public IntermediateInnerNode{
public:
    FactorNode();
    virtual ~FactorNode();
};

class TypeNode: public Leaf{
public:
    TypeNode();
    virtual ~TypeNode();
};

class IdNode: public Leaf{
public:
    IdNode();

    virtual ~IdNode();
};

class NumNode: public Leaf{
public:
    NumNode();

    virtual ~NumNode();

};

class RelOpNode: public Leaf{
public:
    RelOpNode();

    virtual ~RelOpNode();

};

class EpsilonNode: public Leaf{

public:
    EpsilonNode();

    virtual ~EpsilonNode();

};


#endif //COMP_442_AST_H
