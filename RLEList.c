

#include "RLEList.h"
#include <stdlib.h>
#include <stdio.h>
#define FIRST_ASCII 0
#define LAST_ASCII 255


RLEList RLEListCreate()
{
    RLEList list = malloc(sizeof(*list));
    if (list==NULL)
    {
        return NULL;
    }
    list->next=NULL;
    list->reps = 0;
    return list;   
}

void RLEListDestroy(RLEList list)
{
    RLEList next;
    while (list)
    {
        next = list->next;
        free(list);
        list = next;
    }
}


RLEListResult RLEListAppend(RLEList list,char value)
{
    if (!list || value>LAST_ASCII || value<FIRST_ASCII)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }

    while (list->next != NULL)
    {
        list = list->next;
    }

    if((list->value) == value)
    {
        list->reps +=1;
    }
    else
    {
        RLEList newHead = malloc(sizeof(*newHead));

        if (!newHead)
        {
            return RLE_LIST_OUT_OF_MEMORY;
        }

        list->next=newHead;  
        newHead->next = NULL;   

        newHead->value = value;
        newHead->reps = 1;
    }
    return RLE_LIST_SUCCESS;
}


int RLEListSize(RLEList list)
{
    if(!list)
    {
        return -1;
    }
    int size = 0;
    while(list)
    {
        size+=list->reps;
        list = list->next;
    }    
    return size;
}

RLEListResult RLEListRemove(RLEList list, int index)
{   

    if (!list)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    if(index<0)
    {
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    RLEList current = list;
    while(current->next)
        {           
        if(index<=current->reps)
            {
                RLEList toRemove=current->next;
                if(toRemove->reps == 1)
                {
                    current->next = current ->next->next;
                    free(toRemove);
                    return RLE_LIST_SUCCESS;
                }
                else
                    toRemove->reps -=1;
            }
        index--;
        current=current->next;
        
    }
    return RLE_LIST_SUCCESS;
}

char RLEListGet(RLEList list, int index, RLEListResult *result)
{
    *result = RLE_LIST_SUCCESS;
    if (!list)
    {
        *result = RLE_LIST_NULL_ARGUMENT;
    }
        
    if(index<0)
    {
        *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    if(*result != RLE_LIST_SUCCESS) {
        return 0;
    }

    RLEList current = list->next;
    char foundChar;
    while(current)
    {           
        if(index<=current->reps)
        {
            foundChar = current->value;
            return foundChar;
        }
        index-= current->reps;
        current=current->next;
    }
    return 0;
}

static void putDigits(char *str, int n, int digit)
{
    int temp = n;
    for(int i=0; i<digit; i++)
    {
        for(int j = 1; j<(digit-i); j++)
        {
            temp = temp/10;
        }
        str[i]=temp%10 +'0';

        temp = n;
    }
}

static int numDigits (int n)
{
    int count=0;
    while(n)
    {
        n/=10;
        count++;
    }
    return count;
}

char* RLEListExportToString(RLEList list, RLEListResult* result)
{   
    if(!list)
    {
        *result = RLE_LIST_NULL_ARGUMENT;
        return NULL;
    }
    int size = RLEListSize(list);
    char* str = malloc(sizeof(int)*(size*3));
       
    if(!str)
    {
        *result = RLE_LIST_NULL_ARGUMENT;
        return NULL;
    }
    int curr=0;
    while(list->next)
    {
        int repsLen = numDigits(list->next->reps);
        
        str[curr] = list->next->value;
        putDigits(str+curr+1, list->next->reps, repsLen);

        str[curr+1+repsLen] = '\n';
        curr+=(2+repsLen);
        list = list->next;
    }
    *result = RLE_LIST_SUCCESS;
    str[curr] = '\0';
    return str;
}


RLEListResult RLEListMap(RLEList list, MapFunction map_function)
{
    if (!list)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEList current = list->next;

    while(current)
    {
        current->value = map_function(current->value);
        current = current->next;
    }
    return RLE_LIST_SUCCESS;    
}

