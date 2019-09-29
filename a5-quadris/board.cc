#include "board.h"
#include <iostream>
using namespace std;

Board::~Board() {
    /*for (auto block_p: history_block){
        delete block_p;
    }
    delete this->td;
    delete this->graphics;
    delete this->level;
    delete this->cur_block;
    delete this->next_block;*/
}

//added field please change init
void Board::init(vector<char> l_zero_gen, int level_int,
                 char change_undropped) {
    //for level
    this->l_zero_gen = l_zero_gen;//l_zero_gen
    this->level_int = level_int;
    this->change_undropped = change_undropped;
    //starting level
    if (this->level_int == 0) {
        this->level = make_unique<Level_zero> (Level_zero(this->l_zero_gen));
    } else if (this->level_int == 1) {
        this->level = make_unique<Level_one> (Level_one(this->l_zero_gen));
    } else if (this->level_int == 2) {
        this->level = make_unique<Level_two> (Level_two(this->l_zero_gen));
    } else if (this->level_int == 3) {
        this->level = make_unique<Level_three> (Level_three(this->l_zero_gen));
    } else {
        this->level = make_unique<Level_four> (Level_four(this->l_zero_gen));
    }
    
    for (size_t r = 0; r < row; r++) {//theBoard
        vector<Cell> row_v;
        for (size_t c = 0; c < column; c++) {
            row_v.emplace_back(Cell{r,c});
        }
        this->theBoard.emplace_back(row_v);
    }
    unique_ptr<Block> cb(level->generate(&this->theBoard, change_undropped));
    this->cur_block = std::move(cb);
    unique_ptr<Block> nb(level->generate(&this->theBoard, change_undropped));
    this->next_block = std::move(nb);
    //cout<<"next block type init "<<next_block->block_type()<<endl;//debug
    unique_ptr<TextDisplay> t(new TextDisplay(this->row, this->column, this->level_int,
                                              0, 0, next_block->block_type()));
    this->td = std::move(t);
    for (size_t r = 0; r < row; r++) {//attach textdisplay as observer to each cell
        for (size_t c = 0; c < column; c++) {
            theBoard.at(r).at(c).attach(td.get());
        }
    }
    cur_block->appear_next();
    td->change_next(next_block->block_type());
    if (!(this->graphics == nullptr)) {
        graphics->change_next(next_block->block_type());
    }
}

void Board::setGraphics(int cell_size, int text_size) {
    unique_ptr<GraphicsDisplay> g(new GraphicsDisplay(cell_size, text_size, this->column * cell_size,
                                                      this->row * cell_size, this->level_int, 0, 0,
                                                      next_block->block_type()));
    this->graphics = move(g);
    for (size_t r = 0; r < this->row; r++) {
        for (size_t c = 0; c < this->column; c++) {
            this->theBoard.at(r).at(c).attach(this->graphics.get());
        }
    }
    cur_block->appear_next();
    graphics->change_next(this->next_block->block_type());
}

void Board::clear_board() {
    history_block.clear();
    this->level.reset(new Level_zero(this->l_zero_gen));
    this->level_int = 0;
    this->td->change_level(level_int);
    if (this->graphics != nullptr) {
        graphics->change_level(level_int);
    }
    this->td->clear_score();
    if (this->graphics != nullptr) {
        this->graphics->clear_score();
    }
    for (size_t r = 0; r < this->row; r++) {
        for (size_t c = 0; c < this->column; c++) {
            this->theBoard.at(r).at(c).clear();
        }
    }
}

void Board::restart() {
    clear_board();
    cur_block.reset(level->generate(&this->theBoard, change_undropped));
    next_block.reset(level->generate(&this->theBoard, change_undropped));
    cur_block->appear_next();
    td->change_next(next_block->block_type());
    if (this->graphics != nullptr) {
        graphics->change_next(next_block->block_type());
    }
}

void Board::left() {
    cur_block->disappear();
    cur_block->left(&this->theBoard);
    this->cur_block->set();
}

void Board::right() {
    cur_block->disappear();
    cur_block->right(&this->theBoard);
    this->cur_block->set();
}

void Board::down() {
    cur_block->disappear();
    cur_block->down(&this->theBoard);
    this->cur_block->set();
}

