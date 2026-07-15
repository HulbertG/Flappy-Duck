#include <SFML/Graphics.hpp>
using namespace sf;
class button{
    private:
    RenderWindow * win;
    public:
    Text * tex;
    button(Text & t,RenderWindow & w);
    bool update();
};