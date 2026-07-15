#include "PipeColumn.h"
#include <cstdlib>
#include <time.h>
#include "box2ddelete.h"
Texture PipeColumn::Toptex;
Texture PipeColumn::Bottomtex;
bool PipeColumn::hasload=false;
PipeColumn::PipeColumn(b2World & w){
    if(!hasload){
        Toptex.loadFromFile("sprites/PipeT.png");
        Bottomtex.loadFromFile("sprites/PipeB.png");
        hasload=true;
    }
    TopPipe = new Sprite(Toptex);
    BottomPipe = new Sprite(Bottomtex);
    TopPipe->setScale(Vector2f(.50f,.50f));
    BottomPipe->setScale(Vector2f(.50f,.50f));
    TopPipe->setOrigin(Vector2f(Toptex.getSize().x/2,Toptex.getSize().y));
    BottomPipe->setOrigin(Vector2f(Bottomtex.getSize().x/2,0));
    b2BodyDef pbodydef;
    pbodydef.type = b2_dynamicBody;
    pbodydef.position.Set(800.0f/scale,(200.0f-(this->getSize().y/2))/scale);
    pbodydef.userData.pointer = reinterpret_cast<uintptr_t>(&typeobj);
    //pbodydef.position.Set(600.0f/scale,200.0f/scale);
    PipeTBod = w.CreateBody(&pbodydef);
    b2PolygonShape hitboxT;
    hitboxT.SetAsBox(this->getSize().x/2/scale,this->getSize().y/2/scale);
    b2FixtureDef TopOutline;
    TopOutline.shape = &hitboxT;
    TopOutline.filter.categoryBits = 0x0004;
    PipeTBod->CreateFixture(&TopOutline);
    PipeTBod->SetFixedRotation(true);
    b2BodyDef pbodydef2;
    pbodydef2.type = b2_dynamicBody;
    pbodydef2.position.Set(800.0f/scale,(400.0f+(this->getSize().y/2))/scale);
    pbodydef2.userData.pointer = reinterpret_cast<uintptr_t>(&typeobj);
    PipeBBod = w.CreateBody(&pbodydef2);
    b2PolygonShape hitboxB;
    hitboxB.SetAsBox(this->getSize().x/2/scale,this->getSize().y/2/scale);
    b2FixtureDef BotOutline;
    BotOutline.shape = &hitboxB;
    BotOutline.filter.categoryBits = 0x0004;
    PipeBBod->CreateFixture(&BotOutline);
    PipeBBod->SetFixedRotation(true);
    TopPipe->setPosition(Vector2f(PipeTBod->GetPosition().x*scale,(PipeTBod->GetPosition().y*scale+(this->getSize().y/2))));
    BottomPipe->setPosition(Vector2f(PipeBBod->GetPosition().x*scale,(PipeBBod->GetPosition().y*scale-(this->getSize().y/2))));
    haspoint = true;
}
PipeColumn::PipeColumn(b2World & w,float offset){
    if(!hasload){
        Toptex.loadFromFile("sprites/PipeT.png");
        Bottomtex.loadFromFile("sprites/PipeB.png");
        hasload=true;
    }
    TopPipe = new Sprite(Toptex);
    BottomPipe = new Sprite(Bottomtex);
    TopPipe->setScale(Vector2f(.50f,.50f));
    BottomPipe->setScale(Vector2f(.50f,.50f));
    TopPipe->setOrigin(Vector2f(Toptex.getSize().x/2,Toptex.getSize().y));
    BottomPipe->setOrigin(Vector2f(Bottomtex.getSize().x/2,0));
    b2BodyDef pbodydef;
    pbodydef.type = b2_dynamicBody;
    pbodydef.position.Set(1100.0f/scale,((200.0f+offset)-(this->getSize().y/2))/scale);
    pbodydef.userData.pointer = reinterpret_cast<uintptr_t>(&typeobj);
    PipeTBod = w.CreateBody(&pbodydef);
    b2PolygonShape hitboxT;
    hitboxT.SetAsBox(this->getSize().x/2/scale,this->getSize().y/2/scale);
    b2FixtureDef TopOutline;
    TopOutline.shape = &hitboxT;
    TopOutline.filter.categoryBits = 0x0004;
    PipeTBod->CreateFixture(&TopOutline);
    PipeTBod->SetFixedRotation(true);
    b2BodyDef pbodydef2;
    pbodydef2.type = b2_dynamicBody;
    pbodydef2.position.Set(1100.0f/scale,((400.0f+offset)+(this->getSize().y/2))/scale);
    pbodydef2.userData.pointer = reinterpret_cast<uintptr_t>(&typeobj);
    PipeBBod = w.CreateBody(&pbodydef2);
    b2PolygonShape hitboxB;
    hitboxB.SetAsBox(this->getSize().x/2/scale,this->getSize().y/2/scale);
    b2FixtureDef BotOutline;
    BotOutline.shape = &hitboxB;
    BotOutline.filter.categoryBits = 0x0004;
    PipeBBod->CreateFixture(&BotOutline);
    PipeBBod->SetFixedRotation(true);
    TopPipe->setPosition(Vector2f(PipeTBod->GetPosition().x*scale,(PipeTBod->GetPosition().y*scale+(this->getSize().y/2))));
    BottomPipe->setPosition(Vector2f(PipeBBod->GetPosition().x*scale,(PipeBBod->GetPosition().y*scale-(this->getSize().y/2))));
    haspoint = true;
}
vector<Sprite> PipeColumn::getSprites(){
    vector<Sprite> returns;
    returns.push_back(*TopPipe);
    returns.push_back(*BottomPipe);
    return returns;
}
Vector2f PipeColumn::getSize(){
    return Vector2f(Toptex.getSize().x*TopPipe->getScale().x,Toptex.getSize().y*TopPipe->getScale().y);
};
void PipeColumn::Update(){
    PipeTBod->SetLinearVelocity(b2Vec2(-speed,0));
    PipeBBod->SetLinearVelocity(b2Vec2(-speed,0));
    TopPipe->setPosition(Vector2f(PipeTBod->GetPosition().x*scale,(PipeTBod->GetPosition().y*scale+(this->getSize().y/2))));
    BottomPipe->setPosition(Vector2f(PipeBBod->GetPosition().x*scale,(PipeBBod->GetPosition().y*scale-(this->getSize().y/2))));
}
float PipeColumn::getX(){
    return PipeTBod->GetPosition().x*scale;
}
void PipeColumn::ignoreBird(bool y){
    if(y){
        b2Filter newfilt;
        newfilt.groupIndex = 0x0004;
        newfilt.maskBits = 0xFFFF&~0x0002;
        PipeTBod->GetFixtureList()->SetFilterData(newfilt);
        PipeBBod->GetFixtureList()->SetFilterData(newfilt);
    }else{
        b2Filter newfilt;
        newfilt.groupIndex = 0x0004;
        newfilt.maskBits = 0xFFFF;
        PipeTBod->GetFixtureList()->SetFilterData(newfilt);
        PipeBBod->GetFixtureList()->SetFilterData(newfilt);
    }
}
PipeColumn::~PipeColumn(){
}