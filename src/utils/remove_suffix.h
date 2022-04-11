//
// Created by jason on 4/10/22.
//
#ifndef COMP_442_REMOVESUFFIX_H
#define COMP_442_REMOVESUFFIX_H
#include <string>

std::string stripSuffix(std::string s);
/*{
    std::string::size_type position = s.find('.');
    if (position != std::string::npos){
        return s.substr(0, position);
    }
    else{
        return s;
    }
}
 */

#endif