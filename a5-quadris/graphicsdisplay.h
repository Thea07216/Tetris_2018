#ifndef GRAPHICSDISPLAY_H
#define GRAPHICSDISPLAY_H
#include <iostream>
#include <vector>
#include <string>
#include "observer.h"
#include "window.h"
#include "info.h"
class Cell;

class GraphicsDisplay: public Observer {
    const int gridSize, textSize_y, winSize_x, boardSize_y;
    int level, score, highscore;
    char next;
    void change_highscore(int highscore);
    Xwindow xw;
    
public:
    GraphicsDisplay(int gridSize, int textSize_y,
                    int winSize_x, int boardSize_y,
                    int l, int s, int h, char n);
    
    void notify(Subject &whoNotified) override;
    
    void add_score(int score);
    
    void clear_score();
    
    void change_level(int level);
    
    void check_highscore();
    
    void change_next(char next);
};
#endif
