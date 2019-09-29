#include "block.h"
#include <iostream>
using namespace std;
class Cell;

//    std::vector<Cell *> theBlock;
//    char type; //  I O S...;
//    char level;



// don't change block constructor parameter; In level generate ,
// Thea call Block's ctor and heap allocate block, remember to delete when the block landed.
Block::Block(char type, vector<std::vector<Cell>>* theBoard,int curr_level, int member){
    this->type = type;
    this->curr_level = curr_level;
    this->member=member;
    if (type == 'I'){
        for (int i = 0; i < 4 ; i++){
            this->theBlock.push_back(&theBoard->at(3).at(i));
        }
    }
    else if (type == 'J'){
        this->theBlock.push_back(&theBoard->at(3).at(0));
        for (int i = 0 ; i < 3 ; i++){
            this->theBlock.push_back(&theBoard->at(4).at(i));
        }
    }
    else if (type == 'L'){
        this->theBlock.push_back(&theBoard->at(3).at(2));
        for (int i = 0; i < 3; i++){
            this->theBlock.push_back(&theBoard->at(4).at(i));
        }
    }
    else if (type == 'O'){
        this->theBlock.push_back(&theBoard->at(3).at(0));
        this->theBlock.push_back(&theBoard->at(3).at(1));
        this->theBlock.push_back(&theBoard->at(4).at(0));
        this->theBlock.push_back(&theBoard->at(4).at(1));
    }
    else if (type == '*'){
        this->theBlock.push_back(&theBoard->at(3).at(5));
        
    }
    else if (type == 'S'){
        this->theBlock.push_back(&theBoard->at(3).at(1));
        this->theBlock.push_back(&theBoard->at(3).at(2));
        this->theBlock.push_back(&theBoard->at(4).at(0));
        this->theBlock.push_back(&theBoard->at(4).at(1));
    }
    else if (type == 'Z'){
        this->theBlock.push_back(&theBoard->at(3).at(0));
        this->theBlock.push_back(&theBoard->at(3).at(1));
        this->theBlock.push_back(&theBoard->at(4).at(1));
        this->theBlock.push_back(&theBoard->at(4).at(2));
    }
    else if (type == 'T'){
        this->theBlock.push_back(&theBoard->at(3).at(0));
        this->theBlock.push_back(&theBoard->at(3).at(1));
        this->theBlock.push_back(&theBoard->at(3).at(2));
        this->theBlock.push_back(&theBoard->at(4).at(1));
    }
    //not need to do more set step, since we have to check before appear this in borad;
    // and move is not depend on the previous cell, depend one the infor in block;
}

char Block::block_type() {
    return this->type;
}
//bool out_of_bound();
//bool rotate(std::vector<std::vector<Cell>>* thetheBoard);

bool Block::place_next() {
    for(auto cell_p:theBlock) {
        if (cell_p->get_landed()) {
            return false;
        }
    }
    return true;
}

bool valid_rotate(std::vector<Cell*> copy) {
    for(auto cell_p:copy) {
        if (cell_p->get_landed()) {
            return false;
        }
    }
    return true;
}

void Block::appear_next() {
    for(auto cell_p:theBlock) {
        cell_p->set_type(this->type);
    }
}

bool Block::down(std::vector<std::vector<Cell>>* thetheBoard) {
    size_t vec_size = this->theBlock.size();
    for (auto &cell:theBlock) {
        size_t new_r = cell->get_r() + 1;
        size_t new_c = cell->get_c();
        try {
            if(thetheBoard->at(new_r).at(new_c).get_landed()) {
                return false;
            }
        } catch (...) {
            return false;
        }
    }
   
    for (int i = 0; i < vec_size; i++) {
        Cell *cell = this->theBlock.at(i);
        size_t new_r = cell->get_r() + 1;
        size_t new_c = cell->get_c();
        Cell *new_cell = &(thetheBoard->at(new_r).at(new_c));
        this->theBlock.at(i) = new_cell;
        
    }
    return true;
}


void Block::set(){
    for (auto &cell:theBlock){
        cell->set_type(this->type);
        //make change 11.25 move link for bonus
        cell->set_block(this);
        //make change 11.30
    }
}

bool Block::left(std::vector<std::vector<Cell>>* thetheBoard) {
    size_t vec_size = this->theBlock.size();
    for (auto &cell:theBlock) {
        size_t new_r = cell->get_r();
        size_t new_c = cell->get_c() - 1;
        try {
            if(thetheBoard->at(new_r).at(new_c).get_landed()) {//edited
                return false;
            }
        } catch (...) {
            return false;
        }
    }
    for (int i = 0; i < vec_size; i++) {
        Cell *cell = this->theBlock.at(i);
        size_t new_r = cell->get_r();
        size_t new_c = cell->get_c() - 1;
        Cell *new_cell = &(thetheBoard->at(new_r).at(new_c));
        this->theBlock.at(i) = new_cell;
    }
    if (curr_level == 3 || curr_level == 4) {//heavy
        down(thetheBoard);
    }
    return true;
}

