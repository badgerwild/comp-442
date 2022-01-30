//
// Created by jason on 1/28/22.
//
#include <iostream>
#include <fstream>
#include <vector>
#include "../DFA/DFA.h"
#include "lexer.h"

using namespace std;
int main(){
    // DFA Construction
    DFA dfa = DFA();
    dfa.addState(State(1,false, false));
    dfa.addState(State(2,false, false));
    dfa.addState(State(3,false, false));
    dfa.addState(State(4, true, true));
    dfa.addState(State(5,false,true));
    dfa.addState(State(-1, false, true));
//State 1 transition functions
    dfa.addTransition(3,1, '0');
    dfa.addTransition(2,1, '1');
    dfa.addTransition(2,1, '2');
    dfa.addTransition(2,1, '3');
    dfa.addTransition(2,1, '4');
    dfa.addTransition(2,1, '5');
    dfa.addTransition(2,1, '6');
    dfa.addTransition(2,1, '7');
    dfa.addTransition(2,1, '8');
    dfa.addTransition(2,1, '9');
    dfa.addTransition(1,1, ' ');
    // state 2 transition functions
    dfa.addTransition(2,2, '0');
    dfa.addTransition(2,2, '1');
    dfa.addTransition(2,2, '2');
    dfa.addTransition(2,2, '3');
    dfa.addTransition(2,2, '4');
    dfa.addTransition(2,2, '5');
    dfa.addTransition(2,2, '6');
    dfa.addTransition(2,2, '7');
    dfa.addTransition(2,2, '8');
    dfa.addTransition(2,2, '9');
    dfa.addTransition(4,2, ' ');
    dfa.addTransition(4,2, 'e');
    // state 3 transsion functions
    dfa.addTransition(5,3, '0');
    dfa.addTransition(5,3, '1');
    dfa.addTransition(5,3, '2');
    dfa.addTransition(5,3, '3');
    dfa.addTransition(5,3, '4');
    dfa.addTransition(5,3, '5');
    dfa.addTransition(5,3, '6');
    dfa.addTransition(5,3, '7');
    dfa.addTransition(5,3, '8');
    dfa.addTransition(5,3, '9');
    dfa.addTransition(4,3, ' ');

    dfa.addTransition(1,5, ' ');
    dfa.addTransition(1,4, ' ');

// creating state and alphabet vectors
    std::vector<int> states = dfa.stateList();
    std::vector<char> alphabet = dfa.alphabet();
// generating the look up table
    std::vector<std::vector<int>> tableau = dfa.generateTable(states, alphabet);


    //LEXER SETUP
    Lexer scanner = Lexer(states, alphabet, tableau);
    scanner.addFile("/home/jason/collective/comp-442/comp-442/src/a.txt");
    scanner.readFile();
    bool condition =scanner.getLineNumber() < scanner.getProgramSize();
    while (true) {
        int temp_1 = scanner.getLineNumber();
        int temp2 = scanner.getProgramSize();
        condition = temp_1 < temp2;
        if (condition) {
            Token t = scanner.nextToken();
            std::cout << t;
        }
        else{
            break;
        }

    }

    return 0;

    /*
    string text;
    vector<string> words;
    ifstream myFile("/home/jason/collective/comp-442/comp-442/src/a.txt");
    if (myFile.is_open()) {
        while (getline(myFile, text)){
            //cout <<text <<endl;
            words.push_back(text);
        }
    }
    else {
        cout << "file not found";
    }
    for (string &s:words) {
        for (char &c: s) {
            if (c == ' '){
                cout<< "Yay!" <<endl;
            }
            cout << c << ", ";
        }
        cout <<endl;
    }
    myFile.close();
*/
}