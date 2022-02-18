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


Parser::Parser() {
    parseTable = loadTable(PATH+PARSE) ;
    first = loadTable(PATH+FIRST);
    fallow = loadTable(PATH+FOLLOW);
    lexer = Lexer();
}

Parser::~Parser() {}

void Parser::readSource(std::string fileName){
    lexer.addFile(PATH+fileName);
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

void Parser::parse(){
    parseStack.push_back("$");
    parseStack.push_back("START");
    Token token;
    token = getNextToken();
    std::cout<<token.getType() <<" ";
    //tip != to end
    while(parseStack.back() != "$" ){
       std::string topStack = parseStack.back();

       if (topStack == token.getType()) {
           parseStack.pop_back();
           token = getNextToken();
           std::cout<< token.getType() <<" " ;
       }
       else if (topStack == "&epsilon"){
           parseStack.pop_back();
       }

       else{
           int tokenIndex = find2dIndex<std::string>(topStack, parseTable, 'y');
           int nonTerminalIndex = find2dIndex<std::string>(token.getType(), parseTable, 'x');
           if (parseTable[tokenIndex][nonTerminalIndex] != "error"){
               parseStack.pop_back();
               std::string debugTemp = parseTable[tokenIndex][nonTerminalIndex]; //DEBUG
               inverseRHSMultiPush(debugTemp);
               //Push all items in the string to the stack in reverse order
           }
           else{
               std::cout<<"error!!!!!!!" <<std::endl;
           }
       }
        if (false) {
            std::cout<<"Panik" <<std::endl;
        }
        else
            std::cout <<" " <<std::endl;
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



