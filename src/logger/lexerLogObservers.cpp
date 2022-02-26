//
// Created by jason on 2/24/22.
//

#include "lexerLogObservers.h"

lexerLogObservers::lexerLogObservers(std::string *files) {
    for (int i = 0; i<2;++i){
        std::string temp = files[i];
        output[i].open(files[i]);
    }
}
lexerLogObservers::~lexerLogObservers() {
    for (int i = 0; i<2;++i){
        output[i].close();
    }
}
/*
lexerLogObservers& lexerLogObservers::operator=(const lexerLogObservers &toAssign) {
    for (int i = 0; i<2;++i){
        output[i] = toAssign.output[i];
    }
}
*/
void lexerLogObservers::update(Logger *_subject, const std::string& s, bool valid){
    if (valid) {
        output[1] <<s <<std::endl;
    }
    else{
        output[0] <<s << std::endl;
    }
}