bool Block::right(std::vector<std::vector<Cell>>* thetheBoard) {
    size_t vec_size = this->theBlock.size();
    for (auto &cell:theBlock) {
        size_t new_r = cell->get_r();
        size_t new_c = cell->get_c() + 1;
        try {
            if(thetheBoard->at(new_r).at(new_c).get_landed()) {//edited
                return false;
            }
        } catch (...) {
            return false;
        }
    }
    for (int i = 0; i < vec_size; i++) {
        Cell *cell = this->theBlock.at(i);
        size_t new_r = cell->get_r();
        size_t new_c = cell->get_c() + 1;
        Cell *new_cell = &(thetheBoard->at(new_r).at(new_c));
        this->theBlock.at(i) = new_cell;
        }
    if (curr_level == 3 || curr_level == 4) {//heavy
        down(thetheBoard);
    }
    return true;
}

void Block:: drop(std::vector<std::vector<Cell>>* thetheBoard) {
    while (down(thetheBoard)) {
        continue;
    }
    for(auto &cell:this->theBlock) {
        cell->set_landed();
    }
    
}

int Block::score(){
    int n=(this->curr_level+1)*(this->curr_level+1);
    return n;
}

bool Block::lose_member(){
    if (this->member==1){
        return true;
    }else{
        this->member--;
        return false;
    }
}


