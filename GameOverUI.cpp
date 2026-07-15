#include "GameOverUI.h"
#include <string>
using namespace std;
UIgameover::UIgameover(RenderWindow&w){
    window = &w;
    scoreStyle.loadFromFile("Font/Arcade.ttf");
    GameOver = new Text(scoreStyle);
    GameOver->setString("GAME OVER");
    GameOver->setScale(Vector2f(2.5f,3));
    GameOver->setFillColor(Color::White);
    GameOver->setOutlineColor(Color::Black);
    GameOver->setOutlineThickness(2);
    GameOver->setPosition(Vector2f(500-(GameOver->getGlobalBounds().width/2),100.0f));
    urscore = new Text(scoreStyle);
    urscore->setString("Your Score Was: ");
    urscore->setScale(Vector2f(.8f,.8f));
    urscore->setFillColor(Color::White);
    urscore->setOutlineColor(Color::Black);
    urscore->setOutlineThickness(2);
    urscore->setPosition(Vector2f(500-(GameOver->getGlobalBounds().width/2),250.0f));
    replay = new Text(scoreStyle);
    replay->setScale(Vector2f(.8f,.8f));
    replay->setFillColor(Color::White);
    replay->setOutlineColor(Color::Black);
    replay->setOutlineThickness(2);
    replay->setString("Play Again");
    replay->setPosition(Vector2f(500-(replay->getGlobalBounds().width/2),325));
    butt = new button(*replay,w);
    bg = new RectangleShape(Vector2f(450,200));
    bg->setOrigin(Vector2f(bg->getGlobalBounds().width/2,bg->getGlobalBounds().height/2));
    bg->setPosition(Vector2f(500,300));
    bg->setFillColor(Color{0XDED793ff});
}
void UIgameover::draw(){
    window->draw(*GameOver);
    window->draw(*bg);
    window->draw(*urscore);
    window->draw(*butt->tex);
}
void UIgameover::setscore(int & score){
    urscore->setString("Your Score Was: " + to_string(score));
    urscore->setPosition(Vector2f(500-(urscore->getGlobalBounds().width/2),urscore->getPosition().y));
}
bool UIgameover::replayclick(){
    if(butt->update()){
        return true;
    }else{
        return false;
    }
}