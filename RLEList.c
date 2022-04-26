#include "RLEList.h"
#include <stdlib.h>
#include <string.h>
#define FIRST_ASCII 0
#define LAST_ASCII 255
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
    list->value='\0';
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
//                printf("Next Reps:%d Index:%d\n",current->next->reps, index);
//                printf("Current Next Value:%c\n",current->next->value);
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

    if(!result) {
        if (*result != RLE_LIST_SUCCESS)
        {
            return 0;
        }
    }
    return 0;
}

//static void putDigits(char *str, int n, int digit)
//{
//    int temp = n;
//    for(int i=0; i<digit; i++)
//    {
//        for(int j = 1; j<(digit-i); j++)
//        {
//            temp = temp/10;
//        }
//        str[i]=temp%10 +'0';
//
//        temp = n;
//    }
//}
//
//static int numDigits (int n)
//{
//    int count=0;
//    while(n)
//    {
//        n/=10;
//        count++;
//    }
//    return count;
//}

char* RLEListExportToString(RLEList list, RLEListResult* result)
{   
    if(!list)
    {
        *result = RLE_LIST_NULL_ARGUMENT;
        return NULL;
    }
    int size = RLEListSize(list);
    char* str = malloc(sizeof(char)*(size*3 + 1));
       
    if(!str)
    {
        *result = RLE_LIST_NULL_ARGUMENT;
        return NULL;
    }
    int curr=0;
    while(list->next)
    {
        str[curr++] = list->next->value;
        sprintf(str+curr,"%d",list->next->reps);
        curr = strlen(str);
        str[curr++] ='\n';
        list = list->next;
    }

    *result = RLE_LIST_SUCCESS;
    str[curr] = '\0';
    return str;
}


RLEListResult RLEListMap(RLEList list, MapFunction map_function)
{
    if (!list || !map_function)
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

