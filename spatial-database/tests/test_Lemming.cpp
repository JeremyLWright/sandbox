#include "gtest/gtest.h"
#include "LemmingFactory.h"
using namespace SpatialDB;


class LemmingTest: public testing::Test{
    protected:
    virtual void SetUp() {
        atf =new LemmingFactory();
        a = &(atf->get_lemming());
        b = &(atf->get_lemming());
    }
    LemmingFactory* atf;
    Lemming* a;
    Lemming* b;
};

/**
 * @test Creates a Lemming and verifies it move around.
 */
TEST_F(LemmingTest, LemmingMovement)
{
    Point p = a->get_location();
    p.X++;
    p.Y--;
    a->update_location(p);
    Point u = a->get_location();
    EXPECT_EQ(p, u);
    
}
