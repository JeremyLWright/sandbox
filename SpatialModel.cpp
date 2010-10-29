#include "SpatialModel.h"
#include <iostream>
#include <sstream>
#include <cstdio>
using namespace std;
using namespace SpatialDB;

SpatialModel* SpatialModel::_instance = 0;

extern "C" {
    int create_table_callback(void* i, int j, char** k, char** l)
    {
        cout << j << endl << k << endl << l << endl;
        return 0;
    }
    char* default_error_string;
}

#define CREATE_TABLE_REGIONS_QUERY ("CREATE VIRTUAL TABLE \"Regions\" USING rtree (\
    \"Id\" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,\
    \"Max_X\" INTEGER NOT NULL,\
    \"Max_Y\" INTEGER NOT NULL,\
    \"Min_X\" INTEGER NOT NULL,\
    \"Min_Y\" INTEGER NOT NULL)")
#define CREATE_TABLE_AUTOMATONS_QUERY "CREATE TABLE \"Automatons\"\
( \
\"Id\" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,\
\"Loc_X\" INTEGER NOT NULL,\
\"Loc_Y\" INTEGER NOT NULL)"


char* SpatialModel::query_create_automaton(int X, int Y)
{
    char* query = new char[100];
    sprintf(query, "INSERT INTO 'Automatons' ('Loc_X', 'Loc_Y') VALUES ('%d','%d')", X, Y);
    return query;

}

SpatialModel::SpatialModel()
{
    cout << "Creating SpatialModel" << endl;
    int r = sqlite3_open("world_view.db", &database_connection);
    if(r == 0)
        cout << "DB Creation Success." << endl;
    else
        cout << "DB Creation Failed. " << endl;
    
    /* Initialize the database object */
    r = sqlite3_exec(database_connection, 
                    CREATE_TABLE_REGIONS_QUERY,
                    create_table_callback,
                    (void*)1,
                    &default_error_string);
    if(r == 0)
        cout << "Table created Successfully" << endl;
    else
        cout << default_error_string << endl;
    r = sqlite3_exec(   database_connection,
                        CREATE_TABLE_AUTOMATONS_QUERY,
                        create_table_callback,
                        (void*)1,
                        &default_error_string);
    if(r == 0)
        cout << "Table created Successfully" << endl;
    else
        cout << default_error_string << endl;
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
    int r = sqlite3_exec(database_connection, 
                    query_create_automaton(origin.X, origin.Y),
                    create_table_callback,
                    (void*)1,
                    &default_error_string);
    if(r == 0)
        cout << "Automaton created Successfully" << endl;
    else
        cout << default_error_string << endl;
    int y = sqlite3_last_insert_rowid(database_connection);
    Automaton* aut = new Automaton(y, *this);
    cout << "DEBUG: Creating Automaton  "<< y << endl;
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


