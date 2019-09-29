#ifndef container_hpp
#define container_hpp


#include "block.h"

struct Container{
    Block hint_block;
    int deleted_row;
    int low;
    int space;
    int cospace;
    int under;
    int high;
    int lowspace;
};
#endif 

