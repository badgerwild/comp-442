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
    //INvalid char state
    dfa.addState(State(-1, false, true));
    // EOF State
    dfa.addState(State(6, false, true));
    //id states
    dfa.addState(State(7, false, false));
    dfa.addState(State(8, false, false));
    dfa.addState(State(9,true, true));

//State 1 transition functions
//int
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
    // id
    dfa.addTransition(8, 1, 'a');
    dfa.addTransition(8, 1, 'b');
    dfa.addTransition(8, 1, 'c');
    dfa.addTransition(8, 1, 'd');
    dfa.addTransition(8, 1, 'e');
    dfa.addTransition(8, 1, 'd');
    dfa.addTransition(8, 1, 'f');
    dfa.addTransition(8, 1, 'g');
    dfa.addTransition(8, 1, 'h');
    dfa.addTransition(8, 1, 'i');
    dfa.addTransition(8, 1, 'j');
    dfa.addTransition(8, 1, 'k');
    dfa.addTransition(8, 1, 'l');
    dfa.addTransition(8, 1, 'm');
    dfa.addTransition(8, 1, 'n');
    dfa.addTransition(8, 1, 'o');
    dfa.addTransition(8, 1, 'p');
    dfa.addTransition(8, 1, 'q');
    dfa.addTransition(8, 1, 'r');
    dfa.addTransition(8, 1, 's');
    dfa.addTransition(8, 1, 't');
    dfa.addTransition(8, 1, 'u');
    dfa.addTransition(8, 1, 'v');
    dfa.addTransition(8, 1, 'w');
    dfa.addTransition(8, 1, 'x');
    dfa.addTransition(8, 1, 'y');
    dfa.addTransition(8, 1, 'z');
//invalid transitions
    dfa.addTransition(-1, 1, '_');

    //space
    dfa.addTransition(1,1, ' ');
    //return
    dfa.addTransition(6,1,'\r');
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
    dfa.addTransition(4,2,'\r');
    dfa.addTransition(4,2, '\n');
    //int + char = invlaid int state 5
    dfa.addTransition(5, 2, 'a');
    dfa.addTransition(5, 2, 'b');
    dfa.addTransition(5, 2, 'c');
    dfa.addTransition(5, 2, 'd');
    dfa.addTransition(5, 2, 'e');
    dfa.addTransition(5, 2, 'd');
    dfa.addTransition(5, 2, 'f');
    dfa.addTransition(5, 2, 'g');
    dfa.addTransition(5, 2, 'h');
    dfa.addTransition(5, 2, 'i');
    dfa.addTransition(5, 2, 'j');
    dfa.addTransition(5, 2, 'k');
    dfa.addTransition(5, 2, 'l');
    dfa.addTransition(5, 2, 'm');
    dfa.addTransition(5, 2, 'n');
    dfa.addTransition(5, 2, 'o');
    dfa.addTransition(5, 2, 'p');
    dfa.addTransition(5, 2, 'q');
    dfa.addTransition(5, 2, 'r');
    dfa.addTransition(5, 2, 's');
    dfa.addTransition(5, 2, 't');
    dfa.addTransition(5, 2, 'u');
    dfa.addTransition(5, 2, 'v');
    dfa.addTransition(5, 2, 'w');
    dfa.addTransition(5, 2, 'x');
    dfa.addTransition(5, 2, 'y');
    dfa.addTransition(5, 2, 'z');
    dfa.addTransition(5, 2, '_');

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

    dfa.addTransition(5, 3, '_');
    //dfa.addTransition(6,1,'\r');
//state 5
    dfa.addTransition(1,5, ' ');
    //state 6
    dfa.addTransition(1,4, ' ');

    //state 8
    dfa.addTransition(8, 8, 'a');
    dfa.addTransition(8, 8, 'b');
    dfa.addTransition(8, 8, 'c');
    dfa.addTransition(8, 8, 'd');
    dfa.addTransition(8, 8, 'e');
    dfa.addTransition(8, 8, 'd');
    dfa.addTransition(8, 8, 'f');
    dfa.addTransition(8, 8, 'g');
    dfa.addTransition(8, 8, 'h');
    dfa.addTransition(8, 8, 'i');
    dfa.addTransition(8, 8, 'j');
    dfa.addTransition(8, 8, 'k');
    dfa.addTransition(8, 8, 'l');
    dfa.addTransition(8, 8, 'm');
    dfa.addTransition(8, 8, 'n');
    dfa.addTransition(8, 8, 'o');
    dfa.addTransition(8, 8, 'p');
    dfa.addTransition(8, 8, 'q');
    dfa.addTransition(8, 8, 'r');
    dfa.addTransition(8, 8, 's');
    dfa.addTransition(8, 8, 't');
    dfa.addTransition(8, 8, 'u');
    dfa.addTransition(8, 8, 'v');
    dfa.addTransition(8, 8, 'w');
    dfa.addTransition(8, 8, 'x');
    dfa.addTransition(8, 8, 'y');
    dfa.addTransition(8, 8, 'z');

    dfa.addTransition(8, 8, '0');
    dfa.addTransition(8, 8, '1');
    dfa.addTransition(8, 8, '2');
    dfa.addTransition(8, 8, '3');
    dfa.addTransition(8, 8, '4');
    dfa.addTransition(8, 8, '5');
    dfa.addTransition(8, 8, '6');
    dfa.addTransition(8, 8, '7');
    dfa.addTransition(8, 8, '8');
    dfa.addTransition(8, 8, '9');
    dfa.addTransition(8, 8, '_');

    dfa.addTransition(9, 8, '\n');
// creating state and alphabet vectors
    std::vector<int> states = dfa.stateList();
    std::vector<char> alphabet = dfa.alphabet();
// generating the look up table
    std::vector<std::vector<int>> tableau = dfa.generateTable(states, alphabet);


    //LEXER SETUP
    Lexer scanner = Lexer(states, alphabet, tableau);
    scanner.addFile("/home/jason/collective/comp-442/comp-442/src/a.txt");
    scanner.readFile();
    bool condition = false;
    while (!condition) {
            Token t = scanner.nextToken();
            std::cout << t;
            condition = t.isEOF();
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