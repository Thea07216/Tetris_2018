#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <vector>
#include <cstddef>
#include <string>
#include "cell.h"
#include "block.h"
#include <string>
#include "level.h"
#include "level_zero.h"
#include "level_one.h"
#include "level_two.h"
#include "level_three.h"
#include "level_four.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"
#include "observer.h"
#include "container.h"
#include <memory>
#include <utility>

class Observer;

class Board {
    size_t row=18;
    size_t column=11;
    std::vector<char> l_zero_gen;
    std::vector<std::vector<Cell>> theBoard;
    std::vector<std::unique_ptr<Block>> history_block;
    std::unique_ptr<TextDisplay> td = nullptr; // The text display.
    std::unique_ptr<GraphicsDisplay> graphics = nullptr;  // Another observer (intent:  graphics)
    std::unique_ptr<Level> level = nullptr;
    int level_int = 0;
    std::unique_ptr<Block> cur_block = nullptr;
    std::unique_ptr<Block> next_block = nullptr;
    void drop_row(std::vector<Cell> &lower, std::vector<Cell> &upper);
    //for level seed
    char change_undropped = 'N';
    int seed;
    bool need_seed = false;
    std::unique_ptr<Block> phint = nullptr;
public:
    ~Board();
    void init(std::vector<char> l_zero_gen, int level_int, char change_undropped);
    void setGraphics(int cell_size, int text_size);
    void clear_board();
    void clockwise();
    void counterclockwise();
    void restart();
    void left();
    void right();
    void down();
    bool drop();
    void scan();
    void levelup();
    void leveldown();
    void random();
    void norandom(std::vector<char> block_sequence);
    void I();
    void J();
    void L();
    void Z();
    void O();
    void S();
    void T();
    void hint();
    int hint_scan_row();
    int hint_scan_space(int low);
    int hint_scan_cospace(int low);
    int hint_scan_low();
    void delete_hint();
    
    friend std::ostream &operator<<(std::ostream &out, const Board &b);
};

#endif

