//
// Created by jason on 2/13/22.
//
#include <iostream>
//#include <fstream>
#include <sstream>
#include<iterator>
#include <memory>

#include "parser.h"
#include "../DFA/indexTemplate.h"

//using namespace Lexer;


Parser::Parser(std::string src) : lexer() {
    parseTable = loadTable(PATH+PARSE+VERSION) ;
    //index 0 = non-terminal; 1 = first set; 2 = follow set
    firstFollow = loadTable(PATH + FOLLOW);
    //load in terminals from the parse table
    parseTable[0][parseTable[0].size()-1].pop_back(); //deal with \r
    for (std::string &s: parseTable[0]){
        if ((s != "") && (s!="$") ){
            terminals.insert(s);
        }
    }
    lexer = Lexer();
    sourceFile = src;
    outFiles[0] = PATH+LOG+src+OUT;
    outFiles[1] = PATH+LOG+src+ERR;
}

Parser::~Parser() {}

void Parser::readSource() {
    lexer.addFile(SRCPATH+sourceFile+SRCSUFFIX);
    lexer.readFile();
}

std::vector<std::vector<std::string>> Parser::loadTable(std::string fileName) {
    std::vector<std::vector<std::string>> table;
    std::vector<std::string> row;
    std::string temp, word;
    std::ifstream file_pTable(fileName);
    if (file_pTable.is_open()){
        row.clear();
        while(getline(file_pTable, temp)){
            row.clear();
            std::stringstream str(temp);
            while(getline(str, word, ',')) {
                row.push_back(word);
            }
            table.push_back(row);
        }
    }
    return table;
}

Token Parser::getNextToken() {
    return lexer.nextToken();
}

Node * Parser::parse(){
   //logger open files
  std::ofstream outPut[2];
  for (int i =0; i<2;++i){
      outPut[i].open(outFiles[i]);
  }
    bool success = true;
    parseStack.push_back("$");
    parseStack.push_back("START");
    Token token;
    token = getNextToken();
    //tip != to end
    while(parseStack.back() != "$" ) {
        std::string topStack = parseStack.back();
        // by pass comments
        if (token.getType() == "cmt") {
            token = getNextToken();
            int debug = 0;
            //DEBUG
            //std::cout<<token <<std::endl;
        }
        //changed this to else if so it can handle mor ethan one comment???
        else if ((terminals.find(topStack)!= terminals.end()) ||(topStack == "&epsilon")) {
            if (topStack == token.getType()) {
                parseStack.pop_back();
                token = getNextToken();
                //logging for derivation
                for (std::string &s: parseStack ) {
                    outPut[0]<< "[ " <<s <<"] ";
                }
                outPut[0]<<"-->"<<std::endl;
            } else if (topStack == "&epsilon") {
                parseStack.pop_back();
            }
            else{
                //Error logging
                outPut[1]<< "Syntax error at line: " << token.getLineNumber()<<" Token type: "<<token.getType()<< " Token value: " <<token.getLexeme() <<std::endl;
                skipError();
                success = false;
            }
        }

        else if(SEMANTIC_ACTIONS.find(topStack) != SEMANTIC_ACTIONS.end()){
            char DebugTokenType = 'o';
            int swithChoice = SEMANTIC_ACTIONS.at(topStack);
            handleSemanticActions(swithChoice, token);
            parseStack.pop_back();
        }
        else {
            int tokenIndex = find2dIndex<std::string>(topStack, parseTable, 'y');
            int nonTerminalIndex = find2dIndex<std::string>(token.getType(), parseTable, 'x');
            if ((tokenIndex == ERROR) || (nonTerminalIndex == ERROR)) {
                //Error logging
                outPut[1]<< "Invalid Token at line: " << token.getLineNumber()<<" Token type: "<<token.getType()<< " Token value: " <<token.getLexeme() <<std::endl;
                skipError();
                token = getNextToken();
                success = false;
            }
            else if ((parseTable[tokenIndex][nonTerminalIndex] != " ")) {
                parseStack.pop_back();
                std::string debugTemp = parseTable[tokenIndex][nonTerminalIndex]; //DEBUG
                inverseRHSMultiPush(debugTemp);
                //logging for derivation
                for (std::string &s: parseStack ) {
                    outPut[0]<< "[ " <<s <<"] ";
                }
                outPut[0]<<"-->"<<std::endl;
                //Push all items in the string to the stack in reverse order
            } else {
                //Error logging
                outPut[1]<< "Syntax error at line: " << token.getLineNumber()<<" Token type: "<<token.getType()<< " Token value: " <<token.getLexeme() <<std::endl;
                skipError();
                success = false;
            }
        }
    }
        if (!success) {
            outPut[0].close();
            outPut[1].close();
            //if not parse corretly will not generate an ast and compilation will crash
            return factory.makeNode(EPSILON);
        }
        else {
            outPut[0].close();
            outPut[1].close();
            //debug print:
           // Node::traverse(semanticStack.back(), 0);
            return semanticStack.back();
        }
}

