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
            {4, "integer"},
            {5, "invalid number"},
            {-1, "invalid_char"},
            {6, "EOF"},
            {9, "id"}
    };
    const std::unordered_map<std::string, std::string> reserve_words = {
            {"if", "if"},
            {"then", "then"},
            {"else", "else"},
            {"integer", "integer"},
            {"float", "float"},
            {"void", "void"},
            {"public", "public"},
            {"private", "private"},
            {"func", "func"},
            {"var", "var"},
            {"struct", "struct"},
            {"while", "while"},
            {"read", "read"},
            {"write", "write"},
            {"return", "return"},
            {"self", "self"},
            {"inherits", "inherits"},
            {"let", "let"},
            {"impl", "impl"}
    };
public:
    Token();
    ~Token();
    bool isEmpty();
    bool isEOF();
    void create(std::string lex, int type, int number);
    friend std::ostream &operator << (std::ostream &out, Token &T);
    void printToken();
};
#endif //COMP_442_TOKEN_H
