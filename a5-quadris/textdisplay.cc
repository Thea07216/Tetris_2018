#include "textdisplay.h"
#include <iostream>//debug


using namespace std;


    
void TextDisplay::notify(Subject &whoNotified){
    Info ch_cell = whoNotified.getInfo();
    size_t rowcell = ch_cell.row;
    size_t colcell = ch_cell.col;
    char cell_type = ch_cell.type;
    //cout<<"notified"<<endl;//debug
    this->theDisplay.at(rowcell).at(colcell) = cell_type;
}

void TextDisplay::add_score(int score) {
    this->score += score;
}

void TextDisplay::clear_score() {
    this->score = 0;
}

void TextDisplay::change_level(int level) {
    this->level = level;
}

void TextDisplay::check_highscore() {
    if (this->highscore < this->score) {
        change_highscore(this->score);
    }
}

void TextDisplay::change_highscore(int highscore) {
    this->highscore = highscore;
}

void TextDisplay::change_next (char next) {
    this->next = next;
}

string space_typer(size_t n) {
    string space;
    for (int i = 0; i < n; i++) {
        space = space + " ";
    }
    return space;
}

std::ostream & operator<<(std::ostream &out, const TextDisplay &td){
    char next = td.next;
    out<<"Level:      "<<td.level<<endl;
    string score_str = to_string(td.score);
    size_t score_space_len = 7 - score_str.length();
    string score_space = space_typer(score_space_len);
    out<<"Score:"<<score_space<<score_str<<endl;
    string hiscore_str = to_string(td.highscore);
    size_t hiscore_space_len = 4 - hiscore_str.length();
    string hiscore_space = space_typer(hiscore_space_len);
    out<<"Hi Score:"<<hiscore_space<<hiscore_str<<endl;
    out<<"-----------"<<endl;//11
    for (int i = 0; i < td.row; i++){//theboard loop
        for ( int j = 0 ; j < td.col; j++){
             out<<td.theDisplay.at(i).at(j);
        }
        out<<endl;
    }
    out<<"-----------"<<endl;//11
    out<<"Next:"<<endl;
    if (next == 'I'){
        out<<"IIII"<<endl;
    } else if (next == 'J') {
        out<<"J"<<endl;
        out<<"JJJ"<<endl;
    } else if (next == 'L') {
        out<<"  L"<<endl;
        out<<"LLL"<<endl;
    } else if (next == 'O') {
        out<<"OO"<<endl;
        out<<"OO"<<endl;
    } else if (next == 'S') {
        out<<" SS"<<endl;
        out<<"SS"<<endl;
    } else if (next == 'Z') {
        out<<"ZZ"<<endl;
        out<<" ZZ"<<endl;
    } else if (next == 'T'){
        out<<"TTT"<<endl;
        out<<" T"<<endl;
    }
    return out;
}
    
    
