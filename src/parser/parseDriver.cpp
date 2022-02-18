//
// Created by jason on 2/13/22.
//
#include <iostream>
#include "parser.h"


int main() {
    using namespace std;



    cout <<"PARSER!!! " <<endl;
    Parser test = Parser();
    test.readSource("a.txt");
    test.parse();

    cout<< "beans" <<endl;

}