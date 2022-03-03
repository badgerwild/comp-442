//
// Created by jason on 2/24/22.
//

#ifndef COMP_442_OBSERVER_H
#define COMP_442_OBSERVER_H

#include <string>
#include "messageBuilder.h"

template <typename T>
class Observer {
public:
    virtual void update(T *_subject, messageBuilder M) = 0;
    Observer() = default;
    ~Observer() = default;

}
;


#endif //COMP_442_OBSERVER_H
