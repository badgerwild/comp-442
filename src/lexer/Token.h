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
   const std::unordered_map<int, std::string> error_types = {
           {50, "invalid_integer"},
           {-1, "invalid_character"},
           {51, "invalid_float"},
           {53, "invalid_id"},
           {61, "invalid_cmt"}

   };
    const std::unordered_map<int, std::string> type_lookup = {
            {4, "integer"},
            {6, "EOF"},
            {9, "id"},
            {18, "float"},
            {20, "plus"},
            {21, "comma"},
            {22, "and"},
            {23, "or"},
            {24, "not"},
            {25, "semi"},
            {26, "dot"},
            {27, "lsqbr"},
            {28, "rsqbr"},
            {29, "rpar"},
            {30, "lpar"},
            {31, "lcurbr"},
            {32, "rcurbr"},
            {34, "gt"},
            {35, "geq"},
            {37, "lt"},
            {38, "neq"},
            {39, "leq"},
            {41, "equal"},
            {42, "eq"},
            {44, "colon"},
            {45, "coloncolon"},
            {47, "minus"},
            {48, "arrow"},
            {49, "mult"},
            {60,"div"},
            {57, "cmt"},
            {59, "cmt"}
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
    bool getIsError();
    bool isEmpty();
    bool isEOF();
    void create(std::string lex, int type, int number);
    std::string getType();
    friend std::ostream &operator << (std::ostream &out, Token &T);
    void printToken();
};
#endif //COMP_442_TOKEN_H
