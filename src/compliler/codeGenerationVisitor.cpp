//
// Created by jason on 4/3/22.
//

#include "../AST/ast.h"
#include "../utils/remove_suffix.h"
#include "codeGenerationVisitor.h"
const std::string CODE_GEN_PATH = "/home/jason/collective/comp-442/comp-442/src/compliler/output/";
const std::string  MOON = ".m";
const std::string INDENT_11 = "           ";
const std::string INDENT_10 = "          ";//TODO MAKE THIS BETTER,
std::unordered_map<std::string, std::string> RELOPTRANSLATION {
        {">", "cgt"},
        {"<", "clt"},
        {"<=", "cle"},
        {"==", "ceq"},
        {"<>", "cne"},
        {">=", "cge"}
};

CodeGenerationVisitor::CodeGenerationVisitor() {}

CodeGenerationVisitor::CodeGenerationVisitor(const std::string &fileName) {
    this->fileName = CODE_GEN_PATH+stripSuffix(fileName)+MOON;
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


    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }

    moonDataCode.push_back("\n" + INDENT_11 + "%Buffer space for console output");
    moonDataCode.push_back("buf" +INDENT_11 +"res 20");

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
    if (node->getData() == "main"){
        moonExecCode.push_back(INDENT_11 +"entry");
        moonExecCode.push_back(INDENT_11 + "addi r14,r0,topaddr");
    }
    else{
        moonExecCode.push_back(INDENT_11 +"% func def for: " +node->getData());
        moonExecCode.push_back(node->getData());
        //Fix this for a type  once working
        moonDataCode.push_back(node->getData()+"link"+INDENT_10+ "res 4");
        moonExecCode.push_back(INDENT_11+"sw "+node->getData()+"link(r0),r15");

        //return statement
        moonDataCode.push_back(node->getData()+"return"+ INDENT_10+ "res 4");
    }
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }
    if(node->getData() == "main") {
        moonExecCode.push_back(INDENT_11 + "hlt");
    }
    else{
        //jump back address
        moonExecCode.push_back(INDENT_10+ "lw r15," +node->getData()+"link(r0)");
        //jump to register 15
        moonExecCode.push_back(INDENT_11 +"jr r15");

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
    moonDataCode.push_back(children[0]->getData()+ INDENT_10 +" res " +std::to_string((node->size)*arraySize));



}

void CodeGenerationVisitor::visit(DimList *node) {
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }
}

void CodeGenerationVisitor::visit(AssignStat *node) {
    int value_offSet = 0;
    int target_offSet = 0;
    int targetIndex = 0;
    int valueIndex = 0;
    std::string leftId{};
    std::string rightID{};
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }
    //get index of target id
    for (int i = 1; i<children.size(); i++){
        if (children[i]->getType() =="id"){
            targetIndex = i;
        }
    }
    std::string ValueAddressRegister = registerPool.back();
    registerPool.pop_back();
    std::string TargetAddressRegister = registerPool.back();
    registerPool.pop_back();
    std::string localRegister = registerPool.back();
    registerPool.pop_back();
    moonExecCode.push_back(INDENT_11+ "%Processing ,"+children[targetIndex]->moonTag+"<-" +children[valueIndex]->moonTag);
    moonExecCode.push_back(INDENT_11+"% Assigning array access    ");
    //calculate array offsets currently only setup for 1-d arrays
    if (children.size()> 2) {
        if (targetIndex != 1){
            value_offSet = std::stoi(children[valueIndex+1]->getData())*children[valueIndex]->size;
        }
        if(targetIndex != (children.size()-1)){
            target_offSet = std::stoi(children[targetIndex+1]->getData()) * children[targetIndex]->size;
        }
    }
    // register offsets for array access
    moonExecCode.push_back(INDENT_11 +"addi " +ValueAddressRegister+"," +"r0,"+std::to_string(value_offSet));
    moonExecCode.push_back(INDENT_11+"addi "+TargetAddressRegister+","+"r0,"+std::to_string(target_offSet));
    //moonExecCode.push_back(INDENT_11 + "lw "+ localRegister +","+children[0]->moonTag+"(r0)");
    moonExecCode.push_back(INDENT_11 + "lw "+ localRegister +","+children[valueIndex]->moonTag+"("+ValueAddressRegister+")");
    moonExecCode.push_back(INDENT_11+"sw " + children[targetIndex]->moonTag+"("+TargetAddressRegister+"),"+localRegister);
    registerPool.push_back(localRegister);
    registerPool.push_back(TargetAddressRegister);
    registerPool.push_back(ValueAddressRegister);
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

    moonExecCode.push_back(INDENT_11 + "sub r1,r1,r1");
    moonExecCode.push_back(INDENT_11 + "addi r1,r1,10");
    moonExecCode.push_back(INDENT_11 + "putc r1");
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
    //Local moon jump tags generated for branching
    std::string ifTag = "if"+ std::to_string(++branchTagCounter);
    std::string thenTag = "then"+std::to_string(++branchTagCounter);
    std::string endIfTag = "endIf"+ std::to_string(++branchTagCounter);
    std::string elseTag = "else"+std::to_string(++branchTagCounter);
    //assign relop a moontag
    std::string relOpTag = children[0]->moonTag;
    std::string localRegister = registerPool.back();
    registerPool.pop_back();
    moonExecCode.push_back(INDENT_11+"% Ifstat------------" + ifTag);
    children[1]->moonTag = thenTag;
    children[2]->moonTag = elseTag;
    for (auto &a: children) {
        //jump to else tag before the else code is generated
        if (a->moonTag == elseTag){
            moonExecCode.push_back(a->moonTag);
        }
        a->accept(this);
        //jump tag for end if, after the code has already been generated
        if(a->moonTag == thenTag){
            moonExecCode.push_back(INDENT_11 + "j "+ endIfTag);
        }
        //checks if relOp to be sure rel op value has already been generated
        else if (a->moonTag == relOpTag){
            moonExecCode.push_back(INDENT_11+"% done with rel op ");
            moonExecCode.push_back(INDENT_11+"lw "+localRegister+","+children[0]->moonTag+"(r0)");
            moonExecCode.push_back(INDENT_11+"bz "+localRegister+","+elseTag);
        }
    }
    moonExecCode.push_back(endIfTag);
    registerPool.push_back(localRegister);
}

