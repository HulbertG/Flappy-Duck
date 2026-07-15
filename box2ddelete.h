#include <vector>
#include <box2d/box2d.h>
using std::vector;
static vector<b2Body*> todelete;
static void markdelete(b2Body*&b){
    todelete.push_back(b);
}
static void deletebodies(){
    if(todelete.size()>0){
        b2World* world = todelete[0]->GetWorld();
        if(!world->IsLocked()){
            for(int i=0;i<todelete.size();i++){
                todelete[i]->GetWorld()->DestroyBody(todelete[i]);
                todelete.erase(todelete.begin());
            }
        }
    }
}