bool Block::clockwise(std::vector<std::vector<Cell> > *theBoard){
    size_t r1=theBlock.at(0)->get_r();
    size_t c1=theBlock.at(0)->get_c();
    size_t r2=theBlock.at(1)->get_r();
    size_t c2=theBlock.at(1)->get_c();
    size_t r3=theBlock.at(2)->get_r();
    size_t c3=theBlock.at(2)->get_c();
    size_t r4=theBlock.at(3)->get_r();
    size_t c4=theBlock.at(3)->get_c();
    std::vector<Cell*> copy;
    char s=this->type;
    if (s=='O'){
        return false;
    } else if (s=='I'){
        if(this->m==0){
            size_t new_c=c1;
            size_t new_r1=r1;
            size_t new_r2=r1-1;
            size_t new_r3=r1-2;
            size_t new_r4=r1-3;
            try{
                copy.push_back(&theBoard->at(new_r1).at(new_c));
                copy.push_back(&theBoard->at(new_r2).at(new_c));
                copy.push_back(&theBoard->at(new_r3).at(new_c));
                copy.push_back(&theBoard->at(new_r4).at(new_c));
            } catch(...){
                return false;
            }
            this->m=1;
        } else {
            size_t new_r=r1;
            size_t new_c1=c1;
            size_t new_c2=c1+1;
            size_t new_c3=c1+2;
            size_t new_c4=c1+3;
            try{
                copy.push_back(&theBoard->at(new_r).at(new_c1));
                copy.push_back(&theBoard->at(new_r).at(new_c2));
                copy.push_back(&theBoard->at(new_r).at(new_c3));
                copy.push_back(&theBoard->at(new_r).at(new_c4));
            } catch(...){
                return false;
            }
            this->m=0;
        }
        if(valid_rotate(copy)){
            theBlock.swap(copy);
            if (curr_level == 3 || curr_level == 4) {//heavy
                down(theBoard);
            }
            return true;
        }else {
            return false;
        }
    } else if(s=='J'){
        if(this->m==0){
            size_t new_r1=r1-1;
            size_t new_c1=c1+1;
            size_t new_r2=r2-2;
            size_t new_r3=r3-1;
            size_t new_r4=r4;
            size_t new_c=c2;
            try{
                copy.push_back(&theBoard->at(new_r1).at(new_c1));
                copy.push_back(&theBoard->at(new_r2).at(new_c));
                copy.push_back(&theBoard->at(new_r3).at(new_c));
                copy.push_back(&theBoard->at(new_r4).at(new_c));
            } catch(...){
                return false;
            }
            this->m=1;
        } else if(this->m==1){
            size_t new_r1=r1+2;
            size_t new_c1=c1+1;
            size_t new_r=r3;
            size_t new_c2=c2+2;
            size_t new_c3=c3+1;
            size_t new_c4=c4;
            try{
                copy.push_back(&theBoard->at(new_r1).at(new_c1));
                copy.push_back(&theBoard->at(new_r).at(new_c2));
                copy.push_back(&theBoard->at(new_r).at(new_c3));
                copy.push_back(&theBoard->at(new_r).at(new_c4));
            } catch(...){
                return false;
            }
            this->m=2;
        }else if(this->m==2){
            size_t new_r1=r1;
            size_t new_c1=c1-2;
            size_t new_c=c3;
            size_t new_r2=r2+1;
            size_t new_r3=r3;
            size_t new_r4=r4-1;
            try{
                copy.push_back(&theBoard->at(new_r1).at(new_c1));
                copy.push_back(&theBoard->at(new_r2).at(new_c));
                copy.push_back(&theBoard->at(new_r3).at(new_c));
                copy.push_back(&theBoard->at(new_r4).at(new_c));
            } catch(...){
                return false;
            }
            this->m=3;
        }else if(this->m==3){
            size_t new_r1=r1-1;
            size_t new_c1=c1;
            size_t new_r=r1;
            size_t new_c2=c2-1;
            size_t new_c3=c3;
            size_t new_c4=c4+1;
            try{
                copy.push_back(&theBoard->at(new_r1).at(new_c1));
                copy.push_back(&theBoard->at(new_r).at(new_c2));
                copy.push_back(&theBoard->at(new_r).at(new_c3));
                copy.push_back(&theBoard->at(new_r).at(new_c4));
            } catch(...){
                return false;
            }
            this->m=0;
        }
        if(valid_rotate(copy)){
            theBlock.swap(copy);
            if (curr_level == 3 || curr_level == 4) {//heavy
                down(theBoard);
            }
            return true;
        }else {
            return false;
        }
    }else if(s=='L'){
        if(this->m==0){
            size_t new_r1=r1+1;
            size_t new_c1=c1-1;
            size_t new_r2=r2-2;
            size_t new_r3=r3-1;
            size_t new_r4=r4;
            size_t new_c=c2;
            try{
                copy.push_back(&theBoard->at(new_r1).at(new_c1));
                copy.push_back(&theBoard->at(new_r2).at(new_c));
                copy.push_back(&theBoard->at(new_r3).at(new_c));
                copy.push_back(&theBoard->at(new_r4).at(new_c));
            } catch(...){
                return false;
            }
            this->m=1;
        } else if(this->m==1){
            size_t new_r1=r1;
            size_t new_c1=c1-1;
            size_t new_r=r3;
            size_t new_c2=c2+2;
            size_t new_c3=c3+1;
            size_t new_c4=c4;
            try{
                copy.push_back(&theBoard->at(new_r1).at(new_c1));
                copy.push_back(&theBoard->at(new_r).at(new_c2));
                copy.push_back(&theBoard->at(new_r).at(new_c3));
                copy.push_back(&theBoard->at(new_r).at(new_c4));
            } catch(...){
                return false;
            }
            this->m=2;
        }else if(this->m==2){
            size_t new_r1=r1-2;
            size_t new_c1=c1;
            size_t new_c=c3;
            size_t new_r2=r2+1;
            size_t new_r3=r3;
            size_t new_r4=r4-1;
            try{
                copy.push_back(&theBoard->at(new_r1).at(new_c1));
                copy.push_back(&theBoard->at(new_r2).at(new_c));
                copy.push_back(&theBoard->at(new_r3).at(new_c));
                copy.push_back(&theBoard->at(new_r4).at(new_c));
            } catch(...){
                return false;
            }
            this->m=3;
        }else if(this->m==3){
            size_t new_r1=r1+1;
            size_t new_c1=c1+2;
            size_t new_r=r2;
            size_t new_c2=c2-1;
            size_t new_c3=c3;
            size_t new_c4=c4+1;
            try{
                copy.push_back(&theBoard->at(new_r1).at(new_c1));
                copy.push_back(&theBoard->at(new_r).at(new_c2));
                copy.push_back(&theBoard->at(new_r).at(new_c3));
                copy.push_back(&theBoard->at(new_r).at(new_c4));
            } catch(...){
                return false;
            }
            this->m=0;
        }
        if(valid_rotate(copy)){
            theBlock.swap(copy);
            if (curr_level == 3 || curr_level == 4) {//heavy
                down(theBoard);
            }
            return true;
        }else {
            return false;
        }
    }else if(s=='S'){
        if(this->m==0){
            size_t new_r1=r1;
            size_t new_c1=c1;
            size_t new_r2=r2+1;
            size_t new_c2=c1;
            size_t new_r3=r3-2;
            size_t new_c3=c3;
            size_t new_r4=r1;
            size_t new_c4=c3;
            try{
                copy.push_back(&theBoard->at(new_r1).at(new_c1));
                copy.push_back(&theBoard->at(new_r2).at(new_c2));
                copy.push_back(&theBoard->at(new_r3).at(new_c3));
                copy.push_back(&theBoard->at(new_r4).at(new_c4));
            } catch(...){
                return false;
            }
            this->m=1;
        } else if(this->m==1){
            size_t new_r1=r2;
            size_t new_c1=c1;
            size_t new_r2=r2;
            size_t new_c2=c2-1;
            size_t new_r3=r4;
            size_t new_c3=c3+2;
            size_t new_r4=r4;
            size_t new_c4=c1;
            try{
                copy.push_back(&theBoard->at(new_r1).at(new_c1));
                copy.push_back(&theBoard->at(new_r2).at(new_c2));
                copy.push_back(&theBoard->at(new_r3).at(new_c3));
                copy.push_back(&theBoard->at(new_r4).at(new_c4));
            } catch(...){
                return false;
            }
            this->m=2;
        }else if(this->m==2){
            size_t new_r1=r4;
            size_t new_c1=c2;
            size_t new_r2=r2-2;
            size_t new_c2=c2;
            size_t new_r3=r3+1;
            size_t new_c3=c4;
            size_t new_r4=r4;
            size_t new_c4=c4;
            try{
                copy.push_back(&theBoard->at(new_r1).at(new_c1));
                copy.push_back(&theBoard->at(new_r2).at(new_c2));
                copy.push_back(&theBoard->at(new_r3).at(new_c3));
                copy.push_back(&theBoard->at(new_r4).at(new_c4));
            } catch(...){
                return false;
            }
            this->m=3;
        }else if(this->m==3){
            size_t new_r1=r1;
            size_t new_c1=c4;
            size_t new_r2=r1;
            size_t new_c2=c2+2;
            size_t new_r3=r3;
            size_t new_c3=c3-1;
            size_t new_r4=r3;
            size_t new_c4=c4;
            try{
                copy.push_back(&theBoard->at(new_r1).at(new_c1));
                copy.push_back(&theBoard->at(new_r2).at(new_c2));
                copy.push_back(&theBoard->at(new_r3).at(new_c3));
                copy.push_back(&theBoard->at(new_r4).at(new_c4));
            } catch(...){
                return false;
            }
            this->m=0;
        }
        if(valid_rotate(copy)){
            theBlock.swap(copy);
            if (curr_level == 3 || curr_level == 4) {//heavy
                down(theBoard);
            }
            return true;
        }else {
            return false;
        }
    }else if(s=='T'){
        if(this->m==0){
            size_t new_r1=r1-1;
            size_t new_c=c2;
            size_t new_r2=r2;
            size_t new_r3=r3+1;
            size_t new_r4=r4-1;
            size_t new_c4=c4-1;
            try{
                copy.push_back(&theBoard->at(new_r1).at(new_c));
                copy.push_back(&theBoard->at(new_r2).at(new_c));
                copy.push_back(&theBoard->at(new_r3).at(new_c));
                copy.push_back(&theBoard->at(new_r4).at(new_c4));
            } catch(...){
                return false;
            }
            this->m=1;
        } else if(this->m==1){
            size_t new_r=r3;
            size_t new_c1=c1+1;
            size_t new_c2=c2;
            size_t new_c3=c3-1;
            size_t new_r4=r4;
            size_t new_c4=c4+1;
            try{
                copy.push_back(&theBoard->at(new_r).at(new_c1));
                copy.push_back(&theBoard->at(new_r).at(new_c2));
                copy.push_back(&theBoard->at(new_r).at(new_c3));
                copy.push_back(&theBoard->at(new_r4).at(new_c4));
            } catch(...){
                return false;
            }
            this->m=2;
        }else if(this->m==2){
            size_t new_r1=r1;
            size_t new_c=c3;
            size_t new_r2=r2-1;
            size_t new_r3=r3-2;
            size_t new_r4=r4;
            size_t new_c4=c4;
            try{
                copy.push_back(&theBoard->at(new_r1).at(new_c));
                copy.push_back(&theBoard->at(new_r2).at(new_c));
                copy.push_back(&theBoard->at(new_r3).at(new_c));
                copy.push_back(&theBoard->at(new_r4).at(new_c4));
            } catch(...){
                return false;
            }
            this->m=3;
        }else if(this->m==3){
            size_t new_r=r2;
            size_t new_c1=c1;
            size_t new_c2=c2+1;
            size_t new_c3=c3+2;
            size_t new_r4=r4+1;
            size_t new_c4=c4;
            try{
                copy.push_back(&theBoard->at(new_r).at(new_c1));
                copy.push_back(&theBoard->at(new_r).at(new_c2));
                copy.push_back(&theBoard->at(new_r).at(new_c3));
                copy.push_back(&theBoard->at(new_r4).at(new_c4));
            } catch(...){
                return false;
            }
            this->m=0;
        }
        if(valid_rotate(copy)){
            theBlock.swap(copy);
            if (curr_level == 3 || curr_level == 4) {//heavy
                down(theBoard);
            }
            return true;
        }else {
            return false;
        }
    }else if(s=='Z'){
        if(this->m==0){
            size_t new_r1=r1-1;
            size_t new_c1=c2;
            size_t new_r2=r2;
            size_t new_c2=c2;
            size_t new_r3=r2;
            size_t new_c3=c1;
            size_t new_r4=r4;
            size_t new_c4=c1;
            try{
                copy.push_back(&theBoard->at(new_r1).at(new_c1));
                copy.push_back(&theBoard->at(new_r2).at(new_c2));
                copy.push_back(&theBoard->at(new_r3).at(new_c3));
                copy.push_back(&theBoard->at(new_r4).at(new_c4));
            } catch(...){
                return false;
            }
            this->m=1;
        } else if(this->m==1){
            size_t new_r1=r4;
            size_t new_c1=c1+1;
            size_t new_r2=r4;
            size_t new_c2=c2;
            size_t new_r3=r3;
            size_t new_c3=c2;
            size_t new_r4=r3;
            size_t new_c4=c4;
            try{
                copy.push_back(&theBoard->at(new_r1).at(new_c1));
                copy.push_back(&theBoard->at(new_r2).at(new_c2));
                copy.push_back(&theBoard->at(new_r3).at(new_c3));
                copy.push_back(&theBoard->at(new_r4).at(new_c4));
            } catch(...){
                return false;
            }
            this->m=2;
        }else if(this->m==2){
            size_t new_r1=r1;
            size_t new_c1=c4;
            size_t new_r2=r3;
            size_t new_c2=c4;
            size_t new_r3=r3;
            size_t new_c3=c3;
            size_t new_r4=r4-1;
            size_t new_c4=c3;
            try{
                copy.push_back(&theBoard->at(new_r1).at(new_c1));
                copy.push_back(&theBoard->at(new_r2).at(new_c2));
                copy.push_back(&theBoard->at(new_r3).at(new_c3));
                copy.push_back(&theBoard->at(new_r4).at(new_c4));
            } catch(...){
                return false;
            }
            this->m=3;
        }else if(this->m==3){
            size_t new_r1=r2;
            size_t new_c1=c1;
            size_t new_r2=r2;
            size_t new_c2=c3;
            size_t new_r3=r1;
            size_t new_c3=c3;
            size_t new_r4=r1;
            size_t new_c4=c4+1;
            try{
                copy.push_back(&theBoard->at(new_r1).at(new_c1));
                copy.push_back(&theBoard->at(new_r2).at(new_c2));
                copy.push_back(&theBoard->at(new_r3).at(new_c3));
                copy.push_back(&theBoard->at(new_r4).at(new_c4));
            } catch(...){
                return false;
            }
            this->m=0;
        }
        if(valid_rotate(copy)){
            theBlock.swap(copy);
            if (curr_level == 3 || curr_level == 4) {//heavy
                down(theBoard);
            }
            return true;
        }else {
            return false;
        }
    }
    return false;
}




