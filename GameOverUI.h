#include <SFML/Graphics.hpp>
#include "Button.h"
using namespace sf;
class UIgameover{
    private:
    RenderWindow*window;
    Font scoreStyle;
    Text * GameOver;
    Text * urscore;
    Text * replay;
    button * butt;
    RectangleShape * bg;
    public:
    UIgameover(RenderWindow&w);
    void draw();
    void setscore(int & score);
    bool replayclick();
};