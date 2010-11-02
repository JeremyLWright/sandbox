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
    \"AX\" INTEGER NOT NULL,\
    \"AY\" INTEGER NOT NULL,\
    \"BX\" INTEGER NOT NULL,\
    \"BY\" INTEGER NOT NULL,\
    \"CX\" INTEGER NOT NULL,\
    \"CY\" INTEGER NOT NULL,\
    \"DX\" INTEGER NOT NULL,\
    \"DY\" INTEGER NOT NULL)")
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

char* SpatialModel::query_create_region(const Point& A, const Point& B, const Point& C, const Point& D)
{
    char* query = new char[100];
    sprintf(query, "INSERT INTO 'Regions' ('AX', 'AY', 'BX', 'BY', 'CX', 'CY', 'DX', 'DY') VALUES ('%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d')", A.X, A.Y, B.X, B.Y, C.X, C.Y, D.X, D.Y);
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

    int r = sqlite3_exec(database_connection, 
                    query_create_region(A, B, C, D),
                    create_table_callback,
                    (void*)1,
                    &default_error_string);
    int y = sqlite3_last_insert_rowid(database_connection);
    Region* reg = new Region(y, *this);
    return *reg;
}

Automaton& SpatialModel::create(const Point& origin)
{
    int r = sqlite3_exec(database_connection, 
                    query_create_automaton(origin.X, origin.Y),
                    create_table_callback,
                    (void*)1,
                    &default_error_string);
    int y = sqlite3_last_insert_rowid(database_connection);
    Automaton* aut = new Automaton(y, *this);
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
    char* query = new char[100];
    sprintf(query, "UPDATE Automatons SET Loc_X=%d ,Loc_Y=%d WHERE Id=%ld", point.X, point.Y, aut.get_id());
    cout << "Query: " << query << endl;
    int r = sqlite3_exec(database_connection, query, create_table_callback, (void*)1, &default_error_string);
    if(r != 0)
        cout << default_error_string << endl;

}


const Point& SpatialModel::select(const Automaton& aut)
{
    cout << "Getching Automaton #" << aut.get_id() << "'s position." << endl;
    char* query = new char[100];
    sprintf(query, "SELECT Loc_X, Loc_Y FROM Automatons WHERE Id=%ld", aut.get_id());
    cout << "Query: " << query << endl;
    sqlite3_stmt* select_statement = 0; 
    int r = sqlite3_prepare(database_connection,
                            query,
                            -1,
                            &select_statement,
                            0);
    if(r == SQLITE_OK)
    {
        cout << "Statement Compiled" << endl;
        r = sqlite3_step(select_statement);
        if(r == SQLITE_ROW)
        {
            cout << "Statement executed." << endl;
            int x = sqlite3_column_int(select_statement, 0);
            int y = sqlite3_column_int(select_statement, 1);
            const Point* p = new Point(x,y);
            sqlite3_finalize(select_statement);
            return *p;
        }
    }


//TODO Fix this return                        
}