bool Board::drop() {
    cur_block->disappear();
    cur_block->drop(&this->theBoard);
    this->cur_block->set();
    this->history_block.emplace_back(move(cur_block));
    //Block * temp = next_block.release();
    //this->cur_block.reset(temp);
    this->cur_block = move(next_block);
    this->next_block.reset(level->generate(&this->theBoard, this->change_undropped));
    scan();
    vector<Cell> &top_line = theBoard.at(2);
    for (size_t i = 0; i < this->column; i++) {
        if (top_line.at(i).get_landed()) {
            return false;
        }
    }
    if(this->cur_block->place_next()) {
        //for loop to appear block
        cur_block->appear_next();
        td->change_next(next_block->block_type());
        if (this->graphics != nullptr) {
            graphics->change_next(next_block->block_type());
        }
        return true;
    } else {
        return false;
    }
}

void Board::drop_row(vector<Cell> &lower, vector<Cell> &upper) {
    for (int i = 0; i < this->column; i++) {
        Cell &cell_u=upper.at(i);
        Cell &cell_l=lower.at(i);
        cell_l.cell_copy(cell_u);
    }
}

void Board::scan() {
    int line_acc = 0;
    bool any_full = false;
    for (size_t i = 0; i <this->row; i++) {
        bool full = true;
        for (size_t j = 0; j < this->column; j++) {
            if (!(theBoard.at(i).at(j).get_landed())) {
                full = false;
                break;
            }
        }
        if (full) {
            any_full = true;
            line_acc++;
            // bonus score
            for (size_t j = 0; j < this->column; j++){
                Cell cell=theBoard.at(i).at(j);
                if ((cell.get_type() != '*') && cell.getp()->lose_member()){
                    int n = cell.getp()->score();
                    //cout<<"bouns added"<<n<<endl;//debug
                    td->add_score(n);
                    if (this->graphics != nullptr) {
                        graphics->add_score(n);
                    }
                }
            }
            //shift everything down by one
            
            for (size_t k = i; k > 2; k--) {
                
                vector<Cell> &lower = this->theBoard.at(k);
                vector<Cell> &upper = this->theBoard.at(k - 1);
                drop_row(lower, upper);
            }
        }
    }
    //level 4
    if (this->level_int == 4) {
        this->level->times_add_one();
        if (!any_full) {
            int no_clear_times = this->level->get_times();
            if ((no_clear_times > 0) && ((no_clear_times % 5) == 0)) {
                unique_ptr<Block> penalty(this->level->generate(&this->theBoard, this->change_undropped));
                penalty->appear_next();
                penalty->disappear();
                penalty->drop(&theBoard);
                penalty->set();
                level->times_zero();
                
                for (size_t i = 0; i <this->row; i++) {
                    bool full_o = true;
                    for (size_t j = 0; j < this->column; j++) {
                        if (!(theBoard.at(i).at(j).get_landed())) {
                            full_o = false;
                            break;
                        }
                    }
                    if (full_o) {
                        //shift everything down by one
                        for (size_t k = i; k > 2; k--) {
                            vector<Cell> &lower = this->theBoard.at(k);
                            vector<Cell> &upper = this->theBoard.at(k - 1);
                            drop_row(lower, upper);
                        }
                        int m = 1 + this->level_int;
                        m *= m;
                        td->add_score(m);
                        td->check_highscore();
                        if (this->graphics != nullptr) {
                            graphics->add_score(m);
                            graphics->check_highscore();
                        }
                    }
                }
            }
            
        } else {
            this->level->times_zero();
        }
    }
    if(line_acc>0){
        int m = line_acc + this->level_int;
        m *= m;
        td->add_score(m);
        td->check_highscore();
        if (this->graphics != nullptr) {
            graphics->add_score(m);
            graphics->check_highscore();
        }
    }
}

void Board::levelup() {
    if (this->level_int == 0) {
        this->level = make_unique<Level_one> (Level_one(this->l_zero_gen));
    } else if (this->level_int == 1) {
        this->level = make_unique<Level_two> (Level_two(this->l_zero_gen));
    } else if (this->level_int == 2) {
        this->level = make_unique<Level_three> (Level_three(this->l_zero_gen));
    } else if (this->level_int == 3) {
        this->level = make_unique<Level_four> (Level_four(this->l_zero_gen));
    }
    if (this->level_int != 4) {
        this->level_int++;
        td->change_level(level_int);
        if (this->graphics != nullptr) {
            graphics->change_level(level_int);
        }
        char next_type = this->next_block->block_type();
        this->next_block.reset(level->generate(&this->theBoard, next_type));
    }
}

void Board::leveldown() {
    if (this->level_int == 4) {
        this->level = make_unique<Level_three> (Level_three(this->l_zero_gen));
    } else if (this->level_int == 3) {
        this->level = make_unique<Level_two> (Level_two(this->l_zero_gen));
    } else if (this->level_int == 2) {
        this->level = make_unique<Level_one> (Level_one(this->l_zero_gen));
    } else if (this->level_int == 1) {
        this->level = make_unique<Level_zero> (Level_zero(this->l_zero_gen));
    }
    if (this->level_int != 0) {
        this->level_int--;
        td->change_level(level_int);
        if (this->graphics != nullptr) {
            graphics->change_level(level_int);
        }
        char next_type = this->next_block->block_type();
        this->next_block.reset(level->generate(&this->theBoard, next_type));
    }
}

