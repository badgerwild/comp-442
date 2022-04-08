//
// Created by jason on 4/3/22.
//

#include "../AST/ast.h"
#include "codeGenerationVisitor.h"
const std::string CODE_GEN_PATH = "/home/jason/collective/comp-442/comp-442/src/compliler/output/";
const std::string  MOON = ".m";
const std::string INDENT_11 = "           ";
const std::string INDENT_10 = "          ";//TODO MAKE THIS BETTER, probably a for loop

CodeGenerationVisitor::CodeGenerationVisitor() {}

CodeGenerationVisitor::CodeGenerationVisitor(const std::string &fileName) {
    this->fileName = CODE_GEN_PATH+fileName+MOON;
    codeOutput.open(this->fileName);
    //inititalized a stack of registers
    for(int i = 12; i >=1; --i){
        registerPool.push_back("r" + std::to_string(i));
    }

}
CodeGenerationVisitor::~CodeGenerationVisitor() {
    codeOutput.close();
}

void CodeGenerationVisitor::visit(ProgNode *node) {
    moonExecCode.push_back(INDENT_11 +"entry");
    moonExecCode.push_back(INDENT_11 + "addi r14,r0,topaddr");

    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }

    moonDataCode.push_back("\n" + INDENT_11 + "%Buffer space for console output");
    moonDataCode.push_back("buf" +INDENT_11 +"res 20");
    moonExecCode.push_back(INDENT_11 + "hlt");
    //output the exec
    for(std::string &execCode: moonExecCode ){
        codeOutput<<execCode<<std::endl;
    }
    for (std::string &dataCode: moonDataCode){
        codeOutput<<dataCode<<std::endl;
    }

    //then the data code

}

void CodeGenerationVisitor::visit(ClassListNode *node) {
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }

}

void CodeGenerationVisitor::visit(FuncDefList *node) {
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }
}

void CodeGenerationVisitor::visit(ClassDeclNode *node) {
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }
}

void CodeGenerationVisitor::visit(FuncDefNode *node) {
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }
}

void CodeGenerationVisitor::visit(MembListNode *node) {
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }
}

void CodeGenerationVisitor::visit(ProgramBlock *node) {
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }
}

void CodeGenerationVisitor::visit(VarDecl *node) {

    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }
    int arraySize = 1; // no items
    for (auto &a: children){
        if (a->getType() == "dimList"){
            arraySize = std::stoi(a->getLeftMostChild()->getData())+1;
        }
    }
    moonDataCode.push_back(INDENT_11 + "% Space for var " + children[0]->getData());
    //TODO go back to symbol table genration and make sure to assign an entry to each node.
    moonDataCode.push_back(children[0]->getData()+ INDENT_10 +" res " +std::to_string((node->size)*arraySize));



}

void CodeGenerationVisitor::visit(DimList *node) {
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }
}

void CodeGenerationVisitor::visit(AssignStat *node) {
    int offSet = 0;
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }
    std::string addressRegister = registerPool.back();
    registerPool.pop_back();
    std::string localRegister = registerPool.back();
    registerPool.pop_back();
    moonExecCode.push_back(INDENT_11+ "%Processing ,"+children[1]->moonTag+"->" +children[0]->moonTag);
    moonExecCode.push_back(INDENT_11+"% Assigning array access    ");
    //TODO get this working for accessing elemets of an array
    int condition = children.size();
    if (condition > 2) {
        offSet = std::stoi(children[2]->getData())*children[1]->size;
    }
    moonExecCode.push_back(INDENT_11 +"addi " +addressRegister+"," +"r0,"+std::to_string(offSet));
    //moonExecCode.push_back(INDENT_11 + "lw "+ localRegister +","+children[0]->moonTag+"(r0)");
    moonExecCode.push_back(INDENT_11 + "lw "+ localRegister +","+children[0]->moonTag+"("+addressRegister+")");
    moonExecCode.push_back(INDENT_11+"sw " + children[1]->moonTag+"(r0),"+localRegister);

    registerPool.push_back(localRegister);
    registerPool.push_back(addressRegister);
}

