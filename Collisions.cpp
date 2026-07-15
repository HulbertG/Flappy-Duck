#include "Collisions.h"
#include <string>
using std::string;
Collisions::Collisions(bool&a,bool&r){
    alive = &a;
    running = &r; 
}
void Collisions::BeginContact(b2Contact* contact){
    b2Fixture* a = contact->GetFixtureA();
    b2Fixture* b = contact->GetFixtureB();
    string * c = reinterpret_cast<string*>(a->GetBody()->GetUserData().pointer);
    string * d = reinterpret_cast<string*>(b->GetBody()->GetUserData().pointer);
    if(d&&c){
        if(*c=="bird"&&*d=="pipe"){
            *alive=false;
        }else if(*c=="pipe"&&*d=="bird"){
            *alive=false;
        }
        if(*c=="bird"&&*d=="ground"){
            *running=false;
            *alive=false;
        }else if(*c=="ground"&&*d=="bird"){
            *running=false;
            *alive=false;
        }
    }
}
void Collisions::EndContact(b2Contact* contact){

}