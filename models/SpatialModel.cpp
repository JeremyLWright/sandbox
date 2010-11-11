#include "SpatialModel.h"
#include <iostream>
#include <sstream>
#include <cstdio>
#include "Region.h"
#include "Lemming.h"

using namespace std;
using namespace SpatialDB;

SpatialModel* SpatialModel::_instance = 0;

extern "C" {
    int create_table_callback(void* i, int j, char** k, char** l)
    {
        return 0;
    }
    char* default_error_string;
}

#define CREATE_TABLE_REGIONS_QUERY ("CREATE TABLE \"Regions\"  (\
    \"Id\" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,\
    \"AX\" INTEGER NOT NULL,\
    \"AY\" INTEGER NOT NULL,\
    \"BX\" INTEGER NOT NULL,\
    \"BY\" INTEGER NOT NULL,\
    \"CX\" INTEGER NOT NULL,\
    \"CY\" INTEGER NOT NULL,\
    \"DX\" INTEGER NOT NULL,\
    \"DY\" INTEGER NOT NULL)")
#define CREATE_TABLE_AUTOMATONS_QUERY "CREATE TABLE \"Lemmings\" \
( \
\"Id\" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,\
\"Loc_X\" INTEGER NOT NULL,\
\"Loc_Y\" INTEGER NOT NULL)"


char* SpatialModel::query_create_lemming(int X, int Y)
{
    char* query = new char[100];
    sprintf(query, "INSERT INTO 'Lemmings' ('Loc_X', 'Loc_Y') VALUES ('%d','%d')", X, Y);
    return query;

}

char* SpatialModel::query_create_region(const Point& A, const Point& B, const Point& C, const Point& D)
{
    char* query = new char[150];
    sprintf(query, "INSERT INTO 'Regions' ('AX', 'AY', 'BX', 'BY', 'CX', 'CY', 'DX', 'DY') VALUES ('%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d')", A.X, A.Y, B.X, B.Y, C.X, C.Y, D.X, D.Y);
    return query;
}

SpatialModel::SpatialModel()
{
    int r = sqlite3_open("", &database_connection);
    
    /* Initialize the database object */
    r = sqlite3_exec(database_connection, 
                    CREATE_TABLE_REGIONS_QUERY,
                    create_table_callback,
                    (void*)1,
                    &default_error_string);
    r = sqlite3_exec(   database_connection,
                        CREATE_TABLE_AUTOMATONS_QUERY,
                        create_table_callback,
                        (void*)1,
                        &default_error_string);
}

SpatialModel* SpatialModel::get_instance()
{
    if(_instance == 0)
        _instance = new SpatialModel();
    return _instance;
}

void SpatialModel::watch(const Region& region)
{
}

list<Lemming>& SpatialModel::select(const Region& region)
{
    list<Lemming>* l = new list<Lemming>();
    char* query = new char[200];
    Point A = Point();
    Point B = Point();
    Point C = Point();
    // Fetch Regions Points from the database
    sprintf(query, "SELECT AX, BX, CY, AY FROM Regions WHERE Id=%lu", region.get_id()); 
    sqlite3_stmt* select_statement = 0;
    sqlite3_stmt* stmt2 = 0;
    int r = sqlite3_prepare(database_connection,
                            query,
                            -1,
                            &select_statement,
                            0);

    delete query;
    if(r == SQLITE_OK)
    {
        r = sqlite3_step(select_statement);
        
        if(r == SQLITE_DONE || r == SQLITE_ROW)
        {
            A.X = sqlite3_column_int(select_statement, 0);
            B.X = sqlite3_column_int(select_statement, 1);
            C.Y = sqlite3_column_int(select_statement, 2);
            A.Y = sqlite3_column_int(select_statement, 3);
        
        }
        sqlite3_finalize(select_statement);
    }

    char* query2 = new char[300];
    //Create the Region bounding query
    sprintf(query, "SELECT Id FROM Lemmings WHERE (Loc_X >= %d AND Loc_X <= %d AND Loc_Y >= %d AND Loc_Y <= %d)", A.X, B.X, C.Y, A.Y);
    r = sqlite3_prepare(database_connection,
                            query2,
                            -1,
                            &stmt2,
                            0);
    if(r == SQLITE_OK)
    { 
        do{
            r = sqlite3_step(stmt2);
            int id = sqlite3_column_int(stmt2, 0);
            if( r == SQLITE_ROW){
            Lemming* a = new Lemming(id, *this);
            l->push_back(*a);    
            }
        } while(r == SQLITE_ROW);
        sqlite3_finalize(stmt2);
    }

    //Fetch all the Lemmings from the database withint the bounded region.

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

Lemming& SpatialModel::create(const Point& origin)
{
    int r = sqlite3_exec(database_connection, 
                    query_create_lemming(origin.X, origin.Y),
                    create_table_callback,
                    (void*)1,
                    &default_error_string);
    int y = sqlite3_last_insert_rowid(database_connection);
    Lemming* aut = new Lemming(y, *this);
    return *aut;
}

list<Lemming>& SpatialModel::select(const Point& point)
{
    list<Lemming>* l = new list<Lemming>();
    return *l;
}

void SpatialModel::update(Lemming& aut, const Point& point)
{
    
    char* query = new char[100];
    sprintf(query, "UPDATE Lemmings SET Loc_X=%d ,Loc_Y=%d WHERE Id=%lu", point.X, point.Y, aut.get_id());
    int r = sqlite3_exec(database_connection, query, create_table_callback, (void*)1, &default_error_string);

}


const Point& SpatialModel::select(const Lemming& aut)
{
    char* query = new char[100];
    sprintf(query, "SELECT Loc_X, Loc_Y FROM Lemmings WHERE Id=%lu", aut.get_id());
    sqlite3_stmt* select_statement = 0; 
    int r = sqlite3_prepare(database_connection,
                            query,
                            -1,
                            &select_statement,
                            0);
    if(r == SQLITE_OK)
    {
        r = sqlite3_step(select_statement);
        if(r == SQLITE_ROW)
        {
            int x = sqlite3_column_int(select_statement, 0);
            int y = sqlite3_column_int(select_statement, 1);
            const Point* p = new Point(x,y);
            sqlite3_finalize(select_statement);
            return *p;
        }
    }


//TODO Fix this return statement.                    
}


