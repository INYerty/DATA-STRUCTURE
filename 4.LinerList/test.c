#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct {
    int data[MAX_SIZE];
    int length;
} LinerList;

void initList(LinerList *list)
{
    list->length=0;             //初始化链表长度为零
}


int insert(LinerList *list,int index,int value)
{
    if(index<0||index>list->length||list->length>=MAX_SIZE)
    {
        return -1;
    }

    for(int i=list->length;i>index;i--)
    {
        list->data [i]=list->data [i-1];
    }
    list->data[index]=value;
    list->length++;
    return 0;

}

int main () 
{
    LinerList list;
}