void CodeGenerationVisitor::visit(ForStat *node) {
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    std::string goWhileTag = "goWhile"+ std::to_string(++branchTagCounter);
    std::string endWhileTag = "endWhile" +std::to_string(++branchTagCounter);
    std::string relOpTag = children[0]->moonTag; //identify rel op
    std::string loopLocalRegister = registerPool.back();
    registerPool.pop_back();
    moonExecCode.push_back(INDENT_11 + "% Starting while -------");
    moonExecCode.push_back(goWhileTag);

    for (auto &a: children) {
        a->accept(this);
        //after rel op has been visited
        if (a->moonTag == relOpTag){
            moonExecCode.push_back(INDENT_11 + "lw "+loopLocalRegister+","+a->moonTag+"(r0)");
            moonExecCode.push_back(INDENT_11 + "bz "+loopLocalRegister+","+endWhileTag);
        }
        else{
            moonExecCode.push_back(INDENT_11+"j " + goWhileTag);
        }
    }
    moonExecCode.push_back(INDENT_11+"% Exit of while loop -------");
    moonExecCode.push_back(endWhileTag);

    registerPool.push_back(loopLocalRegister);
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
    moonExecCode.push_back(INDENT_11+ "%"+ node->moonTag + "<-" + children[0]->getData() +"+" + children[1]->getData());
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
   std::string localRegister = registerPool.back();
    registerPool.pop_back();

    //Paramater passing will go here

    //jump to the called function's code
    //label is unqiue, currently al functions must have a unique name
    moonExecCode.push_back(INDENT_11+ "jl r15,"+node->getData());
//TODO get return value working!!!!
    //return value, maybe add a condition to make this optional for void return
   // moonDataCode.push_back(INDENT_11 + "%allocating space for return value");
  //  moonDataCode.push_back(node->getData() + INDENT_11 + "res 4");
    //moonExecCode.push_back(INDENT_11 + "lw " +localRegister +"," +node->getData()+"return(r0)");
    //moonExecCode.push_back(INDENT_11 + "sw " + node->getData()+"(r0),"+localRegister );

    registerPool.push_back(localRegister);



}

void CodeGenerationVisitor::visit(RelExprNode *node) {
    //TODO deal with array access after I create a process array function
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }
    std::string leftRegister = registerPool.back();
    registerPool.pop_back();
    std::string rightRegister = registerPool.back();
    registerPool.pop_back();
    std::string localRegister = registerPool.back();
    registerPool.pop_back();
    moonExecCode.push_back(INDENT_11+ "% Dealing with rel expression " + node->moonTag+ " "+ children[0]->getData() +" " +children[1]->getData()
    + " " +children[2]->getData());
    moonExecCode.push_back(INDENT_11+"lw "+leftRegister+","+children[0]->moonTag+"(r0)");
    moonExecCode.push_back(INDENT_11+"lw "+rightRegister+","+children[2]->moonTag+"(r0)");
    moonExecCode.push_back(INDENT_11+RELOPTRANSLATION.at(children[1]->getData())+" "+ localRegister+","+leftRegister+","+rightRegister);

    moonDataCode.push_back(INDENT_11+"% Allocating space for "+ node->moonTag);
    moonDataCode.push_back(node->moonTag + INDENT_10 +"res "+std::to_string(node->size));
    moonExecCode.push_back(INDENT_11+ "sw "+node->moonTag+"(r0),"+ localRegister);

    registerPool.push_back(localRegister);
    registerPool.push_back(rightRegister);
    registerPool.push_back(leftRegister);
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



void CodeGenerationVisitor::visit(ImplNode *node) {
    std::vector<Node*> children = node->reverse(node->getLeftMostChild()->getSiblings());
    for (auto &a: children) {
        a->accept(this);
    }
}



