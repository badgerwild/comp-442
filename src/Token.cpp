//
// Created by jason on 1/27/22.
//

#include "Token.h"
Token::Token() {
    isNull = true;
}
void Token::create(std::string lex, int type, int number) {
    if(lex == "\r") {
        lex = "EOF";
        number = -1;
    }
    if (lex[lex.size()] == '\n'){
        lex.pop_back();
    }
    //check if type is id and then look if it is a reserve word
    std::string tempType = type_lookup.at(type);
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

