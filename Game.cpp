#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "Player.h"
#include "PipeColumn.h"
#include <time.h>
#include <cstdio>
#include "Collisions.h"
#include "GameOverUI.h"
#include "Ambience.h"
#include <fstream>
using namespace std;
using namespace sf;
int main(){
    RenderWindow frame(VideoMode({1000,600}),"Flappy Duck",Style::Default);
    frame.setFramerateLimit(60);
    b2Vec2 gravity(0.0f,23.8f);
    b2World world(gravity);
    int highscore = 0;
    ifstream hsfile("./score.flapp");
    string line;
    if(hsfile.is_open()){
        while(getline(hsfile,line)){
            highscore = stoi(line);
        }
        hsfile.close();
    }else{
        ofstream newfile("./score.flapp");
        newfile << 0;
        newfile.close();
    }
    //flappy.loadFromFile("C:\\Users\\gageh\\Documents\\Bored Coding\\FlappyDuck\\sprites/Flappy.png");
    Player bird(world);
    ambience amb(frame);
    bool hasflap = false;
    // RectangleShape outline(Vector2f(bird.getSize().x,bird.getSize().y));
    // outline.setOrigin(Vector2f(outline.getSize().x/2,outline.getSize().y/2));
    // outline.setPosition(Vector2f(bird.playerBody->GetPosition().x, bird.playerBody->GetPosition().y));
    // outline.setFillColor(Color::Black);
    float SCALE = 60.0f;
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(500.0f / SCALE, 600.0f / SCALE);
    const string groundobj = "ground";
    groundBodyDef.userData.pointer = reinterpret_cast<uintptr_t>(&groundobj);
    b2Body* groundBody = world.CreateBody(&groundBodyDef);
    b2PolygonShape groundBox;
    groundBox.SetAsBox(600.0f / SCALE, 25.0f / SCALE);
    groundBody->CreateFixture(&groundBox, 0.0f);
    b2Filter newfilt = groundBody->GetFixtureList()->GetFilterData();
    newfilt.categoryBits = 0x0008;
    newfilt.maskBits = 0xFFFF & ~0x0004;
    groundBody->GetFixtureList()->SetFilterData(newfilt);
    b2BodyDef skybox;
    const string skyobj = "pipe";
    skybox.position.Set(500/SCALE,0);
    skybox.userData.pointer = reinterpret_cast<uintptr_t>(&skyobj);
    b2Body * skybody = world.CreateBody(&skybox);
    b2PolygonShape skyhitbox;
    skyhitbox.SetAsBox(600/SCALE,5/SCALE);
    b2FixtureDef skyfix;
    skyfix.shape=&skyhitbox;
    skyfix.density = 0;
    skyfix.filter.categoryBits = 0x0004;
    skyfix.filter.maskBits = 0x0002;
    skybody->CreateFixture(&skyfix);
    vector<PipeColumn> columns;
    PipeColumn firstrow(world);
    columns.push_back(firstrow);
    Font scoreStyle;
    scoreStyle.loadFromFile("Font/Arcade.ttf");
    Text scoreboard(scoreStyle);
    scoreboard.setFillColor(Color::White);
    scoreboard.setOutlineColor(Color::Black);
    scoreboard.setOutlineThickness(2.5f);
    scoreboard.setString("0");
    scoreboard.setScale(Vector2f(1.5,1.5));
    scoreboard.setPosition(Vector2f(500-scoreboard.getGlobalBounds().width/2,50));
    int score = 0;
    Text highscoreboard(scoreStyle);
    highscoreboard.setFillColor(Color::White);
    highscoreboard.setOutlineColor(Color::Black);
    highscoreboard.setOutlineThickness(2.5f);
    string highscoretxt = "Highscore: "+to_string(highscore);
    highscoreboard.setString(highscoretxt);
    highscoreboard.setScale(Vector2f(.8f,.8f));
    highscoreboard.setPosition(Vector2f(500-highscoreboard.getGlobalBounds().width/2,100));
    //Game OVER
    UIgameover GameOver(frame);
    //
    bool running = false;
    bool alive = true;
    Collisions listener(alive,running);
    world.SetContactListener(&listener);
    srand(time(NULL));
    while (frame.isOpen())
    {
        Event event;
        while (frame.pollEvent(event))
        {
            if (event.type == Event::Closed)
                frame.close();
            if(event.type==Event::KeyPressed&&!running&&alive){
                if(event.key.code==Keyboard::Key::Space){
                    running=true;
                }
            }
            if(event.type == Event::KeyReleased){
                if(event.key.code==Keyboard::Key::Space)
                hasflap = false;
            }
        }
        frame.clear(Color{0X87CEEB});
        if(running){
            if(Keyboard::isKeyPressed(Keyboard::Key::Space)&&!hasflap&&alive){
                bird.playerBody->SetLinearVelocity(b2Vec2(0.0f,-8.2f));
                hasflap=true;
            }
            //time_t newtime = time(NULL);
            //difftime was old time function
            if(columns[columns.size()-1].getX()<=750){
                //lasttime = time(NULL);
                PipeColumn newrow(world,(rand()%300)-150);
                columns.push_back(newrow);
            }
            if(columns[0].getX()<=-100){
                world.DestroyBody(columns[0].PipeBBod);
                world.DestroyBody(columns[0].PipeTBod);
                columns.erase(columns.begin());
            }
            if(alive){
                amb.update();
                for(auto pipes:columns){
                    pipes.Update();
                }
                for(int i=0;i<columns.size();i++){
                    if(columns[i].getX()<=bird.playerBody->GetPosition().x*SCALE&&columns[i].haspoint){
                        columns[i].haspoint=false;
                        score++;
                        scoreboard.setString(to_string(score));
                    }
                }
            }else{
                for(auto pipes:columns){
                    pipes.ignoreBird(true);
                    pipes.PipeBBod->SetLinearVelocity(b2Vec2(0.0f,0.0f));
                    pipes.PipeTBod->SetLinearVelocity(b2Vec2(0.0f,0.0f));
                }
            }
        }else if(!running&&!alive){
            bird.life = false;
            GameOver.setscore(score);
            for(auto pipes:columns){
                    pipes.ignoreBird(true);
                    pipes.PipeBBod->SetLinearVelocity(b2Vec2(0.0f,0.0f));
                    pipes.PipeTBod->SetLinearVelocity(b2Vec2(0.0f,0.0f));
            }
            if(score>highscore){
                highscore=score;
                ofstream newscore("./score.flapp");
                newscore<<highscore;
                newscore.close();
                highscoretxt = "Highscore: "+to_string(highscore);
                highscoreboard.setString(highscoretxt);
            }
        }
        else{
            bird.playerBody->SetAwake(false);
        }
        world.Step(1.0f / 60.0f, 8, 3);
        for(int i=0;i<columns.size();i++){
            for(auto p:columns[i].getSprites()){
                frame.draw(p);
            }
        }
        amb.draw();
        bird.Update();
        frame.draw(bird.getSprite());
        //frame.draw(outline);
        
        if(running)
        frame.draw(scoreboard);
        if(!running&&alive)
        frame.draw(highscoreboard);
        if(!running&&!alive){
            GameOver.draw();
            if(GameOver.replayclick()){
                bird.life = true;
                alive = true;
                bird.playerBody->SetTransform(b2Vec2(200.0f/SCALE, 300.0f/SCALE),0);
                score = 0;
                scoreboard.setString("0");
                for(auto c:columns){
                    world.DestroyBody(c.PipeBBod);
                    world.DestroyBody(c.PipeTBod);
                }
                columns.clear();
                PipeColumn firstrow(world);
                columns.push_back(firstrow);
            }
        }
        // RectangleShape toppipeme;
        // toppipeme.setSize(Vector2f(newrow.getSize().x,newrow.getSize().y));
        // toppipeme.setOrigin(Vector2f(newrow.getSize().x/2,newrow.getSize().y/2));
        // toppipeme.setPosition(Vector2f(newrow.PipeTBod->GetPosition().x*SCALE,newrow.PipeTBod->GetPosition().y*SCALE));
        // toppipeme.setFillColor(Color::Black);
        // frame.draw(toppipeme);
        frame.display();
    }
    return 0;
}