//
// Created by jason on 4/3/22.
//

#ifndef COMP_442_CODEGENERATIONVISITOR_H
#define COMP_442_CODEGENERATIONVISITOR_H
#include <fstream>
#include <vector>
#include "../semantic/visitors.h"

class CodeGenerationVisitor: public Visitor {
    std::vector<std::string> registerPool{};
    std::string fileName;
    std::ofstream codeOutput;
    std::vector<std::string> moonExecCode;//assembly is stored here
    std::vector<std::string> moonDataCode;//space is allocated here
public:
    CodeGenerationVisitor();

    CodeGenerationVisitor(const std::string &fileName);

    virtual ~CodeGenerationVisitor();
    void visit(ProgNode* node) override;
    void visit(ClassListNode* node) override;
    void visit(FuncDefList* node) override;
    void visit(ClassDeclNode* node) override;
    void visit(FuncDefNode* node) override;
    void visit(MembListNode* node) override;
    void visit(ProgramBlock* node) override; ///might need to change this one
    void visit(VarDecl* node) override;
    void visit(DimList* node) override;
    void visit(AssignStat* node) override;
    void visit(PutStat* node) override;
    void visit(ReturnStat* node) override;
    void visit(GetStat* node) override;
    void visit(IfStat* node) override;
    void visit(ForStat* node) override;
    void visit(AddOp* node) override;
    void visit(MultOp* node) override;
    void visit(NotNode* node) override;
    void visit(SignNode* node) override;
    void visit(DotNode* node) override;
    void visit(DataMemberNode* node) override;
    void visit(FCallNode* node) override;
    void visit(RelOpNode* node) override;
    void visit(FuncDeclNode* node) override;
    void visit(FPAramNode* node) override;
    void visit(InherListNode* node) override;
    void visit(ScopeSpec* node) override;
    void visit(IndexList* node) override;
    void visit(FParamList* node) override;
    void visit(AParamsNode* node) override;
    void visit(StatNode* node) override;
    void visit(DotParamNode* node) override;
    void visit(MembDeclNode* node) override;
    void visit(ExprNode* node) override;
    void visit(ArithExprNode* node) override;
    void visit(TermNode* node) override;
    void visit(StatOrVarDeclNode* node) override;
    void visit(FactorNode* node) override;
    void visit(TypeNode* node) override;
    void visit(IdNode* node) override;
    void visit(NumNode* node) override;
    void visit(EpsilonNode* node) override;
    void visit(RelExprNode* node) override;
    void visit(ImplNode* node) override;

};


#endif //COMP_442_CODEGENERATIONVISITOR_H
