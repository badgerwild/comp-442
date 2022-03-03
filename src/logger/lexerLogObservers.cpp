//
// Created by jason on 2/24/22.
//
#include <iostream>
#include <memory>
#include "lexerLogObservers.h"

lexerLogObservers::lexerLogObservers(std::vector<std::string> files) {

    for (int i = 0; i<files.size();i++){
        std::shared_ptr<std::ofstream> outTemp(new std::ofstream);
        outTemp->open(files[i]);
        output.push_back(outTemp);
    }
}
lexerLogObservers::~lexerLogObservers() {
    for(auto &a: output){
        a->close();
    }
}

void lexerLogObservers::update(Logger *_subject, messageBuilder message) {
    //convert to switch case
    if (message.sourceType == 'L') {
        if (!message.isError) {
            for (std::string &s: message.messages) {
                //output[1] << s << std::endl;
                *output[1]<<s<<std::endl;

            }
        } else {
            for (std::string &s: message.messages) {
                *output[0] << s << std::endl;
            }
        }
    }
    else if (message.sourceType == 'P'){
        if (!message.isError) {
            for (std::string &s: message.messages) {
                *output[2] << s << std::endl;
            }
        } else {
            for (std::string &s: message.messages) {
                *output[3] << s << std::endl;
            }
        }
}
}


