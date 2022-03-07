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