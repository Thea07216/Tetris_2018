#include "cell.h"
#include <iostream>//debug
using namespace std;

Cell::Cell(size_t r,size_t c):r(r),c(c){};

void Cell:: set_type(char type){
    this->type = type;
    //cout<<"notifying"<<endl;//debug
    notifyObservers();
}
void Cell:: set_landed(){
    this->landed=true;
}
void Cell:: clear(){
    this->type=' ';
    this->p=nullptr;
    this->landed=false;
    notifyObservers();
}

Info Cell:: getInfo()const{
    return Info{this->r,this->c,this->type};
}



size_t Cell::get_r(){
    return r;
}
size_t Cell::get_c(){
    return c;
}
char Cell::get_type() {
    return this->type;
}
bool Cell::get_landed(){
    return this->landed;
}
void Cell::set_block(Block* p){
    this->p=p;
}

Block * Cell:: getp(){
    return this->p;
}

void Cell::unlanded(){
    this->landed=false;
}

void Cell::cell_copy(Cell &cell){
    this->type=cell.type;
    this->landed=cell.landed;
    this->p = cell.p;
    notifyObservers();
}

