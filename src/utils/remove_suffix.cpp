//
// Created by jason on 4/10/22.
//
#include "remove_suffix.h"

std::string stripSuffix(std::string s){
    std::string::size_type position = s.find('.');
    if (position != std::string::npos){
        return s.substr(0, position);
    }
    else{
        return s;
    }
}