#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "board.h"
#include "level.h"
#include "command.h"
#include "graphicsdisplay.h"

using namespace std;

// Do not remove any code; do not add code other than where indicated.

int main(int argc, char *argv[]) {
    bool need_graphics = true;
    int text_size = 25;
    int grid_size = 25;
    int seed;
    string scriptfile = "sequence.txt";
    int startlevel = 0;
    for (int i  = 1; i < argc; i++) {
        //cout<<argv[1]<<endl;//debug
        string s = argv[i];
        if (s == "-text") {
            //cout<<"2";//debug
            need_graphics = false;
        } else if (s == "-seed") {
            i++;
            seed = stoi(argv[i]);
            srand(seed);
        } else if (s == "-scriptfile") {
            //change when compiling on linux environment IMPLEMENT FILE STREAM
            i++;
            scriptfile = argv[i];
        } else if (s == "-startlevel") {
            i++;
            startlevel = stoi(argv[i]);
        }
    }
    
    cin.exceptions(ios::eofbit|ios::failbit);
    string cmd;
    Board b;
    Command c = {&b};
    
    //filestream for level 0
    vector <char> block_sequence;
    ifstream file{scriptfile};
    char single_block;
    //block_sequence.emplace_back(single_block);
    while (file>>single_block){
        block_sequence.emplace_back(single_block);
    }
    
    b.init(block_sequence, startlevel, 'N');
    cout<<c;
    
    //graphics
    if (need_graphics){
        b.setGraphics(grid_size, text_size);
    }
    
    //for sequence file
    vector <string> command_sequence;
    string command;
    //for norandom file
    block_sequence.clear();
    try {
        while (true) {
            cin >> cmd;
            if (cmd == "sequence" || cmd == "sequenc"
                || cmd == "sequen" || cmd == "seque"
                || cmd == "sequ"|| cmd == "seq"
                || cmd == "se" || cmd == "s") {
                cin>>cmd;
                ifstream sequence_file{cmd};
                while (sequence_file>>command){
                    command_sequence.emplace_back(command);
                }
                c.sequence(command_sequence);
                cout<<c;
            } else if (cmd == "norandom" || cmd == "norando"
                       || cmd == "norand" || cmd == "noran"
                       || cmd == "nora"|| cmd == "nor"
                       || cmd == "no" || cmd == "n") {
                cin>>cmd;
                ifstream norandom_file{cmd};
                while (norandom_file>>single_block){
                    block_sequence.emplace_back(single_block);
                }
                c.norandom(block_sequence);
                cout<<c;
            } else {
                c.read_command(cmd);
                cout<<c;
            }
        }
    }
    catch (ios::failure &) {}  // Any I/O failure quits
}
