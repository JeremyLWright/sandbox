#include "Point.h"

using namespace SpatialDB;

Point::Point()
{
    this->X = 0;
    this->Y = 0;
}
Point::Point(int X,int Y)
{
    this->X = X;
    this->Y = Y;
}

namespace SpatialDB {
std::ostream& operator<<(std::ostream& out, const Point& obj)
{
    out << "(" << obj.X << "," << obj.Y << ")";
}
}
