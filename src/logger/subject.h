//
// Created by jason on 2/24/22.
//

#ifndef COMP_442_SUBJECT_H
#define COMP_442_SUBJECT_H
#include <vector>
#include <string>
#include "observer.h"
template <typename T> class Observer;

template <typename T>
class subject {
private:
    std::vector<Observer<T>*> observers;
public:
    void notify(T& source, std::string& S, bool valid ) {
        for (auto o: observers) {
            o->update(&source, S, valid);
        }
    }

    void subscribe(Observer<T>& observer){
        observers.push_back(&observer);
    }

    void unsubscribe(Observer<T>& observer){
        observer.erase(
                remove(observers.begin(), observers.end(), observer), observer.end()
                );
    }



};


#endif //COMP_442_SUBJECT_H
