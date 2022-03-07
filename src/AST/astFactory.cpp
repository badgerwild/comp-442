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
                         auto prog = std::make_shared<InnerNode>();
                         prog->setNumberOfChildren(3);
                         prog->setType("prog");
                         prog->setTypeOfChildren("classList");
                         prog->setTypeOfChildren("funcDefList");
                         prog->setTypeOfChildren("statBlock");
                         prog->setIsLeaf(false);
                         return prog;
                     }
                     }
    );
    factories.insert({"classList", []{
                         auto classList = std::make_shared<InnerNode>();
                         classList->setNumberOfChildren(NOLIMIT);
                         classList->setType("classList");
                         classList->setTypeOfChildren("classDecl");
                         classList->setIsLeaf(false);
                         return classList;
                     }
                     }
    );
    factories.insert({"funcDefList", []{
                         auto funcDefList = std::make_shared<InnerNode>();
                         funcDefList->setNumberOfChildren(NOLIMIT);
                         funcDefList->setType("funcDefList");
                         funcDefList->setTypeOfChildren("funcDef");
                         funcDefList->setIsLeaf(false);
                         return funcDefList;
                     }
                     }
    );
    factories.insert({"classDecl", []{
                         auto classDecl = std::make_shared<InnerNode>();
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
                         auto funcDef = std::make_shared<InnerNode>();
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
                         auto membList = std::make_shared<InnerNode>();
                         membList->setNumberOfChildren(NOLIMIT);
                         membList->setType("membList");
                         membList->setTypeOfChildren("membDecl");
                         membList->setIsLeaf(false);
                         return membList;
                     }
                     }
    );
    factories.insert({"programBlock", []{
                         auto programBlock = std::make_shared<InnerNode>();
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
                         auto varDecl = std::make_shared<InnerNode>();
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
                         auto dimList = std::make_shared<InnerNode>();
                         dimList->setNumberOfChildren(NOLIMIT);
                         dimList->setType("dimList");
                         dimList->setTypeOfChildren("num");
                         dimList->setIsLeaf(false);
                         return dimList;
                     }
                     }
    );

    factories.insert({"assignStat", []{
                         auto assignStat = std::make_shared<InnerNode>();
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
                         auto putStat = std::make_shared<InnerNode>();
                         putStat->setNumberOfChildren(1);
                         putStat->setType("putStat");
                         putStat->setTypeOfChildren("expr");
                         putStat->setIsLeaf(false);
                         return putStat;
                     }
                     }
    );

    factories.insert({"returnStat", []{
                         auto returnStat = std::make_shared<InnerNode>();
                         returnStat->setNumberOfChildren(1);
                         returnStat->setType("returnStat");
                         returnStat->setTypeOfChildren("expr");
                         returnStat->setIsLeaf(false);
                         return returnStat;
                     }
                     }
    );
    factories.insert({"getStat", []{
                         auto getStat = std::make_shared<InnerNode>();
                         getStat->setNumberOfChildren(1);
                         getStat->setType("getStat");
                         getStat->setTypeOfChildren("var");
                         getStat->setIsLeaf(false);
                         return getStat;
                     }
                     }
    );
    factories.insert({"ifStat", []{
                         auto ifStat = std::make_shared<InnerNode>();
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
                         auto forStat = std::make_shared<InnerNode>();
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
                         auto addOp = std::make_shared<InnerNode>();
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
                         auto multOp = std::make_shared<InnerNode>();
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
                         auto _not = std::make_shared<InnerNode>();
                         _not->setNumberOfChildren(1);
                         _not->setType("not");
                         _not->setTypeOfChildren("factor");
                         _not->setIsLeaf(false);
                         return _not;
                     }
                     }
    );
    factories.insert({"sign", []{
                         auto sign = std::make_shared<InnerNode>();
                         sign->setNumberOfChildren(1);
                         sign->setType("sign");
                         sign->setTypeOfChildren("factor");
                         sign->setIsLeaf(false);
                         return sign;
                     }
                     }
    );
    factories.insert({"dot", []{
                         auto dot = std::make_shared<InnerNode>();
                         dot->setNumberOfChildren(2);
                         dot->setType("dot");
                         dot->setTypeOfChildren("dotParam");
                         dot->setIsLeaf(false);
                         return dot;
                     }
                     }
    );
    factories.insert({"dataMember", []{
                         auto dataMember = std::make_shared<InnerNode>();
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
                         auto fCall = std::make_shared<InnerNode>();
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
                         auto relExpr = std::make_shared<InnerNode>();
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
                         auto funcDecl = std::make_shared<InnerNode>();
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
                         auto fParam = std::make_shared<InnerNode>();
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
                         auto inherList = std::make_shared<InnerNode>();
                         inherList->setNumberOfChildren(NOLIMIT);
                         inherList->setType("inherList");
                         inherList->setTypeOfChildren("id");
                         inherList->setIsLeaf(false);
                         return inherList;
                     }
                     }
    );
    factories.insert({"scopeSpec", []{
                         auto scopeSpec = std::make_shared<InnerNode>();
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
                         auto indexList = std::make_shared<InnerNode>();
                         indexList->setNumberOfChildren(NOLIMIT);
                         indexList->setType("indexList");
                         indexList->setTypeOfChildren("arithExpr");
                         indexList->setIsLeaf(false);
                         return indexList;
                     }
                     }
    );

    factories.insert({"fParamList", []{
                         auto fParamList = std::make_shared<InnerNode>();
                         fParamList->setNumberOfChildren(NOLIMIT);
                         fParamList->setType("fParamList");
                         fParamList->setTypeOfChildren("fParam");
                         fParamList->setIsLeaf(false);
                         return fParamList;
                     }
                     }
    );
    factories.insert({"aParams", []{
                         auto aParams = std::make_shared<InnerNode>();
                         aParams->setNumberOfChildren(NOLIMIT);
                         aParams->setType("aParams");
                         aParams->setTypeOfChildren("expr");
                         aParams->setIsLeaf(false);
                         return aParams;
                     }
                     }
    );
    factories.insert({"stat", []{
                         auto stat = std::make_shared<IntermediateInnerNode>();
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
                         auto dotParam = std::make_shared<IntermediateInnerNode>();
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
                         auto membDecl = std::make_shared<IntermediateInnerNode>();
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
                         auto expr= std::make_shared<IntermediateInnerNode>();
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
                         auto arithExpr = std::make_shared<IntermediateInnerNode>();
                         arithExpr->setNumberOfChildren(1);
                         arithExpr->setType("arithExpr");
                         arithExpr->setTypeOfChildren("addOp");
                         arithExpr->setTypeOfChildren("term");
                         arithExpr->setIsLeaf(false);
                         return arithExpr;
                     }
                     }
    );
    factories.insert({"term", []{
                         auto term = std::make_shared<IntermediateInnerNode>();
                         term->setNumberOfChildren(1);
                         term->setType("term");
                         term->setTypeOfChildren("multOp");
                         term->setTypeOfChildren("factor");
                         term->setIsLeaf(false);
                         return term;
                     }
                     }
    );

    factories.insert({"starOrVarDecl", []{
                         auto statOrVarDecl = std::make_shared<IntermediateInnerNode>();
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
                         auto factor = std::make_shared<IntermediateInnerNode>();
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
    factories.insert({"type", []{
                         auto type = std::make_shared<Leaf>();
                         type->setType("type");
                         type->setIsLeaf(true);
                         return type;
                     }
                     }
    );

    factories.insert({"id", []{
                         auto id = std::make_shared<Leaf>();
                         id->setType("id");
                         id->setIsLeaf(true);
                         return id;
                     }
                     }
    );

    factories.insert({"num", []{
                         auto num = std::make_shared<Leaf>();
                         num->setType("num");
                         num->setIsLeaf(true);
                         return num;
                     }
                     }
    );
    factories.insert({"relOp", []{
                         auto relOp = std::make_shared<Leaf>();
                         relOp->setType("relOp");
                         relOp->setIsLeaf(true);
                         return relOp;
                     }
                     }
    );
    factories.insert({EPSILON, []{
                         auto num = std::make_shared<Leaf>();
                         num->setType("Null");
                         num->setIsLeaf(true);
                         return num;
                     }
                     }
    );

}

std::shared_ptr<Node> NodeFactory::makeNode(std::string type) {
    return factories[type]();
}