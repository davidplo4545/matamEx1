#include "AsciiArtTool.h"
#include "stdlib.h"
#include <stdio.h>

#define CHUNK_SIZE 256
RLEList asciiArtRead(FILE *in_stream)
{
    if(!in_stream) return NULL;
    RLEList list = RLEListCreate();
    if(!list) return NULL;
    char buffer[CHUNK_SIZE]={0};
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
    char buffer[CHUNK_SIZE] ={0};
    char curr;
    int size = RLEListSize(list);
    int bufferIndex = 0;
    for(int i=0;i<size;i++, bufferIndex++)
    {
        RLEListResult status = RLE_LIST_SUCCESS;
        curr = RLEListGet(list,i,&status);
        if(status != RLE_LIST_SUCCESS) {
            return status;
        }
        if(bufferIndex == CHUNK_SIZE-1)
        {
            fputs(buffer, out_stream);
            bufferIndex=0;
        }
        buffer[bufferIndex]= curr;
    }
    buffer[bufferIndex] = '\0';
    fputs(buffer, out_stream);
    return RLE_LIST_SUCCESS;
}

RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream)
{
    if(!list || !out_stream) {
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEListResult status=RLE_LIST_SUCCESS;
    char buffer[CHUNK_SIZE]={0};

    char* str = RLEListExportToString(list,&status);
    if(status != RLE_LIST_SUCCESS) {
        return status;
    }
    char *tempStr = str;
    int i=0;
    while(*tempStr)
    {
        if(i == CHUNK_SIZE - 1)
        {
            fputs(buffer, out_stream);
            i=0;
        }
        buffer[i] = *tempStr;
        i++;
        tempStr++;
    }
    // There is still data left in the buffer
    buffer[i]='\0';
    fputs(buffer, out_stream);
    free(str);
    return RLE_LIST_SUCCESS;
}