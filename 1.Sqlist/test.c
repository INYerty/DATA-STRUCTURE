#include <stdio.h>
#define Maxsize 10

typedef struct
{
    int data[Maxsize];
    int length;
}Sqlist;

void initlist(Sqlist *L){


    L->length=0;
}

int main()
{
    Sqlist L;
    initlist(&L);
    for(int i=0;i<Maxsize;i++)
    {
        printf("data[%d]=%d\n",i,L.data[i]);
    }

    return 0;
}



