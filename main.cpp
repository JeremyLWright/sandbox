#include <iostream>
#include "LemmingFactory.h"
#include <unistd.h>
#include "RenderManager.h"
using namespace SpatialDB;
using namespace std;

int main(void)
{
    SpatialModel* y = SpatialModel::get_instance();
    const Point* t = new Point(4,5);
    LemmingFactory* atf = new LemmingFactory();

    Lemming& a = atf->get_lemming();
    cout << "Created Lemming: " << a.get_id() << endl;
    RenderManager* r = new RenderManager();
    while(1) {
        if(r->close_requested == true)
            break;
        r->render_frame();
    }
    return 0;
}
