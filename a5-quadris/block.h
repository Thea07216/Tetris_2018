#ifndef block_h
#define block_h
#include "cell.h"
#include <vector>


class Block {
private:
    std::vector<Cell *> theBlock;
    char type; //  I O S...;
    int curr_level;
    int member; // 11.25 # of cell
    int m=0;
public:
    int score();
    Block(char type, std::vector<std::vector<Cell>>* theBoard,int curr_level, int member);
    bool lose_member();
    char block_type();
    bool out_of_bound();
    bool place_next();
    void appear_next();
    bool down(std::vector<std::vector<Cell>>* theBoard);
    bool clockwise(std::vector<std::vector<Cell>>* theBoard);
    bool countclockwise(std::vector<std::vector<Cell> > *theBoard);
    bool right(std::vector<std::vector<Cell>>* theBoard);
    bool left(std::vector<std::vector<Cell>>* theBoard);
    void drop(std::vector<std::vector<Cell>>* theBoard);
    void set();
    void hint_set();
    void disappear();
    int lowest();
    int highest();
    void unlanded();
    int lospace(std::vector<std::vector<Cell> > *theBoard);
};


#endif
