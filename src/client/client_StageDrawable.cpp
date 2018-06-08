#include "client_StageDrawable.h"

StageDrawable::StageDrawable(size_t width, size_t height){
    this->width = width;
    this->height = height;
}

void StageDrawable::be_drawn_by_console(ConsoleDrawer* console_drawer){
  console_drawer->draw(this);
}


size_t StageDrawable::get_width(){
    return this->width;
}

size_t StageDrawable::get_height(){
    return this->height;
}
