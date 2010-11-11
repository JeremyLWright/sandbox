#include "Lemming.h"
#include "SpatialModel.h"
using namespace SpatialDB;

Lemming::Lemming(uint64_t id, SpatialModel& spatial_model)
{
    this->_spatial_model = &spatial_model;
    this->_spatial_id = id;
}

void SpatialDB::Lemming::update_location(const Point& next_position)
{
    this->_spatial_model->update((*this), next_position);
}

const Point& SpatialDB::Lemming::get_location()
{
    return this->_spatial_model->select(*this);
}

uint64_t SpatialDB::Lemming::get_id() const
{
    return _spatial_id;
}
namespace SpatialDB {
bool operator==(const Lemming& left, const Lemming& right)
{
    if(left.get_id() == right.get_id())
        return true;
    else
        return false;
}
}
