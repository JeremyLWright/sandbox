#include <time.h>
#include <stdio.h>

typedef int(*function_ptr)();
typedef struct _State {
    function_ptr f;
} State_t;

State_t s;
int g_update=0;

int done()
{
    ++g_update;
    return 0;
}

int go_to_work()
{
    ++g_update;
    s.f = done;
}

int eat_sandwich()
{
    ++g_update;
    s.f = go_to_work;
}

int put_halves_together()
{
    ++g_update;
    s.f = eat_sandwich;
}

int spread_jam()
{
    ++g_update;
    s.f = put_halves_together;
}

int spread_peanut_butter()
{
    ++g_update;
    s.f = spread_jam;
}

int remove_bread()
{
    ++g_update;
    s.f = spread_peanut_butter;
}

void run_machine()
{
    s.f = remove_bread;
    while(s.f != done)
    {
        s.f();
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

    printf("%ld %ld\n", t2.tv_sec - t1.tv_sec, t2.tv_nsec - t1.tv_nsec);



    return 0;
}
