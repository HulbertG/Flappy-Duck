#include<SFML/Graphics.hpp>
#include<vector>
using namespace sf;
using std::vector;
struct element{
    Sprite * item;
    float speed;
};
struct stattex{
    bool hasinit;
    Texture texture;
};
class ambience{
    private:
    RenderWindow * window;
    static stattex grass;
    vector<element> elements;
    element creategrass(int xoffset);
    public:
    ambience(RenderWindow & w);
    void update();
    void draw();
};