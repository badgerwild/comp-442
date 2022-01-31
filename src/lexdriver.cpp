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
    //float states
    dfa.addState(State(10, false, false));
    dfa.addState(State(11, false, false));
    dfa.addState(State(12, false, false));
    dfa.addState(State(13, false, false));
    dfa.addState(State(14, false, false));
    dfa.addState(State(15, false, false));
    dfa.addState(State(16, false, false));
    dfa.addState(State(17, false, true));
    dfa.addState(State(18, true, true));
    dfa.addState(State(19, false, false));

    //single punc states
    dfa.addState(State(20, false, true));
    dfa.addState(State(22, false, true));
    dfa.addState(State(23, false, true));
    dfa.addState(State(24, false, true));
    dfa.addState(State(25, false, true));
    dfa.addState(State(26, false, true));
    dfa.addState(State(27, false, true));
    dfa.addState(State(28, false, true));
    dfa.addState(State(29, false, true));
    dfa.addState(State(30, false, true));
    dfa.addState(State(31, false, true));
    dfa.addState(State(32, false, true));
// double punk states
    dfa.addState(State(33, false, false));
    dfa.addState(State(34, true, true));
    dfa.addState(State(35, false, true));
    dfa.addState(State(36, false, false));
    dfa.addState(State(37, true, true));
    dfa.addState(State(38, false, true));
    dfa.addState(State(39, false, true));
    dfa.addState(State(40, false, false));
    dfa.addState(State(41, true, true));
    dfa.addState(State(42, false, true));
    dfa.addState(State(43, false, false));
    dfa.addState(State(44, true, true));
    dfa.addState(State(45, false, true));
    dfa.addState(State(46, false, false));
    dfa.addState(State(47, true, true));
    dfa.addState(State(48, false, true));
    dfa.addState(State(49, false, true));



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
    // to id
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
    //to float

//single punk
    dfa.addTransition(20, 1, '+');
    dfa.addTransition(22, 1, '&');
    dfa.addTransition(23, 1, '|');
    dfa.addTransition(24, 1, '!');
    dfa.addTransition(25, 1, ';');
    dfa.addTransition(26, 1, '.');
    dfa.addTransition(27, 1, '[');
    dfa.addTransition(28, 1, ']');
    dfa.addTransition(29, 1, ')');
    dfa.addTransition(30, 1, '(');
    dfa.addTransition(31, 1, '{');
    dfa.addTransition(32, 1, '}');
    dfa.addTransition(49, 1, '*');
    //double punk
    dfa.addTransition(33, 1, '>');
    dfa.addTransition(36, 1, '<');
    dfa.addTransition(40, 1, '=');
    dfa.addTransition(43, 1, ':');
    dfa.addTransition(46, 1, '-');

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
//Any
    dfa.addTransition(4,2, ' ');
    dfa.addTransition(4,2, '+');
    dfa.addTransition(4,2, '&');
    dfa.addTransition(4,2, '*');
    dfa.addTransition(4,2, ';');
    dfa.addTransition(4,2, '!');
    dfa.addTransition(4,2, '.');
    dfa.addTransition(4,2, '[');
    dfa.addTransition(4,2, ']');
    dfa.addTransition(4,2, '(');
    dfa.addTransition(4,2, ')');
    dfa.addTransition(4,2, '{');
    dfa.addTransition(4,2, '}');
    dfa.addTransition(4,2, '>');
    dfa.addTransition(4,2, '<');
    dfa.addTransition(4,2, '=');
    dfa.addTransition(4,2, ':');
    dfa.addTransition(4,2, '-');


    dfa.addTransition(9,8, ' ');
    dfa.addTransition(9,8, '+');
    dfa.addTransition(9,8, '&');
    dfa.addTransition(9,8, '*');
    dfa.addTransition(9,8, ';');
    dfa.addTransition(9,8, '!');
    dfa.addTransition(9,8, '.');
    dfa.addTransition(9,8, '[');
    dfa.addTransition(9,8, ']');
    dfa.addTransition(9,8, '(');
    dfa.addTransition(9,8, ')');
    dfa.addTransition(9,8, '{');
    dfa.addTransition(9,8, '}');
    dfa.addTransition(9,8, '>');
    dfa.addTransition(9,8, '<');
    dfa.addTransition(9,8, '=');
    dfa.addTransition(9,8, ':');
    dfa.addTransition(9,8, '-');






    //  DOT for Float
    dfa.addTransition(10, 3, '.');
    dfa.addTransition(10,2,'.');
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
    dfa.addTransition(10,3,'.');

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

    // Float
    dfa.addTransition(11, 10, '0');
    dfa.addTransition(12, 10, '1');
    dfa.addTransition(12, 10, '2');
    dfa.addTransition(12, 10, '3');
    dfa.addTransition(12, 10, '4');
    dfa.addTransition(12, 10, '5');
    dfa.addTransition(12, 10, '6');
    dfa.addTransition(12, 10, '7');
    dfa.addTransition(12, 10, '8');
    dfa.addTransition(12, 10, '9');

    dfa.addTransition(18, 11, '\n'); //TODO add more accept character
    dfa.addTransition(12, 11, '0');
    dfa.addTransition(12, 11, '1');
    dfa.addTransition(12, 11, '2');
    dfa.addTransition(12, 11, '3');
    dfa.addTransition(12, 11, '4');
    dfa.addTransition(12, 11, '5');
    dfa.addTransition(12, 11, '6');
    dfa.addTransition(12, 11, '7');
    dfa.addTransition(12, 11, '8');
    dfa.addTransition(12, 11, '9');

    // dfa.addTransition(18, 12, '\n'); //TODO add more accept character
    dfa.addTransition(19, 12, '0');
    dfa.addTransition(13, 12, '1');
    dfa.addTransition(13, 12, '2');
    dfa.addTransition(13, 12, '3');
    dfa.addTransition(13, 12, '4');
    dfa.addTransition(13, 12, '5');
    dfa.addTransition(13, 12, '6');
    dfa.addTransition(13, 12, '7');
    dfa.addTransition(13, 12, '8');
    dfa.addTransition(13, 12, '9');
    dfa.addTransition(14, 12, 'e');

    dfa.addTransition(18, 13, '\n'); //TODO add more accept character
    dfa.addTransition(12, 13, '0');// 0 back to 12
    dfa.addTransition(13, 13, '1');
    dfa.addTransition(13, 13, '2');
    dfa.addTransition(13, 13, '3');
    dfa.addTransition(13, 13, '4');
    dfa.addTransition(13, 13, '5');
    dfa.addTransition(13, 13, '6');
    dfa.addTransition(13, 13, '7');
    dfa.addTransition(13, 13, '8');
    dfa.addTransition(13, 13, '9');
    dfa.addTransition(14, 13, 'e');

    dfa.addTransition(15, 14, '+');
    dfa.addTransition(15, 14, '-');
