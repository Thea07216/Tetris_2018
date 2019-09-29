

#ifndef command_hpp
#define command_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include "board.h"

class Command {
    Board * b = nullptr;
    bool game_over = false;
    void repeatable_command(std::string command);
public:
    Command(Board *b);
    void read_command(std::string command);
    void drop();
    void left();
    void right();
    void down();
    void clockwise();
    void counterclockwise();
    void levelup();
    void leveldown();
    void restart();
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
    void sequence(std::vector<std::string> command_sequence);
    friend std::ostream &operator<<(std::ostream &out, const Command &command);
};

#endif
