//
// Created by jason on 3/6/22.
//

#include "astFactory.h"
NodeFactory::~NodeFactory() {}
/*Abstract factory using a map with Lamdba functions as for node creation.
 * Node type is given by a string that is passed through semantic action in the parser.
 *
 */
NodeFactory::NodeFactory() {
    factories.insert({"prog", []{
                         auto prog = new ProgNode();
                         prog -> setNumberOfChildren(3);
                         prog->setType("prog");
                         prog->setTypeOfChildren("classList");
                         prog->setTypeOfChildren("funcDefList");
                         prog->setTypeOfChildren("statBlock");
                         prog->setIsLeaf(false);
                         return prog;
                     }
                     }
    );
    /*
    factories.insert({"classList", []{
                         auto classList = std::make_shared<ClassListNode>();
                         classList->setNumberOfChildren(NOLIMIT);
                         classList->setType("classList");
                         classList->setTypeOfChildren("classDecl");
                         classList->setIsLeaf(false);
                         return classList;
                     }
                     }
    );
    factories.insert({"funcDefList", []{
                         auto funcDefList = std::make_shared<FuncDefList>();
                         funcDefList->setNumberOfChildren(NOLIMIT);
                         funcDefList->setType("funcDefList");
                         funcDefList->setTypeOfChildren("funcDef");
                         funcDefList->setIsLeaf(false);
                         return funcDefList;
                     }
                     }
    );
    factories.insert({"classDecl", []{
                         auto classDecl = std::make_shared<ClassDeclNode>();
                         classDecl->setNumberOfChildren(3);
                         classDecl->setType("classDecl");
                         classDecl->setTypeOfChildren("id");
                         classDecl->setTypeOfChildren("inherList");
                         classDecl->setTypeOfChildren("membList");
                         classDecl->setIsLeaf(false);
                         return classDecl;
                     }
                     }
    );
    factories.insert({"funcDef", []{
                         auto funcDef = std::make_shared<FuncDefNode>();
                         funcDef->setNumberOfChildren(5);
                         funcDef->setType("funcDef");
                         funcDef->setTypeOfChildren("type");
                         funcDef->setTypeOfChildren("scopeSpec");
                         funcDef->setTypeOfChildren("id");
                         funcDef->setTypeOfChildren("fparamList");
                         funcDef->setTypeOfChildren("statBlock");
                         funcDef->setIsLeaf(false);
                         return funcDef;
                     }
                     }
    );

    factories.insert({"membList", []{
                         auto membList = std::make_shared<MembListNode>();
                         membList->setNumberOfChildren(NOLIMIT);
                         membList->setType("membList");
                         membList->setTypeOfChildren("membDecl");
                         membList->setIsLeaf(false);
                         return membList;
                     }
                     }
    );
    factories.insert({"programBlock", []{
                         auto programBlock = std::make_shared<ProgramBlock>();
                         programBlock->setNumberOfChildren(NOLIMIT);
                         programBlock->setType("programBlock");
                         programBlock->setTypeOfChildren("stat");
                         programBlock->setTypeOfChildren("varDecl");
                         programBlock->setIsLeaf(false);
                         return programBlock;
                     }
                     }
    );
    factories.insert({"varDecl", []{
                         auto varDecl = std::make_shared<VarDecl>();
                         varDecl->setNumberOfChildren(3);
                         varDecl->setType("varDecl");
                         varDecl->setTypeOfChildren("type");
                         varDecl->setTypeOfChildren("id");
                         varDecl->setTypeOfChildren("dimList");
                         varDecl->setIsLeaf(false);
                         return varDecl;
                     }
                     }
    );
    factories.insert({"dimList", []{
                         auto dimList = std::make_shared<DimList>();
                         dimList->setNumberOfChildren(NOLIMIT);
                         dimList->setType("dimList");
                         dimList->setTypeOfChildren("num");
                         dimList->setIsLeaf(false);
                         return dimList;
                     }
                     }
    );

    factories.insert({"assignStat", []{
                         auto assignStat = std::make_shared<AssignStat>();
                         assignStat->setNumberOfChildren(2);
                         assignStat->setType("assignStat");
                         assignStat->setTypeOfChildren("var");
                         assignStat->setTypeOfChildren("expr");
                         assignStat->setIsLeaf(false);
                         return assignStat;
                     }
                     }
    );

    factories.insert({"putStat", []{
                         auto putStat = std::make_shared<PutStat>();
                         putStat->setNumberOfChildren(1);
                         putStat->setType("putStat");
                         putStat->setTypeOfChildren("expr");
                         putStat->setIsLeaf(false);
                         return putStat;
                     }
                     }
    );

    factories.insert({"returnStat", []{
                         auto returnStat = std::make_shared<ReturnStat>();
                         returnStat->setNumberOfChildren(1);
                         returnStat->setType("returnStat");
                         returnStat->setTypeOfChildren("expr");
                         returnStat->setIsLeaf(false);
                         return returnStat;
                     }
                     }
    );
    factories.insert({"getStat", []{
                         auto getStat = std::make_shared<GetStat>();
                         getStat->setNumberOfChildren(1);
                         getStat->setType("getStat");
                         getStat->setTypeOfChildren("var");
                         getStat->setIsLeaf(false);
                         return getStat;
                     }
                     }
    );
    factories.insert({"ifStat", []{
                         auto ifStat = std::make_shared<IfStat>();
                         ifStat->setNumberOfChildren(3);
                         ifStat->setType("ifStat");
                         ifStat->setTypeOfChildren("relExpr");
                         ifStat->setTypeOfChildren("programBlock");
                         ifStat->setTypeOfChildren("programBlock");
                         ifStat->setIsLeaf(false);
                         return ifStat;
                     }
                     }
    );

    factories.insert({"forStat", []{
                         auto forStat = std::make_shared<ForStat>();
                         forStat->setNumberOfChildren(6);
                         forStat->setType("forStat");
                         forStat->setTypeOfChildren("type");
                         forStat->setTypeOfChildren("id");
                         forStat->setTypeOfChildren("expr");
                         forStat->setTypeOfChildren("relExpr");
                         forStat->setTypeOfChildren("assignStat");
                         forStat->setTypeOfChildren("programBlock");
                         forStat->setIsLeaf(false);
                         return forStat;
                     }
                     }
    );
    factories.insert({"addOp", []{
                         auto addOp = std::make_shared<AddOp>();
                         addOp->setNumberOfChildren(2);
                         addOp->setType("addOp");
                         addOp->setTypeOfChildren("arithExpr");
                         addOp->setTypeOfChildren("term");
                         addOp->setIsLeaf(false);
                         return addOp;
                     }
                     }
    );

    factories.insert({"multOp", []{
                         auto multOp = std::make_shared<MultOp>();
                         multOp->setNumberOfChildren(2);
                         multOp->setType("multOp");
                         multOp->setTypeOfChildren("factor");
                         multOp->setTypeOfChildren("term");
                         multOp->setIsLeaf(false);
                         return multOp;
                     }
                     }
    );
    factories.insert({"not", []{
                         auto _not = std::make_shared<NotNode>();
                         _not->setNumberOfChildren(1);
                         _not->setType("not");
                         _not->setTypeOfChildren("factor");
                         _not->setIsLeaf(false);
                         return _not;
                     }
                     }
    );
    factories.insert({"sign", []{
                         auto sign = std::make_shared<SignNode>();
                         sign->setNumberOfChildren(1);
                         sign->setType("sign");
                         sign->setTypeOfChildren("factor");
                         sign->setIsLeaf(false);
                         return sign;
                     }
                     }
    );
    factories.insert({"dot", []{
                         auto dot = std::make_shared<DotNode>();
                         dot->setNumberOfChildren(2);
                         dot->setType("dot");
                         dot->setTypeOfChildren("dotParam");
                         dot->setIsLeaf(false);
                         return dot;
                     }
                     }
    );
    factories.insert({"dataMember", []{
                         auto dataMember = std::make_shared<DataMemberNode>();
                         dataMember->setNumberOfChildren(2);
                         dataMember->setType("dataMember");
                         dataMember->setTypeOfChildren("id");
                         dataMember->setTypeOfChildren("indexList");
                         dataMember->setIsLeaf(false);
                         return dataMember;
                     }
                     }
    );

    factories.insert({"fCall", []{
                         auto fCall = std::make_shared<FCallNode>();
                         fCall->setNumberOfChildren(2);
                         fCall->setType("fCall");
                         fCall->setTypeOfChildren("id");
                         fCall->setTypeOfChildren("aParams");
                         fCall->setIsLeaf(false);
                         return fCall;
                     }
                     }
    );

    factories.insert({"relExpr", []{
                         auto relExpr = std::make_shared<RelExprNode>();
                         relExpr->setNumberOfChildren(3);
                         relExpr->setType("relExpr");
                         relExpr->setTypeOfChildren("expr");
                         relExpr->setTypeOfChildren("relOp");
                         relExpr->setIsLeaf(false);
                         return relExpr;
                     }
                     }
    );

    factories.insert({"funcDecl", []{
                         auto funcDecl = std::make_shared<FuncDeclNode>();
                         funcDecl->setNumberOfChildren(3);
                         funcDecl->setType("funcDecl");
                         funcDecl->setTypeOfChildren("type");
                         funcDecl->setTypeOfChildren("id");
                         funcDecl->setTypeOfChildren("fParamList");
                         funcDecl->setIsLeaf(false);
                         return funcDecl;
                     }
                     }
    );
    factories.insert({"fParam", []{
                         auto fParam = std::make_shared<FPAramNode>();
                         fParam->setNumberOfChildren(3);
                         fParam->setType("fParam");
                         fParam->setTypeOfChildren("type");
                         fParam->setTypeOfChildren("id");
                         fParam->setTypeOfChildren("dimList");
                         fParam->setIsLeaf(false);
                         return fParam;
                     }
                     }
    );

    factories.insert({"inherList", []{
                         auto inherList = std::make_shared<InherListNode>();
                         inherList->setNumberOfChildren(NOLIMIT);
                         inherList->setType("inherList");
                         inherList->setTypeOfChildren("id");
                         inherList->setIsLeaf(false);
                         return inherList;
                     }
                     }
    );
    factories.insert({"scopeSpec", []{
                         auto scopeSpec = std::make_shared<ScopeSpec>();
                         scopeSpec->setNumberOfChildren(NOLIMIT);
                         scopeSpec->setType("scopeSpec");
                         scopeSpec->setTypeOfChildren("id");
                         scopeSpec->setTypeOfChildren(EPSILON);
                         scopeSpec->setIsLeaf(false);
                         return scopeSpec;
                     }
                     }
    );
    factories.insert({"indexList", []{
                         auto indexList = std::make_shared<IndexList>();
                         indexList->setNumberOfChildren(NOLIMIT);
                         indexList->setType("indexList");
                         indexList->setTypeOfChildren("arithExpr");
                         indexList->setIsLeaf(false);
                         return indexList;
                     }
                     }
    );

    factories.insert({"fParamList", []{
                         auto fParamList = std::make_shared<FParamList>();
                         fParamList->setNumberOfChildren(NOLIMIT);
                         fParamList->setType("fParamList");
                         fParamList->setTypeOfChildren("fParam");
                         fParamList->setIsLeaf(false);
                         return fParamList;
                     }
                     }
    );
    factories.insert({"aParams", []{
                         auto aParams = std::make_shared<AParamsNode>();
                         aParams->setNumberOfChildren(NOLIMIT);
                         aParams->setType("aParams");
                         aParams->setTypeOfChildren("expr");
                         aParams->setIsLeaf(false);
                         return aParams;
                     }
                     }
    );
    factories.insert({"stat", []{
                         auto stat = std::make_shared<StatNode>();
                         stat->setNumberOfChildren(1);
                         stat->setType("stat");
                         stat->setTypeOfChildren("ifStat");
                         stat->setTypeOfChildren("assignStat");
                         stat->setTypeOfChildren("forStat");
                         stat->setTypeOfChildren("getStat");
                         stat->setTypeOfChildren("putStat");
                         stat->setTypeOfChildren("returnStat");
                         stat->setIsLeaf(false);
                         return stat;
                     }
                     }
    );

    factories.insert({"dotParam", []{
                         auto dotParam = std::make_shared<DotParamNode>();
                         dotParam->setNumberOfChildren(1);
                         dotParam->setType("dotParam");
                         dotParam->setTypeOfChildren("dataMember");
                         dotParam->setTypeOfChildren("fCall");
                         dotParam->setTypeOfChildren("dot");
                         dotParam->setIsLeaf(false);
                         return dotParam;
                     }
                     }
    );
    factories.insert({"membDecl", []{
                         auto membDecl = std::make_shared<MembDeclNode>();
                         membDecl->setNumberOfChildren(1);
                         membDecl->setType("membDecl");
                         membDecl->setTypeOfChildren("varDecl");
                         membDecl->setTypeOfChildren("funcDecl");
                         membDecl->setIsLeaf(false);
                         return membDecl;
                     }
                     }
    );

    factories.insert({"expr", []{
                         auto expr= std::make_shared<ExprNode>();
                         expr->setNumberOfChildren(1);
                         expr->setType("expr");
                         expr->setTypeOfChildren("relExpr");
                         expr->setTypeOfChildren("arithExpr");
                         expr->setIsLeaf(false);
                         return expr;
                     }
                     }
    );
    factories.insert({"arithExpr", []{
                         auto arithExpr = std::make_shared<ArithExprNode>();
                         arithExpr->setNumberOfChildren(1);
                         arithExpr->setType("arithExpr");
                         arithExpr->setTypeOfChildren("addOp");
        arithExpr->setIsLeaf(false);
                         arithExpr->setTypeOfChildren("term");
                         return arithExpr;
                     }
                     }
    );
     */
    factories.insert({"term", []{
                         auto term = new TermNode();
                         term->setNumberOfChildren(1);
                         term->setType("term");
                         term->setTypeOfChildren("multOp");
                         term->setTypeOfChildren("factor");
                         term->setIsLeaf(false);
                         return term;
                     }
                     }
    );
/*
    factories.insert({"starOrVarDecl", []{
                         auto statOrVarDecl = std::make_shared<StatOrVarDeclNode>();
                         statOrVarDecl->setNumberOfChildren(1);
                         statOrVarDecl->setType("starOrVarDecl");
                         statOrVarDecl->setTypeOfChildren("stat");
                         statOrVarDecl->setTypeOfChildren("varDecl");
                         statOrVarDecl->setIsLeaf(false);
                         return statOrVarDecl;
                     }
                     }
    );

    factories.insert({"factor", []{
                         auto factor = std::make_shared<FactorNode>();
                         factor->setNumberOfChildren(1);
                         factor->setType("factor");
                         factor->setTypeOfChildren("dot");
                         factor->setTypeOfChildren("id");
                         factor->setTypeOfChildren("num");
                         factor->setTypeOfChildren("fCall");
                         factor->setTypeOfChildren("arithExpr");
                         factor->setTypeOfChildren("not");
                         factor->setTypeOfChildren("sign");
                         factor->setIsLeaf(false);
                         return factor;
                     }
                     }
    );
    */
    factories.insert({"type", []{
                         auto type = new TypeNode();
                         type->setType("type");
                         type->setIsLeaf(true);
                         return type;
                     }
                     }
    );
/*
    factories.insert({"id", []{
                         auto id = std::make_shared<IdNode>();
                         id->setType("id");
                         id->setIsLeaf(true);
                         return id;
                     }
                     }
    );

    factories.insert({"num", []{
                         auto num = std::make_shared<NumNode>();
                         num->setType("num");
                         num->setIsLeaf(true);
                         return num;
                     }
                     }
    );
    factories.insert({"relOp", []{
                         auto relOp = std::make_shared<RelOpNode>();
                         relOp->setType("relOp");
                         relOp->setIsLeaf(true);
                         return relOp;
                     }
                     }
    );
    factories.insert({EPSILON, []{
                         auto num = std::make_shared<EpsilonNode>();
                         num->setType("Null");
                         num->setIsLeaf(true);
                         return num;
                     }
                     }
    );
*/
}
Node* NodeFactory::makeNode(std::string type) {
    return factories[type]();
}