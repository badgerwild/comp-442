//
// Created by jason on 1/27/22.
//

#include "Token.h"

const std::unordered_map<int, std::string> ERROR_TYPES = {
        {50, "invalid_integer"},
        {-1, "invalid_character"},
        {51, "invalid_float"},
        {53, "invalid_id"},
        {61, "invalid_cmt"}

};
const std::unordered_map<int, std::string> TYPE_LOOKUP = {
        {4, "intlit"},
        {6, "eof"},
        {9, "id"},
        {18, "floatlit"},
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
const std::unordered_map<std::string, std::string>RESERVE_WORDS = {
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
Token::Token() {
    isError = false;
    isNull = true;
}
void Token::create(std::string lex, int type, int number) {
    if(lex == "\r") {
        lex = "eof";
        number = -1;
    }
    if (lex[lex.size()-1] == '\n'){
        lex.pop_back();
    }
    if (lex[lex.size()-1] == '\r') {
        lex.pop_back();
    }
    //check if type is id and then look if it is a reserve word
    std::string tempType{};
    if (!(TYPE_LOOKUP.find(type) == TYPE_LOOKUP.end())) {
       tempType = TYPE_LOOKUP.at(type);
    }
    else if (!(ERROR_TYPES.find(type) == ERROR_TYPES.end())){
        tempType = ERROR_TYPES.at(type);
        this->isError = true;
    }
    else{
        tempType = "Final State error at state " +type;
        this->isError = true;
    }
    if((tempType == "id") &&!(RESERVE_WORDS.find(lex) == RESERVE_WORDS.end())){
        tokenType = RESERVE_WORDS.at(lex);
    }
    else {
        tokenType = tempType;
    }
    if (tokenType == "cmt"){
        lexeme = "cmt";
    }
    else if (tokenType =="invalid_cmt") {
        lexeme = "invalid_cmt";
    }
    else {
        lexeme = lex;
    }
    lineNumber = number;
    isNull = false;
}
Token::Token(Token const&) = default;
Token::~Token() {};
std::string Token::getType() {
    return tokenType;
}

int Token::getLineNumber() {
    return lineNumber;
}
bool Token::getIsError() {
    return isError;
}

std::string Token::getLexeme() {
    return lexeme;
}

bool Token::isEmpty() {
    return isNull;
}

bool Token::isEOF() {
    bool check = (tokenType == "eof");
    return check;
}

 std::ostream &operator<<(std::ostream &out, Token &T){
    out<<'['<<T.tokenType <<", "<<T.lexeme << ", " << T.lineNumber << ']';
    return out;
}

Token& Token::operator=(const Token &toAssign) {
    lexeme = toAssign.lexeme;
    tokenType = toAssign.tokenType;
    lineNumber = toAssign.lineNumber;
    isError = toAssign.isError;
    isNull = toAssign.isNull;
    return *this;
}


