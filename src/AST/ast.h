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
#include "../semantic/SymbolTable.h"
#include "../semantic/visitors.h"

//Node base class
//TODO create a large delete function that completly iterates through tree and deletes everything
class Node{
protected:
    std::string type;
    bool isLeaf;
    Node* parent;
    Node* leftMostSibling;
    Node* rightSibling;
    Node* leftMostChild;
    std::string data;
    std::string name;
public:
    SymbolTable* symbolTable;
    SymbolTableRow symbolTableEntry;

    Node();
    Node(Node const& toCopy);
    virtual ~Node();
    Node& operator = (const Node &toAssign);
    std::vector<Node*> getSiblings();
    static void traverse(Node *node, int depth);
    void deleteAll();
    void deleteAllHelper(Node *node);
    std::vector<Node *> reverse(std::vector<Node*> rev);
    virtual void makeSiblings(Node *sibling);
    virtual void setType(std::string ty);
    virtual void setIsLeaf(bool isLeaf);
    virtual void setRightSibling(Node *rightSibling);
    virtual void setLeftMostSibling(Node *leftMostSibling);
    virtual void setParent(Node *parent);
    virtual void setData(const std::string &data);
    void setName(const std::string &name);

    const std::string &getName() const;

    virtual const std::string &getData() const;
    virtual void adoptChildren(Node *child) = 0;
    //Accept function for visitor pattern
    virtual void accept(Visitor* visitor){};
    const SymbolTableRow &getSymbolTableEntry() const;
    Node *getParent() const;
    Node *getRightSibling();
    Node *getLeftMostChild() const;
    const std::string &getType() const;
};
/*Class for inner nodes of the tree,
 * number of children is the number of cildren that are allowed for this node type, this
 * is handled by the factory class
 * */
class InnerNode: public Node{
private:
   int numberOfChildren;
   std::unordered_set<std::string> typeOfChildren;
public:
    InnerNode() = default;
    virtual ~InnerNode() = default;
    //possibly set these as virtual??
    void setNumberOfChildren(int num);
    int getNumberOfChildren();
    void adoptChildren(Node *child) override;
    static Node* makeFamily(std::string op, std::vector<Node *> children);
    void addChildType(std::string child);
    void setTypeOfChildren(const std::string &typeOfChild);
    void deleteChild();
    //TODO validator fucntion
};
/* Class for non-determinstic nodes, that are replaced, overides
 * the adopt child function from base innerNode class and child replaces this node
 */
class IntermediateInnerNode: public InnerNode{
private:

public:
    IntermediateInnerNode();

    virtual ~IntermediateInnerNode();

  //  const std::string &getData() const;
    void setData(const std::string &data) override;
    void adoptChildren(Node *child) override;
};
/* Leaf node
 * Children cannot be added to it, so it only inherits from base class
 */
class Leaf: public Node{
private:

public:
   // void setData(const std::string &data);
    void adoptChildren(Node *child);

};

class ProgNode: public InnerNode{
public:
    ProgNode();
    virtual ~ProgNode();
    void accept(Visitor* visitor) override;
};

class ClassListNode: public InnerNode{
public:
    ClassListNode();

    virtual ~ClassListNode();
    void accept(Visitor* visitor) override;
};

class FuncDefList: public InnerNode{
public:FuncDefList();

    virtual ~FuncDefList();
    void accept(Visitor* visitor) override;
};

class ClassDeclNode: public InnerNode{
public:
    ClassDeclNode();
    virtual ~ClassDeclNode();
    void accept(Visitor* visitor) override;
};

class FuncDefNode: public InnerNode{
public:
    FuncDefNode();

    virtual ~FuncDefNode();
    void accept(Visitor* visitor) override;
};

class MembListNode: public InnerNode{
public:
    MembListNode();

    virtual ~MembListNode();
    void accept(Visitor* visitor) override;
};

class ProgramBlock: public InnerNode{ //mightneed to change this one
public:
    ProgramBlock();

    virtual ~ProgramBlock();
    void accept(Visitor* visitor) override;

};

class VarDecl: public InnerNode{
public:
    VarDecl();
    virtual ~VarDecl();
    void accept(Visitor* visitor) override;
    void addEntry(VarDeclROW vec);
};

class DimList: public InnerNode{
public:
    DimList();

    virtual ~DimList();
    void accept(Visitor* visitor) override;
};

class AssignStat: public InnerNode{
public:
    AssignStat();

    virtual ~AssignStat();
    void accept(Visitor* visitor) override;
};

class PutStat: public InnerNode{
public:
    PutStat();
    virtual ~PutStat();
    void accept(Visitor* visitor) override;
};

class ReturnStat: public InnerNode{
public:
    ReturnStat();

    virtual ~ReturnStat();
    void accept(Visitor* visitor) override;
};

