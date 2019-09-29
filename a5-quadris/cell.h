#ifndef cell_h
#define cell_h
#include <cstddef>
#include "subject.h"
#include "info.h"
class Block;
class Cell : public Subject {
    const size_t r, c;
    char type=' ';
    bool landed = false;
    //int level = 0;
    //11.25
    Block * p=nullptr;
    //11.25
public:
    Block * getp();
    Info getInfo() const override;
    bool deleted();
    Cell(size_t r, size_t c);
    void set_type(char type);
    void set_landed();
    void clear();//clear the type to '_',and reomove the linked block
    size_t get_r();
    size_t get_c();
    char get_type();
    bool get_landed();
    void set_block(Block* p);
    void cell_copy(Cell &cell);
    void unlanded();
};
#endif


