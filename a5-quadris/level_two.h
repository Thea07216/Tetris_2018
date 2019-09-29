#ifndef level_two_h
#define level_two_h
#include "level.h"
class Block;
class Cell;

class Level_two: public Level{
    const int curr_level = 2; // level 0 1 2 3 4;
public:
    Level_two(std::vector<char> command): Level{command}{};
    Block* generate(std::vector<std::vector<Cell>> * theBoard,char change_undropped) override;
};

#endif
