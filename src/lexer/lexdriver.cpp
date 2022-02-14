//
// Created by jason on 1/28/22.
//
#include <iostream>
#include <fstream>
#include <vector>
#include "../../DFA/DFA.h"
#include "lexer.h"

using namespace std;
int main(){
    //LEXER SETUP
    Lexer scanner = Lexer();
    //Lexer scanner = Lexer(states, alphabet, tableau);
    string filePre ="/home/jason/collective/comp-442/comp-442/src/lexer/";
    string fileName = "a";//change this for different input file
    string fileSuf = ".txt";
    scanner.addFile(filePre+fileName+ fileSuf);
    scanner.readFile();
    bool condition = false;
    vector<Token> err {};
    vector<Token> tok {};
    while (!condition) {
            Token t = scanner.nextToken();
            if(t.getIsError()){
                err.push_back(t);
            }
            else{
                tok.push_back(t);
            }
            condition = t.isEOF();
    }
    //string outFiles[2] = {fileName+".outlexerrors", fileName+".outlextokens"};
    //ofstream outPut[2];
    //for (int i = 0; i < 2; i++){
      //  outPut[i].open(outFiles[i]);
    //}
    cout<< "Invalid Tokens" <<endl;
    for (auto &a :err){
        cout <<a << endl;
     //   outPut[0]<< a;
    }
    cout<< "Accepted tokens" <<endl;
    for (auto &a :tok){
        cout <<a << endl;
      //  outPut[1]<< a;
    }
    //outPut[0].close();
    //outPut[1].close();

    return 0;

}