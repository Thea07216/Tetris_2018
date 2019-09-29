#include "level_zero.h"

using namespace std;


Block * Level_zero :: generate(vector<vector<Cell>> *theBoard,char change_undropped){
    int block_member = 4;
    if (change_undropped == 'N'){
    vector<char> vec_command = this->get_command();
    char command = vec_command[0];
    this->change_command();
    Block * b = new Block(command,theBoard,this->curr_level,block_member);
    return b;
    } else {
    Block * b = new Block(change_undropped,theBoard,this->curr_level, block_member);
    return b;
    }
}