void Parser::skipError() {
    //TODO error logging here
    Token lookahead = getNextToken();
    bool ifTerm = (terminals.find(parseStack.back()) != terminals.end());
    if ((lookahead.getType() == "$") || (follow(parseStack.back(), lookahead.getType())) || ifTerm){
        parseStack.pop_back();//pop
    }
    else{
        while (((!first(parseStack.back(), lookahead.getType())) || (first(parseStack.back(),"&epsilon"))) && (!follow(parseStack.back(), lookahead.getType()))){
            lookahead = getNextToken(); //scan
        }
    }


}

void Parser::handleSemanticActions(int choice, Token token) {
    switch(choice){
        case ID:
            createLeaf(token);
            break;
        case NUM:
            createLeaf(token);
            break;
        case NOT:
            openNot(token);
            break;
        case TYPE:
            createTypeLeaf(token);
            break;
        case ADDOP:
            openAddOpTree(token);
            break;
        case CLOSEADDOP:
            closeAddOpTree();
            break;
        case ASSIGNOP:
            openAssignOp(token);
            break;
        case CLOSEASSIGNOP:
            closeAssignOp();
            break;
        case MULTOP:
            openMultOp(token);
            break;
        case CLOSEMULTOP:
            closeMultOp();
            break;
        case CLOSENOT:
            closeNot();
            break;
        case SIGN:
            openSign(token);
            break;
        case CLOSESIGN:
            closeSign();
            break;
        case EMPTY:
            createEpsilon();
            break;
        case VARDECL:
            createVarDecl(token);
            break;
        case ENDVARDECL:
            endVrDecl();
            break;
        case FUNCDEF:
            createFuncDef();
            break;
        case ENDFUNCDEF:
            endFuncDef();
            break;
        case FPARAMLIST:
            createFparamList();
            break;
        case ENDFPARAMLIST:
            endFparamList();
            break;
        case DIMLIST:
            createDimList();
            break;
        case ENDDIMLIST:
            endDimList();
            break;
        case FPARAM:
            createFparam();
            break;
        case ENDFPARAM:
            endFparam();
            break;
        case STATBLOCK:
            createStatBlock();
            break;
        case ENDSTATBLOCK:
            endStatBlock();
            break;
        case CLASSDECL:
            createClassDef();
            break;
        case ENDCLASSDECL:
            endClassDef();
            break;
        case MEMBDECL:
            //membDecl();
            generalDecl("membDecl");
            break;
        case ENDMEMBDECL:
            endGeneralDecl("membDecl");
            break;
        case FUNCDECL:
            generalDecl("funcDecl");
            break;
        case ENDFUNCDECL:
            endGeneralDecl("funcDecl");
            break;
        case PROG:
            generalDecl("prog");
            break;
        case ENDPROG:
            endGeneralDecl("prog");
            break;
        case ARITHEXPR:
            generalDecl("arithExpr");
            break;
        case ENDARITHEXPR:
            endGeneralDecl("arithExpr");
            break;
        case FACTOR:
            generalDecl("factor");
            break;
        case ENDFACTOR:
            endGeneralDecl("factor");
            break;
        case TERM:
            generalDecl("term");
            break;
        case ENDTERM:
            endGeneralDecl("term");
            break;
        case EXPR:
            generalDecl("expr");
            break;
        case ENDEXPR:
            endGeneralDecl("expr");
            break;
        case RELOP:
            createLeaf(token);
            break;
        case RELEXPR:
            generalDecl("relExpr");
            break;
        case ENDRELEXPR:
            endGeneralDecl("relExpr");
            break;
        case IF:
            generalDecl("ifStat");
            break;
        case ENDIF:
            endGeneralDecl("ifStat");
            break;
        //
        case WHILE:
            generalDecl("whileStat");
            break;
        case ENDWHILE:
            endGeneralDecl("whileStat");
            break;
        case GET:
            generalDecl("getStat");
            break;
        case ENDGET:
            endGeneralDecl("getStat");
            break;
        case PUT:
            generalDecl("putStat");
            break;
        case ENDPUT:
            endGeneralDecl("putStat");
            break;
        case RETURN:
            generalDecl("returnStat");
            break;
        case ENDRETURN:
            endGeneralDecl("returnStat");
            break;
        case SCOPE:
            generalDecl("scopeSpec");
            break;
        case ENDSCOPE:
            endGeneralDecl("scopeSpec");
            break;
        case APARAMS:
            generalDecl("aParams");
            break;
        case ENDAPARAMS:
            endGeneralDecl("aParams");
            break;
        case FCALL:
            openMakeFamily("fCall");
            break;
        case ENDFCALL:
            endGeneralDecl("fCall");
            break;
        case DOT:
            openMakeFamily("dot");
            break;
        case ENDDOT:
            endGeneralDecl("dot");
            break;
        case INHERLIST:
            generalDecl("inherList");
            break;
        case ENDINHERLIST:
            endGeneralDecl("inherList");
            break;
        case IMPL:
            generalDecl("impl");
            break;
        case ENDIMPL:
            endGeneralDecl("impl");
            break;
        default:
            std::cout<<"why are you even here"<<std::endl;
    }
}

