//
// Created by jason on 1/22/22.
//

#ifndef COMP_442_DFA_H
#define COMP_442_DFA_H
#include <iostream>
#include <vector>
#include <tuple>
#include <unordered_set>
class State{
private:
    int name;
    bool initial;
    bool final;
    std::vector<std::tuple<int, char>> transition; //<to, input>
public:
    State();
    State(int n, bool i, bool f);
    ~State();
    void transitionFunction(int to, char input);
    bool isFinal();
    bool isInitial();
    int getName();
    std::vector<std::tuple<int, char>> transitions();
};

class DFA{
private:
    std::vector<State> states;
    int numberOfStates;
public:
    DFA();
    ~DFA();
    void addState(State node);
    void addTransition(int to, int from, char input);
    std::vector<std::tuple<int, char>>getTransitions(int state);
    std::vector<int> stateList();
    std::vector<char> alphabet();
    std::vector<std::vector<int>> generateTable(std::vector<int> stateArray, std::vector<char> alphabetArray);
    void printTable();


};
#endif //COMP_442_DFA_H
