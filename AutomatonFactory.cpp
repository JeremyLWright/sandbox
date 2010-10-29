#include <AutomatonFactory.h>
using namespace SpatialDB;

AutomatonFactory::AutomatonFactory()
{
    this->_simulated_id = 0;
    
    _spatial_model = SpatialModel::get_instance();
}

Automaton& AutomatonFactory::get_automaton()
{
    const Point* p = new Point(0,0);
    Automaton& aut = _spatial_model->create(*p);
    return aut;
}
