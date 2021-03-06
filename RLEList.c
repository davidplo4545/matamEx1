#include "RLEList.h"
#include <stdlib.h>
#include <string.h>

#define FIRST_ASCII 0
#define LAST_ASCII 255

#define MAX_SIZE_MULT 3
#define END_STRING '\0'
#define NEW_LINE '\n'

struct RLEList_t
{
    int reps;
    char value;
    struct RLEList_t* next;
};


RLEList RLEListCreate()
{
    RLEList list = malloc(sizeof(*list));
    if (list==NULL)
    {
        return NULL;
    }
    list->next=NULL;
    list->value=END_STRING;
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

static RLEListResult createNewHead(RLEList list, char value)
{
    RLEList newHead = malloc(sizeof(*newHead));

    if (!newHead) {
        return RLE_LIST_OUT_OF_MEMORY;
    }

    list->next = newHead;
    newHead->next = NULL;

    newHead->value = value;
    newHead->reps = 1;
    return RLE_LIST_SUCCESS;
}
RLEListResult RLEListAppend(RLEList list,char value) {
    if (!list || value > LAST_ASCII || value < FIRST_ASCII) {
        return RLE_LIST_NULL_ARGUMENT;
    }

    while (list->next != NULL) {
        list = list->next;
    }
    if (list->value)
    {
        if(list->value == value)
        {
            list->reps += 1;
            return RLE_LIST_SUCCESS;
        }
    }
    return createNewHead(list, value);
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
    if(index<0 || index > RLEListSize(list) -1)
    {
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    RLEList current = list;
    while(current->next)
    {
        if(index < current->next->reps)
        {
            RLEList toRemove=current->next;
            RLEList toRemoveExtra = NULL;

            if(toRemove->reps == 1)
            {
                if(current->next->next != NULL )
                {
                    if(current->next->next->value ==  current->value)
                    {
                        current->reps += current->next->next->reps;
                         toRemoveExtra = current->next->next;
                    }
                }
                if(toRemoveExtra != NULL)
                {
                    current->next = current->next->next->next;
                    free(toRemoveExtra);
                }
                else
                {
                    current->next = current->next->next;
                }
                free(toRemove);

                return RLE_LIST_SUCCESS;
            }
            else
            {
                toRemove->reps -=1;
                return RLE_LIST_SUCCESS;
            }
        }
        index-=current->next->reps;
        current=current->next;
    }
    return RLE_LIST_SUCCESS;
}

static void setResult(RLEListResult* status, RLEListResult result)
{
    if(status)
    {
        *status = result;
    }
}

char RLEListGet(RLEList list, int index, RLEListResult *result)
{
    if (!list)
    {
        setResult(result,RLE_LIST_NULL_ARGUMENT);
        return 0;
    }
    if(index<0 || index > RLEListSize(list) -1)
    {
        setResult(result,RLE_LIST_INDEX_OUT_OF_BOUNDS);
        return 0;
    }

    RLEList current = list->next;
    char foundChar;
    while(current)
    {           
        if(index<current->reps)
        {
            foundChar = current->value;
            setResult(result,RLE_LIST_SUCCESS);
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
        setResult(result,RLE_LIST_NULL_ARGUMENT);
        return NULL;
    }
    int size = RLEListSize(list);
    char* str = malloc(sizeof(char)*(size*MAX_SIZE_MULT + 1));
    if(!str)
    {
        setResult(result,RLE_LIST_OUT_OF_MEMORY);
        return NULL;
    }
    int curr=0;
    while(list->next)
    {
        str[curr++] = list->next->value;
        sprintf(str+curr,"%d",list->next->reps);
        curr = strlen(str);
        str[curr++] =NEW_LINE;
        list = list->next;
    }
    setResult(result,RLE_LIST_SUCCESS);
    str[curr] = END_STRING;
    return str;
}


RLEListResult RLEListMap(RLEList list, MapFunction map_function)
{
    if (!list || !map_function)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEList current = list;
    bool isDummy = true;
    while(current->next)
    {
        bool wasRemoved = false;
        current->next->value = map_function(current->next->value);
        if(!isDummy)
        {
            if(current->next->value == current->value)
            {
                current->reps+=current->next->reps;
                RLEList toRemove = current->next;
                current->next = current->next->next;
                free(toRemove);
                wasRemoved = true;
            }
        }
        if(!wasRemoved)
        {
            current = current->next;
        }
        isDummy = false;
    }
    return RLE_LIST_SUCCESS;    
}

