//
// Created by jason on 2/13/22.
//
#include <iostream>
#include <fstream>
#include <sstream>
// #include <boost/algorithm/string.hpp>

#include "parser.h"
const std::string PATH = "/home/jason/collective/comp-442/comp-442/src/parser/";
const std::string FIRST = "First_set.csv";
const std::string FOLLOW = "Follow_set.csv";
const std::string PARSE = "parsing_table.csv";

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
    parseStack.push_back("S");
    Token token = getNextToken();
    while(parseStack.back() != "$" ){}
}
