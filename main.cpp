#include <iostream>
#include "AutomatonFactory.h"
#include <unistd.h>
using namespace SpatialDB;
using namespace std;
int main(void)
{
    SpatialModel* y = SpatialModel::get_instance();
    const Point* t = new Point(4,5);
    AutomatonFactory* atf = new AutomatonFactory();

    Automaton& a = atf->get_automaton();
    cout << "Created Automaton: " << a.get_id() << endl;
   for(int i = 0; ; i++)
    {
        sleep(1);
         
        cout << "Automaton at: " << (a.get_location()) << endl;
        a.update_location(Point(0, i));
        
    }
    return 0;
}
