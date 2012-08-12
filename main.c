#include <time.h>
#include <stdio.h>
void run_machine();


int main(int argc, const char *argv[])
{
    int i = 1000;
    struct timespec t1;
    struct timespec t2;

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &t1);
    while(--i)
    {
        run_machine();
    }
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &t2);

    printf("%ld %ld\n", t2.tv_sec - t1.tv_sec, t2.tv_nsec - t1.tv_nsec);



    return 0;
}
