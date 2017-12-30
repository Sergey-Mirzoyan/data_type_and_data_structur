#ifndef _PP_LIST_H_
#define _PP_LIST_H_

#include <stdio.h>
#include <stdlib.h>

struct list
{
    int field;
    struct list *ptr;
};

struct address
{
    void *ad;
    struct address *next;
};

struct queue
{
    struct list *frnt, *rear;
    struct address *head_ad, *tail_ad;
    struct address *head_fr, *tail_fr;
};

void init(struct queue *q);
void push(struct queue *q, int x);
void print(struct queue *q);
int pop(struct queue *q, int *res);
int len_queue(struct queue *q);

void add_addr(struct queue *q, void *x, int flag);
void print_addr(struct queue *q, int flag);
int del_addr(struct queue *q, int flag);

#endif // _PP_LIST_H_
