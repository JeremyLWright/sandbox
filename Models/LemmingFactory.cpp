#include <LemmingFactory.h>
using namespace SpatialDB;

LemmingFactory::LemmingFactory()
{
    this->_simulated_id = 0;
    
    _spatial_model = SpatialModel::get_instance();
}

Lemming& LemmingFactory::get_lemming()
{
    const Point* p = new Point(0,0);
    Lemming& aut = _spatial_model->create(*p);
    return aut;
}
