#include "Button.h"
#include <iostream>
button::button(Text & t,RenderWindow&w){
    tex = &t;
    win = &w;
}
bool button::update(){
    float lef = tex->getPosition().x;
    float rig = lef+tex->getGlobalBounds().width;
    float top = tex->getGlobalBounds().top;
    float bot = top+tex->getGlobalBounds().height;
    float x = Mouse::getPosition(*win).x;
    float y = Mouse::getPosition(*win).y;
    if(x<rig&&x>lef&&y<bot&&y>top&&Mouse::isButtonPressed(Mouse::Button::Left)){
        return true;
    }else{
        return false;
    }
}