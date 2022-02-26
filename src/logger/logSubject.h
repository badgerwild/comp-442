//
// Created by jason on 2/25/22.
//

#ifndef COMP_442_LOGSUBJECT_H
#define COMP_442_LOGSUBJECT_H
#include <string>
#include "subject.h"

class Logger: public subject<Logger> {

public:
    Logger();
    ~Logger();
    void log(std::string s, bool valid);
};

#endif //COMP_442_LOGSUBJECT_H
