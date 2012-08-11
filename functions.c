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


int g_update=0;
#define DO_SOMETHING() do_something()
void do_something()
{
    ++g_update;
    return;
}


void run_machine()
{
    SandwichState_t s = REMOVE_BREAD;
    while(s != DONE)
    {
        switch (s)
        {
            case REMOVE_BREAD:
                s = SPREAD_PEANUT_BUTTER;
                DO_SOMETHING();
                break;
            case SPREAD_PEANUT_BUTTER:
                s = SPREAD_JAM;
                DO_SOMETHING();
                break;
            case SPREAD_JAM:
                s = PUT_HALVES_TOGETHER;
                DO_SOMETHING();
                break;
            case PUT_HALVES_TOGETHER:
                s = EAT_SANDWICH;
                DO_SOMETHING();
                break;
            case EAT_SANDWICH:
                DO_SOMETHING();
                s = GO_TO_WORK;
                break;
            case GO_TO_WORK:
                DO_SOMETHING();
                s = DONE;
                break;
        }
    }
}

int main(int argc, const char *argv[])
{
    int i = 0;
    struct timespec t1;
    struct timespec t2;

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &t1);
    while(i++ < 1000000)
    {
        run_machine();
    }
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &t2);

    printf("%d %d\n", t2.tv_sec - t1.tv_sec, t2.tv_nsec - t1.tv_nsec);



    return 0;
}
