//
// Created by PC on 12.04.2021.
//
#include <stdio.h>
#include <stdlib.h>
#include "circular_buffer.h"
int circular_buffer_create(struct circular_buffer_t *a, int N)
{
    if(a==NULL||N<=0)
        return 1;
    a->ptr=malloc(sizeof(int)*N);
    if(a->ptr==NULL)
        return 2;
    a->begin=0;
    a->end=0;
    a->capacity=N;
    a->full=0;
    return 0;
}
int circular_buffer_create_struct(struct circular_buffer_t **cb, int N)
{
    if(cb==NULL||N<=0)
        return 1;
    *cb=malloc(sizeof(struct circular_buffer_t));
    if(cb==NULL)
        return 2;
    if(circular_buffer_create(*cb,N))
    {
        free(*cb);
        return 2;
    }
    return 0;
}

void circular_buffer_destroy(struct circular_buffer_t *a)
{
    if(a!=NULL&&a->ptr!=NULL)
    {
        free(a->ptr);
    }
}
void circular_buffer_destroy_struct(struct circular_buffer_t **a)
{
    if(a!=NULL&&(*a)->ptr!=NULL)
    {
        circular_buffer_destroy(*a);
        free(*a);
    }
}

int circular_buffer_push_back(struct circular_buffer_t *cb, int value)
{
    if(cb==NULL||cb->ptr==NULL||cb->end<0||cb->capacity<=0||cb->end>cb->capacity||cb->begin<0||cb->begin>cb->capacity)
        return 1;
    int *ptr=cb->ptr;
    *(ptr+cb->end)=value;
    if(cb->full==0)
        cb->end++;
    else
    {
        cb->end++;
        cb->begin++;
    }
    if(cb->end==cb->capacity)
        cb->end=0;
    if(cb->begin==cb->capacity)
        cb->begin=0;
    if(cb->end==cb->begin)
        cb->full=1;
    return 0;
}
int circular_buffer_pop_front(struct circular_buffer_t *a, int *err_code)
{
    if(err_code!=NULL)
        *err_code=0;
    if(a==NULL||a->ptr==NULL||a->end<0||a->capacity<=0||a->end>a->capacity||a->begin<0||a->begin>a->capacity)
    {
        if(err_code!=NULL)
            *err_code=1;
        return 1;
    }
    int *ptr=a->ptr;
    if(circular_buffer_empty(a)==1)
    {
        if(err_code!=NULL)
            *err_code=2;
        return *(ptr+a->begin);
    }
    a->full=0;
    a->begin++;
    if(a->begin>=a->capacity)
    {
        a->begin=0;
        return *(ptr+a->capacity-1);
    }
    return *(ptr+a->begin-1);
}
int circular_buffer_pop_back(struct circular_buffer_t *a, int *err_code)
{
    if(err_code!=NULL)
        *err_code=0;
    if(a==NULL||a->ptr==NULL||a->end<0||a->capacity<=0||a->end>a->capacity||a->begin<0||a->begin>a->capacity)
    {
        if(err_code!=NULL)
            *err_code=1;
        return 1;
    }
    int *ptr=a->ptr;
    if(circular_buffer_empty(a)==1)
    {
        if(err_code!=NULL)
            *err_code=2;
        return *(ptr+a->end);
    }
    a->end--;
    a->full=0;
    if(a->end<=-1)
        a->end=a->capacity-1;
    return *(ptr+a->end);
}

int circular_buffer_empty(const struct circular_buffer_t *a)
{
    if(a==NULL||a->ptr==NULL||a->end<0||a->capacity<=0||a->end>a->capacity||a->begin<0||a->begin>a->capacity)
        return -1;
    if(a->full==0&&a->end==a->begin)
        return 1;
    return 0;
}
int circular_buffer_full(const struct circular_buffer_t *a)
{
    if(a==NULL||a->ptr==NULL||a->end<0||a->capacity<=0||a->end>a->capacity||a->begin<0||a->begin>a->capacity)
        return -1;
    if(a->full==1&&a->end==a->begin)
        return 1;
    return 0;
}

void circular_buffer_display(const struct circular_buffer_t *a)
{
    if(circular_buffer_empty(a)==1||circular_buffer_empty(a)==-1||a==NULL||a->ptr==NULL||a->end<0||a->capacity<=0||a->end>a->capacity||a->begin<0||a->begin>a->capacity)
        return;
    int *ptr=a->ptr;
    if(a->full==1)
    {
        for (int i = a->begin; i < a->capacity; ++i) {
            printf("%d ", *(ptr + i));
        }
        for (int i = 0; i < a->end; ++i) {
            printf("%d ", *(ptr + i));
        }
    }
    else
    {
        if(a->begin<=a->end) {
            for (int i = a->begin; i < a->end; ++i) {
                printf("%d ", *(ptr + i));
            }
        }
        else
        {
            for (int i = a->begin; i <a->capacity ; ++i)
            {
                printf("%d ",*(ptr+i));
            }
            for (int i = 0; i < a->end; ++i)
            {
                printf("%d ",*(ptr+i));
            }
        }
    }

}