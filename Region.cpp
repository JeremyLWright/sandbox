#include "Region.h"

using namespace SpatialDB;

Region::Region(uint64_t id, SpatialModel& model)
{
    _spatial_id = id;
    _spatial_model = &model;
}

uint64_t Region::get_id() const
{
    return _spatial_id;
}