void CodeGenerationVisitor::visit(PutStat *node) {
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }
    std::string localRegister = registerPool.back();
    registerPool.pop_back();

    moonExecCode.push_back(INDENT_11 + "% Processing: write( " + children[0]->moonTag );
    moonExecCode.push_back(INDENT_11 + "lw "+localRegister+","+children[0]->moonTag+"(r0)");
    moonExecCode.push_back(INDENT_11 + "% put value on stack ");
    moonExecCode.push_back(INDENT_11 + "sw -8(r14)," + localRegister);
    moonExecCode.push_back(INDENT_11 + "% link buffer to stack");
    moonExecCode.push_back(INDENT_11 + "addi " + localRegister + ",r0, buf");
    moonExecCode.push_back(INDENT_11 + "sw -12(r14)," + localRegister );
    moonExecCode.push_back(INDENT_11 + "% convert int to string for output");
    moonExecCode.push_back(INDENT_11 + "jl r15, intstr" );
    moonExecCode.push_back(INDENT_11 + "sw -8(r14),r13");
    moonExecCode.push_back(INDENT_11 + "% ourput to console");
    moonExecCode.push_back(INDENT_11 + "jl r15, putstr");

    registerPool.push_back(localRegister);


}

void CodeGenerationVisitor::visit(ReturnStat *node) {
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }
}

void CodeGenerationVisitor::visit(GetStat *node) {
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }
}

void CodeGenerationVisitor::visit(IfStat *node) {
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }
}

void CodeGenerationVisitor::visit(ForStat *node) {
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }
}

void CodeGenerationVisitor::visit(AddOp *node) {
    std::vector<Node*> children = node->getLeftMostChild()->getSiblings();
    for (auto &a: children) {
        a->accept(this);
    }
    std::string localRegister = registerPool.back();
    registerPool.pop_back();
    std::string leftTermRegister = registerPool.back();
    registerPool.pop_back();
    std::string rightTermRegister = registerPool.back();
    registerPool.pop_back();
    //generate code
    moonExecCode.push_back(INDENT_11+ "%"+ node->moonTag + "->" + children[0]->getData() +"+" + children[1]->getData());
    moonExecCode.push_back(INDENT_11 + "lw " + leftTermRegister + "," + children[0]->moonTag+"(r0)");
    moonExecCode.push_back(INDENT_11+"lw " +rightTermRegister+ "," +children[1]->moonTag+"(r0)");
    if (node->getData() == "+") {
        moonExecCode.push_back(INDENT_11 + "add " + localRegister + "," + leftTermRegister + "," + rightTermRegister);
    }
    else {
        moonExecCode.push_back(INDENT_11 + "sub " + localRegister + "," + leftTermRegister + "," + rightTermRegister);
    }
    moonDataCode.push_back(INDENT_11 +"% allocating space for " + node->moonTag + "->" + children[0]->getData() +"+" + children[1]->getData());
    moonDataCode.push_back(node->moonTag+INDENT_10+ " res " + std::to_string(node->size));
    moonExecCode.push_back(INDENT_11+ "sw " + node->moonTag +"(r0)," + localRegister);

    registerPool.push_back(rightTermRegister);
    registerPool.push_back(leftTermRegister);
    registerPool.push_back(localRegister);



}

