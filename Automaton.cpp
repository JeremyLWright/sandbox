#include "Automaton.h"

using namespace SpatialDB;

Automaton::Automaton(uint64_t id, SpatialModel& spatial_model)
{
    this->_spatial_model = &spatial_model;
    this->_spatial_id = id;
}

void SpatialDB::Automaton::update_location(const Point& next_position)
{
    this->_spatial_model->update(next_position);
}

const Point& SpatialDB::Automaton::get_location()
{
    return this->_spatial_model->select(*this);
}
