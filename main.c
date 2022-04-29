#include <stdio.h>
#include <string.h>
#include "AsciiArtTool.h"

#define INVERTED_FLAG 'i'
#define ENCODED_FLAG 'e'
#define REQUIRED_ARGS_COUNT 4
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

// Reads from an ascii art stream and
// outputs the "inverted" art into a new file
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

// Reads from an ascii art stream and
// outputs the "encoded" art form into a new file
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

    if(argc != REQUIRED_ARGS_COUNT)
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
    if(currFlag[1] == INVERTED_FLAG)
        printInvertedArt(inStream, argv[3]);
    else if(currFlag[1] == ENCODED_FLAG)
        printEncodedArt(inStream, argv[3]);
    return 0;
}

