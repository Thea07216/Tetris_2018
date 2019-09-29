#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <iostream>
#include <vector>
#include "subject.h"
#include "info.h"
class Observer;
class Cell;

class TextDisplay: public Observer{
    std::vector<std::vector<char>> theDisplay;
    const int row, col;
    int level, score, highscore;
    char next;
    void change_highscore(int highscore);
public:
    TextDisplay(int r, int c, int l, int s, int h, char n):
    row{r}, col{c}, level{l}, score{s}, highscore{h}, next{n}{
        for (int i = 0; i < row; i++){
            std::vector<char> c;
            for (size_t j = 0; j < col; j++){
                c.push_back(' ');
            }
            theDisplay.push_back(c);
        }
    }
    
    void notify(Subject &whoNotified) override;
    
    void add_score(int score);
    
    void clear_score();
    
    void change_level(int level);
    
    void check_highscore();
    
    void change_next(char next);
    
    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
    
};
#endif
