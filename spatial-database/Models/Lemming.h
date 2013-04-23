#ifndef AUTOMATON_H
#define AUTOMATON_H
#include <stdint.h>
#include "Point.h"
namespace SpatialDB {
    class SpatialModel;
    class Lemming {
        public:
            Lemming(uint64_t id, SpatialModel& spatial_model);
            void update_location(const Point& next_position);
            Point get_location();
            uint64_t get_id() const;
            friend bool operator==(const Lemming& left, const Lemming& right);
        protected:
            uint64_t _spatial_id;
            SpatialDB::SpatialModel* _spatial_model;
    };
}
#endif
