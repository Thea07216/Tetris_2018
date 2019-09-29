#include <iostream>
#include "graphicsdisplay.h"
#include "info.h"
#include "subject.h"
using namespace std;


GraphicsDisplay::GraphicsDisplay(int gridSize, int textSize_y, int winSize_x,
                                 int boardSize_y, int l, int s, int h, char n):
gridSize{gridSize}, textSize_y{textSize_y}, winSize_x{winSize_x},
boardSize_y{boardSize_y}, level{l}, score{s}, highscore{h}, next{n},
xw{winSize_x, boardSize_y + 6 * textSize_y} {
    string level_str = to_string(this->level);
    string score_str = to_string(this->score);
    string highscore_str = to_string(this->score);
    xw.drawString(0, 1 * this->textSize_y, "Level: " + level_str, Xwindow::Black);
    xw.drawString(0, 2 * this->textSize_y, "Score: " + score_str, Xwindow::Black);
    xw.drawString(0, 3 * this->textSize_y, "Hi Score: " + highscore_str, Xwindow::Black);
}

void GraphicsDisplay::add_score(int score) {
    this->score += score;
    string score_str = to_string(this->score);
    xw.fillRectangle(0, 1 * this->textSize_y, this->winSize_x, this->textSize_y, Xwindow::White);
    xw.drawString(0, 2 * this->textSize_y, "Score: " + score_str, Xwindow::Black);
}

void GraphicsDisplay::clear_score() {
    this->score = 0;
    string score_str = to_string(this->score);
    xw.fillRectangle(0, 1 * this->textSize_y, this->winSize_x, this->textSize_y, Xwindow::White);
    xw.drawString(0, 2 * this->textSize_y, "Score: " + score_str, Xwindow::Black);
}

void GraphicsDisplay::change_level(int level) {
    this->level = level;
    string level_str = to_string(this->level);
    xw.fillRectangle(0, 0 * this->textSize_y, this->winSize_x, this->textSize_y, Xwindow::White);
    xw.drawString(0, 1 * this->textSize_y, "Level: " + level_str, Xwindow::Black);
}

void GraphicsDisplay::check_highscore() {
    if (this->highscore < this->score) {
        change_highscore(this->score);
    }
}

void GraphicsDisplay::change_highscore(int highscore) {
    this->highscore = highscore;
    string highscore_str = to_string(this->highscore);
    xw.fillRectangle(0, 2 * this->textSize_y, this->winSize_x, this->textSize_y, Xwindow::White);
    xw.drawString(0, 3 * this->textSize_y, "Hi Score: " + highscore_str, Xwindow::Black);
}