//TODO fill in the transistions
    dfa.addTransition(17, 15, '0');//invlaid
    dfa.addTransition(16, 15, '1');
    dfa.addTransition(16, 15, '2');
    dfa.addTransition(16, 15, '3');
    dfa.addTransition(16, 15, '4');
    dfa.addTransition(16, 15, '5');
    dfa.addTransition(16, 15, '6');
    dfa.addTransition(16, 15, '7');
    dfa.addTransition(16, 15, '8');
    dfa.addTransition(16, 15, '9');

    dfa.addTransition(16, 16, '0');//invlaid
    dfa.addTransition(16, 16, '1');
    dfa.addTransition(16, 16, '2');
    dfa.addTransition(16, 16, '3');
    dfa.addTransition(16, 16, '4');
    dfa.addTransition(16, 16, '5');
    dfa.addTransition(16, 16, '6');
    dfa.addTransition(16, 16, '7');
    dfa.addTransition(16, 16, '8');
    dfa.addTransition(16, 16, '9');
    dfa.addTransition(18, 16, '\n');

    dfa.addTransition(19, 19, '0');//invlaid
    dfa.addTransition(13, 19, '1');
    dfa.addTransition(13, 19, '2');
    dfa.addTransition(13, 19, '3');
    dfa.addTransition(13, 19, '4');
    dfa.addTransition(13, 19, '5');
    dfa.addTransition(13, 19, '6');
    dfa.addTransition(13, 19, '7');
    dfa.addTransition(13, 19, '8');
    dfa.addTransition(13, 19, '9');

    //punk trans
    dfa.addTransition(34, 33, '\n');//EXPAND
    dfa.addTransition(35, 33, '=');
    dfa.addTransition(37, 36, '\n');
    dfa.addTransition(38, 36, '>');
    dfa.addTransition(39, 36, '=');
    dfa.addTransition(41, 40, '\n');
    dfa.addTransition(42, 40, '=');
    dfa.addTransition(44, 43, '\n');
    dfa.addTransition(45, 43, ':');
    dfa.addTransition(47, 46, '\n');
    dfa.addTransition(48, 46, '>');


// creating state and alphabet vectors
    std::vector<int> states = dfa.stateList();
    std::vector<char> alphabet = dfa.alphabet();
// generating the look up table
    std::vector<std::vector<int>> tableau = dfa.generateTable(states, alphabet);


    //LEXER SETUP
    Lexer scanner = Lexer(states, alphabet, tableau);
    string filePre ="/home/jason/collective/comp-442/comp-442/src/";
    string file_a = "a.txt";

    scanner.addFile(filePre+file_a);
    scanner.readFile();
    bool condition = false;
    vector<Token> err {};
    vector<Token> tok {};
    while (!condition) {
            Token t = scanner.nextToken();
            if(t.getType() == "invalid"){
                err.push_back(t);
            }
            else{
                tok.push_back(t);
            }

           // std::cout << t;
            condition = t.isEOF();
    }
    cout<<endl;

    for (auto &a :err){
        cout <<a;
    }
    cout<<endl;
    for (auto &a :tok){
        cout <<a;
    }

    return 0;

}