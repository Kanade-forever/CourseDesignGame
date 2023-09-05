#include "castle.h"

Castle::Castle(){}

Castle::Castle(QString _name,int _treasure){
    castle_name = _name;
    this->treasure = _treasure;
}

void Castle::set_treasure(int _treasure){
    this->treasure = _treasure;
}

int Castle::get_treasure(){
    return this->treasure;
}

QString Castle::get_name(){
    return castle_name;
}
