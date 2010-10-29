#include <iostream>
#include "SpatialModel.h"
using namespace SpatialDB;
using namespace std;
int main(void)
{
    SpatialModel* y = SpatialModel::get_instance();
    const Point* t = new Point(4,5);
    for(int i = 0 ; i < 100 ; i++)
        y->create(*t);
/*    for(int i = 0; i < 10 ; i++)
        y->create(*t,*t,*t,*t);*/
    return 0;
}
