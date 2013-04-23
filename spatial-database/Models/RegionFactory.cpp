#include "RegionFactory.h"
using namespace SpatialDB;

RegionFactory::RegionFactory()
{
    simulated_id = 0;
    this->_spatial_instance = SpatialModel::get_instance();
}

const Region& RegionFactory::get_region(Point A, Point B, Point C, Point D)
{
    //Create a region in the Spatial model, and return the created Region.
    return this->_spatial_instance->create(A, B, C, D);
}
