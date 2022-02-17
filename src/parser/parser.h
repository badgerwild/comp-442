//
// Created by jason on 2/13/22.
//

#ifndef COMP_442_PARSER_H
#define COMP_442_PARSER_H
#include_next <vector>
#include <string>
#include "../lexer/lexer.h"
#include "../lexer/Token.h"

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
    Token getNextToken();


};


#endif //COMP_442_PARSER_H
