#include <stdio.h>
#include <string.h>
#include "AsciiArtTool.h"

#define INVERTED_FLAG "-i"
#define ENCODED_FLAG "-e"

#define SPACE ' '
#define INVERT_SIGN '@'

char invertedMapping(char c)
{
    if(c == SPACE)
    {
        return INVERT_SIGN;
    }
    else if(c == INVERT_SIGN) {
        return SPACE;
    }
    return c;
}
void printInvertedArt(FILE *inStream, char *outputPath)
{
    if(!inStream) {
        return;
    }
    RLEList list = asciiArtRead(inStream);
    fclose(inStream);

    RLEListResult status = RLEListMap(list, invertedMapping);
    if(status != RLE_LIST_SUCCESS)
    {
        return;
    }

    FILE *outStream = fopen(outputPath, "w");
    if(!outStream)
    {
        return;
    }
    asciiArtPrint(list,outStream);
    fclose(outStream);
    RLEListDestroy(list);
}

void printEncodedArt(FILE *inStream, char *outputPath)
{
    if(!inStream)
    {
        return;
    }
    RLEList list = asciiArtRead(inStream);
    fclose(inStream);
    FILE *outStream = fopen(outputPath, "w");
    if(!outStream)
    {
        return;
    }
    asciiArtPrintEncoded(list,outStream);
    fclose(outStream);
    RLEListDestroy(list);
}
int main(int argc, char** argv) {

    if(argc != 4)
    {
        return 0;
    }
    if(strlen(argv[1]) !=2)
    {
        return 0;
    }
    char* currFlag = argv[1];

    FILE *inStream = fopen(argv[2], "r");
    if(!inStream){
        return 0;
    }
    if(currFlag[1] == 'i')
        printInvertedArt(inStream, argv[3]);
    else if(currFlag[1] == 'e')
        printEncodedArt(inStream, argv[3]);
    return 0;
}

