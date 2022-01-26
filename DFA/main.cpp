//
// Created by jason on 1/26/22.
//
#include "DFA.h"

int main(){
    DFA dfa = DFA();
    dfa.addState(State(1,true, false));
    dfa.addState(State(2,false, true));
    dfa.addState(State(3,false, true));

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

    std::vector<int> states = dfa.stateList();
    std::vector<char> alphabet = dfa.alphabet();

    std::vector<std::vector<char>> tableau = dfa.generateTable(alphabet.size(), states.size(), states, alphabet);

    for (auto &a: tableau) {
        for (auto &b: a) {
            std::cout<< b << ", ";
        }
        std::cout<<std::endl;
    }






    return 0;
}