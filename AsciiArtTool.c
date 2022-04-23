#include "AsciiArtTool.h"
#include "RLEList.h"

#include <stdio.h>

#define CHUNK_SIZE 256
RLEList asciiArtRead(FILE *in_stream)
{
    if(!in_stream) return NULL;
    RLEList list = RLEListCreate();
    if(!list) return NULL;
    char buffer[CHUNK_SIZE];
    while (fgets(buffer, CHUNK_SIZE, in_stream) != NULL) {
        int curr=0;
        while(buffer[curr])
        {
            RLEListAppend(list, buffer[curr]);
            curr++;
        }
    }
    return list;
}


RLEListResult asciiArtPrint(RLEList list,FILE *out_stream)
{
    if(!list || !out_stream){
        return RLE_LIST_NULL_ARGUMENT;
    }
    char buffer[CHUNK_SIZE];
    int curr=0, tempReps;
    while(list)
    {
        tempReps = list->reps;
        while(tempReps)
        {
            buffer[curr]=list->value;
            curr++;
            if(curr == CHUNK_SIZE)
            {
                fputs(buffer, out_stream);
                curr=0;
            }
            tempReps--;
        }
        list=list->next;
    }

    buffer[curr] = '\0';
    if(curr>0)
    {
        fputs(buffer, out_stream);
    }
    return RLE_LIST_SUCCESS;
}

RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream)
{
    if(!list || !out_stream) {
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEListResult status=RLE_LIST_SUCCESS;
    char buffer[CHUNK_SIZE];

    char* result = RLEListExportToString(list,&status);
    int i=0;
    while(*result)
    {
        buffer[i] = *result;
        i++;
        if(i == CHUNK_SIZE)
        {
            fputs(buffer, out_stream);
            i=0;
        }
        result++;
    }
    // There is still left in the buffer
    buffer[i]='\0';
    if(i>0) {
        fputs(buffer, out_stream);
    }
    return RLE_LIST_SUCCESS;
}