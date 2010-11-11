#ifndef REGION_FACTORY_H
#define REGION_FACTORY_H
#include "Region.h"
#include "Point.h"
#include "SpatialModel.h"
namespace SpatialDB {
    class RegionFactory {
        public: 
            RegionFactory();
            ~RegionFactory();
            const Region& get_region(Point A, Point B, Point C, Point D);
        protected:
            SpatialModel* _spatial_instance;
            uint64_t simulated_id;
    };
            
}
#endif
