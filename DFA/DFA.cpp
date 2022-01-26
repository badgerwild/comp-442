//
// Created by jason on 1/22/22.
//

#include "DFA.h"
#include "indexTemplate.h"
//class def State
State::State() = default;
State::State(int n, bool i, bool f):name{n}, initial{i}, final{f} {};
State::~State() {}
void State::transitionFunction(int to, char input) {
    transition.push_back(std::make_tuple(to, input));
}
bool State::isFinal(){
    return this->final;
}
bool State::isInitial(){
    return this->initial;
}

int State::getName(){
  return name;
}
std::vector<std::tuple<int, char>> State::transitions() {
    return this->transition;
}

DFA::DFA() {
    numberOfStates = 0;
};
DFA::~DFA(){}
void DFA::addState(State node) {
    states.push_back(node);
    ++numberOfStates;
}
void DFA::addTransition(int to, int from, char input) {
    for (auto &a: states){
        if(a.getName() == from) {
            a.transitionFunction(to, input);
        }
    }
}
std::vector<std::tuple<int, char>> DFA::getTransitions(int state) {
    std::vector<std::tuple<int, char>> temp{};
    for(State &s: states) {
        if(s.getName() == state) {
            temp = s.transitions();
        }
    }
    return temp;
}

std::vector<int> DFA::stateList() {
    std::vector<int> allStates{};
    int temp{0};
    for(State &s: states) {
       allStates.push_back(s.getName());
    }
    return allStates;
}

std::vector<char> DFA::alphabet() {
    std::unordered_set<char> alphTemp{};
    int temp{0};
    for(State &s: states) {
        for(auto &a: s.transitions())
            if(alphTemp.find(std::get<1>(a)) == alphTemp.end()){
                alphTemp.insert(std::get<1>(a));
            }
    }
    std::vector<char> alph{};
    for(auto &a: alphTemp) {
        alph.push_back(a);
    }
    return alph;
}
/* TODO reverse order of rows and columns because that part is wrong currently
 * TODO debug why array is not being filled correctly and why characters are not being placed correctly,
 * TODO could be a type error I think of trying to put ints into a char vector
 */

std::vector<std::vector<char>> DFA::generateTable(int aSize, int nState, std::vector<int> stateArray, std::vector<char> alphabetArray) {
    //char table[aSize][nState];
    std::vector<std::vector<char>> table(aSize, std::vector<char> (nState));
    char inputChar{};
    int destination{}, charIndex{}, stateIndex{};

    //initialize all values in the table to empty char
    for (auto& outer: table){
        for (auto &inner: outer){
            inner = char(0);
        }
    }
    for (State &s: states){
        stateIndex = findIndex<int>(s.getName(), stateArray);
        for (auto &a: s.transitions()){
           inputChar = std::get<1>(a);
           destination = std::get<0>(a);
           charIndex = findIndex<char>(inputChar, alphabetArray);
           table[stateIndex][charIndex] = destination;
        }
    }
    return table;
}






