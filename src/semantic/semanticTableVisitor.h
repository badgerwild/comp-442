//
// Created by jason on 3/30/22.
//
#ifndef COMP_442_SEMANTICTABLEVISITOR_H
#define COMP_442_SEMANTICTABLEVISITOR_H
#include "visitors.h"

class SemanticTableVisitor: public Visitor {
public:
    SemanticTableVisitor() {}

    virtual ~SemanticTableVisitor() {

    }

    void visit(ProgNode *node) override;

    void visit(ClassDeclNode *node) override;

    void visit(MembDeclNode *node) override;

    void visit(FuncDeclNode *node) override;

    void visit(FuncDefNode *node) override;

    void visit(ProgramBlock *node) override;

    void visit(AssignStat *node) override;

    void visit(IdNode *node) override;

    void visit(NotNode *node) override;

    void visit(AddOp *node) override;

    void visit(NumNode *node) override;

    void visit(VarDecl *node) override;

    void visit(TypeNode *node) override;

    void visit(FParamList *node) override;

    void visit(FPAramNode *node) override;

    void visit(DimList *node) override;

    void visit(ImplNode *node) override;
};

#endif //COMP_442_SEMANTICTABLEVISITOR_H
