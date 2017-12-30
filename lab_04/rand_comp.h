#ifndef _RAND_COMP_H_
#define _RAND_COMP_H_

#include <stdlib.h>
#include <time.h>
#include <math.h>

#define EPS 1e-3

double get_rand(double t_b, double t_e);
int get_rand_range_int(const int min, const int max);
int compare_double(const void *p, const void *q);
unsigned long long tick(void);

#endif // _RAND_COMP_H_