std::vector<std::string> Parser::whitespace_split(const std::string &str) {
    std::stringstream stream(str);
    std::istream_iterator<std::string> begin(stream), end;
    return std::vector<std::string>(begin, end);
}

void Parser::inverseRHSMultiPush(std::string rules) {
    std::vector<std::string> recStack = whitespace_split(rules);
    for(int i = recStack.size()-1; i>1; --i){
        parseStack.push_back(recStack[i]);
    }
}

void Parser::log() {
 for (std::string &s: parseStack ) {
     std::cout<< "[ " <<s <<"] ";
 }
 std::cout<<"-->"<<std::endl;

    //"∅"
}

bool Parser::first(std::string top, std::string _lookAhead) {
    int index = find2dIndex<std::string>(top, firstFollow, 'y');
    if (index == ERROR){
        return false;
    }
    std::string firstSet = firstFollow[index][1];
    std::vector<std::string> toFind = whitespace_split(firstSet);
    for (std::string &s: toFind){
        if (s == _lookAhead){
            return true;
        }
    }
    return false;

}

bool Parser::follow(std::string top, std::string _lookAhead) {
    int index = find2dIndex<std::string>(top, firstFollow, 'y');
    if (index == ERROR) {
        return false;
    }

    std::string followSet = firstFollow[index][2];
    followSet.pop_back();
    std::vector<std::string> toFind = whitespace_split(followSet);
    for (std::string &s: toFind){
        if (s == _lookAhead){
            return true;
        }
    }
    return false;
}

//TODO optamize to remove redundancies
void Parser::createLeaf(Token tok) {
    std::string node_type = tok.getType();
    if (TOKEN_NODE_TRANSLATIONS.find(node_type) !=TOKEN_NODE_TRANSLATIONS.end()){
        node_type = TOKEN_NODE_TRANSLATIONS.at(node_type);
    }
    auto leaf = factory.makeNode(node_type);
    if (node_type == "num") {
        if (tok.getType() == "intlit") {
            leaf->setDataType("integer");
        }
        else if (tok.getType() == "floatlit"){
            leaf->setDataType("float");
        }
    }
    leaf->setData(tok.getLexeme());
    semanticStack.push_back(leaf);
}

void Parser::createTypeLeaf(Token tok) {
    auto leaf = factory.makeNode("type");
    leaf->setData(tok.getType());
    semanticStack.push_back(leaf);
}

void Parser::openAddOpTree(Token tok) {
    std::string node_type = tok.getType();
    if (TOKEN_NODE_TRANSLATIONS.find(node_type) !=TOKEN_NODE_TRANSLATIONS.end()){
        node_type = TOKEN_NODE_TRANSLATIONS.at(node_type);
    }
    std::vector<Node*> kids;
    kids.push_back(semanticStack.back());
    semanticStack.pop_back();
    auto opNode = InnerNode::makeFamily(node_type,kids);
    opNode->setData(tok.getLexeme());
    semanticStack.push_back(opNode);
}

