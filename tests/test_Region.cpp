#include "gtest/gtest.h"
#include "RegionFactory.h"
#include "LemmingFactory.h"
using namespace SpatialDB;

class RegionTest : public testing::Test {
    protected:
    virtual void SetUp() {
        rf = new RegionFactory();
    }
    RegionFactory* rf;

};

TEST_F(RegionTest, CreateRegion)
{
    const Region& unit_square = rf->get_region(Point(1,0), Point(1,1), Point(0,1), Point(0,0));
}

/*
5 . . . . . . .
4 . - - - - - . 
3 . | A . A | .
2 . | . A . | . 
1 . - - - - - .
0 . . . . . . .
  0 1 2 3 4 5 6 
*/
TEST_F(RegionTest, SelectRegion)
{
    LemmingFactory& atf = *(new LemmingFactory());
    Lemming& A1 = atf.get_lemming();
    A1.update_location(Point(3,2));
    Lemming& A2 = atf.get_lemming();
    A2.update_location(Point(3,2));
    Lemming& A3 = atf.get_lemming();
    A3.update_location(Point(4,3));

    Point A = Point(1,4);
    Point B = Point(5,4);
    Point C = Point(5,1);
    Point D = Point(1,1);

    const Region& test_region = rf->get_region(A, B, C, D);
    std::list<Lemming>& atom_list = test_region.select();
    EXPECT_EQ(atom_list.size(), 3);
}
