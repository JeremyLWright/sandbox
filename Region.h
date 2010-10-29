#ifndef _REGION_H
#define _REGION_H
#include "Point.h"
#include "stdint.h"
namespace SpatialDB {
    class Region {
        public:
            Region(uint64_t id, Point A, Point B, Point C, Point D);
            virtual ~Region();
        protected:
            uint64_t spatial_id;
    };
}
#endif
