#ifndef level_one_h
#define level_one_h
#include "level.h"
class Cell;
class Block;

class Level_one: public Level{
    const int curr_level = 1; // level 0 1 2 3 4;
public:
    Level_one(std::vector<char> command): Level{command}{};
    Block* generate(std::vector<std::vector<Cell>> * theBoard,char change_undropped)override;
    };
#endif
