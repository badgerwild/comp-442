//
// Created by jason on 1/27/22.
//

#include "Token.h"
Token::Token() {
    isNull = true;
}
Token::~Token() {};

bool Token::isEmpty() {
    return isNull;
}
void Token::create(std::string lex, int type, int number) {
    lexeme = lex;
    tokenType = type_lookup.at(type);
    lineNumber = number;
    isNull = false;
}

 std::ostream &operator<<(std::ostream &out, Token &T){
    out<<'['<<T.tokenType <<", "<<T.lexeme << ", " << T.lineNumber << ']';
    return out;

}

