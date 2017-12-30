#include "pp_list.h"

void init(struct queue *q)
{
    q->frnt = 0;
    q->rear = 0;
    q->head_ad = 0;
    q->head_fr = 0;
    q->tail_ad = 0;
    q->tail_fr = 0;
}

void push(struct queue *q, int x)
{
    struct list *tmp = malloc(sizeof(struct list));
    if (tmp)
    {
        tmp->field = x;
        tmp->ptr = 0;

        if (q->rear == 0 || q->frnt == 0)
        {
            q->rear = tmp;
            q->frnt = q->rear;
        }
        else
        {
            q->rear->ptr = tmp;
            q->rear = tmp;
        }

        add_addr(q, &tmp->field, 1);
        del_addr(q, 2);
    }
    else
    {
        printf("Ошибка выделения памяти\n");
        exit(-1);
    }
}

void print(struct queue *q)
{
    struct list *h;

    if(q->frnt == 0)
    {
        printf("Очередь пуста\n");

        return;
    }

    for (h = q->frnt; h != NULL; h = h->ptr)
        printf("%d ", h->field);

    return;
}

int pop(struct queue *q, int *res)
{
    struct list *tmp;

    if (q->frnt == 0)
    {
        printf("Очередь пуста\n");

        return -1;
    }

    *res = q->frnt->field;
    tmp = q->frnt;
    q->frnt = q->frnt->ptr;

    add_addr(q, &tmp->field, 2);
    del_addr(q, 1);

    free(tmp);

    return 0;
}

int len_queue(struct queue *q)
{
    int cn = 0;

    struct list *cur;

    if(q->frnt == 0)
        return cn;

    for (cur = q->frnt; cur != NULL; cur = cur->ptr)
        cn++;

    return cn;
}

void add_addr(struct queue *q, void *x, int flag)
{
    if (flag == 1)
    {
        struct address *tmp = malloc(sizeof(struct address));
        if (tmp)
        {
            tmp->ad = x;
            tmp->next = 0;

            if (q->head_ad == 0 || q->tail_ad == 0)
            {
                q->tail_ad = tmp;
                q->head_ad = q->tail_ad;
            }
            else
            {
                q->tail_ad->next = tmp;
                q->tail_ad = tmp;
            }
        }
        else
        {
            printf("Ошибка выделения памяти\n");
            exit(-1);
        }
    }
    else if (flag == 2)
    {
        struct address *tmp = malloc(sizeof(struct address));
        if (tmp)
        {
            tmp->ad = x;
            tmp->next = 0;

            if (q->head_fr == 0 || q->tail_fr == 0)
            {
                q->tail_fr = tmp;
                q->head_fr = q->tail_fr;
            }
            else
            {
                q->tail_fr->next = tmp;
                q->tail_fr = tmp;
            }
        }
        else
        {
            printf("Ошибка выделения памяти\n");
            exit(-1);
        }
    }
}

int del_addr(struct queue *q, int flag)
{
    if (flag == 1)
    {
        struct address *tmp;

        if (q->head_ad == 0)
            return -1;

        tmp = q->head_ad;
        q->head_ad = q->head_ad->next;

        free(tmp);

        return 0;
    }
    else if (flag == 2)
    {
        struct address *tmp;

        if (q->head_fr == 0)
            return -1;

        tmp = q->head_fr;
        q->head_fr = q->head_fr->next;

        free(tmp);

        return 0;
    }

    return 0;
}

void print_addr(struct queue *q, int flag)
{
    if (flag == 1)
    {
        struct address *cur;

        if(q->head_ad == 0)
        {
            printf("Выделенных адресов нет\n");

            return;
        }

        int i = 1;
        for (cur = q->head_ad; cur != NULL; cur = cur->next)
            printf("%d. %p\n", i++, cur->ad);
    }
    else if (flag == 2)
    {
        struct address *cur;

        if(q->head_fr == 0)
        {
            printf("Освобожденных адресов нет\n");

            return;
        }

        int i = 1;
        for (cur = q->head_fr; cur != NULL; cur = cur->next)
            printf("%d. %p\n", i++, cur->ad);
    }

    return;
}