void Board::clockwise(){
    this->cur_block->disappear();
    this->cur_block->clockwise(&theBoard);
    this->cur_block->set();
}

void Board::counterclockwise(){
    this->cur_block->disappear();
    this->cur_block->countclockwise(&theBoard);
    this->cur_block->set();
}

void Board::random() {
    this->level->noran_random();
}
void Board::norandom(vector<char> block_sequence){
    this->level->random_noran(block_sequence);
}

void Board::I() {
    this->cur_block->disappear();
    this->cur_block.reset(this->level->generate(&this->theBoard, 'I'));
    this->cur_block->appear_next();
    
}

void Board::J() {
    this->cur_block->disappear();
    this->cur_block.reset(this->level->generate(&this->theBoard, 'J'));
    this->cur_block->appear_next();
    
}

void Board::L() {
    this->cur_block->disappear();
    this->cur_block.reset(this->level->generate(&this->theBoard, 'L'));
    this->cur_block->appear_next();
    
}

void Board::Z() {
    this->cur_block->disappear();
    this->cur_block.reset(this->level->generate(&this->theBoard, 'Z'));
    this->cur_block->appear_next();
}

void Board::O() {
    this->cur_block->disappear();
    this->cur_block.reset(this->level->generate(&this->theBoard, 'O'));
    this->cur_block->appear_next();
}

void Board::S(){
    this->cur_block->disappear();
    this->cur_block.reset(this->level->generate(&this->theBoard, 'S'));
    this->cur_block->appear_next();
}

void Board::T() {
    this->cur_block->disappear();
    this->cur_block.reset(this->level->generate(&this->theBoard, 'T'));
    this->cur_block->appear_next();
}

std::ostream &operator<<(std::ostream &out, const Board &b) {
    out<<(*b.td);
    return out;
}

int Board::hint_scan_row(){
    int line_acc = 0;
    for (size_t i = 0; i <this->row; i++) {
        bool full = true;
        for (size_t j = 0; j < this->column; j++) {
            if (!(theBoard.at(i).at(j).get_landed())) {
                full = false;
                break;
            }
        }
        if (full) {
            line_acc++;
        }
    }
    return line_acc;
}

int Board::hint_scan_space(int low){
    int space = 0;
    for (size_t j = 0; j < this->column; j++) {
        if (!(theBoard.at(low).at(j).get_landed())) {
            space++;
        }
    }
    return space;
}

int Board::hint_scan_cospace(int low){
    int space = 0;
    for (size_t j = 0; j < this->column; j++) {
        if ((!(theBoard.at(low).at(j).get_landed()))&&(j>0)) {
            if(theBoard.at(low).at(j-1).get_landed()){
            space++;
            }
            space++;
        }
    }
    return space;
}

int Board:: hint_scan_low(){
    int space=0;
    for(int y=0;y<this->row-1;y++){
        for (int j = 0; j < this->column; j++) {
             if (theBoard.at(y).at(j).get_landed()) {
                 if(!(theBoard.at(y+1).at(j).get_landed())){
                     space++;
                 }
             }
        }
    }
    return space;
}


