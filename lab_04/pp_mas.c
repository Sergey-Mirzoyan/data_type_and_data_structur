#include "pp_mas.h"

void init(struct queue *q)
{
    q->head = q->tail = 0;
    q->cn = 0;
}

int push(struct queue *q, int x)
{
    int rc;
    
    if (q->cn != QMAX + 1)
    {
        q->mas[q->tail] = x;
        q->tail = (q->tail + 1) % QMAX;
        q->cn++;
        
        rc = 0;
    }
    else
    {
        rc = -1;
    }
    
    return rc;
}

int pop(struct queue *q, int *res)
{
    int rc;
    
    if (q->cn == 0)
    {
        //printf("Очередь пуста\n");
        
        rc = -1;
    }
    else
    {
        *res = q->mas[q->head];
        q->head = (q->head + 1) % QMAX;
        q->cn--;
        
        rc = 0;
    }
    
    return rc;
}

void print(struct queue *q)
{
    if (q->cn == 0)
    {
        //printf("Очередь пуста\n");
    }
    else
    {
        int j = q->head;
        
        for (int i = 0; i < q->cn; i++)
        {
            printf("%d ", q->mas[j]);
            j = (j + 1) % QMAX;
        }
        printf("\n");
    }
}
