#include <iostream>
#include "LemmingFactory.h"
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "RenderManager.h"
using namespace SpatialDB;
using namespace std;

enum {UP=1, DOWN, RIGHT, LEFT};
const int MOVE_CONSTANT = 3;

void move_lemmings()
{
    list<SpatialDB::Lemming>* lemmings = new list<SpatialDB::Lemming>();
    SpatialDB::SpatialModel::get_instance()->get_lemmings(*lemmings);
    for(list<SpatialDB::Lemming>::iterator lemming_itr = lemmings->begin();
        lemming_itr != lemmings->end();
        ++lemming_itr)
    {
        int direction = rand()%4+1;
        Point p = lemming_itr->get_location();
        switch(direction)
        {
            case UP:
                if(p.Y <= 0)
                    p.Y += MOVE_CONSTANT; //Move it DOWN instead
                else
                    p.Y -= MOVE_CONSTANT;
            break;
            case DOWN:
                if(p.Y >= 479)
                    p.Y -= MOVE_CONSTANT; //Move it UP instead
                else
                    p.Y += MOVE_CONSTANT;        
            break;
            case RIGHT:
                if(p.X >= 630)
                    p.X -= MOVE_CONSTANT; // Move it LEFT instead
                else
                    p.X += MOVE_CONSTANT;
            break;
            case LEFT:
                if(p.X <= 0)
                    p.X += MOVE_CONSTANT; //Move it RIGHT instead
                else
                    p.X -= MOVE_CONSTANT;
            break;
        }
        lemming_itr->update_location(p);
    }

}

void create_lemmings(int count)
{
    int initial_x = 0;
    int initial_y = 0;
    Point p = Point(initial_x, initial_y);
    LemmingFactory* atf = new LemmingFactory();
    for(;count > 0; --count)
    {

        Lemming& lemming = atf->get_lemming();
        lemming.update_location(p);
        initial_x = (initial_x + 10 % 640);
        initial_y = (initial_y + 10 % 480);
        p.X = initial_x;
        p.Y = initial_y;
    }
}

int main(void)
{
    srand(time(NULL));
    create_lemmings(10);
    RenderManager* r = new RenderManager();
    while(1) {
        if(r->close_requested == true)
            break;
        r->render_frame();
        move_lemmings();
        
    }
    return 0;
}
