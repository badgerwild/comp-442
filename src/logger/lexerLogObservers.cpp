//
// Created by jason on 2/24/22.
//
#include <iostream>
#include "lexerLogObservers.h"

lexerLogObservers::lexerLogObservers(std::string *files) {
    for (int i = 0; i<2;i++){
        std::string temp = files[i];
        output[i].open(files[i]);
    }
}
lexerLogObservers::~lexerLogObservers() {
    output[0].close();
    output[1].close();
}

void lexerLogObservers::update(Logger *_subject, const std::string& s, bool valid){
    if (!valid) {
        output[1] <<s <<std::endl;
    }
    else{
        output[0] <<s << std::endl;
    }
}