void GraphicsDisplay::change_next(char next) {
    this->next = next;
    xw.drawString(0, 4 * this->textSize_y + this->boardSize_y, "Next:", Xwindow::Black);
    xw.fillRectangle(0, 4 * this->textSize_y + this->boardSize_y,
                     this->winSize_x, this->gridSize, Xwindow::White);
    xw.fillRectangle(0, 4 * this->textSize_y + this->boardSize_y + 1 * this->gridSize,
                     this->winSize_x, this->gridSize, Xwindow::White);
    if (next == 'I'){
        //out<<"IIII"<<endl;
        xw.fillRectangle(0, 4 * this->textSize_y + this->boardSize_y,
                         4 * this->gridSize, this->gridSize, Xwindow::Red);
    } else if (next == 'J') {
        //out<<"J"<<endl;
        //out<<"JJJ"<<endl;
        xw.fillRectangle(0, 4 * this->textSize_y + this->boardSize_y,
                         1 * this->gridSize, this->gridSize, Xwindow::Blue);
        xw.fillRectangle(0, 4 * this->textSize_y + this->boardSize_y + 1 * this->gridSize,
                         3 * this->gridSize, this->gridSize, Xwindow::Blue);
    } else if (next == 'L') {
        //out<<"  L"<<endl;
        //out<<"LLL"<<endl;
        xw.fillRectangle(2 * this->gridSize, 4 * this->textSize_y + this->boardSize_y,
                         1 * this->gridSize, this->gridSize, Xwindow::Green);
        xw.fillRectangle(0, 4 * this->textSize_y + this->boardSize_y + 1 * this->gridSize,
                         3 * this->gridSize, this->gridSize, Xwindow::Green);
    } else if (next == 'O') {
        //out<<"OO"<<endl;
        //out<<"OO"<<endl;
        xw.fillRectangle(0, 4 * this->textSize_y + this->boardSize_y,
                         2 * this->gridSize, this->gridSize, Xwindow::Orange);
        xw.fillRectangle(0, 4 * this->textSize_y + this->boardSize_y + 1 * this->gridSize,
                         2 * this->gridSize, this->gridSize, Xwindow::Orange);
    } else if (next == 'S') {
        //out<<" SS"<<endl;
        //out<<"SS"<<endl;
        xw.fillRectangle(1 * this->gridSize, 4 * this->textSize_y + this->boardSize_y,
                         2 * this->gridSize, this->gridSize, Xwindow::Magenta);
        xw.fillRectangle(0, 4 * this->textSize_y + this->boardSize_y + 1 * this->gridSize,
                         2 * this->gridSize, this->gridSize, Xwindow::Magenta);
    } else if (next == 'Z') {
        //out<<"ZZ"<<endl;
        //out<<" ZZ"<<endl;
        xw.fillRectangle(0, 4 * this->textSize_y + this->boardSize_y,
                         2 * this->gridSize, this->gridSize, Xwindow::Cyan);
        xw.fillRectangle(1 * this->gridSize, 4 * this->textSize_y + this->boardSize_y + 1 * this->gridSize,
                         2 * this->gridSize, this->gridSize, Xwindow::Cyan);
    } else if (next == 'T'){
        //out<<"TTT"<<endl;
        //out<<" T"<<endl;
        xw.fillRectangle(0, 4 * this->textSize_y + this->boardSize_y,
                         3 * this->gridSize, this->gridSize, Xwindow::Yellow);
        xw.fillRectangle(1 * this->gridSize, 4 * this->textSize_y + this->boardSize_y + 1 * this->gridSize,
                         1 * this->gridSize, this->gridSize, Xwindow::Yellow);
    }
}

void GraphicsDisplay::notify(Subject &whoNotified) {
    auto info = whoNotified.getInfo();
    int cellSize = gridSize;
    if (info.type == '*'){
        xw.fillRectangle(info.col * cellSize, info.row * cellSize + 3 * textSize_y, cellSize, cellSize, Xwindow::Black);
    } else if (info.type == 'J'){
        xw.fillRectangle(info.col * cellSize, info.row * cellSize + 3 * textSize_y, cellSize, cellSize, Xwindow::Blue);
    } else if (info.type == 'I'){
        xw.fillRectangle(info.col * cellSize, info.row * cellSize + 3 * textSize_y, cellSize, cellSize, Xwindow::Red);
    } else if (info.type == 'L') {
        xw.fillRectangle(info.col * cellSize, info.row * cellSize + 3 * textSize_y, cellSize, cellSize, Xwindow::Green);
    } else if (info.type == 'O') {
        xw.fillRectangle(info.col * cellSize, info.row * cellSize + 3 * textSize_y, cellSize, cellSize, Xwindow::Orange);
    } else if (info.type == 'Z') {
        xw.fillRectangle(info.col * cellSize, info.row * cellSize + 3 * textSize_y, cellSize, cellSize, Xwindow::Cyan);
    } else if (info.type == 'T'){
        xw.fillRectangle(info.col * cellSize, info.row * cellSize + 3 * textSize_y, cellSize, cellSize, Xwindow::Yellow);
    } else if (info.type == 'S'){
        xw.fillRectangle(info.col * cellSize, info.row * cellSize + 3 * textSize_y, cellSize, cellSize, Xwindow::Magenta);
    } else if (info.type == ' '){
        xw.fillRectangle(info.col * cellSize, info.row * cellSize + 3 * textSize_y, cellSize, cellSize, Xwindow::White);
    } else if (info.type == '?'){
        xw.fillRectangle(info.col * cellSize, info.row * cellSize + 3 * textSize_y, cellSize, cellSize, Xwindow::Brown);
    }
}
