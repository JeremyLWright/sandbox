#include <functional>
#include <stdio.h>
int done();
int remove_bread();

struct StateMachine {
    std::function<int(void)> f;
    StateMachine():
        f(remove_bread),
        finished(false)
    {
    }

    void run()
    {
        while(!finished)
        {
            this->f();
        }
    }
    bool finished;
};

StateMachine s;

int eat_sandwich();

int done()
{
    s.f = done;
    s.finished = true;
    return 0;
}

int go_to_work()
{
   static int tick = 20;
    --tick;
    if(tick <= 0)
    {
        tick = 20;
        s.f = done;
    }
    else
        s.f = go_to_work;
    return 0;
}

int put_halves_together()
{
    static int tick = 1;
    --tick;
    if(tick <= 0)
    {
        tick = 1;
        s.f = eat_sandwich;
    }
    else
        s.f = put_halves_together;
    return 0;
}

int spread_jam()
{
    static int tick = 2;
    --tick;
    if(tick <= 0)
    {
        tick = 2;
        s.f = put_halves_together;
    }
    else
        s.f = spread_jam;
    return 0;
}

int spread_peanut_butter()
{
    static int tick = 2;
    --tick;
    if(tick <= 0)
    {
        tick = 2;
        s.f = spread_jam;
    }
    else
        s.f = spread_peanut_butter;
    return 0;
}

int remove_bread()
{
     static int tick = 5;
    --tick;
    if(tick <= 0)
    {
        tick = 5; //reset this state;
        s.f = spread_peanut_butter;
    }
    else
        s.f = remove_bread;
    return 0;
}

int eat_sandwich()
{
    static int sandwiches_to_eat = 3;
    static int tick = 10;
    --tick;
    if(tick <= 0 && sandwiches_to_eat <= 0)
    {
        sandwiches_to_eat = 3;
        tick = 10;
        s.f = remove_bread;
    }
    else if(tick <= 0)
    {
        --sandwiches_to_eat;
        tick = 10;
        s.f = go_to_work;
    }
    else
        s.f = eat_sandwich;
    return 0;
}

extern "C" void run_machine()
{
    s.run();
}
