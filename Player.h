#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <string>
using std::string;
using namespace sf;
class Player{
    private:
    const float scale = 60.0f;
    Texture flappy;
    Texture flappy2;
    Sprite * bird;
    int animstate;
    public:
    bool life;
    const string typeobj = "bird";
    Player(b2World & w);
    Sprite getSprite();
    b2Body* playerBody;
    void Update();
    Vector2f getSize();
};