void Board::hint(){
    Block copy1=*cur_block;
    Container result={copy1,0,0,0,0,0,0,0};
    bool inserted=false;
    for(int rotate=0;rotate<4;rotate++){
        for(int i=0;i<column;i++){
            for(int x=0;x<column;x++){
            for(int y=0;y<row;y++){
                Block copy=*cur_block;
                for(int a=rotate;a>0;a--){
                    copy.clockwise(&this->theBoard);
                }
                for(int e=x;e>0;e--){
                    if(!copy.right(&this->theBoard)){
                        break;
                    }
                }
                for(int c=y;c>0;c--){
                    if(!copy.down(&this->theBoard)){
                        break;
                    }
                }
                for(int b=i;b>0;b--){
                    if(!copy.right(&this->theBoard)){
                        break;
                    }
                }
                copy.drop(&this->theBoard);
                
                int low=copy.lowest();
                int deleted=hint_scan_row();
                int space=hint_scan_space(low);
                int cospace=hint_scan_cospace(low);
                int under =copy.lospace(&this->theBoard);
                int high= copy.highest();
                int lowspace=hint_scan_low();
                
                copy.unlanded();
                if (!inserted){
                    result={copy,deleted,low,space,cospace,under,high,lowspace};
                    inserted=true;
                } else {
                    if(result.deleted_row<deleted){
                        result={copy,deleted,low,space,cospace,under,high,lowspace};
                        inserted=true;
                    }else if(result.deleted_row==deleted){
                        if(result.under>under){
                            result={copy,deleted,low,space,cospace,under,high,lowspace};
                            inserted=true;
                        } else if(result.under==under){
                            if(result.low<low){
                                result={copy,deleted,low,space,cospace,under,high,lowspace};
                                inserted=true;
                            }else if(result.low==low){
                                if(result.space>space){
                                result={copy,deleted,low,space,cospace,under,high,lowspace};
                                    inserted=true;
                                } else if(result.space==space) {
                                    if(result.cospace>cospace){
                                result={copy,deleted,low,space,cospace,under,high,lowspace};
                                        inserted=true;
                                    }else if(result.cospace==cospace){
                                        if(result.lowspace>lowspace){
                                result={copy,deleted,low,space,cospace,under,high,lowspace};
                                            inserted=true;
                                        } else if(result.lowspace==lowspace){
                                            if (result.high<=high){
                                result={copy,deleted,low,space,cospace,under,high,lowspace};
                                                inserted=true;
                                            }else {
                                                continue;
                                            }
                                        } else {
                                            continue;
                                        }
                                        }else {
                                        continue;
                                    }
                                }else {
                                    continue;
                                }
                            } else {
                                continue;
                            }
                        } else {
                            continue;
                        }
                    }else {
                        continue;
                    }
                }
            }
        }
    }
    }
        
    for(int rotate=0;rotate<4;rotate++){
        for(int i=0;i<column;i++){
            for(int x=0;x<column;x++){
            for(int y=0;y<row;y++){
                Block copy=*cur_block;
                for(int a=rotate;a>0;a--){
                    copy.clockwise(&this->theBoard);
                }
                while(copy.right(&this->theBoard)){
                    continue;
                }
                for(int e=x;e>0;e--){
                    if(!copy.left(&this->theBoard)){
                            break;
                    }
                }
                for(int c=y;c>0;c--){
                    if(!copy.down(&this->theBoard)){
                        break;
                    }
                }
                for(int b=i;b>0;b--){
                    if(copy.left(&this->theBoard)){
                        break;
                    }
                }
                copy.drop(&this->theBoard);
                
                int low=copy.lowest();
                int deleted=hint_scan_row();
                int space=hint_scan_space(low);
                int cospace=hint_scan_cospace(low);
                int under =copy.lospace(&this->theBoard);
                int high= copy.highest();
                int lowspace=hint_scan_low();
                
                copy.unlanded();
                if (!inserted){
                    result={copy,deleted,low,space,cospace,under,high,lowspace};
                    inserted=true;
                } else {
                    if(result.deleted_row<deleted){
                        result={copy,deleted,low,space,cospace,under,high,lowspace};
                        inserted=true;
                    }else if(result.deleted_row==deleted){
                        if(result.under>under){
                            result={copy,deleted,low,space,cospace,under,high,lowspace};
                            inserted=true;
                        } else if(result.under==under){
                            if(result.low<low){
                                result={copy,deleted,low,space,cospace,under,high,lowspace};
                                inserted=true;
                            }else if(result.low==low){
                                if(result.space>space){
                                result={copy,deleted,low,space,cospace,under,high,lowspace};
                                    inserted=true;
                                } else if(result.space==space) {
                                    if(result.cospace>cospace){
                                result={copy,deleted,low,space,cospace,under,high,lowspace};
                                        inserted=true;
                                    }else if(result.cospace==cospace){
                                        if(result.lowspace>lowspace){
                                result={copy,deleted,low,space,cospace,under,high,lowspace};
                                            inserted=true;
                                        } else if(result.lowspace==lowspace){
                                            if (result.high<=high){
                                result={copy,deleted,low,space,cospace,under,high,lowspace};
                                                inserted=true;
                                            }else {
                                                continue;
                                            }
                                        } else {
                                            continue;
                                        }
                                    }else {
                                        continue;
                                    }
                                }else {
                                    continue;
                                }
                            } else {
                                continue;
                            }
                        } else {
                            continue;
                        }
                    }else {
                        continue;
                    }
                }
            }
        }
        }
    }
    result.hint_block.hint_set();
    this->phint=make_unique<Block>(result.hint_block);
}

void Board::delete_hint(){
    if(this->phint!=nullptr){
        this->phint->disappear();
        this->phint.reset(nullptr);
    }
}
