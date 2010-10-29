#include <iostream>
#include "SpatialModel.h"
using namespace SpatialDB;
using namespace std;
int main(void)
{
    SpatialModel* y = SpatialModel::get_instance();
    const Point* t = new Point(4,5);
    y->create(*t);
}
