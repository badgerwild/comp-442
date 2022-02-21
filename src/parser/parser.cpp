//
// Created by jason on 2/13/22.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include<iterator>
#include <memory>

#include "parser.h"
#include "../../DFA/indexTemplate.h"

//using namespace Lexer;


Parser::Parser(std::string src) {
    parseTable = loadTable(PATH+PARSE+VERSION) ;
    //index 0 = non-terminal; 1 = first set; 2 = follow set
    firstFollow = loadTable(PATH + FOLLOW + VERSION);
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
    lexer.addFile(PATH+sourceFile+SRCSUFFIX);
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

bool Parser::parse(){
    //TODO make Logging class for all componets to use
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
        if (token.getType() == "cmt") {
            token = getNextToken();
        }
        if ((terminals.find(topStack)!= terminals.end()) ||(topStack == "&epsilon")) {
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
        else {
            int tokenIndex = find2dIndex<std::string>(topStack, parseTable, 'y');
            int nonTerminalIndex = find2dIndex<std::string>(token.getType(), parseTable, 'x');
            if (parseTable[tokenIndex][nonTerminalIndex] != "error") {
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
            return false;
        }
        else {
            outPut[0].close();
            outPut[1].close();
            return true;
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



