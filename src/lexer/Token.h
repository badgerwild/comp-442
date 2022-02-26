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
    bool isError;
    bool isNull;

public:
    Token();
    Token(Token const&);
    ~Token();
    bool getIsError();
    bool isEmpty();
    bool isEOF();
    void create(std::string lex, int type, int number);
    std::string getType();
    int getLineNumber();
    std::string getLexeme();
    friend std::ostream &operator << (std::ostream &out, Token &T);
    Token& operator = (const Token &toAssign);
    std::string toString();
};
#endif //COMP_442_TOKEN_H
