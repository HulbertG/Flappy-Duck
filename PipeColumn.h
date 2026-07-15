#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <vector>
using namespace sf;
using namespace std;
class PipeColumn{
    private:
        float scale = 60.0f;
        Sprite * TopPipe;
        Sprite * BottomPipe;
        static Texture Toptex;
        static Texture Bottomtex;
        static bool hasload;
        float speed = 5.0f;
    public:
        string typeobj = "pipe";
        bool haspoint;
        b2Body * PipeBBod;
        b2Body * PipeTBod;
        PipeColumn(b2World & w,float horiz);
        PipeColumn(b2World & w);
        vector<Sprite> getSprites();
        Vector2f getSize();
        void Update();
        float getX();
        void ignoreBird(bool y);
        ~PipeColumn();
};