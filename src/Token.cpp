//
// Created by jason on 1/27/22.
//

#include "Token.h"
Token::Token() {
    isError = false;
    isNull = true;
}
void Token::create(std::string lex, int type, int number) {
    if(lex == "\r") {
        lex = "EOF";
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
    if (!(type_lookup.find(type) == type_lookup.end())) {
       tempType = type_lookup.at(type);
    }
    else if (!(error_types.find(type) == error_types.end())){
        tempType = error_types.at(type);
        this->isError = true;
    }
    else{
        tempType = "Final State error at state " +type;
        this->isError = true;
    }
    if((tempType == "id") &&!(reserve_words.find(lex) == reserve_words.end())){
        tokenType = reserve_words.at(lex);
    }
    else {
        tokenType = tempType;
    }
    lexeme = lex;
    lineNumber = number;
    isNull = false;
}
Token::~Token() {};
std::string Token::getType() {
    return tokenType;
}
bool Token::getIsError() {
    return isError;
}

bool Token::isEmpty() {
    return isNull;
}

bool Token::isEOF() {
    bool check = (tokenType == "EOF");
    return check;
}




 std::ostream &operator<<(std::ostream &out, Token &T){
    out<<'['<<T.tokenType <<", "<<T.lexeme << ", " << T.lineNumber << ']';
    return out;

}

