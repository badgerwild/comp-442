//
// Created by jason on 4/1/22.
//

#ifndef COMP_442_SIZEVISITOR_H
#define COMP_442_SIZEVISITOR_H
#include "visitors.h"

class SizeVisitor: public Visitor  {
public:
    SizeVisitor();

    virtual ~SizeVisitor();

    void visit(ProgNode *node) override;

    void visit(ClassDeclNode *node) override;

    void visit(MembDeclNode *node) override;

    void visit(FuncDeclNode *node) override;

    void visit(FuncDefNode *node) override;

    void visit(ProgramBlock *node) override;

    void visit(VarDecl *node) override;

    void visit(FParamList *node) override;

    void visit(FPAramNode *node) override;

    void visit(ImplNode *node) override;

    void visit(AssignStat *node) override;

    void visit(ExprNode *node) override;

    void visit(ArithExprNode *node) override;

    void visit(AddOp *node) override;

    void visit(MultOp *node) override;

    void visit(TermNode *node) override;

    void visit(FactorNode *node) override;

    void visit(NumNode *node) override;

    void visit(DimList *node) override;

    void visit(IdNode *node) override;

    void visit(PutStat *node) override;
};


#endif //COMP_442_TEMPVARIABLEVISITOR_H
