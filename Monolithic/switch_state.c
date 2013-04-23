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

void run_machine()
{
    SandwichState_t s = REMOVE_BREAD;
    int sandwiches_to_eat = 3;
    int step_tick = 5; //First step takes 5 ticks
    while(s != DONE)
    {
        --step_tick;
        switch (s)
        {
            case REMOVE_BREAD:
                if(step_tick <= 0)
                {
                    step_tick = 2; //Next step takes 2 ticks...
                    s = SPREAD_PEANUT_BUTTER;
                }
                break;
            case SPREAD_PEANUT_BUTTER:
                if(step_tick <= 0)
                {
                    step_tick = 2;
                    s = SPREAD_JAM;
                }
                break;
            case SPREAD_JAM:
                if(step_tick <= 0)
                {
                    step_tick = 1;
                    s = PUT_HALVES_TOGETHER;
                }
                break;
            case PUT_HALVES_TOGETHER:
                if(step_tick <= 0)
                {
                    step_tick = 10;
                    s = EAT_SANDWICH;
                }
                break;
            case EAT_SANDWICH:
                if(step_tick <= 0 && sandwiches_to_eat <= 0) //We've eaten all sandwiches
                {
                    step_tick = 20;
                    s = GO_TO_WORK;
                }
                else if(step_tick <= 0) //We've eaten 1 more sandwich
                {
                    --sandwiches_to_eat;
                    step_tick = 10;
                    s = REMOVE_BREAD;
                }
                // else Continue eating current sandwich
                break;
            case GO_TO_WORK:
                if(step_tick <= 0)
                {
                    s = DONE;
                }
                break;
            case DONE:
                s = DONE;
                break;
        }
    }
}

