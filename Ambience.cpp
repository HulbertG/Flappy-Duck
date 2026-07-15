#include "Ambience.h"
stattex ambience::grass;
ambience::ambience(RenderWindow & w){
    window = &w;
    for(int i=0;i<6;i++){
        elements.push_back(creategrass(200+(i*200)));
    }
}
element ambience::creategrass(int xoffset){
    if(!grass.hasinit){
        grass.texture.loadFromFile("sprites/Ground.png");
    }
    element newgrass;
    newgrass.item = new Sprite(grass.texture);
    newgrass.item->setScale(Vector2f(.4,.44));
    newgrass.item->setOrigin(Vector2f(grass.texture.getSize().x,grass.texture.getSize().y));
    newgrass.item->setPosition(Vector2f(xoffset,700));
    newgrass.speed = 5.0f;
    return newgrass;
}
void ambience::update(){
    // if(elements[0].item->getPosition().x<0){
    //     elements.push_back(creategrass(1200));
    //     delete elements[0].item;
    //     elements.erase(elements.begin());
    // }
    for(auto elem:elements){
        elem.item->setPosition(Vector2f(elem.item->getPosition().x-elem.speed,elem.item->getPosition().y));
    }
    if(elements[0].item->getPosition().x<=0){
        elements.push_back(creategrass(elements[0].item->getPosition().x+1200));
        delete elements[0].item;
        elements.erase(elements.begin());
    }
}
void ambience::draw(){
    for(auto elem:elements){
        window->draw(*elem.item);
    }
}