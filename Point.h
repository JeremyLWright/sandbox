#ifndef _POINT_H
#define _POINT_H
#include <iostream>
namespace SpatialDB {
    class Point {
        public:
        Point();
        Point( int X, int Y);
        int X;
        int Y;
        friend std::ostream& operator<<(std::ostream& out, const Point& obj);
        bool operator==(const Point& right) const;
    };
}
#endif
