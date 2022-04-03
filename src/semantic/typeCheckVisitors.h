//
// Created by jason on 4/1/22.
//

#ifndef COMP_442_TYPECHECKVISITORS_H
#define COMP_442_TYPECHECKVISITORS_H
#include <vector>
#include "SymbolTable.h"
#include "../AST/ast.h"
#include "visitors.h"


class TypeVisitor : public Visitor {
public:
    TypeVisitor();

    virtual ~TypeVisitor();

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

    void visit(IdNode *node) override;


};



#endif //COMP_442_TYPECHECKVISITORS_H
