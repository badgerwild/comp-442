//
// Created by jason on 1/25/22.
//

//Helper function for finding and returning indexes used in the parsing and lexical tables
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
template <typename T>
int find2dIndex(T value, std::vector<std::vector<T>>arr, char XY){
    int count = 0;
   if (XY == 'x') {
       std::string debug;
       int temp = arr[0].size();
      for (int i = 0; i< temp ;++i){
          debug = arr[0][i];
          if (debug == value){
              return count;
          }
          else{
              ++count;
          }
      }
   }
    else if (XY == 'y') {
       std::string debug;
       int size = arr.size();
        for (int i = 0; i< size;++i){
            debug = arr[i][0];
            if ( debug == value){
                return count;
            }
            else{
                ++count;
            }
        }
    }
    return -1;
}

#endif //COMP_442_FINDINDEX_H
