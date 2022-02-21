//
// Created by jason on 2/13/22.
//

#ifndef COMP_442_PARSER_H
#define COMP_442_PARSER_H
#include <vector>
#include <string>
#include <unordered_set>
#include "../lexer/lexer.h"
#include "../lexer/Token.h"
const std::string PATH = "/home/jason/collective/comp-442/comp-442/src/parser/";
const std::string FOLLOW = "first_follow_v";
const std::string PARSE = "parse_table_v";
const std::string VERSION ="10.csv";
const int ERROR = -1;
const std::string SRCSUFFIX = ".txt";
const std::string OUT = ".outderivation";
const std::string ERR = ".outsyntaxerrors";
const std::string LOG ="logs/";

class Parser {
private:
    std::vector<std::vector<std::string>> parseTable;
    std::vector<std::vector<std::string>>firstFollow;
    std::unordered_set<std::string> terminals;
    Lexer lexer;
    std::vector<std::string> parseStack{};
    std::string sourceFile;
    std::string outFiles[2];
public:
    Parser(std::string src);
    ~Parser();
    std::vector<std::vector<std::string>>loadTable(std::string fileName);
    void readSource();
    bool parse();
    void skipError();
    void inverseRHSMultiPush(std::string rules);
    Token getNextToken();
    std::vector<std::string>whitespace_split(const std::string& str);
    void log();
    bool first(std::string top, std::string _lookAhead);
    bool follow(std::string top, std::string _lookAhead);


};


#endif //COMP_442_PARSER_H