void Parser::closeAddOpTree() {
    auto value = semanticStack.back();
    semanticStack.pop_back();
    auto opNode = semanticStack.back();
    semanticStack.pop_back();
    opNode->adoptChildren(value);
    semanticStack.push_back(opNode);
}

void Parser::openAssignOp(Token tok) {
    std::string node_type = tok.getType();
    if (TOKEN_NODE_TRANSLATIONS.find(node_type) !=TOKEN_NODE_TRANSLATIONS.end()){
        node_type = TOKEN_NODE_TRANSLATIONS.at(node_type);
    }
    std::vector<Node*> kids;
    while (semanticStack.back()->getType() != "id") {
        kids.push_back(semanticStack.back());
        semanticStack.pop_back();
    }
    kids.push_back(semanticStack.back());
    semanticStack.pop_back();
    auto assignStatNode = InnerNode::makeFamily(node_type,kids);
    semanticStack.push_back(assignStatNode);
}

void Parser::closeAssignOp() {
    std::vector<Node*> kids;
    while (semanticStack.back()->getType() != "assignStat"){
        kids.push_back(semanticStack.back());
        semanticStack.pop_back();
    }
    auto opNode = semanticStack.back();
    semanticStack.pop_back();
    for (auto &node: kids) {
        opNode->adoptChildren(node);
    }
    semanticStack.push_back(opNode);
}

void Parser::openMultOp(Token tok) {
    std::string node_type = tok.getType();
    if (TOKEN_NODE_TRANSLATIONS.find(node_type) !=TOKEN_NODE_TRANSLATIONS.end()){
        node_type = TOKEN_NODE_TRANSLATIONS.at(node_type);
    }
    std::vector<Node*> kids;
    kids.push_back(semanticStack.back());
    semanticStack.pop_back();
    auto multNode = InnerNode::makeFamily(node_type,kids);
    multNode->setData(tok.getLexeme());
    semanticStack.push_back(multNode);

}

void Parser::closeMultOp() {
    auto value = semanticStack.back();
    semanticStack.pop_back();
    auto opNode = semanticStack.back();
    semanticStack.pop_back();
    opNode->adoptChildren(value);
    semanticStack.push_back(opNode);

}


void Parser::openNot(Token tok) {
    auto notNode = factory.makeNode(tok.getType());
    notNode->setData(tok.getLexeme());
    semanticStack.push_back(notNode);
}

void Parser::closeNot() {
    auto value = semanticStack.back();
    semanticStack.pop_back();
    auto notNode = semanticStack.back();
    semanticStack.pop_back();
    notNode->adoptChildren(value);
    semanticStack.push_back(notNode);
}
//TODO make this work????????
void Parser::openSign(Token tok) {
    //Find better way to do this
    auto signNode = factory.makeNode("sign");
    signNode->setData(tok.getLexeme());
    semanticStack.push_back(signNode);
}
//TODO SIGN DOESN"T WORK AT ALL ??????
void Parser::closeSign(){
    auto value = semanticStack.back();
    semanticStack.pop_back();
    auto signNode = semanticStack.back();
    semanticStack.pop_back();
    signNode->adoptChildren(value);
    semanticStack.push_back(signNode);
}

void Parser::createVarDecl(Token tok) {
    std::string node_type = tok.getType();
    if (TOKEN_NODE_TRANSLATIONS.find(node_type) !=TOKEN_NODE_TRANSLATIONS.end()){
        node_type = TOKEN_NODE_TRANSLATIONS.at(node_type);
    }
    auto varDecl = factory.makeNode(node_type);
    semanticStack.push_back(varDecl);

}
void Parser::endVrDecl() {
   std::vector<Node*> temp;
    while (semanticStack.back()->getType() != "varDecl") {
        temp.push_back(semanticStack.back());
        semanticStack.pop_back();
    }
    auto varDecl = semanticStack.back();
    semanticStack.pop_back();
    for(auto &a: temp){
        varDecl->adoptChildren(a);
    }
    semanticStack.push_back(varDecl);

}
void Parser::createEpsilon() {
    auto leaf = factory.makeNode(EPSILON);
    semanticStack.push_back(leaf);
}

