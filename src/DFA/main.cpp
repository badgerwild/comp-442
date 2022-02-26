//
// Created by jason on 1/26/22.
//
#include "DFA.h"

int main(){
    // DFA Construction
    DFA dfa = DFA();
    dfa.addState(State(1,false, false));
    dfa.addState(State(2,false, false));
    dfa.addState(State(3,false, false));
    dfa.addState(State(4, true, true));
    dfa.addState(State(5,false,true));
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

//state Vector
    std::vector<int> states = dfa.stateList();
    std::vector<char> alphabet = dfa.alphabet();
//tableLookUp
    std::vector<std::vector<int>> tableau = dfa.generateTable(states, alphabet);
    for (auto &a: tableau) {
        for (auto &b: a) {
            std::cout<< b << " ";
        }
        std::cout<<'$'<<std::endl;
    }
    return 0;
}