//
// Created by jason on 2/24/22.
//

#ifndef COMP_442_LEXERLOGOBSERVERS_H
#define COMP_442_LEXERLOGOBSERVERS_H
#include <fstream>
#include <vector>
#include "observer.h"
#include "logSubject.h"
#include "messageBuilder.h"
class lexerLogObservers : public Observer<Logger>{
private:
    std::vector<std::shared_ptr<std::ofstream>> output;

    void update(Logger *_subject, messageBuilder message) override;
public:
    lexerLogObservers(std::vector<std::string> files);
    ~lexerLogObservers();
    //lexerLogObservers& operator =(const lexerLogObservers &toAssign);




};


#endif //COMP_442_LEXERLOGOBSERVERS_H
