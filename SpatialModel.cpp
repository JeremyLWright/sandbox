#include "SpatialModel.h"
#include <iostream>
using namespace std;
using namespace SpatialDB;

SpatialModel* SpatialModel::_instance = 0;

SpatialModel::SpatialModel()
{
    cout << "Creating SpatialModel" << endl;
}

SpatialModel* SpatialModel::get_instance()
{
    if(_instance == 0)
        _instance = new SpatialModel();
    return _instance;
}

void SpatialModel::watch(const Region& region)
{
    cout << "DEBUG: Setting Watch on region: " << region.get_id() << endl;
}

list<Automaton>& SpatialModel::select(const Region& region)
{
    cout << "DEBUG: Fetching all Automatons within region: " << region.get_id() << endl;
    list<Automaton>* l = new list<Automaton>();
    return *l;
}

const Region& SpatialModel::create(const Point& A, const Point& B, const Point& C, const Point& D)
{
    cout << "DEBUG: Creating watch region." << endl;
    const Region* reg = new Region(0, A, B, C, D);
    return *reg;
}

Automaton& SpatialModel::create(const Point& origin)
{
    Automaton* aut = new Automaton(0, *this);
    cout << "DEBUG: Creating Automaton  "<< endl;
    return *aut;
}

list<Automaton>& SpatialModel::select(const Point& point)
{
    cout << "DEBUG: Fetching all Automatons at Point (" << point.X << ", " << point.Y << ")." << endl;
    list<Automaton>* l = new list<Automaton>();
    return *l;
}

void SpatialModel::update(Automaton& aut, const Point& point)
{
    
    cout << "Updating Automaton's Position" << endl;
}

const Point& SpatialModel::select(const Automaton& aut)
{
    cout << "Getching Automaton #" << aut.get_id() << "'s position." << endl;
    const Point* p = new Point(0,0);
    return *p;
}