void Parser::createFuncDef() {
    auto funDefNode = factory.makeNode("funcDef");
    semanticStack.push_back(funDefNode);
}

void Parser::endFuncDef() {
    std::vector<Node*> tempKids;
    while (semanticStack.back()->getType() != "funcDef"){
        tempKids.push_back(semanticStack.back());
        semanticStack.pop_back();
    }
    auto funcDefNode = semanticStack.back();
    semanticStack.pop_back();
    for (auto &a: tempKids){
       funcDefNode->adoptChildren(a);
    }
    semanticStack.push_back(funcDefNode);
}

void Parser::createDimList() {
   auto dimList = factory.makeNode("dimList");
   semanticStack.push_back(dimList);
}

void Parser::endDimList() {
    std::vector<Node*> tempKids;
    while (semanticStack.back()->getType() != "dimList"){
        tempKids.push_back(semanticStack.back());
        semanticStack.pop_back();
    }
    auto dimListNode = semanticStack.back();
    semanticStack.pop_back();
    for (auto &a: tempKids){
        dimListNode->adoptChildren(a);
    }
    semanticStack.push_back(dimListNode);
}

void Parser::createFparam() {
    auto dimList = factory.makeNode("fParam");
    semanticStack.push_back(dimList);
}

void Parser::endFparam() {
    std::vector<Node*> tempKids;
    while (semanticStack.back()->getType() != "fParam"){
        tempKids.push_back(semanticStack.back());
        semanticStack.pop_back();
    }
    auto fParamNode = semanticStack.back();
    semanticStack.pop_back();
    for (auto &a: tempKids){
        fParamNode->adoptChildren(a);
    }
    semanticStack.push_back(fParamNode);
}

void Parser::createFparamList() {
    auto dimList = factory.makeNode("fParamList");
    semanticStack.push_back(dimList);
}

void Parser::endFparamList(){
    std::vector<Node*> tempKids;
    while (semanticStack.back()->getType() != "fParamList"){
        tempKids.push_back(semanticStack.back());
        semanticStack.pop_back();
    }
    auto fParamNode = semanticStack.back();
    semanticStack.pop_back();
    for (auto &a: tempKids){
        fParamNode->adoptChildren(a);
    }
    semanticStack.push_back(fParamNode);
}

void Parser::createStatBlock() {
    auto dimList = factory.makeNode("statBlock");
    semanticStack.push_back(dimList);
}

void Parser::endStatBlock(){
    std::vector<Node*> tempKids;
    while (semanticStack.back()->getType() != "statBlock"){
        tempKids.push_back(semanticStack.back());
        semanticStack.pop_back();
    }
    auto fParamNode = semanticStack.back();
    semanticStack.pop_back();
    for (auto &a: tempKids){
        fParamNode->adoptChildren(a);
    }
    semanticStack.push_back(fParamNode);
}

void Parser::createClassDef() {
    auto dimList = factory.makeNode("classDecl");
    semanticStack.push_back(dimList);


}

void Parser::endClassDef() {
    std::vector<Node*> tempKids;
    while (semanticStack.back()->getType() != "classDecl"){
        tempKids.push_back(semanticStack.back());
        semanticStack.pop_back();
    }
    auto fParamNode = semanticStack.back();
    semanticStack.pop_back();
    for (auto &a: tempKids){
        fParamNode->adoptChildren(a);
    }
    semanticStack.push_back(fParamNode);
}

void Parser::generalDecl(std::string type) {
    auto dimList = factory.makeNode(type);
    semanticStack.push_back(dimList);
}

void Parser::endGeneralDecl(std::string type) {
    std::vector<Node*> tempKids;
    while (semanticStack.back()->getType() !=  type){
        tempKids.push_back(semanticStack.back());
        semanticStack.pop_back();
    }
    auto fParamNode = semanticStack.back();
    semanticStack.pop_back();
    for (auto &a: tempKids){
        fParamNode->adoptChildren(a);
    }
    semanticStack.push_back(fParamNode);
}
//TODO continue this
void Parser::openMakeFamily(std::string type) {
    std::vector<Node *> kids;
    kids.push_back(semanticStack.back());
    semanticStack.pop_back();
    auto fCallNode = InnerNode::makeFamily(type, kids);
    fCallNode->setData(kids[0]->getData());
    semanticStack.push_back(fCallNode);
}


