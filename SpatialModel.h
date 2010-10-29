
#ifndef SPATIALMODEL_H
#define SPATIALMODEL_H
#include "Point.h"
#include "Region.h"
#include "Automaton.h"
#include <list>
#include <string>
extern "C" {
#include "sqlite3.h"
}
using namespace std;
namespace SpatialDB {
    class SpatialModel {
        public: 
            static SpatialModel* get_instance(); 
            void watch(const Region& region);
            std::list<SpatialDB::Automaton>& select(const Region& region);
            const Region& create(const Point& A, const Point& B, const Point& C, const Point& D);
            Automaton& create(const Point& origin);
            std::list<Automaton>& select(const Point& point);
            void update(Automaton& aut, const Point& point);
            const Point& select(const Automaton& aut);
        protected:
            SpatialModel();
            char* query_create_automaton(int X, int Y);
            char* query_create_region(const Point& A, const Point& B, const Point& C, const Point& D);
            sqlite3* database_connection;
        private:
            static SpatialModel* _instance;
    };
}
#endif
