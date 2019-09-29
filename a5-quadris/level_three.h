#ifndef level_three_h
#define level_three_h
#include "level.h"
class Block;
class Cell;

class Level_three: public Level{
    const int curr_level = 3; // level 0 1 2 3 4;
public:
    Level_three(std::vector<char> command): Level{command}{};
    Block* generate(std::vector<std::vector<Cell>> * theBoard,char change_undropped) override;
};

#endif
