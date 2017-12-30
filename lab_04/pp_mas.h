#ifndef _PP_MAS_H_
#define _PP_MAS_H_

#include <stdio.h>

#define QMAX 3000

struct queue
{
    int mas[QMAX];
    int head, tail;
    int cn;
} queue;

void init(struct queue *q);
int push(struct queue *q, int x);
int pop(struct queue *q, int *res);
void print(struct queue *q);

#endif // _PP_MAS_H_
