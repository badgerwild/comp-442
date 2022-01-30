//
// Created by jason on 1/25/22.
//

#ifndef COMP_442_FINDINDEX_H
#define COMP_442_FINDINDEX_H

template <typename T>
int findIndex(T value, std::vector<T>arr) {
    int count = 0;
    for ( auto &a: arr){
        if (a == value) {
            return count;
        }
        else {
            ++count;
        }
    }
    //error code
    return -1;
}

#endif //COMP_442_FINDINDEX_H
