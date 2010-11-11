#include <iostream>
#include "LemmingFactory.h"
#include <unistd.h>
#include "main_view.h"
using namespace SpatialDB;
using namespace std;

int main(void)
{
    SpatialModel* y = SpatialModel::get_instance();
    const Point* t = new Point(4,5);
    LemmingFactory* atf = new LemmingFactory();

    Lemming& a = atf->get_lemming();
    cout << "Created Lemming: " << a.get_id() << endl;
    main_view();
   for(int i = 0; ; i++)
    {
        sleep(1);
         
        cout << "Lemming at: " << (a.get_location()) << endl;
        a.update_location(Point(0, i));
        
    }
    return 0;
}
