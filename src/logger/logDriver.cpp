//
// Created by jason on 2/24/22.
//
#include <iostream>
#include <fstream>
#include "observer.h"
#include "subject.h"
using namespace std;

const string THESTRING = "/home/jason/collective/comp-442/comp-442/src/logger/test.txt";


class Log: public subject<Log>{
private:
    string s = "test value";
public:
    string get_s() const{
        return s;
    }

    void set_s(string tee){
       this->s = tee;
        notify(*this, tee);

    }
};

class demoLogger: public Observer<Log> {

private:
   ofstream outPut;
    void update(Log *_subject, const string& tee, bool error) override {
        outPut<< "this string has been changed to "<< tee << endl;

    }
public:
    demoLogger(){
        outPut.open(THESTRING);
    }
    ~demoLogger(){
        outPut.close();
    }
};


int main(){
    cout<<"Hello there"<<endl;
    Log testLog{};
    demoLogger demoLogger;
    testLog.subscribe(demoLogger);
    testLog.set_s("Beans");
    testLog.set_s("cat");

}
