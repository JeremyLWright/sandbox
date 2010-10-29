#ifndef _REGION_H
#define _REGION_H
#include "Point.h"
#include "stdint.h"

namespace SpatialDB {
    class SpatialModel;
    class Region {
        public:
            Region(uint64_t id, SpatialModel& model);
            ~Region();
            uint64_t get_id() const;
        protected:
            uint64_t _spatial_id;
            SpatialModel* _spatial_model;
    };
}
#endif
