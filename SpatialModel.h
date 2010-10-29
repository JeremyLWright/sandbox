#ifndef SPATIALMODEL_H
#define SPATIALMODEL_H
#include "Point.h"
#include "Region.h"
#include <list>
namespace SpatialDB {
    class Automaton;
    class Region;
    class SpatialModel {
        public: 
            static SpatialModel& get_instance(); 
            void watch(const Region& region);
            std::list<SpatialDB::Automaton> select(const Region& region);
            const Region& create(const Point& A, const Point& B, const Point& C, const Point& D);
            void update(const Region& region);
            
            void watch(const Point& point);
            Automaton& create(const Point& point);
            std::list<Automaton> select(const Point& point);
            void update(const Point& point);

            const Point& select(const Automaton& automaton);
        protected:
            static SpatialModel _instance;
            SpatialModel();
            int database_connection;
    };
}
#endif
