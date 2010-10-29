#include "Region.h"

using namespace SpatialDB;

Region::Region(uint64_t id,const Point& A, const Point& B, const Point& C, const Point& D)
{
    _A = A;
    _B = B;
    _C = C;
    _D = D;
    _spatial_id = id;
}

uint64_t Region::get_id() const
{
    return _spatial_id;
}
