#ifndef level_h
#define level_h
#include <vector>
#include <cstdlib>
#include "block.h"

class Cell; // when generated, need gird to be a parameter
class Block;
class Level{
protected:
    int times = 0;
    bool neen_read_file = false;
    std::vector<char> command; //
    // my vector comes from main as
    //ifstream,change it
    // to vector <char> and give it
    // to board; when board change
    // its level check
    // whether it is level 1234 or level 0
public:
   Level(std::vector<char> command): command{command}{};
    virtual void times_zero();
    void random_noran(std::vector<char> block_sequence);
    void noran_random();
    virtual void times_add_one();
    virtual int get_times();
    std::vector<char> get_command();
    void change_command();
    virtual Block *generate(std::vector<std::vector<Cell>> * theBoard,char change_undropped) = 0; // change_undropped for change curr
                              // block, if no input to change, give me 'N'
};

#endif
