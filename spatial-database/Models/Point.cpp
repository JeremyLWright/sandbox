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

bool Point::operator==(const Point& right) const
{
    if(this->X == right.X && this->Y == right.Y)
        return true;
    else
        return false;
}

namespace SpatialDB {
std::ostream& operator<<(std::ostream& out, const Point& obj)
{
    out << "(" << obj.X << "," << obj.Y << ")";
}
}
