#include "rand_comp.h"

const double RAND_MAX_D = RAND_MAX;

double get_rand(double t_b, double t_e)
{
    double time, t;
    
    t = rand() / RAND_MAX_D;
    
    time = (t_e - t_b) * t + t_b;
    
    return time;
}

int get_rand_range_int(const int min, const int max)
{
    return rand() % (max - min + 1) + min;
}

int compare_double(const void *p, const void *q)
{
    const double *a = p;
    const double *b = q;
    
    if (fabs(*a - *b) <= EPS)
        return 0;
    else if ((*a - *b) < EPS)
        return -1;
    else if ((*a - *b) > EPS)
        return 1;
    
    return 0;
}

unsigned long long tick(void)
{
    unsigned long long d;

    __asm__ __volatile__ ("rdtsc" : "=A" (d) );

    return d;
}
