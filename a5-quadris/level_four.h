#ifndef level_four_h
#define level_four_h
#include "level.h"

class Cell;
class Block;

class Level_four: public Level{
    const int curr_level = 4; // level 0 1 2 3 4;
public:
    Level_four(std::vector<char> command): Level{command}{};
    Block* generate(std::vector<std::vector<Cell>> * theBoard,char change_undropped)override;
    void times_zero() override;
    void times_add_one() override;
};


#endif