bool Block::countclockwise(std::vector<std::vector<Cell> > *theBoard){
    size_t r1=theBlock.at(0)->get_r();
    size_t c1=theBlock.at(0)->get_c();
    size_t r2=theBlock.at(1)->get_r();
    size_t c2=theBlock.at(1)->get_c();
    size_t r3=theBlock.at(2)->get_r();
    size_t c3=theBlock.at(2)->get_c();
    size_t r4=theBlock.at(3)->get_r();
    size_t c4=theBlock.at(3)->get_c();
    std::vector<Cell*> copy;
    char s=this->type;
    if (s=='O'){
        return false;
    } else if (s=='I'){
        if(this->m==0){
            size_t new_c=c1;
            size_t new_r1=r1;
            size_t new_r2=r1-1;
            size_t new_r3=r1-2;
            size_t new_r4=r1-3;
            try{
                copy.push_back(&theBoard->at(new_r1).at(new_c));
                copy.push_back(&theBoard->at(new_r2).at(new_c));
                copy.push_back(&theBoard->at(new_r3).at(new_c));
                copy.push_back(&theBoard->at(new_r4).at(new_c));
            } catch(...){
                return false;
            }
            this->m=1;
        } else {
            size_t new_r=r1;
            size_t new_c1=c1;
            size_t new_c2=c1+1;
            size_t new_c3=c1+2;
            size_t new_c4=c1+3;
            try{
                copy.push_back(&theBoard->at(new_r).at(new_c1));
                copy.push_back(&theBoard->at(new_r).at(new_c2));
                copy.push_back(&theBoard->at(new_r).at(new_c3));
                copy.push_back(&theBoard->at(new_r).at(new_c4));
            } catch(...){
                return false;
            }
            this->m=0;
        }
        if(valid_rotate(copy)){
            theBlock.swap(copy);
            if (curr_level == 3 || curr_level == 4) {//heavy
                down(theBoard);
            }
            return true;
        }else {
            return false;
        }
    } else if(s=='J'){
        if(this->m==0){
            size_t new_r1=r1+1;
            size_t new_c1=c1;
            size_t new_r2=r2;
            size_t new_r3=r3-1;
            size_t new_r4=r4-2;
            size_t new_c=c3;
            try{
                copy.push_back(&theBoard->at(new_r1).at(new_c1));
                copy.push_back(&theBoard->at(new_r2).at(new_c));
                copy.push_back(&theBoard->at(new_r3).at(new_c));
                copy.push_back(&theBoard->at(new_r4).at(new_c));
            } catch(...){
                return false;
            }
            this->m=3;
        } else if(this->m==1){
            size_t new_r1=r1+1;
            size_t new_c1=c1-1;
            size_t new_r=r4;
            size_t new_c2=c2;
            size_t new_c3=c3+1;
            size_t new_c4=c4+2;
            try{
                copy.push_back(&theBoard->at(new_r1).at(new_c1));
                copy.push_back(&theBoard->at(new_r).at(new_c2));
                copy.push_back(&theBoard->at(new_r).at(new_c3));
                copy.push_back(&theBoard->at(new_r).at(new_c4));
            } catch(...){
                return false;
            }
            this->m=0;
        }else if(this->m==2){
            size_t new_r1=r1-2;
            size_t new_c1=c1-1;
            size_t new_c=c4;
            size_t new_r2=r2-1;
            size_t new_r3=r3;
            size_t new_r4=r4+1;
            try{
                copy.push_back(&theBoard->at(new_r1).at(new_c1));
                copy.push_back(&theBoard->at(new_r2).at(new_c));
                copy.push_back(&theBoard->at(new_r3).at(new_c));
                copy.push_back(&theBoard->at(new_r4).at(new_c));
            } catch(...){
                return false;
            }
            this->m=1;
        }else if(this->m==3){
            size_t new_r1=r1;
            size_t new_c1=c1+2;
            size_t new_r=r3;
            size_t new_c2=c2+1;
            size_t new_c3=c3;
            size_t new_c4=c4-1;
            try{
                copy.push_back(&theBoard->at(new_r1).at(new_c1));
                copy.push_back(&theBoard->at(new_r).at(new_c2));
                copy.push_back(&theBoard->at(new_r).at(new_c3));
                copy.push_back(&theBoard->at(new_r).at(new_c4));
            } catch(...){
                return false;
            }
            this->m=2;
        }
        if(valid_rotate(copy)){
            theBlock.swap(copy);
            if (curr_level == 3 || curr_level == 4) {//heavy
                down(theBoard);
            }
            return true;
        }else {
            return false;
        }
    }else if(s=='L'){
        if(this->m==0){
            size_t new_r1=r1-1;
            size_t new_c1=c1-2;
            size_t new_r2=r2;
            size_t new_r3=r3-1;
            size_t new_r4=r4-2;
            size_t new_c=c3;
            try{
                copy.push_back(&theBoard->at(new_r1).at(new_c1));
                copy.push_back(&theBoard->at(new_r2).at(new_c));
                copy.push_back(&theBoard->at(new_r3).at(new_c));
                copy.push_back(&theBoard->at(new_r4).at(new_c));
            } catch(...){
                return false;
            }
            this->m=3;
        } else if(this->m==3){
            size_t new_r1=r1+2;
            size_t new_c1=c1;
            size_t new_r=r3;
            size_t new_c2=c2+1;
            size_t new_c3=c3;
            size_t new_c4=c4-1;
            try{
                copy.push_back(&theBoard->at(new_r1).at(new_c1));
                copy.push_back(&theBoard->at(new_r).at(new_c2));
                copy.push_back(&theBoard->at(new_r).at(new_c3));
                copy.push_back(&theBoard->at(new_r).at(new_c4));
            } catch(...){
                return false;
            }
            this->m=2;
        }else if(this->m==2){
            size_t new_r1=r1;
            size_t new_c1=c1+1;
            size_t new_c=c4;
            size_t new_r2=r2-1;
            size_t new_r3=r3;
            size_t new_r4=r4+1;
            try{
                copy.push_back(&theBoard->at(new_r1).at(new_c1));
                copy.push_back(&theBoard->at(new_r2).at(new_c));
                copy.push_back(&theBoard->at(new_r3).at(new_c));
                copy.push_back(&theBoard->at(new_r4).at(new_c));
            } catch(...){
                return false;
            }
            this->m=1;
        }else if(this->m==1){
            size_t new_r1=r1-1;
            size_t new_c1=c1+1;
            size_t new_r=r4;
            size_t new_c2=c2;
            size_t new_c3=c3+1;
            size_t new_c4=c4+2;
            try{
                copy.push_back(&theBoard->at(new_r1).at(new_c1));
                copy.push_back(&theBoard->at(new_r).at(new_c2));
                copy.push_back(&theBoard->at(new_r).at(new_c3));
                copy.push_back(&theBoard->at(new_r).at(new_c4));
            } catch(...){
                return false;
            }
            this->m=0;
        }
        if(valid_rotate(copy)){
            theBlock.swap(copy);
            if (curr_level == 3 || curr_level == 4) {//heavy
                down(theBoard);
            }
            return true;
        }else {
            return false;
        }
    }else if(s=='S'){
        if(this->m==0){
            size_t new_r1=r1;
            size_t new_c1=c1;
            size_t new_r2=r2+1;
            size_t new_c2=c1;
            size_t new_r3=r3-2;
            size_t new_c3=c3;
            size_t new_r4=r1;
            size_t new_c4=c3;
            try{
                copy.push_back(&theBoard->at(new_r1).at(new_c1));
                copy.push_back(&theBoard->at(new_r2).at(new_c2));
                copy.push_back(&theBoard->at(new_r3).at(new_c3));
                copy.push_back(&theBoard->at(new_r4).at(new_c4));
            } catch(...){
                return false;
            }
            this->m=1;
        } else if(this->m==1){
            size_t new_r1=r2;
            size_t new_c1=c1;
            size_t new_r2=r2;
            size_t new_c2=c2-1;
            size_t new_r3=r4;
            size_t new_c3=c3+2;
            size_t new_r4=r4;
            size_t new_c4=c1;
            try{
                copy.push_back(&theBoard->at(new_r1).at(new_c1));
                copy.push_back(&theBoard->at(new_r2).at(new_c2));
                copy.push_back(&theBoard->at(new_r3).at(new_c3));
                copy.push_back(&theBoard->at(new_r4).at(new_c4));
            } catch(...){
                return false;
            }
            this->m=2;
        }else if(this->m==2){
            size_t new_r1=r4;
            size_t new_c1=c2;
            size_t new_r2=r2-2;
            size_t new_c2=c2;
            size_t new_r3=r3+1;
            size_t new_c3=c4;
            size_t new_r4=r4;
            size_t new_c4=c4;
            try{
                copy.push_back(&theBoard->at(new_r1).at(new_c1));
                copy.push_back(&theBoard->at(new_r2).at(new_c2));
                copy.push_back(&theBoard->at(new_r3).at(new_c3));
                copy.push_back(&theBoard->at(new_r4).at(new_c4));
            } catch(...){
                return false;
            }
            this->m=3;
        }else if(this->m==3){
            size_t new_r1=r1;
            size_t new_c1=c4;
            size_t new_r2=r1;
            size_t new_c2=c2+2;
            size_t new_r3=r3;
            size_t new_c3=c3-1;
            size_t new_r4=r3;
            size_t new_c4=c4;
            try{
                copy.push_back(&theBoard->at(new_r1).at(new_c1));
                copy.push_back(&theBoard->at(new_r2).at(new_c2));
                copy.push_back(&theBoard->at(new_r3).at(new_c3));
                copy.push_back(&theBoard->at(new_r4).at(new_c4));
            } catch(...){
                return false;
            }
            this->m=0;
        }
        if(valid_rotate(copy)){
            theBlock.swap(copy);
            if (curr_level == 3 || curr_level == 4) {//heavy
                down(theBoard);
            }
            return true;
        }else {
            return false;
        }
    }else if(s=='T'){
        if(this->m==0){
            size_t new_r1=r1+1;
            size_t new_c=c1;
            size_t new_r2=r2;
            size_t new_r3=r3-1;
            size_t new_r4=r4-1;
            size_t new_c4=c4;
            try{
                copy.push_back(&theBoard->at(new_r1).at(new_c));
                copy.push_back(&theBoard->at(new_r2).at(new_c));
                copy.push_back(&theBoard->at(new_r3).at(new_c));
                copy.push_back(&theBoard->at(new_r4).at(new_c4));
            } catch(...){
                return false;
            }
            this->m=3;
        } else if(this->m==3){
            size_t new_r=r1;
            size_t new_c1=c1+2;
            size_t new_c2=c2+1;
            size_t new_c3=c3;
            size_t new_r4=r4;
            size_t new_c4=c4;
            try{
                copy.push_back(&theBoard->at(new_r).at(new_c1));
                copy.push_back(&theBoard->at(new_r).at(new_c2));
                copy.push_back(&theBoard->at(new_r).at(new_c3));
                copy.push_back(&theBoard->at(new_r4).at(new_c4));
            } catch(...){
                return false;
            }
            this->m=2;
        }else if(this->m==2){
            size_t new_r1=r1-2;
            size_t new_c=c2;
            size_t new_r2=r2-1;
            size_t new_r3=r3;
            size_t new_r4=r4;
            size_t new_c4=c4-1;
            try{
                copy.push_back(&theBoard->at(new_r1).at(new_c));
                copy.push_back(&theBoard->at(new_r2).at(new_c));
                copy.push_back(&theBoard->at(new_r3).at(new_c));
                copy.push_back(&theBoard->at(new_r4).at(new_c4));
            } catch(...){
                return false;
            }
            this->m=1;
        }else if(this->m==1){
            size_t new_r=r2;
            size_t new_c1=c1-1;
            size_t new_c2=c2;
            size_t new_c3=c3+1;
            size_t new_r4=r4+1;
            size_t new_c4=c4+1;
            try{
                copy.push_back(&theBoard->at(new_r).at(new_c1));
                copy.push_back(&theBoard->at(new_r).at(new_c2));
                copy.push_back(&theBoard->at(new_r).at(new_c3));
                copy.push_back(&theBoard->at(new_r4).at(new_c4));
            } catch(...){
                return false;
            }
            this->m=0;
        }
        if(valid_rotate(copy)){
            theBlock.swap(copy);
            if (curr_level == 3 || curr_level == 4) {//heavy
                down(theBoard);
            }
            
            return true;
        }else {
            return false;
        }
    }else if(s=='Z'){
        if(this->m==0){
            size_t new_r1=r1-1;
            size_t new_c1=c2;
            size_t new_r2=r2;
            size_t new_c2=c2;
            size_t new_r3=r2;
            size_t new_c3=c1;
            size_t new_r4=r4;
            size_t new_c4=c1;
            try{
                copy.push_back(&theBoard->at(new_r1).at(new_c1));
                copy.push_back(&theBoard->at(new_r2).at(new_c2));
                copy.push_back(&theBoard->at(new_r3).at(new_c3));
                copy.push_back(&theBoard->at(new_r4).at(new_c4));
            } catch(...){
                return false;
            }
            this->m=1;
        } else if(this->m==1){
            size_t new_r1=r4;
            size_t new_c1=c1+1;
            size_t new_r2=r4;
            size_t new_c2=c2;
            size_t new_r3=r3;
            size_t new_c3=c2;
            size_t new_r4=r3;
            size_t new_c4=c4;
            try{
                copy.push_back(&theBoard->at(new_r1).at(new_c1));
                copy.push_back(&theBoard->at(new_r2).at(new_c2));
                copy.push_back(&theBoard->at(new_r3).at(new_c3));
                copy.push_back(&theBoard->at(new_r4).at(new_c4));
            } catch(...){
                return false;
            }
            this->m=2;
        }else if(this->m==2){
            size_t new_r1=r1;
            size_t new_c1=c4;
            size_t new_r2=r3;
            size_t new_c2=c4;
            size_t new_r3=r3;
            size_t new_c3=c3;
            size_t new_r4=r4-1;
            size_t new_c4=c3;
            try{
                copy.push_back(&theBoard->at(new_r1).at(new_c1));
                copy.push_back(&theBoard->at(new_r2).at(new_c2));
                copy.push_back(&theBoard->at(new_r3).at(new_c3));
                copy.push_back(&theBoard->at(new_r4).at(new_c4));
            } catch(...){
                return false;
            }
            this->m=3;
        }else if(this->m==3){
            size_t new_r1=r2;
            size_t new_c1=c1;
            size_t new_r2=r2;
            size_t new_c2=c3;
            size_t new_r3=r1;
            size_t new_c3=c3;
            size_t new_r4=r1;
            size_t new_c4=c4+1;
            try{
                copy.push_back(&theBoard->at(new_r1).at(new_c1));
                copy.push_back(&theBoard->at(new_r2).at(new_c2));
                copy.push_back(&theBoard->at(new_r3).at(new_c3));
                copy.push_back(&theBoard->at(new_r4).at(new_c4));
            } catch(...){
                return false;
            }
            this->m=0;
        }
        if(valid_rotate(copy)){
            theBlock.swap(copy);
            if (curr_level == 3 || curr_level == 4) {//heavy
                down(theBoard);
            }
            return true;
        }else {
            return false;
        }
    }
    return false;
}
void Block::disappear() {
    for(auto cell:theBlock) {
        cell->clear();
    }
}

int Block::lowest(){
    size_t max=0;
    for(auto cell:theBlock) {
        size_t now=cell->get_r();
        if(now>max){
            max=now;
        }
    }
    return max;
}



int Block::lospace(std::vector<std::vector<Cell> > *theBoard){
    int acc=0;
    for (auto &cell:theBlock) {
        size_t new_r = cell->get_r() + 1;
        size_t new_c = cell->get_c();
        if((new_r<(*theBoard).size())&&(!theBoard->at(new_r).at(new_c).get_landed())){
            acc++;
        }
    }
    return acc;
}

void Block::unlanded(){
    for(auto cell:theBlock) {
        cell->unlanded();
    }
}

int Block::highest(){
    size_t min=19;
    for(auto cell:theBlock) {
        size_t now=cell->get_r();
        if(now<min){
            min=now;
        }
    }
    return min;
}

void Block::hint_set(){
    for(auto cell:theBlock) {
        cell->set_type('?');
    }
}


