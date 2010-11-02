#include "Automaton.h"
#include "SpatialModel.h"
using namespace SpatialDB;

Automaton::Automaton(uint64_t id, SpatialModel& spatial_model)
{
    this->_spatial_model = &spatial_model;
    this->_spatial_id = id;
}

void SpatialDB::Automaton::update_location(const Point& next_position)
{
    this->_spatial_model->update((*this), next_position);
}

const Point& SpatialDB::Automaton::get_location()
{
    return this->_spatial_model->select(*this);
}

uint64_t SpatialDB::Automaton::get_id() const
{
    return _spatial_id;
}
namespace SpatialDB {
bool operator==(const Automaton& left, const Automaton& right)
{
    if(left.get_id() == right.get_id())
        return true;
    else
        return false;
}
}
