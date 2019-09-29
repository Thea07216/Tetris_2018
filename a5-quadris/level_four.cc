#include "level_four.h"

using namespace std;

Block *Level_four::generate(vector<vector<Cell>> * theBoard,char change_undropped){
    int  block_member = 4;
    int square_one = 1;
    if ((this->times)%5 == 0 && this->times != 0){
        Block * b = new Block('*',theBoard,this->curr_level,square_one);
        this->times = 0;
        return b;
    }
    if (change_undropped == 'N' && !this->neen_read_file){
        int random_num = rand()%9 + 1;
        if (random_num == 1 || random_num == 2){
            Block * b = new Block('S',theBoard,this->curr_level, block_member);
            return b;
        }
        else if (random_num == 3 || random_num == 4){
            Block * b = new Block('Z',theBoard,this->curr_level, block_member);
            return b;
        }
        else if (random_num == 5){
            Block * b = new Block('I',theBoard,this->curr_level, block_member);
            return b;
        }
        else if (random_num == 6){
            Block * b = new Block('J',theBoard,this->curr_level, block_member);
            return b;
        }
        else if (random_num == 7){
            Block * b = new Block('L',theBoard,this->curr_level, block_member);
            return b;
        }
        else if (random_num == 8){
            Block * b = new Block('O',theBoard,this->curr_level, block_member);
            return b;
        }
        else {
            Block * b = new Block('T',theBoard,this->curr_level, block_member);
            return b;
        }
    } else if (this->neen_read_file && change_undropped == 'N'){
        //changes on Nov.26 2017
        vector<char> vec_command = this->get_command();
        char command = vec_command[0];
        this->change_command();
        Block * b = new Block(command,theBoard,this->curr_level,block_member);
        return b;
        //changes on Nov.26 2017
    } else {
        Block * b = new Block(change_undropped,theBoard,this->curr_level, block_member);
        return b;
    }
}

void Level_four :: times_zero(){
    this->times = 0;
    return;
}
void Level_four ::times_add_one(){
    this->times++;
    return;
}
