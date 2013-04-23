#include "RenderManager/RenderManager.h"
#include <thread>
#include <functional>
#include <map>
#include <string>
#include <iostream>
using namespace std;
extern map<string, function<void(int)>> scriptInterface;
extern int yyparse();

int main(int argc, const char *argv[])
{
    RenderManager rm;
    scriptInterface["select"] = bind(&RenderManager::selectShip, &rm, placeholders::_1);
    scriptInterface["unselect"] = bind(&RenderManager::unSelectShip, &rm, placeholders::_1);
    scriptInterface["accel"] = bind(&RenderManager::acclShip, &rm, placeholders::_1);
    scriptInterface["turn"] = bind(&RenderManager::turnShip, &rm, placeholders::_1);

    bool sdlCloseEvent = false;
    auto tid = std::thread(yyparse);
    
    do
    {
        sdlCloseEvent = rm.render_frame();
    } while(!sdlCloseEvent);
    tid.join();
    return 0;
}
