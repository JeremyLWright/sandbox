#include <time.h>
#include <stdio.h>

typedef enum {
    REMOVE_BREAD,
    SPREAD_PEANUT_BUTTER,
    SPREAD_JAM,
    PUT_HALVES_TOGETHER,
    EAT_SANDWICH,
    GO_TO_WORK,
    DONE
} SandwichState_t;

SandwichState_t go_to_work_process()
{
    static int tick = 20;
    --tick;
    if(tick <= 0)
    {
        return DONE;
    }
    return GO_TO_WORK;
}

SandwichState_t done_process()
{
    return DONE;
}

SandwichState_t eat_sandwich_process()
{
    static int sandwiches_to_eat = 3;
    static int tick = 10;
    --tick;
    if(tick <= 0 && sandwiches_to_eat <= 0)
    {
        sandwiches_to_eat = 3;
        tick = 10;
        return REMOVE_BREAD;
    }
    else if(tick <= 0)
    {
        --sandwiches_to_eat;
        tick = 10;
        return GO_TO_WORK;
    }
    return EAT_SANDWICH;
}

SandwichState_t spread_peanut_butter_process()
{
    static int tick = 2;
    --tick;
    if(tick <= 0)
    {
        tick = 2;
        return SPREAD_JAM;
    }
    return SPREAD_PEANUT_BUTTER;
}

SandwichState_t spread_jam_process()
{
    static int tick = 2;
    --tick;
    if(tick <= 0)
    {
        tick = 2;
        return PUT_HALVES_TOGETHER;
    }
    return SPREAD_JAM;
}

SandwichState_t put_halves_together_process()
{
    static int tick = 1;
    --tick;
    if(tick <= 0)
    {
        tick = 1;
        return EAT_SANDWICH;
    }
    return PUT_HALVES_TOGETHER;
}

SandwichState_t remove_bread_process()
{
    static int tick = 5;
    --tick;
    if(tick <= 0)
    {
        tick = 5; //reset this state;
        return SPREAD_PEANUT_BUTTER;
    }
    return REMOVE_BREAD;
}

void run_machine()
{
    SandwichState_t s = REMOVE_BREAD;
    while(s != DONE)
    {
        //printf("State is: %d", s);
        switch (s)
        {
            case REMOVE_BREAD:
                s = remove_bread_process();
                break;
            case SPREAD_PEANUT_BUTTER:
                s = spread_peanut_butter_process();
                break;
            case SPREAD_JAM:
                s = spread_jam_process();
                break;
            case PUT_HALVES_TOGETHER:
                s = put_halves_together_process();
                break;
            case EAT_SANDWICH:
                s = eat_sandwich_process();
                break;
            case GO_TO_WORK:
                s = go_to_work_process();
                break;
            case DONE:
                s = done_process();
                break;
        }
    }
}

