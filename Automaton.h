#ifndef AUTOMATON_H
#define AUTOMATON_H
#include <stdint.h>
#include "Point.h"
#include "SpatialModel.h"
namespace SpatialDB {
    class Automaton {
        public:
            Automaton(uint64_t id, SpatialModel& spatial_model);
            void update_location(const Point& next_position);
            const Point& get_location();
        protected:
            uint64_t _spatial_id;
            SpatialDB::SpatialModel* _spatial_model;
    };
}
#endif
