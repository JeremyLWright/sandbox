#include "gtest/gtest.h"
#include "AutomatonFactory.h"
using namespace SpatialDB;


class AutomatonTest: public testing::Test{
    protected:
    virtual void SetUp() {
        atf =new AutomatonFactory();
        a = &(atf->get_automaton());
        b = &(atf->get_automaton());
    }
    AutomatonFactory* atf;
    Automaton* a;
    Automaton* b;
};


TEST_F(AutomatonTest, AutomatonMovement)
{
    Point p = a->get_location();
    p.X++;
    p.Y--;
    a->update_location(p);
    Point u = a->get_location();
    EXPECT_EQ(p, u);
    
}
