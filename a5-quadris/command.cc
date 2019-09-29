#include "command.h"
#include <iostream>
#include <sstream>
using namespace std;

Command::Command(Board *b): b{b}{}

void Command::read_command(string command) {
    if (command == "restart" || command == "restar"
           || command == "resta" || command == "rest"
           || command == "res" || command == "re") {
        this->restart();
    } else if (command == "hint" || command == "hin"
               || command == "hi" || command == "h") {
        this->hint();
    /*} else if (command == "norandom" || command == "norando"
               || command == "norand" || command == "noran"
               || command == "nora" || command == "nor"
               || command == "no" || command == "n") {
        this->norandom();*/
    } else if (command == "random" || command == "rando"
               || command == "rand" || command == "ran"
               || command == "ra") {
        this->random();
    } else if (command == "I") {
        this->I();
    } else if (command == "J") {
        this->J();
    } else if (command == "L") {
        this->L();
    } else if (command == "Z") {
        this->Z();
    } else if (command == "O") {
        this->O();
    } else if (command == "S") {
        this->S();
    } else if (command == "T") {
        this->T();
    } else {
        istringstream is{command};
        int multi;
        string r_command;
        if (is>>multi) {
            is>>r_command;
            for (int i = 0; i < multi; i++) {
                repeatable_command(r_command);
            }
        } else {
            is.clear();
            is>>r_command;
            repeatable_command(r_command);
        }
    }
}

void Command::repeatable_command(string command) {
    if (this->game_over) return;
    b->delete_hint();
    if (command == "drop" || command == "dro"
        || command == "dr") {
        this->drop();
    } else if (command == "left" || command == "lef") {
        this->left();
    } else if (command == "right" || command == "righ"
               || command == "rig" || command == "ri") {
        this->right();
    } else if (command == "down" || command == "dow"
               || command == "do") {
        this->down();
    } else if (command == "levelup" || command == "levelu") {
        this->levelup();
    } else if (command == "leveldown" || command == "leveldow"
               || command == "leveldo" || command == "leveld") {
        this->leveldown();
    } else if (command == "clockwise" || command == "clockwis"
               || command == "clockwi" || command == "clockw"
               || command == "clock"|| command == "cloc"
               || command == "clo" || command == "cl") {
        this->clockwise();
    }else if (command == "counterclockwise" || command == "counterclockwis"
              || command == "counterclockwi" || command == "counterclockw"
              || command == "counterclock"|| command == "countercloc"
              || command == "counterclo" || command == "countercl"
              || command == "counterc" || command == "counter"
              || command == "counter" || command == "counte"
              || command == "count" || command == "count"
              || command == "coun" || command == "cou"
              || command == "co") {
        this->counterclockwise();
    }
}

void Command::drop() {
    if(!(this->b->drop())) {
        game_over = true;
    }
}

void Command::clockwise() {
    b->clockwise();

}


void Command::left() {
    b->left();

}

    
void Command::counterclockwise() {
    b->counterclockwise();

}

    
void Command::right() {
    b->right();

}

void Command::down() {
    b->down();
}

void Command::restart() {
    this->game_over = false;
    b->restart();
}

void Command::levelup() {
    b->levelup();
    
}
void Command::leveldown() {
    b->leveldown();
}

void Command::random() {
    b->random();
}

void Command::norandom(vector<char> block_sequence) {
    b->norandom(block_sequence);
}

void Command::I() {
    b->I();
}

void Command::J() {
    b->J();
}

void Command::L() {
    b->L();
}

void Command::Z() {
    b->Z();
}
void Command::O() {
    b->O();
}

void Command::S() {
    b->S();
}
void Command::T() {
    b->T();
}


void Command::hint(){
    b->hint();
}

void Command::sequence(vector<string> command_sequence) {
    for(auto command: command_sequence) {
        read_command(command);
    }
}

std::ostream &operator<<(std::ostream &out, const Command &command) {
    if (command.game_over) {
        out<<"GAME OVER! Please enter \"restart\""<<endl;
    } else {
        out<<*(command.b)<<endl;
    }
    return out;
}