void CodeGenerationVisitor::visit(MultOp *node) {
    std::vector<Node*> children = node->getLeftMostChild()->getSiblings();
    for (auto &a: children) {
        a->accept(this);
    }
    std::string localRegister = registerPool.back();
    registerPool.pop_back();
    std::string leftTermRegister = registerPool.back();
    registerPool.pop_back();
    std::string rightTermRegister = registerPool.back();
    registerPool.pop_back();
    //generate code
    moonExecCode.push_back(INDENT_11+ "%"+ node->moonTag + "->" + children[0]->getData() +"*" + children[1]->getData());
    moonExecCode.push_back(INDENT_11 + "lw " + leftTermRegister + "," + children[0]->moonTag+"(r0)");
    moonExecCode.push_back(INDENT_11+"lw " +rightTermRegister+ "," +children[1]->moonTag+"(r0)");
    if (node->getData() == "*") {
        moonExecCode.push_back(INDENT_11 + "mul " + localRegister + "," + leftTermRegister + "," + rightTermRegister);
    }
    else {
        moonExecCode.push_back(INDENT_11 + "div " + localRegister + "," + leftTermRegister + "," + rightTermRegister);
    }
    moonDataCode.push_back(INDENT_11 +"% allocating space for " + node->moonTag + "->" + children[0]->getData() +"+" + children[1]->getData());
    moonDataCode.push_back(node->moonTag+INDENT_10+ " res " + std::to_string(node->size));
    moonExecCode.push_back(INDENT_11+ "sw " + node->moonTag +"(r0)," + localRegister);

    registerPool.push_back(rightTermRegister);
    registerPool.push_back(leftTermRegister);
    registerPool.push_back(localRegister);
}

void CodeGenerationVisitor::visit(NotNode *node) {
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }
}

void CodeGenerationVisitor::visit(SignNode *node) {
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }
}

void CodeGenerationVisitor::visit(DotNode *node) {
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }
}

void CodeGenerationVisitor::visit(DataMemberNode *node) {
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }
}

void CodeGenerationVisitor::visit(FCallNode *node) {
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }
}

void CodeGenerationVisitor::visit(RelOpNode *node) {
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
}

void CodeGenerationVisitor::visit(FuncDeclNode *node) {
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }
}

void CodeGenerationVisitor::visit(FPAramNode *node) {
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }
}

void CodeGenerationVisitor::visit(InherListNode *node) {
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }
}

void CodeGenerationVisitor::visit(ScopeSpec *node) {
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }
}

void CodeGenerationVisitor::visit(IndexList *node) {
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }
}

void CodeGenerationVisitor::visit(FParamList *node) {
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    if (children[0] != nullptr) {
        for (auto &a: children) {
            a->accept(this);
        }
    }
}

void CodeGenerationVisitor::visit(AParamsNode *node) {
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }
}

void CodeGenerationVisitor::visit(StatNode *node) {
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }
}

void CodeGenerationVisitor::visit(DotParamNode *node) {
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }
}

void CodeGenerationVisitor::visit(MembDeclNode *node) {
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }
}

void CodeGenerationVisitor::visit(ExprNode *node) {
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }
}

void CodeGenerationVisitor::visit(ArithExprNode *node) {
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }
}

void CodeGenerationVisitor::visit(TermNode *node) {
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }
}

void CodeGenerationVisitor::visit(StatOrVarDeclNode *node) {
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }
}

void CodeGenerationVisitor::visit(FactorNode *node) {
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }
}

void CodeGenerationVisitor::visit(TypeNode *node) {
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
}

void CodeGenerationVisitor::visit(IdNode *node) {
    std::vector<Node *> children = node->reverse(node->getLeftMostChild()->getSiblings());
}

void CodeGenerationVisitor::visit(NumNode *node) {
    if ((node->getParent()->getType() != "dimList") && (node->moonTag != "")) {
        std::vector<Node *> children = node->reverse(node->getLeftMostChild()->getSiblings());
        std::string localRegister = registerPool.back();
        registerPool.pop_back();
        moonDataCode.push_back(INDENT_11 + "%space for const" + node->getData());
        moonDataCode.push_back(node->moonTag + INDENT_10 + " res " + std::to_string(node->size));
        moonExecCode.push_back(INDENT_11 + "% processing" + node->moonTag + "->" + node->getData());
        moonExecCode.push_back(INDENT_11 + "addi " + localRegister + ",r0," + node->getData());
        moonExecCode.push_back(INDENT_11 + "sw " + node->moonTag + "(r0)," + localRegister);
        registerPool.push_back(localRegister);
    }


}

void CodeGenerationVisitor::visit(EpsilonNode *node) {
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
}

void CodeGenerationVisitor::visit(RelExprNode *node) {
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }
}

void CodeGenerationVisitor::visit(ImplNode *node) {
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }
}



