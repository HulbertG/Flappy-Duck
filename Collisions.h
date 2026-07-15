#include <box2d/box2d.h>
class Collisions:public b2ContactListener{
    private:
    bool*alive;
    bool*running;
    public:
    Collisions(bool&a,bool&r);
    void BeginContact(b2Contact* contact);
    void EndContact(b2Contact* contact);
};