//
// Created by jason on 3/17/22.
//

#ifndef COMP_442_VISITORS_H
#define COMP_442_VISITORS_H
//#include "../AST/ast.h"
//#include "visitors.h"
class ProgNode;
class ClassListNode;
class FuncDefList;
class ClassDeclNode;
class FuncDefNode;
class MembListNode;
class ProgramBlock;
class VarDecl;
class DimList;
class AssignStat;
class PutStat;
class ReturnStat;
class GetStat;
class IfStat;
class ForStat;
class AddOp;
class MultOp;
class NotNode;
class SignNode;
class DotNode;
class DataMemberNode;
class FCallNode;
class RelOpNode;
class FuncDeclNode;
class FPAramNode;
class InherListNode;
class ScopeSpec;
class IndexList;
class FParamList;
class AParamsNode;
class StatNode;
class DotParamNode;
class MembDeclNode;
class ExprNode;
class ArithExprNode;
class TermNode;
class StatOrVarDeclNode;
class FactorNode;
class TypeNode;
class IdNode;
class NumNode;
class EpsilonNode;
class RelExprNode;

class Visitor {
public:
    Visitor() {}

    virtual ~Visitor() {

    }
    virtual void visit(ProgNode* node){};
    virtual void visit(ClassListNode* node){};
    virtual void visit(FuncDefList* node){};
    virtual void visit(ClassDeclNode* node){};
    virtual void visit(FuncDefNode* node){};
    virtual void visit(MembListNode* node){};
    virtual void visit(ProgramBlock* node){}; ///might need to change this one
    virtual void visit(VarDecl* node){};
    virtual void visit(DimList* node){};
    virtual void visit(AssignStat* node){};
    virtual void visit(PutStat* node){};
    virtual void visit(ReturnStat* node){};
    virtual void visit(GetStat* node){};
    virtual void visit(IfStat* node){};
    virtual void visit(ForStat* node){};
    virtual void visit(AddOp* node){};
    virtual void visit(MultOp* node){};
    virtual void visit(NotNode* node){};
    virtual void visit(SignNode* node){};
    virtual void visit(DotNode* node){};
    virtual void visit(DataMemberNode* node){};
    virtual void visit(FCallNode* node){};
    virtual void visit(RelOpNode* node){};
    virtual void visit(FuncDeclNode* node){};
    virtual void visit(FPAramNode* node){};
    virtual void visit(InherListNode* node){};
    virtual void visit(ScopeSpec* node){};
    virtual void visit(IndexList* node){};
    virtual void visit(FParamList* node){};
    virtual void visit(AParamsNode* node){};
    virtual void visit(StatNode* node){};
    virtual void visit(DotParamNode* node){};
    virtual void visit(MembDeclNode* node){};
    virtual void visit(ExprNode* node){};
    virtual void visit(ArithExprNode* node){};
    virtual void visit(TermNode* node){};
    virtual void visit(StatOrVarDeclNode* node){};
    virtual void visit(FactorNode* node){};
    virtual void visit(TypeNode* node){};
    virtual void visit(IdNode* node){};
    virtual void visit(NumNode* node){};
    virtual void visit(EpsilonNode* node){};
    virtual void visit(RelExprNode* node){}
};


class SemanticTableVisitor: public Visitor{
public:
    SemanticTableVisitor() {}

    virtual ~SemanticTableVisitor() {

    }
    void visit(ProgNode* node) override;
    void visit(ClassDeclNode* node) override;
    void visit(MembDeclNode* node) override;
    void visit(FuncDeclNode* node) override;
    void visit(FuncDefNode* node) override;
    void visit(ProgramBlock* node) override;
    void visit(AssignStat* node) override;
    void visit(IdNode* node) override;
    void visit(NotNode* node) override;
    void visit(AddOp* node) override;
    void visit(NumNode* node) override;
    void visit(VarDecl* node) override;
    void visit(TypeNode* node) override;
    void visit(FParamList* node) override;
    void visit(FPAramNode* node) override;
    void visit(DimList* node) override;








};


#endif //COMP_442_VISITORS_H
