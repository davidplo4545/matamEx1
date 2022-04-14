#include "RLEList.h"
#include <stdlib.h>
#include <stdio.h>
#define FIRST_ASCII 0
#define LAST_ASCII 255

typedef struct RLEList_t{
    int reps;
    char value;
    struct RLEList_t* next;
    struct RLEList_t* first;
}*RLEList;

void printNode(RLEList node)
{
    printf("%c %d\n",node->value, node->reps);
}

RLEList RLEListCreate()
{
    RLEList list = malloc(sizeof(list));
    if (list==NULL)
        return NULL;
    list->next=NULL;
    list->first=list;   
    list->reps = 0;
    printNode(list);
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
            return RLE_LIST_NULL_ARGUMENT;
    RLEList first = list->first;
    if(first->value == value)
    {
        first->reps +=1;
        printNode(first);
    }
    else
    {
        RLEList newHead = malloc(sizeof(newHead));

        if (!newHead)
            return RLE_LIST_OUT_OF_MEMORY;
        newHead->value = value;
        newHead->reps =1;
        list->next=newHead;
        newHead->next = NULL;
        newHead->first = list->first;
        printNode(newHead);
    }
    return RLE_LIST_SUCCESS;
}

int RLEListSize(RLEList list)
{
    if(!list)
        return -1;
    RLEList first = list -> first;
    int size = 0;
    while(first)
    {
        size+=list->reps;
        first = first->next;
    }    
    return size;
}

RLEListResult RLEListRemove(RLEList list, int index)
{   

    if (!list)
        return RLE_LIST_NULL_ARGUMENT;
    if(index<0)
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;    
    RLEList current = list->first;
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
        *result = RLE_LIST_NULL_ARGUMENT;
        
    if(index<0)
        *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;    
    if(*result != RLE_LIST_SUCCESS) return 0;

    RLEList current = list->first->next;
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
    RLEList first = list->first->next;
    int curr=0;
    while(first)
    {
        str[curr] = first->value;
        str[curr+1] = first->reps - '0';
        str[curr+2] = '\n';
        curr+=3;
        first = first->next;
    }
    *result = RLE_LIST_SUCCESS;
    str[curr] = '\0';
    return str;
}

RLEListResult RLEListMap(RLEList list, MapFunction map_function)
{
    if (!list)
        return RLE_LIST_NULL_ARGUMENT;
    RLEList current = list->first->next;

    while(current)
        {
            current->value = map_function(current->value);
            current = current->next;
        }    
    return RLE_LIST_SUCCESS;    
}
// RLEList a =RLEListCreate()
