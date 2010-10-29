#ifndef _REGION_H
#define _REGION_H
#include "Point.h"
#include "stdint.h"
namespace SpatialDB {
    class Region {
        public:
            Region(uint64_t id, const Point& A, const Point& B, const Point& C, const Point& D);
            ~Region();
            uint64_t get_id() const;
        protected:
            uint64_t _spatial_id;
            Point _A;
            Point _B;
            Point _C;
            Point _D;
    };
}
#endif
