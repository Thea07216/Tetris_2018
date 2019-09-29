#include "level_one.h"
using namespace std;

Block * Level_one::generate(vector<vector<Cell>> * theBoard,char change_undropped){
    int  block_member = 4;
    if (change_undropped == 'N'){
        int random_num = rand()%12 + 1;
        if (random_num == 1){
            Block * b = new Block('S',theBoard,this->curr_level, block_member);
            return b;
        }
        else if (random_num == 2){
            Block * b = new Block('Z',theBoard,this->curr_level, block_member);
            return b;
        }
        else if (random_num == 3 || random_num == 4){
            Block * b = new Block('I',theBoard,this->curr_level, block_member);
            return b;
        }
        else if (random_num == 5 || random_num == 6){
            Block * b = new Block('J',theBoard,this->curr_level, block_member);
            return b;
        }
        else if (random_num == 7 || random_num == 8){
            Block * b = new Block('L',theBoard,this->curr_level, block_member);
            return b;
        }
        else if (random_num == 9 || random_num == 10){
            Block * b = new Block('O',theBoard,this->curr_level, block_member);
            return b;
        }
        else {
            Block * b = new Block('T',theBoard,this->curr_level, block_member);
            return b;
        }
    } else {
        Block * b = new Block(change_undropped,theBoard,this->curr_level, block_member);
        return b;
    }
}
