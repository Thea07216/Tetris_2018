#include "level.h"
using namespace std;

void Level::random_noran(vector<char> block_sequence){
    this->neen_read_file = true;
    this->command = block_sequence;
    return;
}

void Level::noran_random(){
    this->neen_read_file = false;
    return;
}

void Level::times_zero(){
    return;
}
void Level::times_add_one(){
    return;
}

int Level::get_times(){
    return this->times;
}

vector<char> Level :: get_command(){
    return this->command;
}

void Level::change_command(){
    char myfirst = *command.begin();
    this->command.erase(command.begin());
    this->command.push_back(myfirst);
}
