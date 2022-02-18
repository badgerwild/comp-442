//
// Created by jason on 2/13/22.
//

#ifndef COMP_442_PARSER_H
#define COMP_442_PARSER_H
#include_next <vector>
#include <string>
#include "../lexer/lexer.h"
#include "../lexer/Token.h"
const std::string PATH = "/home/jason/collective/comp-442/comp-442/src/parser/";
const std::string FIRST = "First_set.csv";
const std::string FOLLOW = "Follow_set.csv";
const std::string PARSE = "parse_table_v2.csv";

class Parser {
private:
    std::vector<std::vector<std::string>> parseTable;
    std::vector<std::vector<std::string>>first;
    std::vector<std::vector<std::string>>fallow;
    Lexer lexer;
    std::vector<std::string> parseStack{};
    //stack of some kind
public:
    Parser();
    ~Parser();
    std::vector<std::vector<std::string>>loadTable(std::string fileName);
    void readSource(std::string fileName);
    void parse();
    void inverseRHSMultiPush(std::string rules);
    Token getNextToken();
    std::vector<std::string>whitespace_split(const std::string& str);


};


#endif //COMP_442_PARSER_H
