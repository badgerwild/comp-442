//
// Created by jason on 1/27/22.
//

#ifndef COMP_442_TOKEN_H
#define COMP_442_TOKEN_H
#include <string>
#include <iostream>
#include <unordered_map>

class Token {
private:
    std::string lexeme;
    std::string tokenType;
    int lineNumber;
    bool isNull;
    const std::unordered_map<int, std::string> type_lookup = {
            {4, "INT"},
            {5, "INVALID_INT"},
            {-1, "INVALID_CHARACTER"}
    };
public:
    Token();
    ~Token();
    bool isEmpty();
    void create(std::string lex, int type, int number);
    friend std::ostream &operator << (std::ostream &out, Token &T);
    void printToken();
};
#endif //COMP_442_TOKEN_H
