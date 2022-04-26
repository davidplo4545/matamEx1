#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "AsciiArtTool.h"



char invertedMapping(char c)
{
    if(c == ' ') return '@';
    else if(c == '@') return ' ';
    return c;

}
void printInvertedArt(char *inputPath, char *outputPath)
{
    FILE *inStream = fopen(inputPath, "r");
    if(!inStream) return;
    RLEList list = asciiArtRead(inStream);
    fclose(inStream);

    RLEListResult status = RLEListMap(list, invertedMapping);
    if(status != RLE_LIST_SUCCESS) return;

    FILE *outStream = fopen(outputPath, "w");
    if(!outStream) return;
    asciiArtPrint(list,outStream);
    fclose(outStream);
    RLEListDestroy(list);
}

void printEncodedArt(char *inputPath, char *outputPath)
{
    FILE *inStream = fopen(inputPath, "r");
    if(!inStream) return;
    RLEList list = asciiArtRead(inStream);
    fclose(inStream);
    FILE *outStream = fopen(outputPath, "w");
    if(!outStream) return;
    asciiArtPrintEncoded(list,outStream);
    fclose(outStream);
    RLEListDestroy(list);
}
int main(int argc, char** argv) {

    if(argc != 4) return 0;
    if(strlen(argv[1]) !=2)  return 0;
    bool isInverted = argv[1][1] == 'i';
    if(isInverted)
        printInvertedArt(argv[2], argv[3]);
    else
        printEncodedArt(argv[2], argv[3]);
    return 0;
}

