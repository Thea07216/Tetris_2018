#ifndef level_zero_h
#define level_zero_h
#include "level.h"
class Block;
class Cell;

class Level_zero: public Level{
    const int curr_level = 0; // level 0 1 2 3 4;
public:
    Level_zero(std::vector<char> command): Level{command}{};
    Block *generate(std::vector<std::vector<Cell>> * theBoard,char change_undropped) override;
};

#endif 