class GetStat: public InnerNode{
public:
    GetStat();
    virtual ~GetStat();
    void accept(Visitor* visitor) override;
};

class IfStat: public InnerNode{

public:
    IfStat();

    virtual ~IfStat();
    void accept(Visitor* visitor) override;

};

class ForStat: public InnerNode{
public:
    ForStat();

    virtual ~ForStat();
    void accept(Visitor* visitor) override;
};

class AddOp: public InnerNode{
public:
    AddOp();

    virtual ~AddOp();
    void accept(Visitor* visitor) override;
};

class MultOp: public InnerNode{
public:
    MultOp();

    virtual ~MultOp();
    void accept(Visitor* visitor) override;
};

class NotNode: public InnerNode{
public:
    NotNode();
    virtual ~NotNode();
    void accept(Visitor* visitor) override;
};

class SignNode: public InnerNode{
public:
    SignNode();

    virtual ~SignNode();
    void accept(Visitor* visitor) override;
};

class DotNode: public InnerNode{
public:
    DotNode();

    virtual ~DotNode();
    void accept(Visitor* visitor) override;
};

class DataMemberNode: public InnerNode{
public:
    DataMemberNode();

    virtual ~DataMemberNode();
    void accept(Visitor* visitor) override;
};

class FCallNode: public InnerNode{
public:
    FCallNode();

    virtual ~FCallNode();
    void accept(Visitor* visitor) override;
};

class RelExprNode: public InnerNode{
public:
    RelExprNode();

    virtual ~RelExprNode();
    void accept(Visitor* visitor) override;
};

class FuncDeclNode: public InnerNode{
public:

    FuncDeclNode();

    virtual ~FuncDeclNode();
    void accept(Visitor* visitor) override;
};

class FPAramNode: public InnerNode{

public:
    FPAramNode();

    virtual ~FPAramNode();
    void accept(Visitor* visitor) override;
};

class InherListNode: public InnerNode{
public:
    InherListNode();

    virtual ~InherListNode();
    void accept(Visitor* visitor) override;

};

class ScopeSpec: public InnerNode{
public:
    ScopeSpec();

    virtual ~ScopeSpec();
    void accept(Visitor* visitor) override;
};
class IndexList: public InnerNode{
public:
    IndexList();

    virtual ~IndexList();
    void accept(Visitor* visitor) override;
};
class FParamList: public InnerNode{
public:
    FParamList();

    virtual ~FParamList();
    void accept(Visitor* visitor) override;
};

class AParamsNode: public InnerNode{
public:
    AParamsNode();

    virtual ~AParamsNode();
    void accept(Visitor* visitor) override;
};

class StatNode: public IntermediateInnerNode {
public:
    StatNode();

    virtual ~StatNode();
    void accept(Visitor* visitor) override;
};

class DotParamNode: public IntermediateInnerNode{
public:
    DotParamNode();
    virtual ~DotParamNode();
    void accept(Visitor* visitor) override;
};


class MembDeclNode: public IntermediateInnerNode{
public:
    MembDeclNode();
    virtual ~MembDeclNode();
    void accept(Visitor*) override;
};

class ExprNode: public IntermediateInnerNode{
public:
    ExprNode();

    virtual ~ExprNode();
    void accept(Visitor* visitor) override;
};

class ArithExprNode: public IntermediateInnerNode{
public:
    ArithExprNode();
    virtual ~ArithExprNode();
    void accept(Visitor* visitor) override;
};

class TermNode: public IntermediateInnerNode{
public:
    TermNode();
    virtual ~TermNode();
    void accept(Visitor* visitor) override;
};

class StatOrVarDeclNode: public IntermediateInnerNode{
public:
    StatOrVarDeclNode();
    virtual ~StatOrVarDeclNode();

    void accept(Visitor* visitor) override;
};

class FactorNode: public IntermediateInnerNode{
public:
    FactorNode();
    virtual ~FactorNode();
    void accept(Visitor* visitor) override;
};

class TypeNode: public Leaf{
public:
    TypeNode();
    virtual ~TypeNode();
    void accept(Visitor* visitor) override;
};

class IdNode: public Leaf{
public:
    IdNode();

    virtual ~IdNode();
    void accept(Visitor* visitor) override;
};

class NumNode: public Leaf{
public:
    NumNode();

    virtual ~NumNode();
    void accept(Visitor* visitor) override;
};

class RelOpNode: public Leaf{
public:
    RelOpNode();

    virtual ~RelOpNode();
    void accept(Visitor* visitor) override;
};

class EpsilonNode: public Leaf{

public:
    EpsilonNode();

    virtual ~EpsilonNode();
    void accept(Visitor* visitor) override;
};


#endif //COMP_442_AST_H
