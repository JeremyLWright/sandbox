
#ifndef SPATIALMODEL_H
#define SPATIALMODEL_H
#include "Point.h"
#include <list>
#include <string>
extern "C" {
#include "sqlite3.h"
}
using namespace std;
namespace SpatialDB {
    class Region;
    class Lemming;

    class SpatialModel {
        public: 
            static SpatialModel* get_instance(); 
            void watch(const Region& region);
            std::list<SpatialDB::Lemming>& select(const Region& region);
            const Region& create(const Point& A, const Point& B, const Point& C, const Point& D);
            Lemming& create(const Point& origin);
            std::list<Lemming>& select(const Point& point);
            void update(Lemming& aut, const Point& point);
            Point select(Lemming& aut);
            void get_lemmings(std::list<Lemming>&);
        protected:
            SpatialModel();
            char* query_create_lemming(int X, int Y);
            char* query_create_region(const Point& A, const Point& B, const Point& C, const Point& D);
            sqlite3* database_connection;
        private:
            static SpatialModel* _instance;
    };
}
#endif
