#include <stdio.h>
#include <stdlib.h>
#include "circular_buffer.h"
int main() {
    int n;
    struct circular_buffer_t *buff;
    int action=1;
    printf("podaj rozmiar buffora: ");
    int err=scanf("%d",&n);
    while(getchar()!='\n');
    if(err!=1)
    {
        printf("Incorrect input");
        return 1;
    }
    if(n<=0)
    {
        printf("Incorrect input data");
        return 2;
    }
    err=circular_buffer_create_struct(&buff,n);
    if(err==1||err==2)
    {
        printf("Failed to allocate memory");
        return 8;
    }
    while(1)
    {
        printf("Co chcesz zrobic?");
        err=scanf("%d",&action);
        if(err!=1)
        {
            free(buff->ptr);
            free(buff);
            printf("Incorrect input");
            return 1;
        }
        if(action==0)
            break;
        else if(action==1)
        {
            int liczba;
            printf("podaj liczbe:");
            err=scanf("%d",&liczba);
            if(err!=1)
            {
                printf("incorrect input");
                free(buff->ptr);
                free(buff);
                return 1;
            }
            circular_buffer_push_back(buff,liczba);
        }
        else if(action==2)
        {
            int liczba=circular_buffer_pop_back(buff,&err);
            if(err==2||err==1)
                printf("Buffer is empty\n");
            else
                printf("%d\n",liczba);

        }
        else if(action==3)
        {
            int liczba=circular_buffer_pop_front(buff,&err);
            if(err==2)
                printf("Buffer is empty\n");
            else if(err==1)
                printf("1\n");
            else
                printf("%d\n",liczba);
        }
        else if(action==4)
        {
            circular_buffer_display(buff);
            if(circular_buffer_empty(buff)==1)
                printf("buffer is empty");
            printf("\n");
        }
        else if(action==5)
            printf("%d\n",circular_buffer_empty(buff));
        else if(action==6)
            printf("%d\n",circular_buffer_full(buff));
        else
            printf("Incorrect input data\n");
    }
    free(buff->ptr);
    free(buff);
    return 0;
}
