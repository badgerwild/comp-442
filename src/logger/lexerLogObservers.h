//
// Created by jason on 2/24/22.
//

#ifndef COMP_442_LEXERLOGOBSERVERS_H
#define COMP_442_LEXERLOGOBSERVERS_H
#include <fstream>
#include <vector>
#include "observer.h"
#include "logSubject.h"


class lexerLogObservers : public Observer<Logger>{
private:
    std::ofstream output[2];
    void update(Logger* _subject, const std::string& s, bool valid) override;
public:
    lexerLogObservers(std::string files[]);
    ~lexerLogObservers();
    //lexerLogObservers& operator =(const lexerLogObservers &toAssign);




};


#endif //COMP_442_LEXERLOGOBSERVERS_H
