#include "Player.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <vector>
using json = nlohmann::json;
using namespace std;
Player::Player(b2World & w) : life(true){
    flappy.loadFromFile("sprites/flap2.png");
    flappy2.loadFromFile("sprites/flap2up.png");
    bird = new Sprite(flappy);
    bird->setScale(Vector2f(.12f,.09f));
    b2BodyDef bbody;
    bbody.type = b2_dynamicBody;
    bbody.position.Set(200.0f/scale, 300.0f/scale);
    bbody.userData.pointer = reinterpret_cast<uintptr_t>(&typeobj);
    playerBody = w.CreateBody(&bbody);
    //Auto Hitbox
    // b2PolygonShape hitBox;
    // hitBox.SetAsBox((this->getSize().x/2)/scale,(this->getSize().y/2)/scale);
    // b2FixtureDef playerFixtureDef;
    // playerFixtureDef.shape = &hitBox;
    // playerFixtureDef.density = 1.0f;
    // playerFixtureDef.filter.categoryBits = 0x0002;
    // playerBody->CreateFixture(&playerFixtureDef);
    //Hitbox defined by file
    json bodyfile{json::parse(ifstream("./sprites/Hitbox.json"))};
    vector<json> verts = bodyfile[0]["rigidBodies"][0]["polygons"].get<vector<json>>();
    for(int i=0;i<verts.size();i++){
        b2FixtureDef fixt;
        b2PolygonShape shapez;
        b2Vec2 * points = new b2Vec2[verts[i].size()];
        for(int v=0;v<verts[i].size();v++){
            points[v] = b2Vec2(((verts[i][v]["x"].get<float>()-.5f)*666.0f*.12f)/60.0f,(((verts[i][v]["y"].get<float>()-.35f)*666.0f*.09f))/60.0f);
        }
        shapez.Set(points,verts[i].size());
        fixt.shape = &shapez;
        fixt.density = 1.0f;
        fixt.filter.categoryBits = 0x0002;
        playerBody->CreateFixture(&fixt);
        delete points;
    }
    playerBody->SetFixedRotation(true);
    playerBody->SetAwake(false);
    bird->setOrigin(Vector2f(flappy.getSize().x/2,flappy.getSize().y/2));
    bird->setPosition(Vector2f(playerBody->GetPosition().x*scale,playerBody->GetPosition().y*scale));
    animstate = 0;
}
Sprite Player::getSprite(){
    return *bird;
}
void Player::Update(){
    if(life){
        animstate++;
        if(animstate==10){
                bird->setTexture(flappy2);
        }else if(animstate==20){
                bird->setTexture(flappy);
                animstate = 0;
        }
        if(playerBody->GetLinearVelocity().y<0.0f&&playerBody->GetAngle()>-b2_pi/8){
            playerBody->SetTransform(playerBody->GetPosition(),playerBody->GetAngle()-.1f);
        }
        else if(playerBody->GetLinearVelocity().y>0&&playerBody->GetAngle()<2*b2_pi/6){
            playerBody->SetTransform(playerBody->GetPosition(),playerBody->GetAngle()+.035f);
        }
    }
    bird->setPosition(Vector2f(playerBody->GetPosition().x*scale,playerBody->GetPosition().y*scale));
    bird->setRotation(radians(playerBody->GetAngle()));
}
Vector2f Player::getSize(){
    return Vector2f(bird->getTexture().getSize().x * bird->getScale().x, bird->getTexture().getSize().y * bird->getScale().y);
}